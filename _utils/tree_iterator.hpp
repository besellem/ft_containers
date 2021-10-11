/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:07:19 by besellem          #+#    #+#             */
/*   Updated: 2021/10/11 14:50:44 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include <iostream>

# include "iterator.hpp"
# include "RedBlackTree.hpp"
# include "utils.hpp"


_BEGIN_NAMESPACE_FT

template <class T>
class tree_iterator : public iterator<bidirectional_iterator_tag, T>
{

	public:
		typedef typename T::value_type                        value_type;
		typedef T                                             node_type;
		typedef T*                                            node_pointer;
		
		typedef bidirectional_iterator_tag                    iterator_category;
		typedef iterator<iterator_category, value_type>       iterator_type;
		typedef typename iterator_type::difference_type       difference_type;
		typedef typename iterator_type::pointer               pointer;
		typedef typename iterator_type::reference             reference;


	public:
		tree_iterator(void) : _begin(nullptr_), _end(nullptr_), _cur(nullptr_) {}
		
		tree_iterator(node_pointer const& begin, node_pointer const& end, node_pointer const& current) :
			_begin(begin),
			_end(end),
			_cur(current)
		{}

		tree_iterator(tree_iterator const& u)
		{
			*this = u;
		}

		tree_iterator&		operator=(const tree_iterator& u)
		{
			if (this == &u)
				return *this;
			
			_begin = u._begin;
			_end = u._end;
			_cur = u._cur;
			return *this;
		}
		
		~tree_iterator() {}

		reference			operator*() const
		{
			return _cur->val;
		}
		
		pointer				operator->() const
		{
			return &(operator*());
		}

		tree_iterator&		operator++()
		{
			if (_cur == max(_begin))
			{
				_cur = _end;
				return *this;
			}
			else if (_cur == _end)
			{
				_cur = nullptr_;
				return *this;
			}
			_cur = successor(_cur);
			return *this;
		}
		
		tree_iterator		operator++(int)
		{
			tree_iterator	tmp(*this);
			operator++();
			return tmp;
		}
		
		tree_iterator&		operator--()
		{
			if (_cur == _end)
			{
				_cur = max(_begin);
				return *this;
			}
			_cur = predecessor(_cur);
			return *this;
		}
		
		tree_iterator		operator--(int)
		{
			tree_iterator	tmp(*this);
			operator--();
			return tmp;
		}
		
		template <class IteratorL, class IteratorR>
		friend bool		operator==(tree_iterator<IteratorL> const& x,
								   tree_iterator<IteratorR> const& y)
		{ return x._cur == y._cur; }

		template <class IteratorL, class IteratorR>
		friend bool		operator!=(tree_iterator<IteratorL> const& x,
								   tree_iterator<IteratorR> const& y)
		{ return x._cur != y._cur; }


	private:
		node_pointer	min(node_pointer s)
		{
			for ( ; s->left != _end; s = s->left);
			return s;
		}

		node_pointer	max(node_pointer s)
		{
			for ( ; s->right != _end; s = s->right);
			return s;
		}

		node_pointer	successor(node_pointer s)
		{
			if (s->right != _end)
				return min(s->right);

			node_pointer	y = s->parent;
			while (y != _end && s == y->right)
			{
				s = y;
				y = y->parent;
			}
			return y;
		}

		node_pointer	predecessor(node_pointer s)
		{
			if (s->left != _end)
				return max(s->left);

			node_pointer	tmp = s->parent;
			while (tmp != _end && s == tmp->left)
			{
				s = tmp;
				tmp = tmp->parent;
			}
			return tmp;
		}


	private:
		node_pointer	_begin;
		node_pointer	_end;
		node_pointer	_cur;

}; /* tree_iterator */


_END_NAMESPACE_FT

#endif /* define TREE_ITERATOR_HPP */
