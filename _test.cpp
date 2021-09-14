/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:51:47 by besellem          #+#    #+#             */
/*   Updated: 2021/09/14 15:32:43 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include <memory>
#include <vector>
// #include <iterator>
#include <iostream>

int	main(__unused int ac, __unused char **av)
{
	/* PUSH_BACK */
	std::cout << BLUE "PUSH_BACK TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>::size_type	sz;
		std::vector<int>			foo;

		sz = foo.capacity();
		std::cout << "making foo grow: " << std::endl;
		std::cout << "capacity:         [" << sz << "]" << std::endl;
		for (int i = 0; i < 100; ++i)
		{
			// std::cout << "pushing " << i << std::endl;
			foo.push_back(i);
			if (sz != foo.capacity())
			{
				sz = foo.capacity();
				std::cout << "capacity changed: [" << sz << "]" << std::endl;
			}
		}
		std::cout << "front: " << foo.front() << std::endl;
		std::cout << "back:  " << foo.back() << std::endl;
		std::cout << std::endl;
	}

	{
		ft::vector<int>::size_type	sz;
		ft::vector<int>				foo;

		sz = foo.capacity();
		std::cout << "making foo grow: " << std::endl;
		std::cout << "capacity:         [" << sz << "]" << std::endl;
		for (int i = 0; i < 100; ++i)
		{
			// std::cout << "pushing " << i << std::endl;
			foo.push_back(i);
			if (sz != foo.capacity())
			{
				sz = foo.capacity();
				std::cout << "capacity changed: [" << sz << "]" << std::endl;
			}
		}
		std::cout << "front: " << foo.front() << std::endl;
		std::cout << "back:  " << foo.back() << std::endl;
		std::cout << std::endl;
	}


	/* RESIZE && operator[] */
	std::cout << BLUE "RESIZE TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>	vec;

		for (int i = 1; i < 10; ++i) // set some initial content:
			vec.push_back(i);

		vec.resize(5);
		vec.resize(8, 100);
		vec.resize(12);

		std::cout << "std::vector contains:";
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << ' ' << vec[i];
		std::cout << std::endl;
	}

	{
		ft::vector<int>		vec;

		for (int i = 1; i < 10; ++i) // set some initial content:
			vec.push_back(i);

		vec.resize(5);
		vec.resize(8, 100);
		vec.resize(12);

		std::cout << "ft::vector contains: ";
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << ' ' << vec[i];
		std::cout << std::endl;
		std::cout << std::endl;
	}

	/* ASSIGN */
	std::cout << BLUE "ASSIGN TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>	vec(10);
		const size_t		cap = vec.capacity();
		
		vec.assign(15, 42);
		std::cout << "std::vector capacity: old[" << cap << "] new[" << vec.capacity() << "]" << std::endl;
		std::cout << "std::vector contains:";
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << ' ' << vec[i];
		std::cout << std::endl;
	}

	{
		ft::vector<int>		vec(10);
		const size_t		cap = vec.capacity();
		
		vec.assign(15, 42);
		std::cout << "ft::vector capacity:  old[" << cap << "] new[" << vec.capacity() << "]" << std::endl;
		std::cout << "ft::vector contains: ";
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << ' ' << vec[i];
		std::cout << std::endl;
		std::cout << std::endl;
	}

	/* COPY CONSTRUCTOR */
	// std::cout << BLUE "COPY CONSTRUCTOR TEST:" CLR_COLOR << std::endl;
	// {
	// 	std::vector<int>	vec;

	// 	for (int i = 1; i < 10; ++i) // set some initial content:
	// 		vec.push_back(i);

	// 	vec.resize(5);
	// 	vec.resize(8, 100);
	// 	vec.resize(12);

	// 	std::vector<int>	cpy(vec);

	// 	std::cout << "std::vector contains:";
	// 	for (size_t i = 0; i < cpy.size(); ++i)
	// 		std::cout << ' ' << cpy[i];
	// 	std::cout << std::endl;
	// }

	// {
	// 	ft::vector<int>	vec;

	// 	for (int i = 1; i < 10; ++i) // set some initial content:
	// 		vec.push_back(i);

	// 	vec.resize(5);
	// 	vec.resize(8, 100);
	// 	vec.resize(12);

	// 	ft::vector<int>	cpy(vec);

	// 	std::cout << "std::vector contains:";
	// 	for (size_t i = 0; i < cpy.size(); ++i)
	// 		std::cout << ' ' << cpy[i];
	// 	std::cout << std::endl;
	// 	std::cout << std::endl;
	// }

	/* operator= */
	// std::cout << (vec == ft::vector<int>(19)) << std::endl;


	std::vector<int>			real(2);
	ft::vector<int>				mine(2);


	std::vector<int>::iterator	real_it;
	std::vector<int>::iterator	real_ite;

	std::cout << "/////////////////////////////////////// " GREEN "REAL" CLR_COLOR << std::endl;
	std::cout << "real size ->            [" << real.size() << "]" << std::endl;
	std::cout << "real cpty ->            [" << real.capacity() << "]" << std::endl;
	real.push_back(10);
	std::cout << "real cpty after push -> [" << real.capacity() << "]" << std::endl;

	for (real_it = real.begin(), real_ite = real.end(); real_it != real_ite ; ++real_it)
		std::cout << *real_it << std::endl;
	std::cout << std::endl;


	std::cout << "/////////////////////////////////////// " GREEN "MINE" CLR_COLOR << std::endl;
	std::cout << "mine size ->            [" << mine.size() << "]" << std::endl;
	std::cout << "mine cpty ->            [" << mine.capacity() << "]" << std::endl;
	mine.push_back(10);
	std::cout << "mine cpty after push -> [" << mine.capacity() << "]" << std::endl;
	mine._print();
	
	// std::vector<int>::iterator	is;

	std::allocator<int>		ptr;
	// int	*p = ptr.allocate(0);
	// std::cout << "max_size: " << ptr.max_size() << std::endl;
	
	return 0;
}
