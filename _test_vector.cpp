/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _test_vector.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:31:17 by besellem          #+#    #+#             */
/*   Updated: 2021/09/26 17:36:31 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef STD
	#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif

# define RED       "\e[1;31m"
# define GREEN     "\e[1;33m"
# define BLUE      "\e[1;34m"
# define CLR_COLOR "\e[0m"

int	main(void)
{
	std::cout << BLUE "PUSH_BACK TEST:" CLR_COLOR << std::endl;
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

	return 0;
}
