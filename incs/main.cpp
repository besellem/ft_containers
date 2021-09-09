/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:51:47 by besellem          #+#    #+#             */
/*   Updated: 2021/09/10 00:36:13 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <memory>
#include <vector>
#include <iostream>

int	main(int ac, char **av)
{
	std::vector<std::string>	real(0);
	std::cout << "real: " << &real << std::endl;
	std::cout << "real -> " << real.size() << std::endl;

	// std::allocator<std::string>		ptr;
	
	// std::cout << "max_size: " << ptr.max_size() << std::endl;

	ft::vector<int>		mine(0);
	std::cout << "mine: " << &mine << std::endl;
	std::cout << "mine -> " << mine.size() << std::endl;

	return 0;
}
