#include "vector.hpp"
#include <vector>
#include "catch2.hpp"

TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

	std::vector<int> v( 5 );
	ft::Vector<int> m(5);

	REQUIRE( v.size() == m.size() );
	REQUIRE( m.capacity() >= 5 );

	SECTION( "resizing bigger changes size and capacity" ) {
		v.resize( 10 );
		m.resize(10);

		REQUIRE( v.size() == m.size() );
		REQUIRE( m.capacity() >= 10 );
	}
	SECTION( "resizing smaller changes size but not capacity" ) {
		v.resize( 0 );
		m.resize(0);

		REQUIRE( v.size() == m.size());
		REQUIRE( m.capacity() >= 5 );
	}
	SECTION( "reserving bigger changes capacity but not size" ) {
		v.reserve( 10 );
		m.reserve(10);

		REQUIRE( v.size() == m.size() );
		REQUIRE( m.capacity() >= 10 );
	}
	SECTION( "reserving smaller does not change size or capacity" ) {
		v.reserve( 0 );
		m.reserve(0);

		REQUIRE( v.size() == m.size() );
		REQUIRE( m.capacity() >= 5 );
	}
}


//void testInsert(void) {
//	ft::Vector<int> myvector(13,100);
//	std::vector<int> v(13,100);
//
//	ft::Vector<int>::iterator it;
//	std::vector<int>::iterator vit;
//
//	vit = v.begin() + 5;
//	it = myvector.begin() + 5;
//
//	myvector.insert(it, 200);
//	v.insert(vit, 200);
//
//	int myarray [] = { 501,502,503 , 504, 405};
//
//	myvector.insert(myvector.begin(), myarray, myarray + 3);
//	v.insert(v.begin(), myarray, myarray + 3);
//
//	for (size_t i = 0; i < v.size(); ++i) {
//		std::cout << myvector[i] << " and ori " << v[i] << std::endl;
//	}
//	ABBASSERT("Vector insert: ", myvector.size() == v.size());
//}
//
//void testErase(void) {
//	ft::Vector<int> myvector(13,100);
//	std::vector<int> v(13,100);
//
//	myvector.erase(myvector.begin() + 2, myvector.begin() + 5);
//	v.erase(v.begin() + 2, v.begin() + 5);
//
//	std::vector<int>::iterator it = v.begin();
//	ft::Vector<int>::iterator my;
//
//	for (my = myvector.begin(); my != myvector.end(); ) {
//		if (*my % 2 == 0) {
//			my = myvector.erase(my);
//			it = v.erase(it);
//		} else {
//			my++;
//			it++;
//		}
//	}
//	ABBASSERT("Vector erase: ", myvector.size() == v.size());
//	printContainer(v, myvector);
//}
//
//template <class T>
//void test(const ft::Vector<T>& a, std::string message) {
//	std::cout << message << " ";
//	for (size_t i = 0; i < a.size(); ++i) {
//		std::cout << a[i] << " ";
//	}
//	std::cout << std::endl;
//}
//void testSwap(void) {
//	ft::Vector<int> myvector(2,100);
//	ft::Vector<int> v(2,200);
//
//	test(myvector, "a");
//	test(v, "b");
//	myvector.swap(v);
//	test(myvector, "a");
//	test(v, "b");
//}
//
//void testData(void) {
//	ft::Vector<int> myvector (5);
//
//	int* p = myvector.data();
//
//	*p = 10;
//	++p;
//	*p = 20;
//	p[2] = 100;
//
//	std::cout << "myvector contains:";
//	for (unsigned i=0; i<myvector.size(); ++i)
//		std::cout << ' ' << myvector[i];
//	std::cout << '\n';
//}