#ifndef ITERATOR
#define ITERATOR

#include <iostream>
#include "vector.hpp"
namespace ft {

	template<
//			class Category,
			class T,
			class Distance = std::ptrdiff_t,
			class Pointer = T *,
			class Reference = T &
	>

	class Iterator {
	protected:
		Pointer _data;
	public:
		Iterator() : _data(NULL){}
		Iterator(Pointer data) : _data(data){}

		~Iterator() {}

		Iterator operator++(int) {
			Iterator tmp(_data);
			_data++;
			return tmp;
		}

		Iterator& operator++() {
			_data++;
			return *this;
		}

		Iterator operator--(int) {
			Iterator tmp(_data);
			_data--;
			return tmp;
		}

		Iterator& operator--() {
			_data--;
			return *this;
		}

		Iterator operator+=(int) { return operator++(); }
		Iterator operator+(int a) { return _data + a; }
		Iterator operator-=(int) { return operator--(); }
		Iterator operator-(int a) { return _data - a; }
		Reference operator*() { return *_data; }
		Reference operator[](int a) { return *(_data + a); }
		Pointer operator->() { return _data; }
		bool operator==(const Iterator& other) { return (this->_data == other._data); }
		bool operator!=(const Iterator<T> other) {return !(*this == other); }
		bool operator>=(const Iterator& other) { return (this->_data >= other._data); }
		bool operator>(const Iterator& other) { return (this->_data > other._data); }
		bool operator<=(const Iterator& other) { return (this->_data <= other._data); }
		bool operator<(const Iterator& other) { return (this->_data < other._data); }
		friend Iterator operator+(const int offset, Iterator out) { return out += offset; }
	};
}

#endif

