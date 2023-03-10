#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <iostream>
#include "pair.hpp"
#include "rb_iterator.hpp"
#include "enable_if.hpp"
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
		rb_tree(): _root(NULL), _size(0), _compare() {
			std::cout << "init the pointer\n";
		}

		explicit rb_tree(const value_compare& comp): _root(NULL), _size(0), _compare(comp) {}

	public:
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
		ft::pair<iterator, bool> insert(const value_type& value) {
			if (empty()) {
				_root = new_leaf(NULL, value);
				_root->_value_colour = BLACK;
				return ft::make_pair(iterator(_root), true);
			} else {
				node_pointer exist;
				exist = _find_node(_root, value);
				if (!exist) {
					node_pointer node = insert_node_at(value);
					return ft::make_pair(iterator(node), true);
				}
				return ft::make_pair(iterator(exist), false);
			}
		}

		iterator insert(iterator hint, const value_type& value) {
			return hint.first == value.first ? hint.first : insert(value).first;
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last, typename enable_if<true>::type* = 0) {
			while (*first != *last) {
				insert(first);
				first++;
			}
		}

		size_type size() const {
			return _size;
		}

		size_type max_size() const {
			return _alloc.max_size();
		}

		iterator begin() {
			return iterator(find_first_element(_root));
		}

		const_iterator begin() const {
			return const_iterator(find_first_element(_root));
		}

		iterator end() {
			return iterator(find_last_element(_root));
		}

		iterator erase(iterator pos) {
			node_pointer exist = _find_node(_root, pos.base()->_value);
			if (exist) {
				delete_node(exist);
			}
			return pos;
		}

	private:
		node_pointer new_leaf(node_pointer parent, const value_type& value) {
			node_pointer new_node;

			new_node = _alloc.allocate(1);
			_alloc.construct(new_node, value);
			new_node->_parent = parent;
			_size += 1;
			return new_node;
		}

		node_pointer insert_node_at(const value_type& value) {
			node_pointer parent;
			node_pointer new_node;

			new_node = new_leaf(NULL, value);
			parent = node_position_at(_root, value);
			new_node->_parent = parent;
			if (parent == NULL) {
				_root = new_node;
			} else if(new_node->_value.first < parent->_value.first) {
				parent->_left = new_node;
			} else {
				parent->_right = new_node;
			}
			insert_fix_up(new_node);
			return new_node;
		}

		void insert_fix_up(node_pointer node) {
			while (node->_parent->_value_colour == RED) {
				if (node->_parent == node->_parent->_parent->_right) {
					fix_right_violation(node);
				} else {
					fix_left_violation(node);
				}
				if(node == _root) {
					break;
				}
			}
			_root->_value_colour = BLACK;
		}

		void fix_left_violation(node_pointer node) {
			node_pointer uncle = node->_parent->_parent->_right;
			if (uncle->_value_colour == RED) {
				set_colour(node, uncle);
			}
			else {
				if(node == node->_parent->_right) {
					node = node->_parent;
					left_rotate(node);
				}
				node->_parent->_value_colour = BLACK;//case 3
				node->_parent->_parent->_value_colour = RED;
				right_rotate(node->_parent->_parent);
			}
		}

		void fix_right_violation(node_pointer node) {
			node_pointer uncle = node->_parent->_parent->_left;
			if (uncle && uncle->_value_colour == RED) {
				set_colour(node, uncle);
			}
			else {
				if (node == node->_parent->_left) {
					node = node->_parent;
					right_rotate(node);
				}
				node->_parent->_value_colour = BLACK;//case 3
				node->_parent->_parent->_value_colour = RED;
				left_rotate(node->_parent->_parent);
			}
		}

		void left_rotate(node_pointer node) {
			node_pointer tmp = node->_right;

			node->_right = tmp->_left;
			if (tmp->_left != NULL) {
				tmp->_left->_parent = node;
			}
			tmp->_parent = node->_parent;
			if (node->_parent == NULL) {
				_root = tmp;
			} else if(node == node->_parent->_left) {
				node->_parent->_left = tmp;
			} else {
				node->_parent->_right = tmp;
			}
			tmp->_left = node;
			node->_parent = tmp;
		}

		void right_rotate(node_pointer node) {
			node_pointer tmp = node->_left;

			node->_right = tmp->_right;
			if (tmp->_right != NULL) {
				tmp->_right->_parent = node;
			}
			tmp->_parent = node->_parent;
			if (node->_parent == NULL) {
				_root = tmp;
			} else if(node == node->_parent->_right) {
				node->_parent->_right = tmp;
			} else {
				node->_parent->_left = tmp;
			}
			tmp->_right = node;
			node->_parent = tmp;
		}

		void set_colour(node_pointer node, node_pointer uncle) {
			node->_parent->_value_colour = BLACK;
			uncle->_value_colour = BLACK;
			node->_parent->_parent->_value_colour = RED;
			node = node->_parent->_parent;
		}


		node_pointer node_position_at(node_pointer root, const value_type& value) {
			node_pointer end_node;

			while (root != NULL) {
				end_node = root;
				if (root->_value.first > value.first) {
					root = root->_left;
				} else {
					root = root->_right;
				}
			}
			return end_node;
		}

		node_pointer _find_node(const node_pointer node, const value_type& value) {
			if (node == NULL) {
				return NULL;
			} else if(node->_value.first == value.first) {
				return node;
			} else if(_compare(node->_value.first, value.first)) {
				return _find_node(node->_right, value);
			}
			return _find_node(node->_left, value);
		}

		node_pointer find(const value_type& value) {
			return _find_node(_root, value);
		}

		node_pointer find_first_element(node_pointer node) {
			while (node->_left) {
				node = node->_left;
			}
			return node;
		}

		node_pointer find_last_element(node_pointer node) {
			while (node->_right) {
				node = node->_right;
			}
			return node->_right;
		}

		void transplant(node_pointer node, node_pointer right) {
			if (!node) {
				_root = right;
			} else if (node == node->_parent->_left) {
				node->_parent->_left = right;
			} else {
				node->_parent->_right = right;
			}
			right->_parent = node->_parent;
		}

		void delete_node(node_pointer node) {
			node_pointer x;

			node_pointer tmp = node;
			rb_colour original_colour = tmp->_value_colour;
			if (!node->_left) {
				x = node->_right;
				transplant(node, node->_right);
			} else if (!node->_right) {
				x = node->_left;
				transplant(node, node->_left);
			} else {
				tmp = find_first_element(node->_right);
				original_colour = tmp->_value_colour;
				x = tmp->_right;
				if (tmp->_parent == node) {
					x->_parent = tmp;
				} else {
					transplant(tmp, tmp->_right);
					tmp->_right = node->_right;
					tmp->_right->_parent = tmp;
				}
				transplant(node, tmp);
				tmp->_left = node->_left;
				tmp->_left->_parent = tmp;
				tmp->_value_colour = node->_value_colour;
			}
			if (original_colour == BLACK) {
				delete_fix(x);
			}
		}

	public:
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
				std::string sColor = root->_value_colour == true ? "RED" : "BLACK";
				std::cout << root->_value.first << "(" << sColor << ")" << std::endl;
				print_helper(root->_left, indent, false);
				print_helper(root->_right, indent, true);
			}
		}

		void print_node() {
			if (_root) {
				print_helper(_root, "", true);
			}
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