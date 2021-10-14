/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.swap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:35:24 by besellem          #+#    #+#             */
/*   Updated: 2021/10/14 10:43:09 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

int main ()
{
	int myints[]={12,75,10,32,20,25};
	__NAMESPACE__::set<int> first (myints,myints+3);     // 10,12,75
	__NAMESPACE__::set<int> second (myints+3,myints+6);  // 20,25,32

	first.swap(second);

	std::cout << "first contains:";
	for (__NAMESPACE__::set<int>::iterator it=first.begin(); it!=first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (__NAMESPACE__::set<int>::iterator it=second.begin(); it!=second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}