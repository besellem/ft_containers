/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:30 by besellem          #+#    #+#             */
/*   Updated: 2021/09/14 15:24:42 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

# include "_utils/iterator.hpp"

#define RED       "\e[1;31m"
#define GREEN     "\e[1;33m"
#define BLUE      "\e[1;34m"
#define CLR_COLOR "\e[0m"

#define LOG(m) std::cout << RED << __FILE__ << ":" << __LINE__ << ": " CLR_COLOR << m << std::endl;

namespace ft
{
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
			

			// TO DO : IMPLEMENT ITERATORS
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			// typedef ...	reverse_iterator;
			// typedef ...	const_reverse_iterator;
			

		public:
			explicit vector(const allocator_type &alloc = allocator_type()) :
				_alloc(alloc),
				_begin(NULL),
				_end(NULL),
				_capacity(NULL)
			{
				LOG("Contructor #1")
			}
			
			explicit vector(size_type n, const value_type &val = value_type(),
							const allocator_type &alloc = allocator_type()) :
				_alloc(alloc),
				_begin(NULL),
				_end(NULL),
				_capacity(NULL)
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
				_capacity = _end;
			}
			
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type())
			{
				LOG("Contructor #3")
			}
			
			vector(const vector &x)
			{
				LOG("Copy Constructor")
				*this = x;
			}
			
			~vector()
			{
				clear();
				_alloc.deallocate(_begin, capacity());
			}
			
			vector &				operator=(const vector &x)
			{
				LOG("Assignment Operator")
				if (*this == x)
					return *this;

				this->clear();
				this->_alloc = x._alloc;
				this->_begin = x._begin;
				this->_end = x._end;
				this->_capacity = x._capacity;
				
				return *this;
			}
			
			/*
			** -- Iterators --
			*/
			// iterator				begin();
			// const_iterator			begin() const;
			// iterator				end();
			// const_iterator			end() const;
			// reverse_iterator		rbegin();
			// const_reverse_iterator	rbegin() const;
			// reverse_iterator		rend();
			// const_reverse_iterator	rend() const;

			/*
			** -- Capacity --
			*/
			size_type		size() const     { return _end - _begin; }
			size_type		max_size() const { return allocator_type().max_size(); }
			size_type		capacity() const { return _capacity - _begin; }
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
						_capacity = _begin + n;
						_end = _begin;
						while (tmp_begin != old_end)
						{
							_alloc.construct(_end, *tmp_begin);
							++_end;
							++tmp_begin;
						}
						while (_end != _capacity)
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
					_capacity = _begin + n;
					_end = _begin;
					
					for (; tmp_begin != old_end; ++_end, ++tmp_begin)
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
			// template <class InputIterator>
			// void			assign(InputIterator first, InputIterator last);
			
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
					_capacity = _begin + n;
					_end = _begin;

					for (; _end != _capacity; ++_end)
						_alloc.construct(_end, val);
					_alloc.deallocate(old_begin, old_capacity);
				}
			}
			
			void			push_back(const value_type &val)
			{	
				if (_end == _capacity)
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
			// template <class InputIterator>
			// void			insert(iterator position, InputIterator first, InputIterator last);
			// iterator		erase(iterator position);
			// iterator		erase(iterator first, iterator last);
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




		////////////////////////////////////////////////////////////////////////
		// TO REMOVE
		////////////////////////////////////////////////////////////////////////
		void			_print(void) const
		{
			pointer			b = _begin;
			const size_type	sz = size();

			for (size_type i = 0; i < sz; ++i)
			{
				std::cout << *b++ << std::endl;
			}
		}
		////////////////////////////////////////////////////////////////////////
		// END - TO REMOVE
		////////////////////////////////////////////////////////////////////////





		private:
			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			pointer			_capacity;
		
	}; /* class vector */

	/*
	** -- Non-member --
	*/
	template <class T, class Alloc>
	bool	operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		typename ft::vector<T>::const_iterator	left = lhs.begin();
		typename ft::vector<T>::const_iterator	left_end = lhs.end();
		typename ft::vector<T>::const_iterator	right = rhs.begin();
		typename ft::vector<T>::const_iterator	right_end = rhs.end();

		for ( ; left != left_end ; ++left, ++right)
		{
			if (right == right_end || left != right)
				return false;
		}
		return true;
	}
	
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		return !(lhs == rhs);
	}
	
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);

	template <class T, class Alloc>
	void	swap(vector<T,Alloc> &x, vector<T,Alloc> &y)
	{
		x.swap(y);
	}

} /* namespace ft */
