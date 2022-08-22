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
		typedef Iterator<T> iterator;
		typedef  typename allocator_type::pointer pointer;
//		typedef pointer iterator;
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

	//MEMBER FUNCTION
	public:
		void assign(iterator first, iterator last) {
			size_type		distance;

			distance = last - first;
			reserve(distance);
			while (first != last) {
				*first = *last;
				first++;
			}
			_size = distance;
			_capacity = distance;
		}

		void assign(size_type n, const value_type& val) {
			reserve(n);
			for (size_type i = 0; i < n; ++i) {
				_data[i] = val;
			}
			_size = n;
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
			std::cerr << "debugging " << n << std::endl;
			if (n <= _capacity)
				return;
			value_type	*newData;
			newData = _alloc_.allocate(n);
			_copy_(newData, 0, size());
			_alloc_.deallocate(_data, capacity());
			_data = newData;
			_capacity = n;
		}

		iterator insert(iterator position, const value_type& val) {
			return _fill_insert(position, 1, val);
		}

		void insert(iterator position, size_type n, const value_type& val) {
			position = _fill_insert(position, n, val);
		}

		iterator _fill_insert(iterator position, size_type n, const value_type& val) {
			if (size() + n > capacity()) {
				reserve((size() + n) * 2);
			}
			iterator tmp = position;
			iterator cy = end();
			position = end();
			while (cy != tmp) {
				cy--;
				*position = *cy;
				position--;
			}
			size_type i = 0;
			while (i < n) {
				*position = val;
				i++;
			}
			_size += n;
			return position;
		}

		template <class InputIterator>
		iterator _fill_insert_range(iterator position, InputIterator first, InputIterator last) {
			size_type distance = last - first;
			std::cout << "debugging " << distance << std::endl;
			iterator test = position;
			if (distance > capacity()) {
				reserve(distance * 2);
			}
			size_type tmp = end() - position;
			size_type i = 0;
			while (first != last) {
				*position = *first;
				position++;
				first++;
			}
			std::cout << "IM TESTING " << *test << std::endl;
			while (i < tmp) {
				*position = *test;
				position++;
				test++;
				i++;
			}
			_size += distance;
			return position;
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last) {
			position = _fill_insert_range(position, first, last);
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
			_alloc_.destroy(&back());
			_size--;
			return position;
		}

		iterator erase(iterator first, iterator last) {
			size_type distance = last - first;

			while (last != end()) {
				*first = *last;
				first++;
				last++;
			}
			_size -= distance;
			for (size_type i = 0; i < distance; ++i) {
				_alloc_.destroy(&back());
			}
			return first;
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