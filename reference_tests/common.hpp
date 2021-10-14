/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 17:46:43 by besellem          #+#    #+#             */
/*   Updated: 2021/10/13 23:32:39 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_HPP
# define COMMON_HPP

# include <iostream>

# if defined(STD)
#  include <map>
#  include <stack>
#  include <vector>
#  include <set>
#  define __NAMESPACE__      std
#  define __NAMESPACE_NAME__ "std"
# else
#  include "map.hpp"
#  include "stack.hpp"
#  include "vector.hpp"
#  include "set.hpp"
#  define __NAMESPACE__     ft
#  define __NAMESPACE_NAME_ "ft"
# endif /* defined(STD) */


#endif /* define COMMON_HPP */
