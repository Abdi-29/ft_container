#ifndef FT_CONTAINER
#define FT_CONTAINER

#include <iostream>
#include <iterator>
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "util.hpp"
#include <type_traits>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"

namespace ft {
	template < class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef  typename allocator_type::const_pointer	const_pointer;
		typedef  typename allocator_type::pointer pointer;
		typedef  typename allocator_type::reference reference;
		typedef  typename allocator_type::const_reference const_reference;
		typedef  typename allocator_type::const_pointer const_iterator;
		typedef pointer iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator; //TODO create your own reverse iterator
		typedef std::reverse_iterator<const iterator> const_reverse_iterator;
		typedef size_t size_type;

	private:
		allocator_type	_alloc_;
		size_type 		_size;
		size_type 		_capacity;
		value_type 		*_data;

	public:
		vector() : _size(0), _capacity(0), _data(NULL) { }
		explicit	vector(const Allocator& alloc): _alloc_(alloc), _size(0), _capacity(0), _data(NULL) {}
		explicit	vector(const vector& rhs)
				: _alloc_(rhs._alloc_), _size(rhs._size), _capacity(rhs.size()), _data(_alloc_.allocate(rhs.size())) {
			try	{
				std::uninitialized_copy(rhs.begin(), rhs.end(), begin());
			}
			catch(...) {
				_alloc_.deallocate(_data, capacity());
				throw;
			}
		}

		explicit vector(size_type n, const T& value = T(), const Allocator& alloc = Allocator())
				: _alloc_(alloc), _size(n), _capacity(n), _data(_alloc_.allocate(n)) {
			try {
				std::uninitialized_fill_n(begin(), n, value);
			} catch(...) {
				_alloc_.deallocate(_data, capacity());
				throw;
			}
		}

		template< class InputIt>
		vector( InputIt first, InputIt last,
				const Allocator& alloc = Allocator(),
		typename ft::enable_if<!ft::is_integral<InputIt>::value, bool>::type = true)
				: _alloc_(alloc), _size(0), _capacity(0), _data(NULL) {
			try {
				typedef typename ft::is_integral<InputIt>::type	Integral;
				range_alloc(first, last, Integral());
				insert(begin(), first, last);
			} catch(...) {
				_alloc_.deallocate(_data, capacity());
				throw;
			}
		}

		vector& operator=(const vector& other) {
            if(this == &other) {
                return *this;
            }
			_alloc_ = other.get_allocator(); //double check
			_data = _alloc_.allocate(other.capacity());
			assign(other.begin(), other.end());
			std::cout << "the problem is here\n";
			return *this;
		}

		~vector() {
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

		template<class InputIt>
		void range_alloc(InputIt first, InputIt last, std::false_type) {
			_size = std::distance(first, last);
			_capacity = size();
			_data = _alloc_.allocate(size());
		}

	public:
		template <typename InputIt>
		typename ft::enable_if<!ft::is_integral<InputIt>::value, void>::type
		assign(InputIt first, InputIt last) {
			clear();
			insert(begin(), first, last);
		}

		void assign(size_type n, const value_type& val) {
			clear();
			reserve(n);
			std::uninitialized_fill_n(begin(), n, val);
			_size = n;
		}

		allocator_type get_allocator() const {
			return _alloc_;
		}

	public:

		reference operator[](size_type n) const { return *(_data + n); }
		reference operator[](size_type n) { return *(_data + n); }

		reference at(size_type pos) {
			if (pos >= size()) {
				throw std::out_of_range("vector");
			}
			return _data[pos];
		}

		value_type* data() { return _data; }
		const value_type* data() const { return _data; }

		const_reference at( size_type pos ) const {
			if (pos >= size()) {
				throw std::out_of_range("vector");
			}
			return _data[pos];
		}

		reference front() { return _data[0]; }
		const_reference front() const { return _data[0];}
		reference back() { return *(end() - 1);}
		const_reference back() const { return *(end() - 1);}
		reverse_iterator rbegin() { return reverse_iterator(end());}
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end());}
		reverse_iterator rend() { return reverse_iterator(begin());}
		const_reverse_iterator rend() const { return const_reverse_iterator(begin());}

		void clear() {
			erase(begin(), end());
		}

		void pop_back() {
			_alloc_.destroy(end() - 1);
			_size--;
		}

		void swap(vector& other) {
			ft::swap(this->_size, other._size);
			ft::swap(this->_capacity, other._capacity);
			ft::swap(this->_data, other._data);
			ft::swap(this->_alloc_, other._alloc_);
		}
		//capacity
		bool empty() { return size() == 0; }
		size_type	size() const { return _size; }
		size_type	max_size() const { return _alloc_.max_size(); }
		size_type capacity() const { return _capacity; }

		void _copy_(value_type *newData, size_type end) {
			for (size_type i = 0; i < end; ++i) {
				_alloc_.construct(newData + i, *(begin() + i));
				_alloc_.destroy(begin() + i);
			}
			_alloc_.deallocate(_data, _capacity);
			_data = newData;
		}

		void reserve(size_type n) {
			if(n > max_size()) {
				throw std::length_error("vector");
			}
			if (n <= _capacity)
				return;
			value_type	*newData = _alloc_.allocate(n);
			_copy_(newData, size());
			_capacity = n;
		}

		iterator insert(iterator position, const value_type& val) {
			return _fill_insert(position, 1, val);
		}

		void insert(iterator position, size_type n, const value_type& val) {
			position = _fill_insert(position, n, val);
		}

		iterator _fill_insert(iterator position, size_type n, const value_type& val) {
			iterator last = end();
			if (size() + n > capacity()) {
				reserve((size() + n) * 2);
			}
			size_type distance = last - position; //change it as siebe was failed because of that
			position = end() + n;
			size_type i = 0;
			while (i < distance) {
				_alloc_.construct(position, *(end() - i - 1));
				position--;
				i++;
			}
			position--;
			_alloc_.construct(position, val);
			_size += n;
			return position;
		}

		void	move_forward(iterator pos, size_type n) {
			size_type i = end() - pos;
			size_type index = pos - begin();

			reserve(size() + n);
			pos = begin() + index;
			while(i) {
				i--;
				_alloc_.construct(pos + n + i, *(pos + i));
				_alloc_.destroy(pos + i);
			}
			std::cout << "testing: " << i << " inde: " << index << std::endl;
		}

		template <class InputIt>
		void  _fill_insert_range(iterator pos, InputIt first, InputIt last) {
			size_type count = std::distance(first, last);
			size_type index = std::distance(begin(), pos);
			vector<T, Allocator>	tmp;

			for(; first != last; first++)
				tmp.push_back(*first);
			move_forward(pos, count);
			std::uninitialized_copy(tmp.begin(), tmp.end(), begin() + index);
		}

		template <class InputIterator>
		typename std::enable_if<!std::is_integral<InputIterator>::value, void>::type
		insert(iterator position, InputIterator first, InputIterator last) {
			_fill_insert_range(position, first, last);
		}

		iterator erase(iterator pos) {
			return erase(pos, pos + 1);
		}

		iterator erase(iterator first, iterator last) {
			size_type distance = last - first;

			std::move(last, end(), first);
			while(distance) {
				pop_back();
				distance--;
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
			return _data + size();
		}

		const_iterator end() const {
			return _data + size();
		}

		iterator begin() {
			return _data;
		}

		const_iterator begin() const {
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
			reserve(ft::max(size_type(1), capacity() * 2));
		}

	public:
		void push_back(const value_type& value) {
			_increment_capacity();
			_alloc_.construct(end(), value);
			_size++;
		}
	};

	template<typename T, typename Alloc>
	bool operator<(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
		return (lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}
	template<typename T, typename Alloc>
	bool operator>=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
		return !(x < y);
	}
	template<typename T, typename Alloc>
	bool operator<=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
		return !(x > y);
	}
	template<typename T, typename Alloc>
	bool operator>(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
		return !(y < x);
	}
	template<typename T, typename Alloc>
	bool operator==(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
		if(x.size() == x.size()) {
			return std::equal(x.begin(), x.end(), y.begin()); //TODO implement your own eqaul
		}
		return false;
	}
	template<typename T, typename Alloc>
	bool operator!=(const vector<T, Alloc>& x, const vector<T, Alloc>& y) {
		return !(x == y);
	}
}
#endif
