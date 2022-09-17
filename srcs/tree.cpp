#include "../includes/rb_tree.hpp"
#include "../includes/pair.hpp"
#include <map>
#include <utility>

template<
		class Key,
		class T,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
>
class value_compare: std::binary_function<ft::pair<const Key, T>, ft::pair<const Key, T>, bool> {
public:
	typedef ft::pair<const Key, T> value_type;
protected:
	Compare comp;
public:
	bool operator()( const value_type& lhs, const value_type& rhs ) const {
		return comp(lhs.first_type, rhs.first_type);
	}
	value_compare(Compare c): comp(c) {}
};

int main(void) {
	ft::rb_tree<int, int> test;
	int i = 10;
	ft::pair<int, int> value;
	value = ft::make_pair(i, i);
	test.insert(value);
}