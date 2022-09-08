#include <vector>
#include "vector.hpp"
#include "abbassert.hpp"
#include "reverse_iterator.hpp"

void testEmpty(void);
void testInsert(void);
void testErase(void);
void testSwap(void);
void testData(void);

int main(void) {
//	testEmpty();
//	testErase();
//	testInsert();
//	testSwap();
//	testData();
	std::vector<int> v;
	ft::Vector<int> my;

	for (size_t i = 0; i < 5; ++i) {
		v.push_back(i);
		my.push_back(i);
	}

	std::vector<int>::reverse_iterator in = v.rbegin();
	ft::Vector<int>::reverse_iterator mine = my.rbegin();
	std::cout << "rev vec = " << *in << " my " << *mine;
//	ft::Iterator<std::random_access_iterator_tag, int> it;
//	ft::reverse_iterator<decltype(nit)> itr(nit);
//	std::vector<int>::reverse_iterator hi;
//	ft::Vector<int>::reverse_iterator it = my.rbegin();
//	std::cout << "testing " << *it << std::endl;
}