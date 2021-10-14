/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.assign_operator.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:34:16 by besellem          #+#    #+#             */
/*   Updated: 2021/10/14 10:43:09 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

int main ()
{
	int myints[]={ 12,82,37,64,15 };
	__NAMESPACE__::set<int> first (myints,myints+5);   // set with 5 ints
	__NAMESPACE__::set<int> second;                    // empty set

	second = first;                          // now second contains the 5 ints
	first = __NAMESPACE__::set<int>();                 // and first is empty

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	return 0;
}
