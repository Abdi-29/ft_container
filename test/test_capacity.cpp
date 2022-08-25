#include "abbassert.hpp"
#include "vector.hpp"
#include <vector>

template<class T>
void printContainer(const std::vector<T>& v, const ft::Vector<T>& myvector) {
	for (size_t i = 0; i < myvector.size(); ++i) {
		std::cout << "my vector " << myvector[i] << " and " << v[i] << std::endl;
	}
}

void testEmpty(void) {
	std::vector<int> v;
	ft::Vector<int> myvector;
	ABBASSERT("Vector empty: ", myvector.empty() == v.empty());
}

void testInsert(void) {
	ft::Vector<int> myvector(13,100);
	std::vector<int> v(13,100);

	ft::Vector<int>::iterator it;
	std::vector<int>::iterator vit;

	vit = v.begin() + 5;
	it = myvector.begin() + 5;

	myvector.insert(it, 200);
	v.insert(vit, 200);

	int myarray [] = { 501,502,503 , 504, 405};

	myvector.insert(myvector.begin(), myarray, myarray + 3);
	v.insert(v.begin(), myarray, myarray + 3);

	for (size_t i = 0; i < v.size(); ++i) {
		std::cout << myvector[i] << " and ori " << v[i] << std::endl;
	}
	ABBASSERT("Vector insert: ", myvector.size() == v.size());
}

void testErase(void) {
	ft::Vector<int> myvector(13,100);
	std::vector<int> v(13,100);

	myvector.erase(myvector.begin() + 2, myvector.begin() + 5);
	v.erase(v.begin() + 2, v.begin() + 5);

	std::vector<int>::iterator it = v.begin();
	ft::Vector<int>::iterator my;

	for (my = myvector.begin(); my != myvector.end(); ) {
		if (*my % 2 == 0) {
			my = myvector.erase(my);
			it = v.erase(it);
		} else {
			my++;
			it++;
		}
	}
	ABBASSERT("Vector erase: ", myvector.size() == v.size());
	printContainer(v, myvector);
}