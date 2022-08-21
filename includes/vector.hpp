#ifndef FT_CONTAINER
#define FT_CONTAINER

#include <iostream>
#include "iterator.hpp"
#include "util.hpp"

namespace ft {
	template < class T, class Allocator = std::allocator<T> >
	class Vector {
	public:
        typedef T value_type;
		typedef Allocator allocator_type;
		typedef  typename allocator_type::const_pointer	const_pointer;
//		typedef Iterator<T> iterator;
		typedef  typename allocator_type::pointer pointer;
		typedef pointer iterator;
		typedef T& reference;
		typedef const T& const_reference;
		typedef const_pointer const_iterator;
		typedef size_t size_type;

	protected:
		size_type _size;
		size_type _capacity;
        value_type 			*_data;
		allocator_type		_alloc_;

	public:
		Vector() : _size(0), _capacity(0), _data(NULL) { }

		Vector(const size_type n) : _size(n), _capacity(n) {
			_data = _alloc_.allocate(n);
		}

		Vector(const size_type n, const T& val) : _size(n), _capacity(n * 2){
			_data = _alloc_.allocate(n);
			for (size_type i = 0; i < n; ++i) {
				_data[i] = val;
			}
		}

		~Vector() {
			std::cerr << "IM HERE";
		}

	public:
		reference operator[](size_type n) const { return *(_data + n); }
		reference operator[](size_type n) { return *(_data + n); }
		//capacity
		bool empty() { return size() == 0; }
		size_type	size() { return _size; }
		size_type capacity() const { return _capacity; }

		void _copy_(value_type *newData, size_type start, size_type end) {
			for (size_type i = start; i < end; ++i) {
				newData[i] = _data[i];
			}
		}

		void reserve (size_type n) {
			if (n <= _capacity)
				return;
			value_type	*newData;
			newData = _alloc_.allocate(n);
			_copy_(newData, 0, size());
			_alloc_.deallocate(_data, size());
			_data = newData;
			_capacity = n;
		}

		iterator insert (iterator position, const value_type& val) {

		}
		reference back() { return _data[_size - 1]; }
		const_reference back() const { return _data[_size - 1]; }

		iterator erase(iterator position) {
			iterator tmp = position + 1;
			while (tmp != end()) {
				*position = *tmp;
				position++;
				tmp++;
			}
//			_alloc_.destroy(&back());
			_size--;
			return position;
		}
		void resize(size_type n, value_type val = value_type()) {
			if (n < size()) {
				_reduce_elements_(n);
			} else if (n > size()) {
				if (n > capacity()) {
					reserve(ft::max(capacity() * 2, n));
				}
				for (size_type i = size(); i < n; ++i) {
					_data[i] = val;
				}
				_size = n;
			}
		}

		void _reduce_elements_(size_type n) {
			for (size_type i = n; i < size(); ++i) {
				_alloc_.destroy(&back());
			}
			_size = n;
		}

	public:
		iterator end() { return iterator(&_data[_size]); }
		iterator begin() { return iterator(_data); }
		const_iterator cend() const { return _data - size();}
		const_iterator cbegin() const { return _data; }

        //modifiers
		void	_increment_capacity() {
			if (_capacity == 0) {
				_capacity = 1;
			} else if (_size >= _capacity) {
				_capacity *= 2;
			}
		}

    public:
        void push_back(const value_type& value) {
			value_type *newData;
			_increment_capacity();
			newData = _alloc_.allocate(_size + 1);
			for(size_type i = 0; i < _size; i++) {
				newData[i] = _data[i];
			}
			newData[_size] = value;
			_alloc_.deallocate(_data, _size);
			_data = newData;
			_size++;
        }
	};
}
#endif