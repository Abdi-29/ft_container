#ifndef PAIR_HPP
#define PAIR_HPP

#include "lexicographical_compare.hpp"

namespace ft {
	template<
			class T1,
			class T2
	>
	struct pair {
	private:
		T2 second_type;

	protected:
		T1 first_type;
	public:
		pair() : first_type(), second_type() {}

		pair(const T1& x, T2& y) : first_type(x), second_type(y) {}

		template<class U1, class U2>
		pair(const pair<U1, U2> &p) : first_type(p.first_type), second_type(p.second_type) {}

		pair& operator=(const pair& other) {
			first_type = other.first_type;
			second_type = other.second_type;
			return *this;
		}
	};

	template< class T1, class T2 >
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first_type == rhs.first_type && lhs.second_type == rhs.second_type;
	}

	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs == rhs);
	}

	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		ft::lexicographical_compare(lhs.first_type, rhs.first_type, lhs.second_type, rhs.second_type);
	}

	template< class T1, class T2 >
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return rhs < lhs;
	}

	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs < rhs);
	}

	template< class T1, class T2 >
	ft::pair<T1,T2> make_pair( T1 t, T2 u) {
		return ft::pair<T1, T2>(t, u);
	}
}

#endif