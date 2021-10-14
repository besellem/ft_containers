/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.iterator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:34:18 by besellem          #+#    #+#             */
/*   Updated: 2021/10/14 10:43:09 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

int main ()
{
	int myints[] = {75,23,65,42,13};
	__NAMESPACE__::set<int> myset (myints,myints+5);

	std::cout << "myset contains:";
	for (__NAMESPACE__::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	return 0;
}