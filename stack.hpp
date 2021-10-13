/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:33 by besellem          #+#    #+#             */
/*   Updated: 2021/10/13 15:49:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"


_BEGIN_NAMESPACE_FT

template< class T, class Container = ft::vector<T> >
class stack
{
	
	public:
		typedef Container                                       container_type;
		typedef typename Container::value_type                  value_type;
		typedef typename Container::size_type                   size_type;
		typedef typename Container::reference                   reference;
		typedef typename Container::const_reference             const_reference;


	public:
		explicit stack(container_type const &cont = Container()) : c(cont)
		{}
		
		~stack() {}

		bool			empty()               const { return c.empty(); }
		size_type		size()                const { return c.size(); }
		reference		top()                       { return c.back(); }
		const_reference	top()                 const { return c.back(); }
		
		void			push(const value_type& val) { return c.push_back(val); }
		void			pop()                       { return c.pop_back(); }
	
		stack &			operator=(stack const &x)
		{
			if (this == &x)
				return *this;
			
			c = x.c;
			return *this;
		}

		template <class _Tp, class _Cont>
		friend bool		operator==(const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs.c == rhs.c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator!=(const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs.c != rhs.c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator< (const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs.c <  rhs.c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator<=(const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs.c <= rhs.c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator> (const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs.c >  rhs.c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator>=(const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs.c >= rhs.c; }
	
	
	protected:
		container_type		c;
	
}; /* class stack */


_END_NAMESPACE_FT

#endif /* define STACK_HPP */
