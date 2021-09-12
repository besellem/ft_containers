/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:30 by besellem          #+#    #+#             */
/*   Updated: 2021/09/12 15:31:21 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>

# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

#define RED       "\e[1;31m"
#define CLR_COLOR "\e[0m"

#define LOG std::cout << RED << __FILE__ << ":" << __LINE__ << ":" CLR_COLOR " Here" << std::endl;

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
			// typedef ...	iterator;
			// typedef ...	const_iterator;
			// typedef ...	reverse_iterator;
			// typedef ...	const_reverse_iterator;
			

		public:
			explicit vector(const allocator_type &alloc = allocator_type()) :
				_alloc(alloc),
				_begin(NULL),
				_end(NULL),
				_capacity(NULL)
			{}
			
			explicit vector(size_type n, const value_type &val = value_type(),
							const allocator_type &alloc = allocator_type()) :
				_alloc(alloc),
				_begin(NULL),
				_end(NULL),
				_capacity(NULL)
			{
				// if (n < 0)
				// 	throw std::length_error();
				_begin = _alloc.allocate(n);
				_end = _begin + n;
				_capacity = _end;
				LOG
			}
			
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type());
			
			vector(const vector &x)
			{
				*this = x;
			}
			
			~vector()
			{
				// clear();
				_alloc.deallocate(_begin, capacity());
			}
			
			vector &				operator=(const vector &x)
			{
				if (*this == x)
					return *this;

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

			void			resize(size_type n, value_type val = value_type());

			size_type		capacity() const { return _capacity - _begin; }

			bool			empty() const    { return size() == 0; }
			
			void			reserve(size_type n);

			/*
			** -- Element access --
			*/
			reference		operator[] (size_type n);
			const_reference	operator[] (size_type n) const;
			reference		at(size_type n);
			const_reference	at(size_type n) const;
			reference 		front()       { return *_begin; }
			const_reference	front() const { return *_begin; }
			reference		back()        { return *_end; }
			const_reference	back() const  { return *_end; }

			/*
			** -- Modifiers --
			*/
			// template <class InputIterator>
  			// void			assign(InputIterator first, InputIterator last);
			void			assign(size_type n, const value_type &val);
			void			push_back(const value_type &val);
			void			pop_back();
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
			
			void			clear();

			/*
			** -- Allocator --
			*/
			allocator_type	get_allocator() const { return allocator_type(); }




		////////////////////////////////////////////////////////////////////////
		// TO REMOVE
		////////////////////////////////////////////////////////////////////////
		void			_print(void) const
		{
			pointer	b = _begin;
			for (size_t i = 0; i < size(); ++i)
			{
				std::cout << *b << std::endl;
				++b;
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
	bool	operator==(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	
	template <class T, class Alloc>
	bool	operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	
	template <class T, class Alloc>
	bool	operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	
	template <class T, class Alloc>
	bool	operator<=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	
	template <class T, class Alloc>
	bool	operator>(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);
	
	template <class T, class Alloc>
	bool	operator>=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs);

	template <class T, class Alloc>
	void	swap(vector<T,Alloc> &x, vector<T,Alloc> &y);

} /* namespace ft */
