/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.insert.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:59:34 by besellem          #+#    #+#             */
/*   Updated: 2021/10/14 10:07:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

int main ()
{
	__NAMESPACE__::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( __NAMESPACE__::pair<char,int>('a',100) );
	mymap.insert ( __NAMESPACE__::pair<char,int>('z',200) );

	__NAMESPACE__::pair<__NAMESPACE__::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( __NAMESPACE__::pair<char,int>('z',500) );
	if (ret.second==false) {
		std::cout << "element 'z' already existed";
		std::cout << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	__NAMESPACE__::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, __NAMESPACE__::pair<char,int>('b',300));  // max efficiency inserting
	mymap.insert (it, __NAMESPACE__::pair<char,int>('c',400));  // no max efficiency inserting

	// third insert function version (range insertion):
	__NAMESPACE__::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	std::cout << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	std::cout << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';

	return 0;
}
