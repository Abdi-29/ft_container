#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include "pair.hpp"
#include "rb_iterator.hpp"
#include "enable_if.hpp"

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
		typedef ft::pair<const Key, T> value_type;
		typedef size_t size_type;

	private:
		typedef rb_node<T>	node_type;
		typedef rb_node<const T> const_node_type;
		typedef typename node_type::node_pointer node_pointer;
		typedef typename node_type::const_node_pointer const_node_pointer;
		typedef typename Allocator::template rebind<node_type>::other Alloc;

	public:
		rb_tree(): _root(NULL), _size(0) {
			_init_nil();
		}

		rb_tree(const value_compare& comp): _root(NULL), _size(0), _compare(comp) {
			_init_nil();
		}

	public:
		//capacity
		bool empty() const {
			return _size == 0;
		}
	public:
		/**
		 * while inserting a new node, the new node is always inserted as a red node
		 * after insertion of a new node. if the tree is violating the properties
		 * of the red-black tree them er do the following operations:
		 * 1: recolor
		 * 2. rotation
		 * @param value
		 * @return
		 */
		node_pointer insert(const value_type& value) {
			node_pointer new_node = new node_type(value);
			if (_root == TNULL) {
				_root = new_node;
			}
		}
//		iterator insert(iterator hint, const value_type& value) {
//
//		}
		//private
		ft::pair<iterator, bool> _add_to_tree(const value_type& value) {

		}
		void _init_nil() {
			TNULL = new node_type();
		}

		node_pointer _find_node(const node_pointer root, const value_type& value) {
			if (!root) {
				return NULL;
			} else if(root->_value == value) {
				return root;
			} else if(root->_value > value) {
				_find_node(root->_left, value);
			}
			_find_node(root->_right, value);
		}

		node_pointer find(const value_type& value) {
			return _find_node(_root, value);
		}

		node_pointer get_root() {
			return _root;
		}

	private:
		node_pointer	_root;
		node_pointer	TNULL;
		Alloc			_alloc;
		size_type		_size;
		value_compare	_compare;
	};
}
#endif