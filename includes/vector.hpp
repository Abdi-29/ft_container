#ifndef FT_CONTAINER
#define FT_CONTAINER

#include <iostream>

namespace ft {
	template < class T, class Alloc = std::allocator<T> >
	class Vector {
        typedef T value_type;
	private:
        T *_array;
		size_t _size;
		size_t _capacity;
	public:
		Vector() : _size(0), _capacity(0) { }

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

        //modifiers
    public:
        void push_back(const value_type& value) {
            _array  = new value_type (7);
            _array[0] = value;
        }
        //TODO implement the beging and end function so you can test the push_back function
        //TODO resize function to finish and do more testing
	};
}
#endif