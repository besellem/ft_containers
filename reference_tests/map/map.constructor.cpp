/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.constructor.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 09:59:19 by besellem          #+#    #+#             */
/*   Updated: 2021/10/14 10:07:04 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../common.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main ()
{
	__NAMESPACE__::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	__NAMESPACE__::map<char,int> second (first.begin(),first.end());

	__NAMESPACE__::map<char,int> third (second);

	__NAMESPACE__::map<char,int,classcomp> fourth;                 // class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	__NAMESPACE__::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare

	return 0;
}
