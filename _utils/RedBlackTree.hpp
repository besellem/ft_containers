/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:40:35 by kaye              #+#    #+#             */
/*   Updated: 2021/10/13 15:49:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <iostream>

# include <memory>
# include "utils.hpp"
# include "tree_iterator.hpp"

# define BLACK_NODE 0
# define RED_NODE	1


_BEGIN_NAMESPACE_FT


template <class T>
struct Node
{
	public:
		typedef T              value_type;
		typedef bool           size_type;
	
	public:
		Node(void) :
			val(),
			color(BLACK_NODE),
			parent(nullptr_),
			left(nullptr_),
			right(nullptr_)
		{}

		Node(value_type const& val,
			 size_type color = BLACK_NODE,
			 Node* parent = nullptr_,
			 Node* left = nullptr_,
			 Node* right = nullptr_) :
				val(val),
				color(color),
				parent(parent),
				left(left),
				right(right)
		{}

		Node(Node const& src) :
			 val(src.val),
			 color(src.color),
			 parent(src.parent),
			 left(src.left),
			 right(src.right)
		{}

		~Node() {}

		Node&	operator=(Node const& rhs)
		{
			if (this == &rhs)
				return *this;

			val = rhs.val;
			color = rhs.color;
			parent = rhs.parent;
			left = rhs.left;
			right = rhs.right;
			return *this;
		}

		bool	operator==(Node const& rhs) { return val == rhs.val; }
	
	public:
		value_type	val;
		size_type	color;
		Node		*parent;
		Node		*left;
		Node		*right;
	
};


template <class T,
		  class Compare,
		  class Node = Node<T>,
		  class Allocator = std::allocator<Node> >
class RedBlackTree
{
	
	public:
		typedef T                                           value_type;
		typedef Compare                                     value_compare;
		typedef Allocator                                   allocator_type;
		typedef Node                                        node_type;
		typedef typename allocator_type::reference          reference;
		typedef typename allocator_type::const_reference    const_reference;
		typedef typename allocator_type::pointer            pointer;
		typedef typename allocator_type::const_pointer      const_pointer;
		typedef typename allocator_type::difference_type    difference_type;
		typedef typename allocator_type::size_type          size_type;


	public:
		RedBlackTree(value_compare const& cmp = value_compare()) :
			_cmp(cmp)
		{
			_last = allocator_type().allocate(1);
			allocator_type().construct(_last, node_type());
			_root = _last;
		}

		~RedBlackTree() {}

		pointer		min(pointer s) const
		{
			if (s == nullptr_ || s == _last)
				return _last;
			for ( ; s->left != _last; s = s->left);
			return s;
		}

		pointer		min() const { return min(_root); }

		pointer		max(pointer s) const
		{
			if (s == nullptr_ || s == _last)
				return _last;
			for ( ; s->right != _last; s = s->right);
			return s;
		}

		pointer		max() const { return max(_root); }
		
		size_type	size(pointer s) const
		{
			if (s == _last)
				return 0;
			return size(s->right) + size(s->left) + 1;
		}
		
		size_type	size()                        const { return size(_root); }
		size_type	max_size()                    const { return allocator_type().max_size(); }
		pointer		search(const value_type& key) const { return __search_wrapper(_root, key); }

		pointer		successor(pointer s) const
		{
			if (s->right != _last)
				return min(s->right);
			if (s->parent == nullptr_ || s == max())
				return _last;
			
			pointer	tmp = s->parent;
			while (tmp != _last && s == tmp->right)
			{
				s = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}

		pointer		predecessor(pointer s) const
		{
			if (s->left != _last)
				return max(s->left);
			if (s->parent == nullptr_ || s == min())
				return _last;
			
			pointer	tmp = s->parent;
			while (tmp != _last && s == tmp->left)
			{
				s = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}
		
		bool	insert(const value_type& key)
		{
			pointer	y = nullptr_;
			pointer	x = _root;
		
			pointer	s = allocator_type().allocate(1);
			allocator_type().construct(s, node_type(key, RED_NODE, nullptr_, _last, _last));

			while (x != _last)
			{
				y = x;
				if (_cmp(s->val, x->val))
					x = x->left;
				else if (_cmp(x->val, s->val))
					x = x->right;
				else
				{
					allocator_type().destroy(s);
					allocator_type().deallocate(s, 1);
					return false;
				}
			}

			s->parent = y;
			if (y == nullptr_)
				_root = s;
			else if (_cmp(s->val, y->val))
				y->left = s;
			else
				y->right = s;

			if (s->parent == nullptr_)
			{
				s->color = BLACK_NODE;
				return true;
			}

			if (s->parent->parent == nullptr_)
				return true;

			_fix_insertion(s);
			return true;
		}

		pointer		get_root() const { return _root; }
		pointer		get_last() const { return _last; }

		bool	delete_node(const value_type& key)
		{ return __delete_node_wrapper(_root, key); }

		void		destroy()
		{
			_destroy(_root);
			_root = _last;
		}

		void		destroy_last()
		{
			allocator_type().destroy(_last);
			allocator_type().deallocate(_last, 1);
		}

		pointer		lower_bound(const value_type& v) const
		{
			pointer	p = min();

			for ( ; p != _last; p = successor(p))
			{
				if (!_cmp(p->val, v))
					break ;
			}
			return p;
		}

		pointer		upper_bound(const value_type& v) const
		{
			pointer	p = min();

			for ( ; p != _last; p = successor(p))
			{
				if (_cmp(v, p->val))
					break ;
			}
			return p;
		}

		void		swap(RedBlackTree& ref)
		{
			pointer			tmp_root = _root;
			pointer			tmp_last = _last;

			_root = ref.get_root();
			_last = ref.get_last();
			ref._root = tmp_root;
			ref._last = tmp_last;
		}


	private:
		pointer		__search_wrapper(pointer node, const value_type& key) const
		{
			if (node == _last)
				return node;
			else if (_cmp(key, node->val))
				return __search_wrapper(node->left, key);
			else if (_cmp(node->val, key))
				return __search_wrapper(node->right, key);
			else
				return node;
		}

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

		bool	__delete_node_wrapper(pointer node, const value_type& key)
		{
			pointer	z = _last;
			pointer	x;
			pointer	y;

			while (node != _last)
			{
				if (_cmp(node->val, key))
					node = node->right;
				else if (_cmp(key, node->val))
					node = node->left;
				else
				{
					z = node;
					node = node->right;
				}
			}

			if (z == _last) // if the key doesn't exist
				return false;

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

			allocator_type().destroy(z);
			allocator_type().deallocate(z, 1);
			
			if (y_original_color == BLACK_NODE)
				_fix_delete(x);
			return true;
		}

		void		_destroy(pointer root)
		{
			if (root == _last)
				return ;
			_destroy(root->left);
			_destroy(root->right);
			allocator_type().destroy(root);
			allocator_type().deallocate(root, 1);
		}


	private:
		value_compare	_cmp;
		pointer			_root;
		pointer			_last;
	
}; /* class RedBlackTree */


_END_NAMESPACE_FT

#endif /* define RED_BLACK_TREE_HPP */
