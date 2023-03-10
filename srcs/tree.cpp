#include "../includes/rb_tree.hpp"
#include <map>

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
	typedef ft::rb_tree<ft::pair<int, int>, std::less<int> > tree;
	ft::rb_node<int> t;
	tree test;
	ft::pair<int, int> ok;
	ok.first = 12;
	ok.second = 24;
	test.insert(ok);
//	test.insert(ft::make_pair(13, 14));
	test.insert(ft::make_pair(13, 11));
	test.insert(ft::make_pair(15, 14));
	test.insert(ft::make_pair(9, 11));
	test.insert(ft::make_pair(15, 14));
//	ft::rb_iterator<ft::pair<const int, int> > it = test.begin();
//	std::cout << "iterator = " << it->first;
//	it++;
//	std::cout << "  iterator = " << it->first;
	for (tree::iterator it = test.begin(); it != test.end(); it++) {
		test.erase(it);
		break;
		std::cout << "testing: " << it->first << " ";
	}
//	std::cout << "hello\n";
//	test.print_node();
//	std::cout << "testing " << test.insert(i)->_value;
}