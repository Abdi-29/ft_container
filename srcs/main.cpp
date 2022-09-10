#include <vector>
#include "vector.hpp"
#include "abbassert.hpp"
#include "reverse_iterator.hpp"

int main(void) {
	std::vector<int> v;
	ft::vector<int> my;

	for (size_t i = 0; i < 5; ++i) {
		v.push_back(i);
		my.push_back(i);
	}

	std::vector<int>::reverse_iterator in = v.rbegin() + 3;
	ft::vector<int>::reverse_iterator lol = my.rbegin() + 3;
	std::cout << "rev vec = " << *in << " my " << *lol;
	//TODO const_reverse_iterator to implement or find a way to make work with the normal reverse_iterator
}