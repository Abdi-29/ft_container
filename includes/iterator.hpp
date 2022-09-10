#ifndef ITERATOR
#define ITERATOR

#include <iostream>
#include "vector.hpp"
#include "iterator_traits.hpp"

namespace ft {

	template<
			class Category,
			class T,
			class Distance = std::ptrdiff_t,
			class Pointer = T *,
			class Reference = T &
	>

	class Iterator {
	public:
		typedef Iterator iterator_type;
		typedef Category iterator_category;
		typedef T  value_type;
		typedef  std::ptrdiff_t difference_type;
		typedef Pointer pointer;
		typedef Reference reference;

	public:
		typedef size_t size_type;

	protected:
		pointer _data;
	public:
		Iterator() : _data(NULL){}
		Iterator(pointer data) : _data(data){}

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
		Distance operator-(const Iterator<iterator_category ,T>& other) { return this->_data - other._data; }
		Iterator operator+(const Iterator& other) { return this->_data + other._data; }
		Iterator operator+=(int) { return operator++(); }
		Iterator operator+(int a) { return _data + a; }
		Iterator operator-=(int) { return operator--(); }
		Iterator operator-(int a) { return _data - a; }
		reference operator*() { return *_data; }
		reference operator[](size_type n) const { return *(_data + n); }
		reference operator[](size_type n) { return *(_data + n); }
		pointer operator->() { return _data; }
		bool operator==(const Iterator& other) { return (this->_data == other._data); }
		bool operator!=(const Iterator<iterator_category, T> other) {return !(*this == other); }
		bool operator>=(const Iterator& other) { return (this->_data >= other._data); }
		bool operator>(const Iterator& other) { return (this->_data > other._data); }
		bool operator<=(const Iterator& other) { return (this->_data <= other._data); }
		bool operator<(const Iterator& other) { return (this->_data < other._data); }
		friend Iterator operator+(const int offset, Iterator out) { return out += offset; }
	};
}

#endif
