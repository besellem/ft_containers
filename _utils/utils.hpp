/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:23:38 by besellem          #+#    #+#             */
/*   Updated: 2021/10/08 12:07:51 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

/* namespace `ft' declaration */
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


/* Pair */
template <class T1, class T2>
struct pair
{
	/* -- Types -- */
	typedef T1		first_type;
	typedef T2		second_type;


	/* -- Construction -- */
	pair() : first(), second() {}
	pair(const first_type& a, const second_type& b) : first(a), second(b) {}
	
	template<class U, class V>
	pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

	~pair() {}

	/* -- Operators -- */
	pair&	operator=(const pair& pr)
	{
		first = pr.first;
		second = pr.second;
		return *this;
	}

	/* -- Public Variables -- */
	first_type		first;
	second_type		second;
}; /* struct pair */

/* -- pair non-member functions -- */
template <class T1, class T2>
bool	operator==(const pair<T1,T2>& x, const pair<T1,T2>& y)
{ return x.first == y.first && x.second == y.second; }

template <class T1, class T2>
bool	operator!=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{ return !(x == y); }

template <class T1, class T2>
bool	operator< (const pair<T1,T2>& x, const pair<T1,T2>& y)
{ return x.first < y.first || (!(y.first < x.first) && x.second < y.second); }

template <class T1, class T2>
bool	operator<=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{ return !(y < x); }

template <class T1, class T2>
bool	operator> (const pair<T1,T2>& x, const pair<T1,T2>& y)
{ return y < x; }

template <class T1, class T2>
bool	operator>=(const pair<T1,T2>& x, const pair<T1,T2>& y)
{ return !(x < y); }

// Used to print the key from a pair (TO REMOVE)
template <class T1, class T2>
std::ostream &	operator<<(std::ostream &out, const pair<T1,T2>& x)
{
	out << x.first;
	return out;
}
/* -- [END] pair non-member functions -- */


/* make_pair */
template <class T1, class T2>
pair<T1, T2>	make_pair(T1 x, T2 y) { return pair<T1, T2>(x, y); }


/* Binary Functions */
template <class Arg1, class Arg2, class Result>
struct binary_function
{
	typedef Arg1        first_argument_type;
	typedef Arg2        second_argument_type;
	typedef Result      result_type;
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
