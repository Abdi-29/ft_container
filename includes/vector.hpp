#ifndef FT_CONTAINER
#define FT_CONTAINER

#include <iostream>
#include "iterator.hpp"

namespace ft {
	template < class T, class Allocator = std::allocator<T> >
	class Vector {
	public:
        typedef T value_type;
		typedef Allocator allocator_type;
		typedef  typename allocator_type::pointer pointer;
		typedef  typename allocator_type::const_pointer	const_pointer;
		typedef  typename allocator_type::reference		reference;
		typedef  typename allocator_type::const_reference	const_reference;
		typedef Iterator<T> iterator;
		typedef const_pointer const_iterator;
		typedef size_t size_type;

//		typedef typename value_type:: pointer;

	protected:
		allocator_type		_alloc_;
        value_type 			*_data;
		size_type _size;
		size_type _capacity;

	public:
		Vector() : _size(0), _capacity(0) { }

	public:
		//capacity
		bool empty() {
			return size() == 0;
		}

		size_type	size() {
			return _size;
		}

		size_type capacity() const {
			return _capacity;
		}

		void reserve (size_type n) {
			if (n > _capacity)
				_capacity += n;
		}

		void resize(size_type n, value_type val) {
			(void)n;
			(void)val;
		}
		void resize(size_type n) {
			_size = n;
		}

	public:
	//iterator
	public:
		iterator end() {
			return iterator(&_data[_size]);
		}

		iterator begin() {
			return iterator(_data);
		}

		const_iterator cend() const {
			return _data - size();
		}

		const_iterator cbegin() const {
			return _data;
		}

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