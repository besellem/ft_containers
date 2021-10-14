/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.constructor.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 23:27:30 by besellem          #+#    #+#             */
/*   Updated: 2021/10/13 23:36:26 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"
#include <deque>

int main ()
{
	std::deque<int> mydeque (3,100);          // deque with 3 elements
	__NAMESPACE__::vector<int> myvector (2,200);        // vector with 2 elements

	__NAMESPACE__::stack<int> first;                    // empty stack
	__NAMESPACE__::stack<int, std::deque<int> > second (mydeque);         // stack initialized to copy of deque

	__NAMESPACE__::stack<int,__NAMESPACE__::vector<int> > third;  // empty stack using vector
	__NAMESPACE__::stack<int,__NAMESPACE__::vector<int> > fourth (myvector);

	std::cout << "size of first: " << first.size() << '\n';
	std::cout << "size of second: " << second.size() << '\n';
	std::cout << "size of third: " << third.size() << '\n';
	std::cout << "size of fourth: " << fourth.size() << '\n';

	return 0;
}
