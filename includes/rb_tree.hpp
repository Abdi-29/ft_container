#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include "pair.hpp"
#include "rb_iterator.hpp"

namespace ft {
	template<
			class Key,
			class T,
			class Compare,
			class Allocator = std::allocator<T>
	> class rb_tree {
	public:
		typedef rb_iterator<T> iterator;
		typedef rb_iterator<const T> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef Allocator allocator_type;
		typedef Compare value_compare;
		typedef T value_type;
		typedef size_t size_type;

	private:
		typedef rb_node<T>	node_type;
		typedef rb_node<const T> const_node_type;
		typedef typename node_type::node_pointer node_pointer;
		typedef typename node_type::const_node_pointer const_node_pointer;
		typedef typename Allocator::template rebind<node_type>::other allocator_node;

	public:
		ft::pair<iterator, bool> insert(const value_type& value) {

		}

		iterator insert(iterator hint, const value_type& value) {

		}

	private:
		node_pointer	_root;
		Allocator		_alloc;
		allocator_node	_alloc_node;
		size_type		_size;
		value_compare	_compare;
	};
}
#endif