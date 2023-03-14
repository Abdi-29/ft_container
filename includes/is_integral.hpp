#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <type_traits>
#include "remove_cv.hpp"

namespace ft {
	template <typename T> struct is_integral_imp		: public std::false_type{};

	template <> struct is_integral_imp<bool>			: public std::true_type{};
	template <> struct is_integral_imp<char>			: public std::true_type{};

	template <> struct is_integral_imp<signed char>		: public std::true_type{};
	template <> struct is_integral_imp<signed short>	: public std::true_type{};
	template <> struct is_integral_imp<signed int>		: public std::true_type{};
	template <> struct is_integral_imp<signed long>		: public std::true_type{};

	template <> struct is_integral_imp<unsigned char>	: public std::true_type{};
	template <> struct is_integral_imp<unsigned short>	: public std::true_type{};
	template <> struct is_integral_imp<unsigned int>	: public std::true_type{};
	template <> struct is_integral_imp<unsigned long>	: public std::true_type{};

	template<typename T> struct is_integral: is_integral_imp<ft::remove_cv<T> > {};
}

#endif //IS_INTEGRAL_HPP
