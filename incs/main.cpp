/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:51:47 by besellem          #+#    #+#             */
/*   Updated: 2021/09/12 15:25:34 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <memory>
#include <vector>
#include <iostream>

int	main(int ac, char **av)
{
	std::vector<int>			real(1);
	ft::vector<int>				mine(1);

	std::vector<int>::iterator	real_it;
	std::vector<int>::iterator	real_ite;

	// real.push_back(1);
	// real.push_back(2);

	// real.reserve(1);
	std::cout << "real size -> " << real.size() << std::endl;
	std::cout << "real capacity -> " << real.capacity() << std::endl;
	real.push_back(10);
	std::cout << "real -> front: " << real.front() << std::endl;

	for (real_it = real.begin(), real_ite = real.end(); real_it != real_ite ; ++real_it)
		std::cout << *real_it << std::endl;
	std::cout << std::endl;

	// mine.reserve(20);
	std::cout << "mine size -> " << mine.size() << std::endl;
	std::cout << "mine capacity -> " << mine.capacity() << std::endl;
	// mine.push_back(10);
	mine._print();
	std::cout << "mine -> front: " << mine.front() << std::endl;

	std::allocator<int>		ptr;
	// std::cout << "max_size: " << ptr.max_size() << std::endl;
	
	return 0;
}
