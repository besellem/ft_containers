/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:23:38 by besellem          #+#    #+#             */
/*   Updated: 2021/09/30 16:27:42 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* for namespace declaration */
#define _BEGIN_NAMESPACE_FT   namespace ft {
#define _END_NAMESPACE_FT      }


_BEGIN_NAMESPACE_FT

/* nullptr_t */
struct nullptr_t
{
	void	*_ptr;

	struct __nat { int __for_bool_; };

	nullptr_t() : _ptr(0) {}
	nullptr_t(int __nat::*) : _ptr(0) {}
	
	operator int __nat::*() const { return 0; }

	template <class T>
	operator	T*() const { return 0; }

	template <class T, class _Up>
	operator	T _Up::*() const { return 0; }

	friend bool	operator==(nullptr_t, nullptr_t) { return true; }
	friend bool	operator!=(nullptr_t, nullptr_t) { return false; }
};

/* nullptr_ is equivalent to nullptr */
#define nullptr_ nullptr_t(0)

_END_NAMESPACE_FT
