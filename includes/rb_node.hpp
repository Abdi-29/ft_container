#ifndef RB_NODE_HPP
#define RB_NODE_HPP

#include <cstddef>

namespace ft {
	enum rb_colour {
		BLACK = false,
		RED = true
	};

	template<class T>
	class rb_node {
	public:
		typedef T value_type;
		typedef rb_node node_type;
		typedef node_type* node_pointer;
		typedef const node_pointer const_node_pointer;

	public:
		rb_node(): _parent(NULL), _left(NULL), _right(NULL), _value(), _value_colour(RED) {}
		rb_node(node_pointer parent, value_type value): _parent(parent), _left(NULL), _right(NULL), _value(value), _value_colour(RED) {}
		rb_node(const rb_node& rhs) {*this = rhs;}
		rb_node& operator=(const rb_node& rhs) {
			if (*this == rhs) {
				return *this;
			}
			_parent = rhs._parent;
			_left = rhs._left;
			_right = rhs._right;
			_value = rhs._value;
			_value_colour = rhs._value_colour;
			return *this;
		}

	private:
		node_pointer	_parent;
		node_pointer	_left;
		node_pointer	_right;
		value_type		_value;
		rb_colour		_value_colour;
	};
}

#endif