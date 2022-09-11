#ifndef LESS_HPP
#define LESS_HPP

namespace ft {
	template<
			class Arg1,
			class Arg2,
			class Result
	> struct binary_function;

	template<class T>
	struct less : ft::binary_function<T, T, bool> {
		bool operator()(const T& lhs, const T& rhs) const {
			return lhs < rhs;
		}
	};
}

#endif