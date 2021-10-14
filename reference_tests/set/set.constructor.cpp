/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.constructor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:34:28 by besellem          #+#    #+#             */
/*   Updated: 2021/10/14 10:43:09 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const int& lhs, const int& rhs) const
  {return lhs<rhs;}
};

int main ()
{
	__NAMESPACE__::set<int> first;                           // empty set of ints

	int myints[]= {10,20,30,40,50};
	__NAMESPACE__::set<int> second (myints,myints+5);        // range

	__NAMESPACE__::set<int> third (second);                  // a copy of second

	__NAMESPACE__::set<int> fourth (second.begin(), second.end());  // iterator ctor.

	__NAMESPACE__::set<int,classcomp> fifth;                 // class as Compare

	bool(*fn_pt)(int,int) = fncomp;
	__NAMESPACE__::set<int,bool(*)(int,int)> sixth (fn_pt);  // function pointer as Compare

	return 0;
}
