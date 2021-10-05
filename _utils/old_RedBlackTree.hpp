/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_RedBlackTree.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 10:29:20 by besellem          #+#    #+#             */
/*   Updated: 2021/10/05 17:09:01 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OLD_RED_BLACK_TREE_HPP
# define OLD_RED_BLACK_TREE_HPP

# include <iostream>

# include "utils.hpp"

# define RBT_BLACK 0
# define RBT_RED   1


_BEGIN_NAMESPACE_FT


template <class T,
		  class Compare = ft::less<T>,
		  class Allocator = std::allocator<T> >
class RedBlackTree
{
	
	public:
		typedef T              value_type;
		typedef T&             reference;
		typedef const T&       const_reference;
		typedef T*             pointer;
		typedef const T*       const_pointer;

		// data structure that represents a node in the tree
		typedef struct	node_s
		{
			T				data;    // holds the key
			int				color;   // 1 -> Red, 0 -> Black
			struct node_s	*parent; // pointer to the parent
			struct node_s	*left;   // pointer to left child
			struct node_s	*right;  // pointer to right child
		}				node;

		typedef node*          node_ptr;


	private:
		// initializes the nodes with appropirate values
		// all the pointers are set to point to the null pointer
		void	initializeNULLNode(node_ptr node, node_ptr parent)
		{
			node->data = 0;
			node->parent = parent;
			node->left = nullptr_;
			node->right = nullptr_;
			node->color = RBT_BLACK;
		}

		void	preOrderHelper(node_ptr node)
		{
			if (node != _last)
			{
				std::cout << node->data << " ";
				preOrderHelper(node->left);
				preOrderHelper(node->right);
			} 
		}

		void	inOrderHelper(node_ptr node)
		{
			if (node != _last)
			{
				inOrderHelper(node->left);
				std::cout << node->data << " ";
				inOrderHelper(node->right);
			} 
		}

		void	postOrderHelper(node_ptr node)
		{
			if (node != _last)
			{
				postOrderHelper(node->left);
				postOrderHelper(node->right);
				std::cout << node->data << " ";
			} 
		}

		node_ptr	searchTreeHelper(node_ptr node, int key)
		{
			if (node == _last || key == node->data)
				return node;
			if (key < node->data)
				return searchTreeHelper(node->left, key);
			return searchTreeHelper(node->right, key);
		}

		// fix the rb tree modified by the delete operation
		void	fixDelete(node_ptr x)
		{
			node_ptr	s;
			while (x != _root && x->color == RBT_BLACK)
			{
				if (x == x->parent->left)
				{
					s = x->parent->right;
					if (s->color == RBT_RED)
					{
						// case 3.1
						s->color = RBT_BLACK;
						x->parent->color = RBT_RED;
						leftRotate(x->parent);
						s = x->parent->right;
					}

					if (s->left->color == RBT_BLACK && s->right->color == RBT_BLACK)
					{
						// case 3.2
						s->color = RBT_RED;
						x = x->parent;
					} else
					{
						if (s->right->color == RBT_BLACK)
						{
							// case 3.3
							s->left->color = RBT_BLACK;
							s->color = RBT_RED;
							rightRotate(s);
							s = x->parent->right;
						} 

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = RBT_BLACK;
						s->right->color = RBT_BLACK;
						leftRotate(x->parent);
						x = _root;
					}
				} else
				{
					s = x->parent->left;
					if (s->color == RBT_RED)
					{
						// case 3.1
						s->color = RBT_BLACK;
						x->parent->color = RBT_RED;
						rightRotate(x->parent);
						s = x->parent->left;
					}

					if (s->left->color == RBT_BLACK && s->right->color == RBT_BLACK)
					{
						// case 3.2
						s->color = RBT_RED;
						x = x->parent;
					} else
					{
						if (s->left->color == RBT_BLACK)
						{
							// case 3.3
							s->right->color = RBT_BLACK;
							s->color = RBT_RED;
							leftRotate(s);
							s = x->parent->left;
						} 

						// case 3.4
						s->color = x->parent->color;
						x->parent->color = RBT_BLACK;
						s->left->color = RBT_BLACK;
						rightRotate(x->parent);
						x = _root;
					}
				} 
			}
			x->color = RBT_BLACK;
		}


		void	rbTransplant(node_ptr u, node_ptr v)
		{
			if (u->parent == nullptr_)
				_root = v;
			else if (u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void	deleteNodeHelper(node_ptr node, int key)
		{
			// find the node containing key
			node_ptr z = _last;
			node_ptr x, y;
			while (node != _last){
				if (node->data == key)
				{
					z = node;
				}

				if (node->data <= key)
				{
					node = node->right;
				} else
				{
					node = node->left;
				}
			}

			if (z == _last)
			{
				std::cout << "Couldn't find key in the tree" << std::endl;
				return ;
			} 

			y = z;
			int y_original_color = y->color;
			if (z->left == _last)
			{
				x = z->right;
				rbTransplant(z, z->right);
			} else if (z->right == _last)
			{
				x = z->left;
				rbTransplant(z, z->left);
			} else
			{
				y = min(z->right);
				y_original_color = y->color;
				x = y->right;
				if (y->parent == z)
				{
					x->parent = y;
				} else
				{
					rbTransplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}

				rbTransplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			delete z;
			if (y_original_color == RBT_BLACK)
				fixDelete(x);
		}
		
		// fix the red-black tree
		void	fixInsert(node_ptr k)
		{
			node_ptr	u;
			
			while (k->parent->color == RBT_RED)
			{
				if (k->parent == k->parent->parent->right)
				{
					u = k->parent->parent->left; // uncle
					if (u->color == RBT_RED)
					{
						// case 3.1
						u->color = RBT_BLACK;
						k->parent->color = RBT_BLACK;
						k->parent->parent->color = RBT_RED;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left)
						{
							// case 3.2.2
							k = k->parent;
							rightRotate(k);
						}
						// case 3.2.1
						k->parent->color = RBT_BLACK;
						k->parent->parent->color = RBT_RED;
						leftRotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right; // uncle

					if (u->color == RBT_RED)
					{
						// mirror case 3.1
						u->color = RBT_BLACK;
						k->parent->color = RBT_BLACK;
						k->parent->parent->color = RBT_RED;
						k = k->parent->parent;	
					}
					else
					{
						if (k == k->parent->right)
						{
							// mirror case 3.2.2
							k = k->parent;
							leftRotate(k);
						}
						// mirror case 3.2.1
						k->parent->color = RBT_BLACK;
						k->parent->parent->color = RBT_RED;
						rightRotate(k->parent->parent);
					}
				}
				if (k == _root)
					break ;
			}
			_root->color = RBT_BLACK;
		}

		void	printHelper(node_ptr root, std::string indent, bool last)
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
				
				std::string	sColor = root->color ? "RED" : "BLACK";
				std::cout << root->data << "(" << sColor << ")" << std::endl;
				printHelper(root->left, indent, false);
				printHelper(root->right, indent, true);
			}
			// std::cout << root->left->data << std::endl;
		}

	public:
		RedBlackTree()
		{
			_last = new node;
			_last->color = RBT_BLACK;
			_last->left = nullptr_;
			_last->right = nullptr_;
			_root = _last;
		}

		// Pre-Order traversal
		// node->Left Subtree->Right Subtree
		void	preorder()         { preOrderHelper(_root); }

		// In-Order traversal
		// Left Subtree -> node -> Right Subtree
		void	inorder()          { inOrderHelper(_root); }

		// Post-Order traversal
		// Left Subtree -> Right Subtree -> node
		void	postorder()        { postOrderHelper(_root); }

		// search the tree for the key k
		// and return the corresponding node
		node_ptr	searchTree(int k)  { return searchTreeHelper(_root, k); }

		// find the node with the minimum key
		node_ptr	min(node_ptr s)
		{
			while (s->left != _last)
				s = s->left;
			return s;
		}

		// find the node with the maximum key
		node_ptr	max(node_ptr s)
		{
			while (s->right != _last)
				s = s->right;
			return s;
		}

		// find the successor of a given node
		node_ptr	successor(node_ptr x)
		{
			// if the right subtree is not null,
			// the successor is the leftmost node in the
			// right subtree
			if (x->right != _last)
				return min(x->right);

			// else it is the lowest ancestor of x whose
			// left child is also an ancestor of x.
			node_ptr y = x->parent;
			while (y != _last && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		// find the predecessor of a given node
		node_ptr	predecessor(node_ptr s)
		{
			// if the left subtree is not null,
			// the predecessor is the rightmost node in the 
			// left subtree
			if (s->left != _last)
				return max(s->left);

			node_ptr	tmp = s->parent;
			while (tmp != _last && s == tmp->left)
			{
				s = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}

		// rotate left at node x
		void	leftRotate(node_ptr s)
		{
			node_ptr	tmp = s->right;
			
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
		void	rightRotate(node_ptr x)
		{
			node_ptr	y = x->left;
			
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

		// insert the key to the tree in its appropriate position
		// and fix the tree
		void	insert(int key)
		{
			// Ordinary Binary Search Insertion
			node_ptr	s = new node;
			
			s->parent = nullptr_;
			s->data = key;
			s->left = _last;
			s->right = _last;
			s->color = RBT_RED; // new node must be red

			node_ptr y = nullptr_;
			node_ptr x = _root;

			while (x != _last)
			{
				y = x;
				if (s->data < x->data)
					x = x->left;
				else
					x = x->right;
			}

			// y is parent of x
			s->parent = y;
			if (y == nullptr_)
				_root = s;
			else if (s->data < y->data)
				y->left = s;
			else
				y->right = s;

			// if new node is a _root node, simply return
			if (s->parent == nullptr_)
			{
				s->color = RBT_BLACK;
				return ;
			}

			// if the grandparent is null, simply return
			if (s->parent->parent == nullptr_)
				return ;

			// Fix the tree
			fixInsert(s);
		}

		node_ptr	getRoot()        { return _root; }

		// delete the node from the tree
		void	deleteNode(int data) { deleteNodeHelper(_root, data); }

		// print the tree structure on the screen
		void	prettyPrint()
		{
			if (_root)
				printHelper(_root, "", true);
		}
	
	
	private:
		node_ptr		_root;
		node_ptr		_last;

};


_END_NAMESPACE_FT

#endif /* define OLD_RED_BLACK_TREE_HPP */
