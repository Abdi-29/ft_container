#include "vector.hpp"
#include <vector>
#include "catch2.hpp"

TEST_CASE("TESTING EMPTY", "EMPTY") {
    std::vector<int> v;
    ft::Vector<int> myvector;
    REQUIRE(v.empty() == myvector.empty());
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

template <class T>
void test(const ft::Vector<T>& a, std::string message) {
	std::cout << message << " ";
	for (size_t i = 0; i < a.size(); ++i) {
		std::cout << a[i] << " ";
	}
	std::cout << std::endl;
}
void testSwap(void) {
	ft::Vector<int> myvector(2,100);
	ft::Vector<int> v(2,200);

	test(myvector, "a");
	test(v, "b");
	myvector.swap(v);
	test(myvector, "a");
	test(v, "b");
}

void testData(void) {
	ft::Vector<int> myvector (5);

	int* p = myvector.data();

	*p = 10;
	++p;
	*p = 20;
	p[2] = 100;

	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}