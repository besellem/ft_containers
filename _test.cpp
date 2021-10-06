/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 23:51:47 by besellem          #+#    #+#             */
/*   Updated: 2021/10/06 23:00:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "stack.hpp"
#include "_utils/utils.hpp"
#include "map.hpp"
#include "_utils/RedBlackTree.hpp"

#include <vector>
#include <stack>
#include <map>

#include <memory>
#include <iostream>
#include <iomanip>
#include <mach/boolean.h>


# define RED       "\e[1;31m"
# define GREEN     "\e[1;33m"
# define BLUE      "\e[1;34m"
# define CLR_COLOR "\e[0m"

#ifndef DEBUG
# define DEBUG TRUE
#endif

#if (DEBUG == FALSE)
# define LOG(m) std::cout << RED << __FILE__ << ":" << __LINE__ << ": " CLR_COLOR << m << std::endl;
#else
# define LOG(m) ;
#endif


template <class T, class Alloc>
bool	operator==(std::vector<T,Alloc>& real, ft::vector<T,Alloc>& mine)
{
	bool										check = true;
	typename std::vector<T, Alloc>::iterator	real_it(real.begin());
	typename ft::vector<T, Alloc>::iterator		my_it(mine.begin());

	// compare size
	if (real.size() != mine.size())
	{
		std::cerr << "size ->     [" << real.size() << "] [" << mine.size() << "]\n";
		check = false;
	}

	// compare capacity
	if (real.capacity() != mine.capacity())
	{
		std::cerr << "capacity -> [" << real.capacity() << "] [" << mine.capacity() << "]\n";
		check = false;
	}

	// compare max_size
	if (real.max_size() != mine.max_size())
	{
		std::cerr << "max_size -> [" << real.max_size() << "] [" << mine.max_size() << "]\n";
		check = false;
	}

	// compare emptiness
	if (real.empty() != mine.empty())
	{
		std::cerr << "empty ->    [" << real.empty() << "] [" << mine.empty() << "]\n";
		check = false;
	}

	// compare content
	for ( ; real_it != real.end(); ++real_it, ++my_it)
	{
		if (my_it == mine.end() || *real_it != *my_it)
		{
			std::cerr << "iterator -> [" << *real_it << "] [" << *my_it << "]\n";
			check = false;
			break ;
		}
	}
	
	
	if (check) std::cout << "✅" << std::endl;
	else       std::cout << "❌" << std::endl;

	return check;
}

void	other_vector_tests(void)
{
	std::cout << BLUE "PUSH_BACK TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>::size_type	sz;
		std::vector<int>			foo;

		sz = foo.capacity();
		std::cout << "making foo grow: " << std::endl;
		std::cout << "capacity:         [" << sz << "]" << std::endl;
		for (int i = 0; i < 100; ++i)
		{
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

		for (int i = 1; i < 10; ++i)
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

		for (int i = 1; i < 10; ++i)
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
		const size_t		sz = vec.size();
		
		vec.assign(15, 42);
		std::cout << "std::vector capacity: old[" << cap << "] new[" << vec.capacity() << "]" << std::endl;
		std::cout << "std::vector size:     old[" << sz << "] new[" << vec.size() << "]" << std::endl;
		std::cout << "std::vector contains:";
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << ' ' << vec[i];
		std::cout << std::endl;
	}

	{
		ft::vector<int>		vec(10);
		const size_t		cap = vec.capacity();
		const size_t		sz = vec.size();
		
		vec.assign(15, 42);
		std::cout << "ft::vector capacity:  old[" << cap << "] new[" << vec.capacity() << "]" << std::endl;
		std::cout << "ft::vector size:      old[" << sz << "] new[" << vec.size() << "]" << std::endl;
		std::cout << "ft::vector contains: ";
		for (size_t i = 0; i < vec.size(); ++i)
			std::cout << ' ' << vec[i];
		std::cout << std::endl;
		std::cout << std::endl;
	}

	/* ITERATOR */
	std::cout << BLUE "ITERATOR TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>	vec;

		for (int i = 1; i < 10; ++i)
			vec.push_back(i);
		
		std::vector<int>::iterator	it(vec.begin());
		
		std::cout << "std::vector contains:";
		for ( ; it != vec.end() ; ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
	}
	
	{
		ft::vector<int>		vec;

		for (int i = 1; i < 10; ++i)
			vec.push_back(i);

		ft::vector<int>::iterator	it(vec.begin());
		
		std::cout << "ft::vector contains: ";
		for ( ; it != vec.end() ; ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << std::endl;
	}

	/* REVERSE ITERATOR */
	std::cout << BLUE "REVERSE ITERATOR TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>	vec;

		for (int i = 1; i < 10; ++i)
			vec.push_back(i);
		
		std::vector<int>::reverse_iterator	it(vec.rbegin());
		
		std::cout << "std::vector contains:";
		for ( ; it != vec.rend() ; ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
	}
	
	{
		ft::vector<int>		vec;

		for (int i = 1; i < 10; ++i)
			vec.push_back(i);

		ft::vector<int>::reverse_iterator	it(vec.rbegin());
		
		std::cout << "ft::vector contains: ";
		for ( ; it != vec.rend() ; ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << std::endl;
	}

	/* AT */
	std::cout << BLUE "AT TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int> vct(7);

		for (unsigned long int i = 0; i < vct.size(); ++i)
		{
			vct.at(i) = (vct.size() - i) * 3;
			std::cout << "vct.at(): " << vct.at(i) << " | ";
			std::cout << "vct[]: " << vct[i] << std::endl;
		}

		std::vector<int> const vct_c(vct);

		std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
		std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

		try {
			vct.at(10) = 42;
		}
		catch (std::out_of_range &e) {
			std::cout << "Catch out_of_range exception!" << std::endl;
		}
		catch (std::exception &e) {
			std::cout << "Catch exception: " << e.what() << std::endl;
		}
	}
	
	{
		ft::vector<int> vct(7);

		for (unsigned long int i = 0; i < vct.size(); ++i)
		{
			vct.at(i) = (vct.size() - i) * 3;
			std::cout << "vct.at(): " << vct.at(i) << " | ";
			std::cout << "vct[]: " << vct[i] << std::endl;
		}

		ft::vector<int> const vct_c(vct);

		std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
		std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

		try {
			vct.at(10) = 42;
		}
		catch (std::out_of_range &e) {
			std::cout << "Catch out_of_range exception!" << std::endl;
		}
		catch (std::exception &e) {
			std::cout << "Catch exception: " << e.what() << std::endl;
		}
		std::cout << std::endl;
	}

	/* ERASE */
	std::cout << BLUE "ERASE TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>	vec;

		for (int i = 1; i <= 10; ++i)
			vec.push_back(i);

		std::cout << "ptr returned: " << *vec.erase(vec.begin() + 5) << std::endl;
		std::cout << "ptr returned: " << *vec.erase(vec.begin(), vec.begin() + 3) << std::endl;

		std::vector<int>::iterator	it(vec.begin());
		
		std::cout << "std::vector contains:";
		for ( ; it != vec.end() ; ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
	}

	{
		ft::vector<int>		vec;

		for (int i = 1; i <= 10; ++i)
			vec.push_back(i);

		std::cout << "ptr returned: " << *vec.erase(vec.begin() + 5) << std::endl;
		std::cout << "ptr returned: " << *vec.erase(vec.begin(), vec.begin() + 3) << std::endl;

		ft::vector<int>::iterator	it(vec.begin());
		
		std::cout << "ft::vector contains: ";
		for ( ; it != vec.end() ; ++it)
			std::cout << " " << *it;
		std::cout << std::endl;
		std::cout << std::endl;
	}


	/* COMPARISIONS */
	std::cout << BLUE "COMPARISIONS TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>	vec1;
		std::vector<int>	vec2;

		for (int i = 0; i < 10; ++i)
		{
			vec1.push_back(i);
			vec2.push_back(i);
		}

		std::cout << "real before -> (vec1 == vec2): " << (vec1 == vec2) << std::endl;
		std::cout << "real before -> (vec1 >= vec2): " << (vec1 >= vec2) << std::endl;
		std::cout << "real before -> (vec1 <= vec2): " << (vec1 <= vec2) << std::endl;
		std::cout << "real before -> (vec1 >  vec2): " << (vec1 > vec2) << std::endl;
		std::cout << "real before -> (vec1 <  vec2): " << (vec1 < vec2) << std::endl;
		vec2.push_back(42);
		std::cout << "real after  -> (vec1 == vec2): " << (vec1 == vec2) << std::endl;
		std::cout << "real after  -> (vec1 >= vec2): " << (vec1 >= vec2) << std::endl;
		std::cout << "real after  -> (vec1 <= vec2): " << (vec1 <= vec2) << std::endl;
		std::cout << "real after  -> (vec1 >  vec2): " << (vec1 > vec2) << std::endl;
		std::cout << "real after  -> (vec1 <  vec2): " << (vec1 < vec2) << std::endl;
		std::cout << std::endl;
	}
	
	{
		ft::vector<int>		vec1;
		ft::vector<int>		vec2;

		for (int i = 0; i < 10; ++i)
		{
			vec1.push_back(i);
			vec2.push_back(i);
		}

		std::cout << "mine before -> (vec1 == vec2): " << (vec1 == vec2) << std::endl;
		std::cout << "mine before -> (vec1 >= vec2): " << (vec1 >= vec2) << std::endl;
		std::cout << "mine before -> (vec1 <= vec2): " << (vec1 <= vec2) << std::endl;
		std::cout << "mine before -> (vec1 >  vec2): " << (vec1 > vec2) << std::endl;
		std::cout << "mine before -> (vec1 <  vec2): " << (vec1 < vec2) << std::endl;
		vec2.push_back(42);
		std::cout << "mine after  -> (vec1 == vec2): " << (vec1 == vec2) << std::endl;
		std::cout << "mine after  -> (vec1 >= vec2): " << (vec1 >= vec2) << std::endl;
		std::cout << "mine after  -> (vec1 <= vec2): " << (vec1 <= vec2) << std::endl;
		std::cout << "mine after  -> (vec1 >  vec2): " << (vec1 > vec2) << std::endl;
		std::cout << "mine after  -> (vec1 <  vec2): " << (vec1 < vec2) << std::endl;
		std::cout << std::endl;
	}


	/* MISC */
	std::cout << BLUE "MISC TEST:" CLR_COLOR << std::endl;
	{
		std::vector<int>	real(2);

		std::cout << "real size ->            [" << real.size() << "]" << std::endl;
		std::cout << "real cpty ->            [" << real.capacity() << "]" << std::endl;
		real.push_back(10);
		std::cout << "real cpty after push -> [" << real.capacity() << "]" << std::endl;

		std::vector<int>::iterator	real_it(real.begin());
		
		std::cout << "std::vector contains:";
		for ( ; real_it != real.end() ; ++real_it)
			std::cout << " " << *real_it;
		std::cout << std::endl;
		std::cout << std::endl;
	}

	{
		ft::vector<int>		mine(2);
		
		std::cout << "mine size ->            [" << mine.size() << "]" << std::endl;
		std::cout << "mine cpty ->            [" << mine.capacity() << "]" << std::endl;
		mine.push_back(10);
		std::cout << "mine cpty after push -> [" << mine.capacity() << "]" << std::endl;

		ft::vector<int>::iterator	mine_it(mine.begin());
		
		std::cout << "ft::vector contains: ";
		for ( ; mine_it != mine.end() ; ++mine_it)
			std::cout << " " << *mine_it;
		std::cout << std::endl;
	}
}

void	test_vector(void)
{
	std::cout << GREEN "VECTOR" CLR_COLOR << std::endl;
	std::vector<int>	real;
	ft::vector<int>		mine;
	size_t				count = 0;


	printf("%02zu: ", count++);
	operator==(real, mine);
	
	printf("%02zu: ", count++);
	real.resize(1340);
	mine.resize(1340);
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.resize(5);
	mine.resize(5);
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.push_back(42);
	mine.push_back(42);
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.resize(0);
	mine.resize(0);
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.reserve(358);
	mine.reserve(358);
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.reserve(358);
	mine.reserve(358);
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.assign(100, 42);
	mine.assign(100, 42);
	operator==(real, mine);
	
	printf("%02zu: ", count++);
	real.assign(14, 345);
	mine.assign(14, 345);
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.erase(real.begin());
	mine.erase(mine.begin());
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.erase(real.end() - 1);
	mine.erase(mine.end() - 1);
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.erase(real.begin(), real.end());
	mine.erase(mine.begin(), mine.end());
	operator==(real, mine);

	printf("%02zu: ", count++);
	real.clear();
	mine.clear();
	operator==(real, mine);

	printf("%02zu: ", count++);
	real = std::vector<int>(10);
	mine = ft::vector<int>(10);
	real.assign(15, 42);
	mine.assign(15, 42);
	operator==(real, mine);


	// other_vector_tests();
}


int		main(void)
{
	// test_vector();

	ft::RedBlackTree<ft::pair<int, int> >	bst;

	bst.insert( ft::make_pair<int, int>(1, 10) );
	bst.insert( ft::make_pair<int, int>(2, 20) );
	bst.insert( ft::make_pair<int, int>(3, 30) );
	bst.insert( ft::make_pair<int, int>(4, 40) );
	bst.insert( ft::make_pair<int, int>(5, 50) );
	bst.insert( ft::make_pair<int, int>(6, 60) );
	bst.print();

	ft::map<char, int>		mymap;

	std::cout << "size: " << mymap.max_size() << std::endl;
	// std::map<char, int>::iterator			it;

	// insert some values:
	// mymap.insert( ft::make_pair<char, int>('a', 10) );
	// mymap['a'] = 10;
	// mymap['b'] = 20;
	// mymap['c'] = 30;
	// mymap['d'] = 40;
	// mymap['e'] = 50;
	// mymap['f'] = 60;
	
	// for (it = mymap.begin() ; it != mymap.end() ; ++it)
	// {
	// 	std::cout << it->first << " " << it->second << std::endl;
	// 	// mymap.erase(it);
	// }


	/*
	  b 
	a   d
       c  e
            f
	*/

	// for (it = mymap.begin() ; it != mymap.end() ; ++it)
	// {
	// 	std::cout << it->first << " " << it->second << std::endl;
	// }
  
	return 0;
}
