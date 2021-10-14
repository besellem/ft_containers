/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.constructor.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:44:14 by besellem          #+#    #+#             */
/*   Updated: 2021/10/13 23:22:48 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

int	main(void)
{
	// constructors used in the same order as described above:
	__NAMESPACE__::vector<int>	first;                                // empty vector of ints
	__NAMESPACE__::vector<int>	second(4,100);                       // four ints with value 100
	__NAMESPACE__::vector<int>	third(second.begin(),second.end());  // iterating through second
	__NAMESPACE__::vector<int>	fourth(third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	__NAMESPACE__::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

	std::cout << "The contents of fifth are:";
	for (__NAMESPACE__::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
