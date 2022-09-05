#ifndef FT_CONTAINER
#define FT_CONTAINER

#include <iostream>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "util.hpp"
#include "enable_if.hpp"

namespace ft {
	template < class T, class Allocator = std::allocator<T> >
	class Vector {
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef  typename allocator_type::const_pointer	const_pointer;
		typedef  typename allocator_type::pointer pointer;
		typedef  typename allocator_type::reference reference;
		typedef  typename allocator_type::const_reference const_reference;
		typedef  typename allocator_type::const_pointer const_iterator;
		typedef pointer iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
//		typedef const_pointer reverse_iterator;
//		typedef const pointer const_reverse_iterator;
//		typedef T& reference;
//		typedef const T& const_reference;
//		typedef const_pointer const_iterator;
		typedef size_t size_type;

	private:
		size_type _size;
		size_type _capacity;
		value_type 			*_data;
		allocator_type		_alloc_;

	public:
		Vector() : _size(0), _capacity(0), _data(NULL) { }

		Vector(const size_type n) : _size(n), _capacity(n * 2) {
			_data = _alloc_.allocate(_capacity * sizeof(T));
			for (size_type i = 0; i < n; ++i) {
				_alloc_.construct(_data + i, 0);
			}
		}

		Vector(const size_type n, const T& val) : _size(n), _capacity(n * 2) {
			_data = _alloc_.allocate(_capacity * sizeof(T));
			for (size_type i = 0; i < n; ++i) {
				_alloc_.construct(end() - i - 1, val);
			}
		}

		Vector& operator=(const Vector& other) {
			this->_size = other._size;
			this->_capacity = other._capacity;
			this->_data = other._data;
			this->_alloc_ = other._alloc_;
			return *this;
		}

//		Vector& operator==(const Vector& other) {
//			this->_size = other._size;
//			this->_capacity = other._capacity;
//			this->_data = other._data;
//			this->_alloc_ = other._alloc_;
//			return *this;
//		}

		~Vector() {
			if (!_data) {
				return;
			}
			for (size_type i = 0; i < size(); ++i) {
				_alloc_.destroy(_data + i);

			}
			_alloc_.deallocate(_data, capacity());
			_capacity = 0;
			_data = NULL;
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

		allocator_type get_allocator() const {
			return _alloc_;
		}

	public:

		reference operator[](size_type n) const { return *(_data + n); }
		reference operator[](size_type n) { return *(_data + n); }

		reference at( size_type pos) {
			if (pos > size()) {
				throw std::out_of_range("hello");
			}
			return _data[pos];
		}

		value_type* data() noexcept {
			return _data;
		}

		const value_type* data() const noexcept {
			return _data;
		}

		const_reference at( size_type pos ) const {
			if (pos > size()) {
				throw std::out_of_range("hello");
			}
			return _data[pos];
		}

		reference front() {
			return _data[0];
		}

		const_reference front() const {
			return _data[0];
		}

		reference back() {
			return _data[size() - 1];
		}

		const_reference back() const {
			return _data[size() - 1];
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end() - 1);
		}

//		const_reverse_iterator rbegin() const {
//			return end() - 1;
//		}

		reverse_iterator rend() {
			return begin();
		}
//
//		const_reverse_iterator rend() const {
//			return begin();
//		}



		void clear() {
			for (size_type i = 0; i < size(); ++i) {
				_alloc_.destroy(_data[i]);
			}
			_size = 0;
		}

		void pop_back() {
			_alloc_.destroy(&back());
			_size--;
		}

		void swap(Vector& other) {
			ft::swap(this->_size, other._size);
			ft::swap(this->_capacity, other._capacity);
			ft::swap(this->_data, other._data);
			ft::swap(this->_alloc_, other._alloc_);
		}
		//capacity
		bool empty() { return size() == 0; }
		size_type	size() const { return _size; }
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
			newData = _alloc_.allocate(n * sizeof(T));
			_copy_(newData, 0, size());
			for (size_type i = 0; i < size(); ++i) {
				_alloc_.destroy(_data + i);
			}
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
			iterator tmp = position;
			iterator last = end();
			if (size() + n > capacity()) {
				reserve((size() + n) * 2);
			}
			size_type distance = last - tmp;
			position = end() + n;
			size_type i = 0;
			while (i <= distance) {
				_alloc_.construct(position, *last);
				last--;
				position--;
				i++;
			}
			i = 0;
			while (i < n) {
				_alloc_.construct(position, val);
				position--;
				i++;
			}
			_size += n;
			return position;
		}

		template <class InputIterator>
		iterator _fill_insert_range(iterator position, InputIterator first, InputIterator last) {
			size_type distance = (last - first);
			iterator test = position;
			iterator tmp = end();
			if (distance + size() > capacity()) {
				reserve((distance + size()) * 2);
				_size += distance;
			}
			position = tmp + distance;
			size_type i = 0;
			size_type end = (position - test) - distance;
			while (i < end) {
				_alloc_.construct(position, *tmp);
				i++;
				position--;
				tmp--;
			}
			_alloc_.construct(position, *test);
			position -= distance;
			while (first != last) {
				_alloc_.construct(position, *first);
				position++;
				first++;
			}
			_size += distance;
			return test;
		}

		template <class InputIterator>
		typename enable_if<true>::type
		insert(iterator position, InputIterator first, InputIterator last) {
			position = _fill_insert_range(position, first, last);
		}

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
		iterator end() {
			std::cerr << "iterator\n" << size();
			return _data + size();
		}

		iterator begin() {
			return _data;
		}

		const_iterator cend() const {
			return _data + size();
		}

		const_iterator cbegin() const {
			return _data;
		}

		//modifiers
		void	_increment_capacity() {
			if (_capacity > _size) {
				return;
			}
			reserve(ft::max(size_type(1), _capacity *= 2));
		}

	public:
		void push_back(const value_type& value) {
			_increment_capacity();
			std::cerr << "capacity " << _capacity << std::endl;
			_alloc_.construct(end(), value);
			std::cerr << "size " << _size << std::endl;
			_size++;
		}
	};
}
#endif