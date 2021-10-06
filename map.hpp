/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 13:19:21 by besellem          #+#    #+#             */
/*   Updated: 2021/10/06 16:23:08 by besellem         ###   ########.fr       */
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
		  class Compare,
		  class Node,
		  class AllocNode>
class RedBlackTree;

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

		typedef ft::map_iterator<value_type>                 iterator;
		typedef ft::map_iterator<const value_type>           const_iterator;
		// typedef ft::reverse_iterator<iterator>               reverse_iterator;
		// typedef ft::reverse_iterator<const_iterator>         const_reverse_iterator;

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


	public:
		explicit map(__unused const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type()) :
			_alloc(alloc), _rbt()
		{
			// _rbt = RedBlackTree<key_type, mapped_type, comp, _alloc>();
		}
		
		template <class InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type());
		
		map(const map& m);
		
		~map();

		map&	operator=(const map& m);


		/*
		** -- Iterators --
		*/
		iterator				begin()        { return iterator(_rbt.get_root_node()); }
		const_iterator			begin() const  { return const_iterator(_rbt.get_root_node()); }
		iterator				end()          { return iterator(_rbt.get_last_node()); }
		const_iterator			end() const    { return const_iterator(_rbt.get_last_node()); }
		// reverse_iterator		rbegin()       { return reverse_iterator(end()); }
		// const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		// reverse_iterator		rend()         { return reverse_iterator(begin()); }
		// const_reverse_iterator	rend() const   { return const_reverse_iterator(begin()); }


		/*
		** -- Capacity --
		*/
		bool			empty()    const { return size() == 0; }
		size_type		size()     const;
		size_type		max_size() const;


		/*
		** -- Element access --
		*/
		mapped_type&	operator[](const key_type& k);

		
		/*
		** -- Modifiers --
		*/
		pair<iterator, bool>	insert(const value_type& v);
		iterator 				insert(const_iterator position, const value_type& v);
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last);

		iterator		erase(const_iterator position);
		size_type		erase(const key_type& k);
		iterator		erase(const_iterator first, const_iterator last);
		void			swap(map& m);
		void			clear();

		
		/*
		** -- Observers --
		*/
		key_compare		key_comp()      const { return key_compare(); }
		value_compare	value_comp()    const { return value_compare(); }


		/*
		** -- Operations --
		*/
		iterator		find(const key_type& k);
		const_iterator	find(const key_type& k) const;
		size_type		count(const key_type& k) const;
		iterator		lower_bound(const key_type& k);
		const_iterator	lower_bound(const key_type& k) const;
		iterator		upper_bound(const key_type& k);
		const_iterator	upper_bound(const key_type& k) const;
		pair<iterator, iterator>				equal_range(const key_type& k);
		pair<const_iterator, const_iterator>	equal_range(const key_type& k) const;
		
		
		/*
		** -- Allocator --
		*/
		allocator_type	get_allocator() const { return allocator_type(); }


		private:
			allocator_type										_alloc;
			RedBlackTree<key_type, mapped_type, key_compare>	_rbt;
		
}; /* class map */


_END_NAMESPACE_FT

#endif /* define MAP_HPP */
