#ifndef RB_ITERATOR_HPP
#define RB_ITERATOR_HPP

#include "pair.hpp"
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "rb_node.hpp"

/**
 * RED BLACK TREE
 * 1. every node is either red or black
 * 2. the root is black
 * 3.every leaf(NIL) is black
 * 4. if a node is red, then both its children are black
 * 5. for each node, all simple paths from the nde to descendant leaves contain the same number of black nodes
 *
 */

namespace ft {
	template<class T>
	class rb_iterator: public ft::Iterator<std::bidirectional_iterator_tag, T> {
	public:
		typedef rb_iterator self;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T* pointer;
		typedef T& reference;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef size_t size_type;
		typedef rb_node<T>* node_pointer;
		typedef rb_node<const T>* const_node_pointer;

	public:
		rb_iterator(): _node() {}
		explicit rb_iterator(node_pointer node): _node(node) {}
		template<class U>
		rb_iterator(const rb_iterator<U>& other): _node(other._node) {}
		rb_iterator& operator=(const rb_iterator& other) {
			if (this == &other) {
				return *this;
			}
			_node = other._node;
			return *this;
		}

		pointer operator->() const {
			return _node;
		}

		pointer operator->() {
			return _node->_value;
		}

		reference operator*() const {
			return *_node->_value;
		}

		reference operator*() {
			return *_node->_value;
		}

		self& operator++() {
			_node = rb_tree_increment(_node);
			return *this;
		}

		self operator++(int) {
			self tmp(*this);
			_node = rb_tree_increment(_node);
			return tmp;
		}

		self& operator--() {
			_node = rb_tree_decrement(_node);
		}

	private:
		node_pointer max_node(node_pointer node) {
			while (node->_right) {
				node = node->_right;
			}
			return node;
		}

		node_pointer min_node(node_pointer node) {
			while (node->_left) {
				node = node->_left;
			}
			return node;
		}

		node_pointer rb_tree_increment(node_pointer node) {
			if (node->_right) {
				return min_node(node->_right);
			}
			node_pointer parent = node->_parent;
			while (parent && node == parent->_right) {
				node = parent;
				parent = parent->_parent;
			}
			return parent;
		}

		node_pointer rb_tree_decrement(node_pointer node) {
			if (node->_left) {
				return max_node(node->_left);
			}
			node_pointer parent = node->_parent;
			while (parent && node == parent->_left) {
				node = parent;
				parent = parent->_parent;
			}
			return parent;
		}

	private:
		node_pointer _node;
	};
}

#endif