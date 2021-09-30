/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:30 by besellem          #+#    #+#             */
/*   Updated: 2021/09/30 16:39:06 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>

# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

# include "_utils/iterator.hpp"

# define RED       "\e[1;31m"
# define GREEN     "\e[1;33m"
# define BLUE      "\e[1;34m"
# define CLR_COLOR "\e[0m"

# include <mach/boolean.h>

#ifndef DEBUG
# define DEBUG TRUE
#endif

#if (DEBUG == FALSE)
# define LOG(m) std::cout << RED << __FILE__ << ":" << __LINE__ << ": " CLR_COLOR << m << std::endl;
#else
# define LOG(m) ;
#endif


_BEGIN_NAMESPACE_FT

template < class T, class Alloc = std::allocator<T> >
class vector
{

	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename allocator_type::size_type			size_type;
		typedef typename allocator_type::difference_type	difference_type;
		
		typedef ft::random_access_iterator<pointer>			iterator;
		typedef ft::random_access_iterator<const_pointer>	const_iterator;
		typedef ft::reverse_iterator<pointer>				reverse_iterator;
		typedef ft::reverse_iterator<const_pointer>			const_reverse_iterator;
		

	public:
		explicit vector(const allocator_type &alloc = allocator_type()) :
			_alloc(alloc),
			_begin(nullptr_),
			_end(nullptr_),
			_end_cap(nullptr_)
		{
			LOG("Contructor #1")
		}
		
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) :
			_alloc(alloc),
			_begin(nullptr_),
			_end(nullptr_),
			_end_cap(nullptr_)
		{
			LOG("Contructor #2")
			try
			{
				_begin = _alloc.allocate(n);
			}
			catch (std::exception &e)
			{
				throw std::length_error("vector");
			}
			
			_end = _begin;
			for (size_t i = 0; i < n; ++i, ++_end)
				_alloc.construct(_end, val);
			_end_cap = _end;
		}

		template <class _InputIte>
		vector(_InputIte first, _InputIte last,
				const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<_InputIte>::value, _InputIte>::type* = nullptr_) :
			_alloc(alloc),
			_begin(nullptr_),
			_end(nullptr_),
			_end_cap(nullptr_)
		{
			LOG("Contructor #3")
			difference_type		n = ft::distance(first, last);
			
			_begin = _alloc.allocate(n);
			_end_cap = _begin + n;
			_end = _begin;
			for ( ; n > 0 ; --n, ++_end, ++first)
				_alloc.construct(_end, *first);
		}
		
		vector(const vector &x)
		{
			LOG("Copy Constructor")
			
			size_type	n = x.size();

			_begin = x._alloc.allocate(n);
			_end_cap = _begin + n;
			_end = _begin;

			for (iterator it = x.begin(); n > 0; --n, ++_end)
				_alloc.construct(_end, *it++);
		}
		
		~vector()
		{
			if (_begin != nullptr_)
			{
				clear();
				_alloc.deallocate(_begin, capacity());
			}
		}
		
		vector &				operator=(const vector &x)
		{
			LOG("Assignment Operator")
			if (*this == x)
				return *this;
			
			// this->clear();
			// this->_alloc = x._alloc;
			// this->_begin = x._begin;
			// this->_end = x._end;
			// this->_end_cap = x._end_cap;
			
			return *this;
		}
		
		/*
		** -- Iterators --
		*/
		iterator				begin()        { return iterator(_begin); }
		const_iterator			begin() const  { return const_iterator(_begin); }
		iterator				end()          { return iterator(_end); }
		const_iterator			end() const    { return const_iterator(_end); }
		reverse_iterator		rbegin()       { return reverse_iterator(_end); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(_end); }
		reverse_iterator		rend()         { return reverse_iterator(_begin); }
		const_reverse_iterator	rend() const   { return const_reverse_iterator(_begin); }

		/*
		** -- Capacity --
		*/
		size_type		size() const     { return static_cast<size_type>(_end - _begin); }
		size_type		max_size() const { return allocator_type().max_size(); }
		size_type		capacity() const { return static_cast<size_type>(_end_cap - _begin); }
		bool			empty() const    { return size() == 0; }

		void			resize(size_type n, value_type val = value_type())
		{
			size_type	i;

			if (n > max_size())
				throw std::length_error("vector::resize");
			
			if (n < size())
			{
				for (i = size(); i > n; --i)
					_alloc.destroy(--_end);
			}
			else
			{
				if (n < capacity())
				{
					i = size();
					reserve(n);
					for ( ; i < n; ++i, ++_end)
						_alloc.construct(_end, val);
				}
				else
				{
					pointer			old_begin = _begin;
					pointer			tmp_begin = _begin;
					pointer			old_end = _end;
					const size_type	old_capacity = capacity();

					_begin = _alloc.allocate(n, old_begin);
					_end_cap = _begin + n;
					_end = _begin;
					while (tmp_begin != old_end)
					{
						_alloc.construct(_end, *tmp_begin);
						++_end;
						++tmp_begin;
					}
					while (_end != _end_cap)
						_alloc.construct(_end++, val);
					_alloc.deallocate(old_begin, old_capacity);
				}
			}
		}

		void			reserve(size_type n)
		{
			pointer			old_begin = _begin;
			pointer			tmp_begin = _begin;
			pointer			old_end = _end;
			const size_type	old_capacity = capacity();

			if (n > max_size())
				throw std::length_error("vector::reserve");
			
			if (n > capacity())
			{
				_begin = _alloc.allocate(n, old_begin);
				_end_cap = _begin + n;
				_end = _begin;
				
				for ( ; tmp_begin != old_end; ++_end, ++tmp_begin)
					_alloc.construct(_end, *tmp_begin);
				_alloc.deallocate(old_begin, old_capacity);
			}
		}

		/*
		** -- Element access --
		*/
		reference 		front()                        { return *_begin; }
		const_reference	front() const                  { return *_begin; }
		reference		back()                         { return *(_end - 1); }
		const_reference	back() const                   { return *(_end - 1); }
		reference		operator[] (size_type n)       { return *(_begin + n); }
		const_reference	operator[] (size_type n) const { return *(_begin + n); }
		
		reference		at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("vector");
			return *(_begin + n);
		}

		const_reference	at(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector");
			return *(_begin + n);
		}
		
		/*
		** -- Modifiers --
		*/
		// template <class _InputIte>
		// void			assign(_InputIte first, _InputIte last)
		// {
		// 	pointer			old_begin = _begin;
		// 	const size_type	old_capacity = capacity();

		// 	// if (n > max_size())
		// 	// 	throw std::length_error("vector");

		// 	std::cout << GREEN "DIFF => " << (last - first) << CLR_COLOR << std::endl;

		// 	// clear();
		// 	// if (n < capacity())
		// 	// {	
		// 	// 	for (size_type i = 0; i < n; ++i)
		// 	// 		push_back(val);
		// 	// }
		// 	// else
		// 	// {
		// 	// 	_begin = _alloc.allocate(n, old_begin);
		// 	// 	_end_cap = _begin + n;
		// 	// 	_end = _begin;

		// 	// 	for ( ; _end != _end_cap; ++_end)
		// 	// 		_alloc.construct(_end, val);
		// 	// 	_alloc.deallocate(old_begin, old_capacity);
		// 	// }


		// 	// for (; first != last; ++first)
		// 	// {
				
		// 	// }
		// }
		
		void			assign(size_type n, const value_type &val)
		{
			pointer			old_begin = _begin;
			const size_type	old_capacity = capacity();

			if (n > max_size())
				throw std::length_error("vector");

			clear();
			if (n < capacity())
			{	
				for (size_type i = 0; i < n; ++i)
					push_back(val);
			}
			else
			{
				_begin = _alloc.allocate(n, old_begin);
				_end_cap = _begin + n;
				_end = _begin;

				for ( ; _end != _end_cap; ++_end)
					_alloc.construct(_end, val);
				_alloc.deallocate(old_begin, old_capacity);
			}
		}
		
		void			push_back(const value_type &val)
		{	
			if (_end == _end_cap)
				reserve(size() > 0 ? size() * 2 : 1);
			_alloc.construct(_end, val);
			++_end;
		}

		void			pop_back()
		{
			_alloc.destroy(_end);
			--_end;
		}
		
		// iterator		insert(iterator position, const value_type &val);
		// void			insert(iterator position, size_type n, const value_type &val);
		// template <class _InputIte>
		// void			insert(iterator position, _InputIte first, _InputIte last);
		
		iterator		erase(iterator position)
		{
			iterator	ret = position;

			for ( ; position != end(); ++position)
			{
				_alloc.destroy(&*position);
				_alloc.construct(&*position, *(position + 1));
			}
			--_end;
			return ret;
		}
		
		iterator		erase(iterator first, iterator last)
		{
			iterator				it = first;
			iterator				ret = first;
			const difference_type	diff = std::abs(last - first);

			for ( ; first != last; ++first)
				_alloc.destroy(&*first);
			
			for ( ; last != end(); ++last, ++it)
			{
				_alloc.construct(&*it, *last);
				_alloc.destroy(&*last);
			}
			_end -= diff;
			return ret;
		}
		
		void			swap(vector &x)
		{
			if (*this == x)
				return ;
			
			vector<T>	cpy(*this);
			
			*this = x;
			x = cpy;
		}
		
		void			clear()
		{
			const size_type	sz = size();

			for (size_type i = 0; i < sz; ++i)
			{
				--_end;
				_alloc.destroy(_end);
			}
		}

		/*
		** -- Allocator --
		*/
		allocator_type	get_allocator() const { return allocator_type(); }


	private:
		allocator_type	_alloc;
		pointer			_begin;
		pointer			_end;
		pointer			_end_cap;
	
}; /* class vector */

/*
** -- Non-member --
*/
template <class T, class Alloc>
bool	operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
{
	typename ft::vector<T>::const_iterator	left = lhs.begin();
	typename ft::vector<T>::const_iterator	right = rhs.begin();

	if (lhs.size() != rhs.size())
		return false;

	for ( ; left != lhs.end(); ++left, ++right)
	{
		if (right == rhs.end() || *left != *right)
			return false;
	}
	return true;
}

template <class T, class Alloc>
bool	operator!=(const vector<T,Alloc> &x, const vector<T,Alloc> &y)
{ return !(x == y); }

template <class T, class Alloc>
bool	operator<(const vector<T,Alloc> &x, const vector<T,Alloc> &y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template <class T, class Alloc>
bool	operator<=(const vector<T,Alloc> &x, const vector<T,Alloc> &y)
{ return !(y < x); }

template <class T, class Alloc>
bool	operator>(const vector<T,Alloc> &x, const vector<T,Alloc> &y)
{ return y < x; }

template <class T, class Alloc>
bool	operator>=(const vector<T,Alloc> &x, const vector<T,Alloc> &y)
{ return !(x < y); }

template <class T, class Alloc>
void	swap(vector<T,Alloc> &x, vector<T,Alloc> &y)
{ x.swap(y); }


_END_NAMESPACE_FT

#endif /* define VECTOR_HPP */
