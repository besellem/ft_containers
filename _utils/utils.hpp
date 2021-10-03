/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:23:38 by besellem          #+#    #+#             */
/*   Updated: 2021/10/03 22:03:11 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

/* for namespace declaration */
#define _BEGIN_NAMESPACE_FT  namespace ft {
#define _END_NAMESPACE_FT    }


_BEGIN_NAMESPACE_FT

/* nullptr_t */
struct nullptr_t
{
	void	*_ptr;

	struct __nat { int __for_bool_; };

	nullptr_t() : _ptr(0) {}
	nullptr_t(int __nat::*) : _ptr(0) {}
	
	operator int __nat::*() const { return 0; }

	template <class T>
	operator	T*() const { return 0; }

	template <class T, class _Up>
	operator	T _Up::*() const { return 0; }

	friend bool	operator==(nullptr_t, nullptr_t) { return true; }
	friend bool	operator!=(nullptr_t, nullptr_t) { return false; }
};

/* nullptr_ is equivalent to nullptr */
#define nullptr_  nullptr_t(0)


/* pair */
template <class T1, class T2>
struct pair
{
	/* Types */
	typedef T1		first_type;
	typedef T2		second_type;


	/* Construction */
	pair() : first(), second() {}
	pair(const first_type& a, const second_type& b) : first(a), second(b) {}
	~pair() {}
	
	template<class U, class V>
	pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}


	/* Operators */
	pair&	operator=(const pair& pr)
	{
		this->first = pr.first;
		this->second = pr.second;
		return *this;
	}
	
	template <class _T1, class _T2>
	friend bool	operator==(const pair<_T1,_T2>& lhs, const pair<_T1,_T2>& rhs)
	{ return lhs.first == rhs.first && lhs.second == rhs.second; }

	template <class _T1, class _T2>
	friend bool	operator!=(const pair<_T1,_T2>& lhs, const pair<_T1,_T2>& rhs)
	{ return !(lhs == rhs); }

	template <class _T1, class _T2>
	friend bool	operator< (const pair<_T1,_T2>& lhs, const pair<_T1,_T2>& rhs)
	{ return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }

	template <class _T1, class _T2>
	friend bool	operator<=(const pair<_T1,_T2>& lhs, const pair<_T1,_T2>& rhs)
	{ return !(rhs < lhs); }

	template <class _T1, class _T2>
	friend bool	operator> (const pair<_T1,_T2>& lhs, const pair<_T1,_T2>& rhs)
	{ return rhs < lhs; }

	template <class _T1, class _T2>
	friend bool	operator>=(const pair<_T1,_T2>& lhs, const pair<_T1,_T2>& rhs)
	{ return !(lhs < rhs); }


	/* Variables */
	first_type		first;
	second_type		second;
};

template <class T1, class T2>
pair<T1, T2>	make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }


/* Binary Functions */
template <class Arg1, class Arg2, class Result>
struct binary_function
{
	typedef Arg1	first_argument_type;
	typedef Arg2	second_argument_type;
	typedef Result	result_type;
};

template <class T>
struct less : binary_function <T, T, bool>
{
	bool	operator()(const T& x, const T& y) const { return x < y; }
};

template <class T>
struct equal_to : binary_function <T, T, bool>
{
	bool	operator()(const T& x, const T& y) const { return x == y; }
};

template <class T>
struct not_equal_to : binary_function <T, T, bool>
{
	bool	operator()(const T& x, const T& y) const { return x != y; }
};

template <class T>
struct greater : binary_function <T, T, bool>
{
	bool	operator()(const T& x, const T& y) const { return x > y; }
};

template <class T>
struct greater_equal : binary_function <T, T, bool>
{
	bool	operator()(const T& x, const T& y) const { return x >= y; }
};

template <class T>
struct less_equal : binary_function <T, T, bool>
{
	bool	operator()(const T& x, const T& y) const { return x <= y; }
};


_END_NAMESPACE_FT

#endif /* define UTILS_HPP */
