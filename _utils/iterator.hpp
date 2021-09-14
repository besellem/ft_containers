/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:16:46 by besellem          #+#    #+#             */
/*   Updated: 2021/09/14 16:22:52 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <cstddef>
# include <tgmath.h>

namespace ft
{

	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t								difference_type;
		typedef T										value_type;
		typedef T*										pointer;
		typedef T&										reference;
		typedef random_access_iterator_tag				iterator_category;
	};

	template <class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T										value_type;
		typedef Distance								difference_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef Category								iterator_category;
	};

	/* Iterator Tags */
	struct input_iterator_tag  {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag         {};
	struct bidirectional_iterator_tag : public forward_iterator_tag       {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	/* reverse_iterator */
	template <class Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
		public:
			typedef Iterator											iterator_type;
			typedef typename iterator_traits<Iterator>::difference_type	difference_type;
			typedef typename iterator_traits<Iterator>::reference		reference;
			typedef typename iterator_traits<Iterator>::pointer			pointer;

			constexpr			reverse_iterator()           : _cur() {}
			constexpr explicit	reverse_iterator(Iterator x) : _cur(x) {};

			template <class U> constexpr	reverse_iterator(const reverse_iterator<U> &u) :
				_cur(u.base())
			{}

			template <class U> constexpr	reverse_iterator& operator=(const reverse_iterator<U> &u)
			{
				_cur = u.base();
			}
			
			constexpr Iterator				base() const
			{
				return _cur;
			}
			
			constexpr reference				operator*() const
			{
				iterator_type	cpy = _cur;
				return *(--cpy);
			}
			
			constexpr pointer				operator->() const
			{
				return &(operator*());
			}
			
			constexpr reverse_iterator&		operator++()
			{
				--_cur;
				return *this;
			}
			
			constexpr reverse_iterator		operator++(int)
			{
				reverse_iterator	tmp(*this);
				--_cur;
				return tmp;
			}
			
			constexpr reverse_iterator&		operator--()
			{
				++_cur
				return *this;
			}
			
			constexpr reverse_iterator		operator--(int)
			{
				reverse_iterator	tmp(*this);
				++_cur;
				return *this;
			}
			
			constexpr reverse_iterator		operator+(difference_type n) const
			{
				return reverse_iterator(_cur - n);
			}
			
			constexpr reverse_iterator&		operator+=(difference_type n)
			{
				_cur -= n;
				return *this;
			}
			
			constexpr reverse_iterator		operator-(difference_type n) const
			{
				return reverse_iterator(_cur + n);
			}
			
			constexpr reverse_iterator&		operator-=(difference_type n)
			{
				_cur += n;
				return *this;
			}
			
			constexpr reference				operator[](difference_type n) const
			{
				return (*(*this + n));
			}
		
		protected:
			iterator_type	_cur;
	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() == rhs.base(); }

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() != rhs.base(); }
	
	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() < rhs.base(); }
	
	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() <= rhs.base(); }
	
	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() > rhs.base(); }
	
	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{ return lhs.base() >= rhs.base(); }
	
	template <class Iterator>
	reverse_iterator<Iterator> operator+ (
					typename reverse_iterator<Iterator>::difference_type n,
					const reverse_iterator<Iterator>& x)
	{ return reverse_iterator<Iterator>(x.base() - n); }

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (
					const reverse_iterator<Iterator>& lhs,
					const reverse_iterator<Iterator>& rhs)
	{ return rhs.base() - lhs.base(); }

} /* namespace ft */
