/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:30 by besellem          #+#    #+#             */
/*   Updated: 2021/09/03 06:02:40 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <memory>

namespace ft
{
	template < class T, class Alloc = allocator<T>>
	class vector
	{

		public:
			explicit vector(const allocator_type& alloc = allocator_type());	
			explicit vector(size_type n, const value_type &val = value_type(),
							const allocator_type &alloc = allocator_type());
			template <class InputIterator>
			vector(InputIterator first, InputIterator last,
					const allocator_type &alloc = allocator_type());
			vector(const vector &x);
			~vector();
			
			vector &	operator=(const vector &x);
		
			/*
			** -- Iterators --
			*/
			iterator				begin();
			const_iterator			begin() const;
			iterator				end();
			const_iterator			end() const;
			reverse_iterator		rbegin();
			const_reverse_iterator	rbegin() const;
			reverse_iterator		rend();
			const_reverse_iterator	rend() const;

			/*
			** -- Capacity --
			*/
			size_type		size() const;
			size_type		max_size() const;
			void			resize(size_type n, value_type val = value_type());
			size_type		capacity() const;
			bool			empty() const;
			void			reserve(size_type n);

			/*
			** -- Element access --
			*/
			reference		operator[] (size_type n);
			const_reference	operator[] (size_type n) const;
			reference		at(size_type n);
			const_reference	at(size_type n) const;
			reference 		front();
			const_reference	front() const;
			reference		back();
			const_reference	back() const;

			/*
			** -- Modifiers --
			*/
			template <class InputIterator>
  			void			assign(InputIterator first, InputIterator last);
			void			assign(size_type n, const value_type &val);
			void			push_back(const value_type& val);
			void			pop_back();
			iterator		insert(iterator position, const value_type &val);
    		void			insert(iterator position, size_type n, const value_type &val);
			template <class InputIterator>
			void			insert(iterator position, InputIterator first, InputIterator last);
			iterator		erase(iterator position);
			iterator		erase(iterator first, iterator last);
			void			swap(vector &x);
			void			clear();

			/*
			** -- Allocator --
			*/
			allocator_type	get_allocator() const;

		private:
			/* data */
		
	};

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
