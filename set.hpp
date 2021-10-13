/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besellem <besellem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 21:37:37 by besellem          #+#    #+#             */
/*   Updated: 2021/10/13 15:49:54 by besellem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <iostream>

# include <memory>
# include <algorithm>
# include <cstddef>

# include "_utils/RedBlackTree.hpp"
# include "_utils/tree_iterator.hpp"
# include "_utils/iterator.hpp"
# include "_utils/utils.hpp"


_BEGIN_NAMESPACE_FT

template <class Key,
		  class Compare = ft::less<Key>,
		  class Allocator = std::allocator<Key> >
class set
{
	
	public:
		typedef Key                                      key_type;
		typedef key_type                                 value_type;
		typedef Compare                                  key_compare;
		typedef key_compare                              value_compare;
		typedef Allocator                                allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::difference_type difference_type;

		typedef ft::tree_iterator<const value_type, ft::Node<value_type> >  iterator;
		typedef ft::tree_iterator<const value_type, ft::Node<value_type> >  const_iterator;
		typedef ft::reverse_iterator<iterator>                              reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>                        const_reverse_iterator;


	public:
		
		explicit set(const key_compare& comp = key_compare(),
					 __unused const allocator_type& alloc = allocator_type()) :
			_rbt(value_compare(comp))
		{}
		
		template <class InputIterator>
		set(InputIterator first,
			InputIterator last,
			const key_compare& comp = key_compare(),
			__unused const allocator_type& alloc = allocator_type()) :
				_rbt(value_compare(comp))
		{
			insert(first, last);
		}
		
		set(const set& s) : _rbt(value_compare(key_compare()))
		{
			insert(s.begin(), s.end());
		}
		
		~set()
		{
			clear();
			_rbt.destroy_last();
		}

		set&			operator=(const set& s)
		{
			if (this == &s)
				return *this;
			
			this->~set();
			_rbt = ft::RedBlackTree<value_type, value_compare>(value_compare(key_compare()));
			insert(s.begin(), s.end());
			return *this;
		}

		
		/*
		** -- Iterators --
		*/
		iterator		begin()       { return       iterator(_rbt.get_root(), _rbt.get_last(), _rbt.min()); }
		const_iterator	begin() const { return const_iterator(_rbt.get_root(), _rbt.get_last(), _rbt.min()); }
		iterator		end()         { return       iterator(_rbt.get_root(), _rbt.get_last(), _rbt.get_last()); }
		const_iterator	end()   const { return const_iterator(_rbt.get_root(), _rbt.get_last(), _rbt.get_last()); }

		reverse_iterator		rbegin()       { return       reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend()         { return       reverse_iterator(begin()); }
		const_reverse_iterator	rend()   const { return const_reverse_iterator(begin()); }


		/*
		** -- Capacity --
		*/
		bool			empty()    const { return size() == 0; }
		size_type		size()     const { return _rbt.size(); }
		size_type		max_size() const { return _rbt.max_size(); }

		
		/*
		** -- Modifiers --
		*/
		ft::pair<iterator,bool>	insert(const value_type& v)
		{
			const bool	r = _rbt.insert(v);
			return ft::make_pair(find(v), r);
		}
		
		iterator	insert(__unused const_iterator position, const value_type& v)
		{
			insert(v);
			return find(v);
		}
		
		template <class InputIterator>
		void		insert(InputIterator first, InputIterator last)
		{
			for ( ; first != last; ++first)
				insert(*first);
		}

		void		erase(iterator position)
		{ erase(*position); }
		
		size_type	erase(const key_type& k)
		{ return _rbt.delete_node(k); }
		
		void		erase(iterator first, iterator last)
		{
			while (first != last)
			{
				first = find(*first);
				erase(first++);
			}
		}
		
		void		swap(set& s) { _rbt.swap(s._rbt); }
		void		clear()      { return _rbt.destroy(); }


		/*
		** -- Observers --
		*/
		key_compare		key_comp()   const { return key_compare(); }
		value_compare	value_comp() const { return value_compare(key_comp()); }


		/*
		** -- Operations --
		*/
		size_type		count(const key_type& k) const
		{ return find(k) != end(); }

		iterator		find(const key_type& k)
		{ return       iterator(_rbt.get_root(), _rbt.get_last(), _rbt.search(k)); }

		const_iterator	find(const key_type& k) const
		{ return const_iterator(_rbt.get_root(), _rbt.get_last(), _rbt.search(k)); }
		
		iterator		lower_bound(const key_type& k)
		{ return       iterator(_rbt.get_root(), _rbt.get_last(), _rbt.lower_bound(k)); }
		
		const_iterator	lower_bound(const key_type& k) const
		{ return const_iterator(_rbt.get_root(), _rbt.get_last(), _rbt.lower_bound(k)); }
		
		iterator		upper_bound(const key_type& k)
		{ return       iterator(_rbt.get_root(), _rbt.get_last(), _rbt.upper_bound(k)); }

		const_iterator	upper_bound(const key_type& k) const
		{ return const_iterator(_rbt.get_root(), _rbt.get_last(), _rbt.upper_bound(k)); }
		
		ft::pair<iterator, iterator>				equal_range(const key_type& k)
		{ return ft::make_pair(lower_bound(k), upper_bound(k)); }

		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& k) const
		{ return ft::make_pair(lower_bound(k), upper_bound(k)); }


		/*
		** -- Allocator --
		*/
		allocator_type	get_allocator() const { return allocator_type(); }
	
		
		private:
			RedBlackTree<value_type, value_compare>		_rbt;

}; /* class set */

template <class Key, class Compare, class Allocator>
bool	operator==(const set<Key,Compare,Allocator>& x,
				   const set<Key,Compare,Allocator>& y)
{ return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()); }

template <class Key, class Compare, class Allocator>
bool	operator!=(const set<Key,Compare,Allocator>& x,
				   const set<Key,Compare,Allocator>& y)
{ return !(x == y); }

template <class Key, class Compare, class Allocator>
bool	operator< (const set<Key,Compare,Allocator>& x,
				   const set<Key,Compare,Allocator>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template <class Key, class Compare, class Allocator>
bool	operator<=(const set<Key,Compare,Allocator>& x,
				   const set<Key,Compare,Allocator>& y)
{ return !(y < x); }

template <class Key, class Compare, class Allocator>
bool	operator> (const set<Key,Compare,Allocator>& x,
				   const set<Key,Compare,Allocator>& y)
{ return y < x; }

template <class Key, class Compare, class Allocator>
bool	operator>=(const set<Key,Compare,Allocator>& x,
				   const set<Key,Compare,Allocator>& y)
{ return !(x < y); }

template <class Key, class Compare, class Allocator>
void	swap(set<Key,Compare,Allocator>& x,
			 set<Key,Compare,Allocator>& y)
{ x.swap(y); }


_END_NAMESPACE_FT

#endif /* define SET_HPP */
