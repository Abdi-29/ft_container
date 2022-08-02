#ifndef FT_CONTAINER
#define FT_CONTAINER

#include <iostream>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class Vector {
	public:
		Vector() : _size(0), _capacity(0){ }

	private:
		size_t _size;
		size_t _capacity;

	public:
		//capacity
		bool empty() {
			return size() == 0;
		}

		size_t	size() {
			return _size;
		}

		size_t capacity() const {
			return _capacity;
		}

		size_t reserve(size_t  size) const {
			if (_capacity > size)
				return _capacity;
			return size;
		}

		template<typename value_type>
		void resize(size_t n, value_type val) {
			(void)n;
			(void)val;
		}
		void resize(size_t n)
		{
			_size = n;
		}
	};
}
#endif