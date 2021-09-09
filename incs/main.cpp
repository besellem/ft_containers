/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:51:47 by besellem          #+#    #+#             */
/*   Updated: 2021/09/10 00:55:08 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <memory>
#include <vector>
#include <iostream>

int	main(int ac, char **av)
{
	std::vector<int>	real(0);
	std::cout << "real: " << &real << std::endl;
	std::cout << "real -> " << real.size() << std::endl;
	real.push_back(10);
	std::cout << "real -> front: " << real.front() << std::endl;

	ft::vector<int>		mine(0);
	std::cout << "mine: " << &mine << std::endl;
	std::cout << "mine -> " << mine.size() << std::endl;
	// mine.push_back(10);
	std::cout << "mine -> front: " << mine.front() << std::endl;

	// std::allocator<int>		ptr;
	// std::cout << "max_size: " << ptr.max_size() << std::endl;
	
	return 0;
}
