/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:51:47 by besellem          #+#    #+#             */
/*   Updated: 2021/09/13 15:58:48 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <memory>
#include <vector>
#include <iostream>

int	main(int ac, char **av)
{
	// {
	// 	std::vector<int>::size_type	sz;
	// 	std::vector<int>			foo;

	// 	sz = foo.capacity();
	// 	std::cout << "making foo grow: " << sz << "\n";
	// 	for (int i = 0; i < 100; ++i)
	// 	{
	// 		std::cout << "pushing " << i << std::endl;
	// 		foo.push_back(i);
	// 		if (sz!=foo.capacity())
	// 		{
	// 			sz = foo.capacity();
	// 			std::cout << "capacity changed: " << sz << std::endl;
	// 		}
	// 	}
	// }
	
	std::vector<int>			real(10);
	ft::vector<int>				mine(10);


	std::vector<int>::iterator	real_it;
	std::vector<int>::iterator	real_ite;

	std::cout << "/////////////////////////////////////// " GREEN "REAL" CLR_COLOR << std::endl;
	// real.reserve(1);
	std::cout << "real size -> " << real.size() << std::endl;
	std::cout << "real capacity -> " << real.capacity() << std::endl;
	// std::cout << "real -> front: " << real.front() << std::endl;
	real.push_back(10);
	std::cout << "real capacity after push -> " << real.capacity() << std::endl;
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();
	// real.pop_back();

	for (real_it = real.begin(), real_ite = real.end(); real_it != real_ite ; ++real_it)
		std::cout << *real_it << std::endl;
	std::cout << std::endl;


	std::cout << "/////////////////////////////////////// " GREEN "MINE" CLR_COLOR << std::endl;
	// mine.reserve(1);
	std::cout << "mine size -> " << mine.size() << std::endl;
	std::cout << "mine capacity -> " << mine.capacity() << std::endl;
	// std::cout << "mine -> front: " << mine.front() << std::endl;
	mine.push_back(10);
	std::cout << "mine capacity after push -> " << mine.capacity() << std::endl;
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	// mine.pop_back();
	mine._print();
	
	// std::vector<int>::iterator	is;

	std::allocator<int>		ptr;
	// int	*p = ptr.allocate(0);
	// std::cout << "max_size: " << ptr.max_size() << std::endl;
	
	return 0;
}
