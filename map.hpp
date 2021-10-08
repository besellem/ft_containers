/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:21 by besellem          #+#    #+#             */
/*   Updated: 2021/10/08 12:27:56 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>

# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>

# include "_utils/iterator.hpp"
# include "_utils/map_iterator.hpp"
# include "_utils/utils.hpp"
# include "_utils/RedBlackTree.hpp"


_BEGIN_NAMESPACE_FT

template <class Key,
		  class T,
		  class Compare = ft::less<Key>,
		  class Allocator = std::allocator< ft::pair<const Key, T> > >
class map
{
	
	public:
		typedef Key                                          key_type;
		typedef T                                            mapped_type;
		typedef ft::pair<const key_type, mapped_type>        value_type;
		typedef Compare                                      key_compare;
		typedef Allocator                                    allocator_type;
		typedef typename allocator_type::reference           reference;
		typedef typename allocator_type::const_reference     const_reference;
		typedef typename allocator_type::pointer             pointer;
		typedef typename allocator_type::const_pointer       const_pointer;
		typedef typename allocator_type::size_type           size_type;
		typedef typename allocator_type::difference_type     difference_type;

		class value_compare : public ft::binary_function<value_type, value_type, bool>
		{
			friend class map;
			
			protected:
				key_compare	comp;
				value_compare(key_compare c) : comp(c) {}
				
			public:
				bool	operator()(const value_type& x, const value_type& y) const
				{ return comp(x.first, y.first); }
		};
		
		typedef typename RedBlackTree<value_type, key_compare>::iterator             iterator;
		typedef typename RedBlackTree<value_type, key_compare>::const_iterator const_iterator;
		typedef typename ft::reverse_iterator<iterator>                              reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>                        const_reverse_iterator;


	public:
		explicit map(__unused const key_compare& comp = key_compare(),
					 const allocator_type& alloc = allocator_type()) :
			_alloc(alloc),
			_rbt()
		{}
		
		template <class InputIte>
		map(InputIte first, InputIte last,
			__unused const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) :
				_alloc(alloc),
				_rbt()
		{
			insert(first, last);
		}
		
		map(const map& m)
		{
			insert(m.begin(), m.end());
		}
		
		~map() { clear(); }

		map&	operator=(const map& m)
		{
			if (this == &m)
				return *this;
			clear();
			insert(m.begin(), m.end());
			return *this;
		}


		/*
		** -- Iterators --
		*/
		iterator		begin()       { return       iterator(_rbt.get_root(), _rbt.get_last(), _rbt.min()); }
		const_iterator	begin() const { return const_iterator(_rbt.get_root(), _rbt.get_last(), _rbt.min()); }
		iterator		end()         { return       iterator(_rbt.get_root(), _rbt.get_last(), _rbt.get_last()); }
		const_iterator	end() const   { return const_iterator(_rbt.get_root(), _rbt.get_last(), _rbt.get_last()); }

		reverse_iterator		rbegin()       { return       reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend()         { return       reverse_iterator(begin()); }
		const_reverse_iterator	rend() const   { return const_reverse_iterator(begin()); }
		

		/*
		** -- Capacity --
		*/
		bool			empty()    const { return size() == 0; }
		size_type		size()     const { return _rbt.size(); }
		size_type		max_size() const { return _rbt.max_size(); }


		/*
		** -- Element access --
		*/
		mapped_type&	operator[](const key_type& k)
		{
			insert(ft::make_pair(k, mapped_type()));

			iterator	it = find(k);
			return it->second;
		}

		
		/*
		** -- Modifiers --
		*/
		pair<iterator, bool>	insert(const value_type& v)
		{ return _rbt.insert(v); }

		iterator 		insert(__unused const_iterator position, const value_type& v)
		{
			insert(v);
			return find(v.first);
		}

		template <class InputIte>
		void			insert(InputIte first,
							  InputIte last,
							  typename ft::enable_if<!ft::is_integral<InputIte>::value, InputIte>::type* = nullptr_)
		{
			for ( ; first != last; ++first)
				insert(*first);
		}

		iterator		erase(const_iterator position);
		
		size_type		erase(const key_type& k)
		{
			size_type	n = count(k);
			
			_rbt.delete_node(ft::make_pair(k, mapped_type()));
			return n;
		}

		iterator		erase(const_iterator first, const_iterator last);
		
		void			swap(map& m) { _rbt.swap(m._rbt); }
		void			clear()      { return _rbt.destroy(); }

		
		/*
		** -- Observers --
		*/
		key_compare		key_comp()      const { return key_compare(); }
		value_compare	value_comp()    const { return value_compare(); }


		/*
		** -- Operations --
		*/
		iterator		find(const key_type& k)
		{
			return iterator(_rbt.get_root(),
							_rbt.get_last(),
							_rbt.search( ft::make_pair(k, mapped_type()) )
							);
		}
		
		const_iterator	find(const key_type& k) const
		{
			return const_iterator(_rbt.get_root(),
								 _rbt.get_last(),
								 _rbt.search( ft::make_pair(k, mapped_type()) )
								);
		}
		
		size_type		count(const key_type& k) const
		{ return find(k) != end(); }

		iterator		lower_bound(const key_type& k)
		{
			iterator		it = begin();
			const iterator	ite = end();
			
			for ( ; it != ite; ++it)
			{
				if (!key_comp()(it->first, k))
					break ;
			}
			return it;
		}

		const_iterator	lower_bound(const key_type& k) const;
		
		iterator		upper_bound(const key_type& k)
		{
			iterator		it = begin();
			const iterator	ite = end();
			
			for ( ; it != ite; ++it)
			{
				if (key_comp()(k, it->first))
					break ;
			}
			return it;
		}
		
		const_iterator	upper_bound(const key_type& k) const;
		pair<iterator, iterator>				equal_range(const key_type& k);
		pair<const_iterator, const_iterator>	equal_range(const key_type& k) const;
		
		
		/*
		** -- Allocator --
		*/
		allocator_type	get_allocator() const { return allocator_type(); }




		////////////////////////////////////////////////////////////////////////
		// TO REMOVE
		////////////////////////////////////////////////////////////////////////

		void	__print() const
		{ _rbt.print(); }

		////////////////////////////////////////////////////////////////////////
		// [END] TO REMOVE
		////////////////////////////////////////////////////////////////////////






		private:
			allocator_type							_alloc;
			RedBlackTree<value_type, key_compare>	_rbt;
		
}; /* class map */

template<class Key, class T, class Compare, class Alloc>
bool	operator==(const map<Key,T,Compare,Alloc>& lhs,
				   const map<Key,T,Compare,Alloc>& rhs)
{
	typename ft::map<Key,T,Compare,Alloc>::const_iterator	left = lhs.begin();
	typename ft::map<Key,T,Compare,Alloc>::const_iterator	right = rhs.begin();

	if (lhs.size() != rhs.size())
		return false;

	for ( ; left != lhs.end(); ++left, ++right)
	{
		if (right == rhs.end() || *left != *right)
			return false;
	}
	return true;
}

template<class Key, class T, class Compare, class Alloc>
bool	operator!=(const map<Key,T,Compare,Alloc>& x,
				   const map<Key,T,Compare,Alloc>& y)
{ return !(x == y); }

template<class Key, class T, class Compare, class Alloc>
bool	operator< (const map<Key,T,Compare,Alloc>& x,
				   const map<Key,T,Compare,Alloc>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template<class Key, class T, class Compare, class Alloc>
bool	operator<=(const map<Key,T,Compare,Alloc>& x,
				   const map<Key,T,Compare,Alloc>& y)
{ return !(y < x); }

template<class Key, class T, class Compare, class Alloc>
bool	operator> (const map<Key,T,Compare,Alloc>& x,
				   const map<Key,T,Compare,Alloc>& y)
{ return y < x; }

template<class Key, class T, class Compare, class Alloc>
bool	operator>=(const map<Key,T,Compare,Alloc>& x,
				   const map<Key,T,Compare,Alloc>& y)
{ return !(x < y); }


_END_NAMESPACE_FT

#endif /* define MAP_HPP */
