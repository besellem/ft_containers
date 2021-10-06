/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:07:19 by besellem          #+#    #+#             */
/*   Updated: 2021/10/06 15:59:33 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>

// # include "../map.hpp"
# include "iterator.hpp"
# include "utils.hpp"


_BEGIN_NAMESPACE_FT

template <class T>
class map_iterator : public iterator<bidirectional_iterator_tag, T>
{
	
	// friend class map;

	public:
		typedef typename T::value_type                           value_type;
		
		typedef iterator<bidirectional_iterator_tag, value_type> iterator_type;
		
		typedef T                                                node_type;
		typedef T*                                               node_pointer;
		typedef typename iterator_type::difference_type          difference_type;
		typedef typename iterator_type::pointer                  pointer;
		typedef typename iterator_type::reference                reference;
		typedef typename iterator_type::iterator_category        iterator_category;


	public:
		map_iterator(void) : _begin(nullptr_), _cur(nullptr_), _end(nullptr_) {}
		
		map_iterator(node_pointer const& begin, node_pointer const& end, node_pointer const& current) :
			_begin(begin),
			_end(end),
			_cur(current)
		{}

		map_iterator(map_iterator const& u)
		{
			*this = u;
		}

		map_iterator&		operator=(const map_iterator& u)
		{
			if (*this == u)
				return *this;
			
			_begin = u._begin;
			_end = u._end;
			_cur = u._cur;
			return *this;
		}
		
		~map_iterator() {}

		reference			operator*() const
		{
			return _cur->val;
		}
		
		pointer				operator->() const
		{
			return &(operator*());
		}

		map_iterator&		operator++()
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
		
		map_iterator		operator++(int)
		{
			map_iterator	tmp(*this);
			++_cur;
			return tmp;
		}
		
		map_iterator&		operator--()
		{
			--_cur;
			return *this;
		}
		
		map_iterator		operator--(int)
		{
			map_iterator	tmp(*this);
			--_cur;
			return tmp;
		}


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


	private:
		node_pointer	_begin;
		node_pointer	_end;
		node_pointer	_cur;

}; /* map_iterator */


_END_NAMESPACE_FT

#endif /* define MAP_ITERATOR_HPP */
