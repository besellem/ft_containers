/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:40:35 by kaye              #+#    #+#             */
/*   Updated: 2021/10/05 17:16:56 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream> // debug

# include <memory>
# include "utils.hpp"
# include "map_iterator.hpp"

# define BLACK_NODE 0
# define RED_NODE	1


_BEGIN_NAMESPACE_FT


template <class T>
struct Node
{
	public:
		typedef T              value_type;
		typedef size_t         size_type;
	
	public:
		Node(void) :
			val(),
			color(BLACK_NODE),
			parent(nullptr_),
			left(nullptr_),
			right(nullptr_)
		{}

		Node(size_type color = BLACK_NODE,
			Node *parent = nullptr_,
			Node *left = nullptr_,
			Node *right = nullptr_) :
				val(),
				color(color),
				parent(parent),
				left(left),
				right(right)
		{}
		
		Node(value_type val,
			size_type color = BLACK_NODE,
			Node *parent = nullptr_,
			Node *left = nullptr_,
			Node *right = nullptr_) :
				val(val),
				color(color),
				parent(parent),
				left(left),
				right(right)
		{}

		Node(Node const & src) :
			val(src.val),
			color(src.color),
			parent(src.parent),
			left(src.left),
			right(src.right)
		{}

		~Node(void) {}

		Node&	operator=(Node const & rhs)
		{
			if (*this == rhs)
				return *this;

			val = rhs.val;
			color = rhs.color;
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			return *this;
		}

		bool	operator==(Node const & rhs) { return val == rhs.val; }
	
	public:
		value_type	val;
		size_type	color;
		Node		*parent;
		Node		*left;
		Node		*right;
	
};

template <class T,
		  class Compare = ft::less<T>,
		  class Node = Node<T>,
		  class AllocNode = std::allocator<Node> >
class RedBlackTree
{
	
	public:
		typedef T                                           value_type;
		typedef Node                                        node_type;
		typedef AllocNode                                   allocator_type;
		typedef typename allocator_type::reference          reference;
		typedef typename allocator_type::const_reference    const_reference;
		typedef typename allocator_type::pointer            pointer;
		typedef typename allocator_type::const_pointer      const_pointer;
		typedef typename allocator_type::difference_type    difference_type;
		typedef typename allocator_type::size_type          size_type;
		typedef ft::map_iterator<Node>                      iterator;

	public:
		RedBlackTree(allocator_type const & alloc = allocator_type()) : _alloc(alloc)
		{
			_last = _alloc.allocate(1);
			_alloc.construct(_last, node_type(BLACK_NODE, nullptr_, nullptr_, nullptr_));
			_root = _last;
		}

		~RedBlackTree() {}

		pointer		min() { return min(_root); }
		pointer		max() { return max(_root); }

		// search the tree for the key,
		// return the corresponding node
		pointer		search(value_type key)
		{ return __search_wrapper(_root, key); }

		// find the successor of a given node
		pointer		successor(pointer s)
		{
			if (s->right != _last)
				return min(s->right);

			pointer	tmp = s->parent;
			while (tmp != _last && s == tmp->right)
			{
				s = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}

		// find the predecessor of a given node
		pointer		predecessor(pointer s)
		{
			if (s->left != _last)
				return max(s->left);

			pointer	tmp = s->parent;
			while (tmp != _last && s == tmp->left)
			{
				s = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}

		// insert the key to the tree in its appropriate position
		// and fix the tree
		pair<iterator, bool>	insert(value_type const & key)
		{
			pointer	y = nullptr_;
			pointer	x = _root;
			pointer	s = _alloc.allocate(1);
			_alloc.construct(s, node_type(key, RED_NODE, nullptr_, _last, _last)); // new node must be red

			while (x != _last)
			{
				y = x;
				if (s->val.first < x->val.first)
					x = x->left;
				else if (s->val.first > x->val.first)
					x = x->right;
				else
				{
					_alloc.destroy(s);
					_alloc.deallocate(s, 1);
					return make_pair<iterator, bool>(iterator(get_root_node(), y, get_last_node()), false);
				}
			}

			// y is parent of x
			s->parent = y;
			if (y == nullptr_)
				_root = s;
			else if (s->val.first < y->val.first)
				y->left = s;
			else
				y->right = s;

			// if new node is a _root node, simply return
			if (s->parent == nullptr_)
			{
				s->color = BLACK_NODE;
				return make_pair<iterator, bool>(iterator(get_root_node(), y, get_last_node()), true);
			}

			// if the grandparent is null, simply return
			if (s->parent->parent == nullptr_)
				return make_pair<iterator, bool>(iterator(get_root_node(), y, get_last_node()), true);

			// Fix the tree
			_fix_insertion(s);
			return make_pair<iterator, bool>(iterator(get_root_node(), y, get_last_node()), true);
		}

		pointer		get_root_node() { return _root; }
		pointer		get_last_node() { return _last; }

		// delete the node from the tree
		size_type	delete_node(value_type const & key)
		{ return __delete_node_wrapper(_root, key); }

		void		destroy()
		{
			_destroy(_root);

			_alloc.destroy(_last);
			_alloc.deallocate(_last, 1);
		}

		void		print()
		{
			if (_root)
				__print_wrapper(_root, "", true);
		}


	private:
		pointer		min(pointer s)
		{
			for ( ; s->left != _last; s = s->left);
			return s;
		}

		pointer		max(pointer s)
		{
			for ( ; s->right != _last; s = s->right);
			return s;
		}

		pointer		__search_wrapper(pointer node, value_type const & key)
		{
			if (node == _last || key.first == node->val.first)
				return node;
			if (key.first < node->val.first)
				return __search_wrapper(node->left, key);
			return __search_wrapper(node->right, key);
		}

		// rotate left at node x
		void		_left_rotate(pointer s)
		{
			pointer	tmp = s->right;
			
			s->right = tmp->left;
			if (tmp->left != _last)
				tmp->left->parent = s;
			tmp->parent = s->parent;
			if (s->parent == nullptr_)
				_root = tmp;
			else if (s == s->parent->left)
				s->parent->left = tmp;
			else
				s->parent->right = tmp;
			tmp->left = s;
			s->parent = tmp;
		}

		// rotate right at node x
		void		_right_rotate(pointer x)
		{
			pointer	y = x->left;
			
			x->left = y->right;
			if (y->right != _last)
				y->right->parent = x;
			y->parent = x->parent;
			if (x->parent == nullptr_)
				_root = y;
			else if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}

		// fix the red-black tree
		void		_fix_insertion(pointer k)
		{
			pointer	u;
			
			while (k->parent->color == RED_NODE)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left;
					if (u->color == RED_NODE)
					{
						u->color = BLACK_NODE;
						k->parent->color = BLACK_NODE;
						k->parent->parent->color = RED_NODE;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							k = k->parent;
							_right_rotate(k);
						}
						k->parent->color = BLACK_NODE;
						k->parent->parent->color = RED_NODE;
						_left_rotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right;

					if (u->color == RED_NODE)
					{
						u->color = BLACK_NODE;
						k->parent->color = BLACK_NODE;
						k->parent->parent->color = RED_NODE;
						k = k->parent->parent;	
					}
					else
					{
						if (k == k->parent->right)
						{
							k = k->parent;
							_left_rotate(k);
						}
						k->parent->color = BLACK_NODE;
						k->parent->parent->color = RED_NODE;
						_right_rotate(k->parent->parent);
					}
				}
				if (k == _root)
					break ;
			}
			_root->color = BLACK_NODE;
		}

		// fix the rb tree modified by the delete operation
		void		_fix_delete(pointer x)
		{
			pointer	s;
			
			while (x != _root && x->color == BLACK_NODE)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RED_NODE)
					{
						s->color = BLACK_NODE;
						x->parent->color = RED_NODE;
						_left_rotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == BLACK_NODE && s->right->color == BLACK_NODE)
					{
						s->color = RED_NODE;
						x = x->parent;
					}
					else
					{
						if (s->right->color == BLACK_NODE)
						{
							s->left->color = BLACK_NODE;
							s->color = RED_NODE;
							_right_rotate(s);
							s = x->parent->right;
						} 
						s->color = x->parent->color;
						x->parent->color = BLACK_NODE;
						s->right->color = BLACK_NODE;
						_left_rotate(x->parent);
						x = _root;
					}
				}
				else
				{
					s = x->parent->left;
					if (s->color == RED_NODE)
					{
						s->color = BLACK_NODE;
						x->parent->color = RED_NODE;
						_right_rotate(x->parent);
						s = x->parent->left;
					}

					if (s->left->color == BLACK_NODE && s->right->color == BLACK_NODE)
					{
						s->color = RED_NODE;
						x = x->parent;
					}
					else
					{
						if (s->left->color == BLACK_NODE)
						{
							s->right->color = BLACK_NODE;
							s->color = RED_NODE;
							_left_rotate(s);
							s = x->parent->left;
						} 
						s->color = x->parent->color;
						x->parent->color = BLACK_NODE;
						s->left->color = BLACK_NODE;
						_right_rotate(x->parent);
						x = _root;
					}
				} 
			}
			x->color = BLACK_NODE;
		}

		void		_rb_transplant(pointer u, pointer v)
		{
			if (u->parent == nullptr_)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		size_type	__delete_node_wrapper(pointer node, value_type const & key)
		{
			// find the node containing key
			pointer	z = _last;
			pointer	x;
			pointer	y;

			while (node != _last)
			{
				if (node->val.first == key.first)
					z = node;
				
				if (node->val.first <= key.first)
					node = node->right;
				else
					node = node->left;
			}

			if (z == _last)
			{
				std::cout << "Couldn't find key in the tree" << std::endl;
				return false;
			} 

			y = z;
			int	y_original_color = y->color;
			if (z->left == _last)
			{
				x = z->right;
				_rb_transplant(z, z->right);
			}
			else if (z->right == _last)
			{
				x = z->left;
				_rb_transplant(z, z->left);
			}
			else
			{
				y = min(z->right);
				y_original_color = y->color;
				x = y->right;
				
				if (y->parent == z)
					x->parent = y;
				else
				{
					_rb_transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				_rb_transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}

			// delete z;
			_alloc.destroy(z);
			_alloc.deallocate(z, 1);

			if (y_original_color == BLACK_NODE)
				_fix_delete(x);
			return true;
		}

		void		__print_wrapper(pointer root, std::string indent, bool last)
		{
			// print the tree structure on the screen
			if (root != _last)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "     ";
				}
				else
				{
					std::cout << "L----";
					indent += "|    ";
				}
				
				std::string	color = root->color ? "RED" : "BLACK";
				std::cout << root->val.first << "(" << color << ")" << std::endl;
				__print_wrapper(root->left, indent, false);
				__print_wrapper(root->right, indent, true);
			}
			// std::cout << root->left->val << std::endl;
		}

		void		_destroy(pointer root)
		{
			if (root == _last)
				return ;

			_destroy(root->left);
			_destroy(root->right);
			_alloc.destroy(root);
			_alloc.deallocate(root, 1);
		}


	private:
		allocator_type	_alloc;
		pointer			_root;
		pointer			_last;
	
}; /* RedBlackTree */


_END_NAMESPACE_FT

#endif /* define RED_BLACK_TREE_HPP */