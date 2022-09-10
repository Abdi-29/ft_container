#ifndef UTIL_HPP
#define UTIL_HPP

namespace ft {
	template<typename T>
	 T max(T a, T b) {
		return (a > b) ? a : b;
	}

	template<class T>
	void swap(T& a, T& b) {
		T tmp;

		tmp = a;
		a = b;
		b = tmp;
	}
}

#endif
