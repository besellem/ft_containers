/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.push_back.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 18:03:59 by besellem          #+#    #+#             */
/*   Updated: 2021/10/13 23:19:58 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

int main ()
{
	__NAMESPACE__::vector<int> myvector;

	std::cout << "Please enter some integers (enter 0 to end):\n";

	for (int i = 0; i < 1000000; ++i)
		myvector.push_back (i);
	
	std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

	return 0;
}
