/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:30 by besellem          #+#    #+#             */
/*   Updated: 2021/10/03 20:42:36 by besellem         ###   ########.fr       */
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
		
		typedef ft::random_access_iterator<value_type>			iterator;
		typedef ft::random_access_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		

	public:
		explicit vector(const allocator_type &alloc = allocator_type()) :
			_alloc(alloc),
			_begin(nullptr_),
			_end(nullptr_),
			_end_cap(nullptr_)
		{}
		
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type()) :
			_alloc(alloc),
			_begin(nullptr_),
			_end(nullptr_),
			_end_cap(nullptr_)
		{
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
			difference_type		n = ft::distance(first, last);
			
			_begin = _alloc.allocate(n);
			_end_cap = _begin + n;
			_end = _begin;
			for ( ; n > 0 ; --n, ++_end, ++first)
				_alloc.construct(_end, *first);
		}
		
		vector(const vector &x) :
			_alloc(x._alloc),
			_begin(nullptr_),
			_end(nullptr_),
			_end_cap(nullptr_)
		{
			insert(begin(), x.begin(), x.end());
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
			if (*this == x)
				return *this;
			
			clear();
			insert(end(), x.begin(), x.end());
			return *this;
		}
		
		/*
		** -- Iterators --
		*/
		iterator				begin()        { return iterator(_begin); }
		const_iterator			begin() const  { return const_iterator(_begin); }
		iterator				end()          { return iterator(_end); }
		const_iterator			end() const    { return const_iterator(_end); }
		reverse_iterator		rbegin()       { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend()         { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const   { return const_reverse_iterator(begin()); }

		/*
		** -- Capacity --
		*/
		size_type		size() const     { return static_cast<size_type>(_end - _begin); }
		size_type		max_size() const { return allocator_type().max_size(); }
		size_type		capacity() const { return static_cast<size_type>(_end_cap - _begin); }
		bool			empty() const    { return size() == 0; }

		void			resize(size_type n, value_type val = value_type())
		{
			size_type	old_size = size();
			size_type	old_cap = capacity();

			if (n > max_size())
				throw std::length_error("vector::resize");
			
			if (n < size())
			{
				while (size() > n)
					_alloc.destroy(--_end);
			}
			else
			{
				if (n > capacity())
				{
					if (n > old_cap)
					{
						if ((old_cap * 2) >= n)
							reserve(old_cap * 2);
						else
							reserve(n);
					}
				}
				for ( ; old_size < n; ++old_size, ++_end)
					_alloc.construct(_end, val);
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
		template <class _InputIte>
		void			assign(_InputIte first,
			_InputIte last,
			typename ft::enable_if<!ft::is_integral<_InputIte>::value, _InputIte>::type* = nullptr_)
		{
			clear();
			reserve(ft::distance(first, last));
			for ( ; first != last; ++first, ++_end)
				_alloc.construct(_end, *first);
		}

		void			assign(size_type n, const value_type & val)
		{
			clear();
			reserve(n);
			for ( ; n > 0; --n, ++_end)
				_alloc.construct(_end, val);
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
		
		iterator		insert(iterator position, const value_type &val)
		{
			insert(position, 1, val);
			return iterator(position);
		}

		void			insert(iterator position, size_type n, const value_type &val)
		{
			const difference_type	sz = ft::distance(begin(), position);
			
			resize(size() + n);
			position = begin() + sz;
			
			size_type	rhs = ft::distance(position, end() - n);
			pointer		old_end = _end - n - 1;
			for (size_type i = 0; i < rhs; ++i, --old_end)
				*(_end - i - 1) = *old_end;
			
			for (size_type i = 0; i < n; ++i)
				position[i] = val;
		}
		
		template <class _InputIte>
		void			insert(iterator position,
			_InputIte first,
			_InputIte last,
			typename ft::enable_if<!ft::is_integral<_InputIte>::value, _InputIte>::type* = nullptr_)
		{
			const difference_type	sz = ft::distance(begin(), position);
			const size_type			n = ft::distance(first, last);
			
			resize(size() + n);
			position = begin() + sz;
			
			size_type	rhs = ft::distance(position, end() - n);
			pointer		old_end = _end - n - 1;
			for (size_type i = 0; i < rhs; ++i, --old_end)
				*(_end - i - 1) = *old_end;
			
			for (size_type i = 0; i < n && first != last; ++i, ++first)
				position[i] = *first;
		}
		
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
			iterator	ret = first;
			
			for ( ; first != last; --last)
				erase(first);
			return ret;
		}
		
		void			swap(vector &x)
		{
			if (*this == x)
				return ;
			
			allocator_type	tmp_alloc = _alloc;
			pointer			tmp_begin = _begin;
			pointer			tmp_end = _end;
			pointer			tmp_end_cap = _end_cap;

			_alloc = x._alloc;
			_begin = x._begin;
			_end = x._end;
			_end_cap = x._end_cap;

			x._alloc = tmp_alloc;
			x._begin = tmp_begin;
			x._end = tmp_end;
			x._end_cap = tmp_end_cap;
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
