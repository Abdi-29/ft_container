#include <vector>
#include "vector.hpp"

#define RED  "\x1B[31m"
#define GREEN  "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define RESET  "\x1B[0m"

#define ABBASSERT(message, expr) do { \
	std::cout << YELLOW << (message) << RESET; \
	if (expr) { \
		std::cout << GREEN "pass\n" RESET; \
	} else { \
		std::cout << RED "fail\n" RESET; \
	} \
} while (0)

template<typename T>
void TestVector(std::vector<T> v, ft::Vector<T> mine) {
	ABBASSERT("Vector Size: ", v.size() == mine.size());
	std::cout << "vector " << v.size() << " and " << mine.size() << "\n";
}

template<typename T>
void TestCapacity(std::vector<T> v, ft::Vector<T> mine) {
	ABBASSERT("Vector Capacity: ", mine.capacity() >= v.capacity());
	std::cout << "vector " << v.capacity() << " and " << mine.capacity() << "\n";
}

int main(void) {
	ft::Vector<int> myvector (3,100);
	std::vector<int> v(3,100);

//	myvector.assign(7, 100);
//	v.assign(7, 100);
	for (size_t i = 0; i < 10; ++i) {
		myvector.push_back(i);
		v.push_back(i);
	}
	ft::Vector<int>::iterator it;
	std::vector<int>::iterator vit;
	vit=v.begin() + 1;
	it = myvector.begin() + 1;
	myvector.insert(it, 200);
	v.insert(vit, 200);
	int myarray [] = { 501,502,503 };
	myvector.insert (myvector.begin(), myarray, myarray+3);
	v.insert (v.begin(), myarray, myarray+3);
//	std::cout << "size " << myvector.size() << " and " << v.size();
	for (size_t i = 0; i < myvector.size(); ++i) {
		std::cout << myvector[i] << " and ori " << v[i] << std::endl;
	}
//	vtest.assign(vit, v.end()-1);
//	test.assign(it, myvector.end()-1);

//	for (size_t i = 0; i < v.size(); ++i) {
//		std::cout << v[i] << " and myvector " << myvector[i] << std::endl;
//	}
//	std::cout << test.size();
//	myvector.erase(myvector.begin() + 5);
//	v.erase(v.begin() + 5);
//	myvector.erase (myvector.begin(),myvector.begin()+2);
//	v.erase(v.begin(),v.begin()+2);
//
//	// erase the first 3 elements:
//
//	std::cout << "myvector contains:";
//	for (unsigned i=0; i< v.size(); ++i)
//		std::cout << ' ' << myvector[i] << " and " << v[i];
//	std::cout << '\n';
//
//	TestVector(v, myvector);
//	TestCapacity(v, myvector);
//
//	v.resize( 5 );
//	myvector.resize(5);
////
	TestVector(v, myvector);
	TestCapacity(v, myvector);
//
//	mine.resize(8, 100);
//	v.resize( 8, 100 );
//
//	TestVector(v, mine);
//	TestCapacity(v, mine);
//
//	v.resize( 12 );
//	mine.resize(12);
//
//	TestVector(v, mine);
//	TestCapacity(v, mine);
//
//	TestVector(v, mine);
//	for (size_t i = 0; i < mine.size(); ++i) {
//		std::cout << " " << mine[i];
//	}

}


