/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:33 by besellem          #+#    #+#             */
/*   Updated: 2021/09/01 14:03:25 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <deque>

namespace ft
{
	template< class T, class Container = std::deque<T> >
	class stack
	{

		public:
			explicit stack(Container const &cont = Container());
			~stack();

			typedef Container					container_type;
			typedef Container::value_type		value_type;
			typedef Container::size_type		size_type;
			typedef Container::reference		reference;
			typedef Container::const_reference	const_reference;

			reference		top();
			const_reference	top() const;
			bool			empty() const;
		
		public:
			stack &		operator=(stack const &other);
		
		private:
			stack(void);
		
	};

} /* namespace ft */
