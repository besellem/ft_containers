/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:07:19 by besellem          #+#    #+#             */
/*   Updated: 2021/10/05 17:12:31 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include <iostream>

# include "utils.hpp"


_BEGIN_NAMESPACE_FT

template <class _Ite>
class map_iterator : public iterator<random_access_iterator_tag, _Ite>
{
	
}; /* map_iterator */


_END_NAMESPACE_FT

#endif /* define MAP_ITERATOR_HPP */
