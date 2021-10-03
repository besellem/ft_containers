/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:16:46 by besellem          #+#    #+#             */
/*   Updated: 2021/10/03 19:55:28 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include <cstddef>
# include <tgmath.h>
# include "utils.hpp"


_BEGIN_NAMESPACE_FT
	
/* Iterator Tags */
struct input_iterator_tag  {};
struct output_iterator_tag {};
struct forward_iterator_tag       : public input_iterator_tag         {};
struct bidirectional_iterator_tag : public forward_iterator_tag       {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/* Iterator Traits */
template <class Iterator>
struct iterator_traits
{
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*>
{
	typedef ptrdiff_t								difference_type;
	typedef T										value_type;
	typedef T*										pointer;
	typedef T&										reference;
	typedef random_access_iterator_tag				iterator_category;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef ptrdiff_t								difference_type;
	typedef T										value_type;
	typedef T*										pointer;
	typedef T&										reference;
	typedef random_access_iterator_tag				iterator_category;
};

/* Iterator */
template <class Category,
		  class T,
		  class Distance = ptrdiff_t,
		  class Pointer = T*,
		  class Reference = T&>
struct iterator {
	typedef T										value_type;
	typedef Distance								difference_type;
	typedef Pointer									pointer;
	typedef Reference								reference;
	typedef Category								iterator_category;
};


/* Random Access Iterator */
template <class _Ite>
class random_access_iterator : public iterator<random_access_iterator_tag, _Ite>
{
	public:
		typedef typename ft::iterator<random_access_iterator_tag, _Ite>::value_type			value_type;
		typedef typename ft::iterator<random_access_iterator_tag, _Ite>::difference_type	difference_type;
		typedef typename ft::iterator<random_access_iterator_tag, _Ite>::pointer			pointer;
		typedef typename ft::iterator<random_access_iterator_tag, _Ite>::reference			reference;
		typedef typename ft::iterator<random_access_iterator_tag, _Ite>::iterator_category	iterator_category;
	
		random_access_iterator()                   : _cur(nullptr_) {}
		explicit random_access_iterator(pointer x) : _cur(x) {}
		random_access_iterator(const random_access_iterator& u) : _cur(u.base()) {}
		~random_access_iterator() {}

		random_access_iterator&	operator=(const random_access_iterator& u)
		{
			if (*this == u)
				return *this;
			
			_cur = u.base();
			return *this;
		}
		
		pointer					base() const
		{
			return _cur;
		}
		
		reference				operator*() const
		{
			return *_cur;
		}
		
		pointer					operator->() const
		{
			return &(operator*());
		}
		
		random_access_iterator&	operator++()
		{
			++_cur;
			return *this;
		}
		
		random_access_iterator	operator++(int)
		{
			random_access_iterator	tmp(*this);
			++_cur;
			return tmp;
		}
		
		random_access_iterator&	operator--()
		{
			--_cur;
			return *this;
		}
		
		random_access_iterator	operator--(int)
		{
			random_access_iterator	tmp(*this);
			--_cur;
			return tmp;
		}
		
		random_access_iterator	operator+(difference_type n) const
		{
			return random_access_iterator(_cur + n);
		}
		
		random_access_iterator&	operator+=(difference_type n)
		{
			_cur += n;
			return *this;
		}
		
		random_access_iterator	operator-(difference_type n) const
		{
			return random_access_iterator(_cur - n);
		}
		
		random_access_iterator&	operator-=(difference_type n)
		{
			_cur -= n;
			return *this;
		}
		
		reference				operator[](difference_type n) const
		{
			return *(_cur + n);
		}

		operator random_access_iterator<const _Ite>(void)
		{
			return static_cast< random_access_iterator<const _Ite> >(_cur);
		}

		/* Non-member functions */
		template <class IteratorL, class IteratorR>
		friend bool		operator==(const random_access_iterator<IteratorL>& lhs,
								   const random_access_iterator<IteratorR>& rhs)
		{ return lhs.base() == rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator!=(const random_access_iterator<IteratorL>& lhs,
								   const random_access_iterator<IteratorR>& rhs)
		{ return lhs.base() != rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator< (const random_access_iterator<IteratorL>& lhs,
								   const random_access_iterator<IteratorR>& rhs)
		{ return lhs.base() < rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator<=(const random_access_iterator<IteratorL>& lhs,
								   const random_access_iterator<IteratorR>& rhs)
		{ return lhs.base() <= rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator> (const random_access_iterator<IteratorL>& lhs,
								   const random_access_iterator<IteratorR>& rhs)
		{ return lhs.base() > rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator>=(const random_access_iterator<IteratorL>& lhs,
								   const random_access_iterator<IteratorR>& rhs)
		{ return lhs.base() >= rhs.base(); }

		template <class Iterator>
		friend random_access_iterator<Iterator>	operator+(
						difference_type n,
						const random_access_iterator<Iterator>& x)
		{ return random_access_iterator<Iterator>(x.base() + n); }

		template <class IteratorL, class IteratorR>
		friend difference_type				operator-(
						const random_access_iterator<IteratorL>& lhs,
						const random_access_iterator<IteratorR>& rhs)
		{ return lhs.base() - rhs.base(); }
		
		private:
			pointer		_cur;
		
};


/* Reverse Iterator */
template <class Iterator>
class reverse_iterator
	: public iterator<typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference>
{
	protected:
		Iterator	_cur;
	
	public:
		typedef Iterator											iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type	difference_type;
		typedef typename iterator_traits<Iterator>::reference		reference;
		typedef typename iterator_traits<Iterator>::pointer			pointer;

		reverse_iterator()                    : _cur() {}
		explicit reverse_iterator(Iterator x) : _cur(x) {}

		template <class U>
		reverse_iterator(const reverse_iterator<U>& u) : _cur(u.base()) {}

		template <class U>
		reverse_iterator&	operator=(const reverse_iterator<U>& u)
		{
			if (*this == u)
				return *this;
			
			_cur = u.base();
			return *this;
		}
		
		Iterator			base() const
		{
			return _cur;
		}
		
		reference			operator*() const
		{
			iterator_type	cpy = _cur;
			return *--cpy;
		}
		
		pointer				operator->() const
		{
			return &(operator*());
		}
		
		reverse_iterator&	operator++()
		{
			--_cur;
			return *this;
		}
		
		reverse_iterator	operator++(int)
		{
			reverse_iterator	tmp(*this);
			--_cur;
			return tmp;
		}
		
		reverse_iterator&	operator--()
		{
			++_cur;
			return *this;
		}
		
		reverse_iterator	operator--(int)
		{
			reverse_iterator	tmp(*this);
			++_cur;
			return tmp;
		}
		
		reverse_iterator	operator+(difference_type n) const
		{
			return reverse_iterator(_cur - n);
		}
		
		reverse_iterator&	operator+=(difference_type n)
		{
			_cur -= n;
			return *this;
		}
		
		reverse_iterator	operator-(difference_type n) const
		{
			return reverse_iterator(_cur + n);
		}
		
		reverse_iterator&	operator-=(difference_type n)
		{
			_cur += n;
			return *this;
		}
		
		reference			operator[](difference_type n) const
		{
			return (*(*this + n));
		}

		/* Non-member functions */
		template <class IteratorL, class IteratorR>
		friend bool		operator==(const reverse_iterator<IteratorL>& lhs,
								   const reverse_iterator<IteratorR>& rhs)
		{ return lhs.base() == rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator!=(const reverse_iterator<IteratorL>& lhs,
								   const reverse_iterator<IteratorR>& rhs)
		{ return lhs.base() != rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator< (const reverse_iterator<IteratorL>& lhs,
								   const reverse_iterator<IteratorR>& rhs)
		{ return lhs.base() > rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator<=(const reverse_iterator<IteratorL>& lhs,
								   const reverse_iterator<IteratorR>& rhs)
		{ return lhs.base() >= rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator> (const reverse_iterator<IteratorL>& lhs,
								   const reverse_iterator<IteratorR>& rhs)
		{ return lhs.base() < rhs.base(); }

		template <class IteratorL, class IteratorR>
		friend bool		operator>=(const reverse_iterator<IteratorL>& lhs,
								   const reverse_iterator<IteratorR>& rhs)
		{ return lhs.base() <= rhs.base(); }

		template <class _Ite>
		friend reverse_iterator<_Ite>	operator+(
						difference_type n,
						const reverse_iterator<_Ite>& x)
		{ return reverse_iterator<_Ite>(x.base() - n); }

		template <class IteratorL, class IteratorR>
		friend difference_type			operator-(
						const reverse_iterator<IteratorL>& lhs,
						const reverse_iterator<IteratorR>& rhs)
		{ return rhs.base() - lhs.base(); }
};


/* Lexicographical Compare */
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
							InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}


/* Enable if */
template<bool Cond, class T = void> struct enable_if {};
template<class T> struct enable_if<true, T> { typedef T type; };

/* Integral Constant */
template <class T, T __v>
struct integral_constant
{
	static const T				value = __v;
	typedef T					value_type;
	typedef integral_constant	type;
	
	operator value_type() const { return value; }
};

typedef integral_constant<bool, true>	true_type;
typedef integral_constant<bool, false>	false_type;

/* Is Integral */
template <class _Tp> struct is_integral                     : public false_type {};
template <>          struct is_integral<bool>               : public true_type {};
template <>          struct is_integral<char>               : public true_type {};
template <>          struct is_integral<signed char>        : public true_type {};
template <>          struct is_integral<unsigned char>      : public true_type {};
template <>          struct is_integral<wchar_t>            : public true_type {};
template <>          struct is_integral<short>              : public true_type {};
template <>          struct is_integral<unsigned short>     : public true_type {};
template <>          struct is_integral<int>                : public true_type {};
template <>          struct is_integral<unsigned int>       : public true_type {};
template <>          struct is_integral<long>               : public true_type {};
template <>          struct is_integral<unsigned long>      : public true_type {};
template <>          struct is_integral<long long>          : public true_type {};
template <>          struct is_integral<unsigned long long> : public true_type {};

/* Distance */
template <class _InputIte>
typename iterator_traits<_InputIte>::difference_type
distance(_InputIte first, _InputIte last)
{
	typename iterator_traits<_InputIte>::difference_type	_n = 0;	
	for ( ; first != last; ++first, ++_n);
	return _n;
}


_END_NAMESPACE_FT

#endif /* define ITERATOR_HPP */
