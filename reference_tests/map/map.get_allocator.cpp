/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.get_allocator.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:59:31 by besellem          #+#    #+#             */
/*   Updated: 2021/10/14 10:07:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

int main ()
{
	int psize;
	__NAMESPACE__::map<char,int> mymap;
	__NAMESPACE__::pair<const char,int>* p;

	// allocate an array of 5 elements using mymap's allocator:
	p=mymap.get_allocator().allocate(5);

	// assign some values to array
	psize = sizeof(__NAMESPACE__::map<char,int>::value_type)*5;

	std::cout << "The allocated array has a size of " << psize << " bytes.\n";

	mymap.get_allocator().deallocate(p,5);

	return 0;
}
