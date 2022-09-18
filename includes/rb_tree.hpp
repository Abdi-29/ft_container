#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include "pair.hpp"
#include "rb_iterator.hpp"
#include "enable_if.hpp"

namespace ft {
	template<
			typename T,
			typename Compare,
			typename Allocator = std::allocator<T>
	> class rb_tree {
	public:
		typedef rb_iterator<T> iterator;
		typedef rb_iterator<const T> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef Compare value_compare;
		typedef T value_type;
		typedef size_t size_type;
		typedef rb_node<T>	node_type;
		typedef rb_node<const T> const_node_type;
		typedef typename node_type::node_pointer node_pointer;
		typedef typename node_type::const_node_pointer const_node_pointer;
		typedef typename Allocator::template rebind<node_type>::other Alloc;

	public:
		rb_tree(): _size(0) {
			std::cout << "init the pointer\n";
			_init_nil();
			_root = TNULL;
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
			if (empty()) {
				_root = new_node;
				_root->_value_colour = BLACK;
			} else {
				node_pointer search;
				search = _find_node(_root, new_node);
				if (search == NULL) {
					search = node_position_at(_root, new_node);
					new_node->_parent = search;
					if (search == NULL) {
						_root = new_node;
					} else if(_compare(new_node->_value, search->_value)) {
						search->_left = new_node;
					} else {
						search->_right = new_node;
					}
				}
				insert_fixup(search);
			}
			print_node();
			_size++;
			return new_node;
		}

		void print_helper(node_pointer root, std::string indent, bool last) {
			if (root != NULL) {
				std::cout << indent;
				if (last) {
					std::cout << "R----";
					indent += "   ";
				} else {
					std::cout << "L----";
					indent += "|  ";
				}

				std::string sColor = root->_value_colour == false ? "RED" : "BLACK";
				std::cout << root->_value << "(" << sColor << ")" << std::endl;
				print_helper(root->_left, indent, false);
				print_helper(root->_right, indent, true);
			}
		}

		void print_node() {
			if (_root) {
				print_helper(_root, "", true);
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

		node_pointer node_position_at(node_pointer root, node_pointer new_node) {
			node_pointer end_node;

			end_node = TNULL;
			while (root != NULL) {
				end_node = root;
				if (root->_value > new_node->_value) {
					root = root->_left;
				} else {
					root = root->_right;
				}
			}
			return end_node;
		}

		node_pointer _find_node(const node_pointer root, const node_pointer new_node) {
			if (!root) {
				return root;
			} else if(root->_value == new_node->_value) {
				return root;
			} else if(_compare(root->_value, new_node->_value)) {
				return _find_node(root->_left, new_node);
			}
			return _find_node(root->_right, new_node);
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