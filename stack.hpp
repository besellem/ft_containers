/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:33 by besellem          #+#    #+#             */
/*   Updated: 2021/10/03 21:07:16 by besellem         ###   ########.fr       */
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
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

	public:
		explicit stack(container_type const &cont = Container()) : _c(cont)
		{}
		
		~stack() {}

		bool			empty() const               { return _c.empty(); }
		size_type		size() const                { return _c.size(); }
		reference		top()                       { return _c.back(); }
		const_reference	top() const                 { return _c.back(); }
		void			push(const value_type& val) { return _c.push_back(val); }
		void			pop()                       { return _c.pop_back(); }
	
		stack &			operator=(stack const &x)
		{
			this->_c = x._c;
			return *this;
		}

		template <class _Tp, class _Cont>
		friend bool		operator==(const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs._c == rhs._c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator!=(const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs._c != rhs._c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator< (const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs._c <  rhs._c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator<=(const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs._c <= rhs._c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator> (const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs._c >  rhs._c; }
		
		template <class _Tp, class _Cont>
		friend bool		operator>=(const stack<_Tp,_Cont>& lhs,
								   const stack<_Tp,_Cont>& rhs)
		{ return lhs._c >= rhs._c; }
	
	protected:
		container_type	_c;
	
}; /* class stack */


_END_NAMESPACE_FT

#endif /* define STACK_HPP */
