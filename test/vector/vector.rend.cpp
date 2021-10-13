/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.rend.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:04:07 by besellem          #+#    #+#             */
/*   Updated: 2021/10/13 18:12:52 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

int main ()
{
	__NAMESPACE__::vector<int> myvector (5);  // 5 default-constructed ints

	__NAMESPACE__::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i=0;
	for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
	*rit = ++i;

	std::cout << "myvector contains:";
	for (__NAMESPACE__::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}
