#define CATCH_CONFIG_MAIN
#if 0
	#include <vector>
	namespace ft = std;
#else
	#include "vector.hpp"
#endif
#include "catch2.hpp"

TEST_CASE( "vectors can be sized and resized", "[vector]" ) {
	ft::vector<int> m(5);

	REQUIRE(m.size() == 5);
	REQUIRE( m.capacity() >= 5 );

	SECTION( "resizing bigger changes size and capacity" ) {
		m.resize(10);

		REQUIRE( m.size() == 10);
		REQUIRE( m.capacity() >= 10 );
	}
	SECTION( "resizing smaller changes size but not capacity" ) {
		m.resize(0);

		REQUIRE(m.size() == 0);
		REQUIRE( m.capacity() >= 5 );
	}
	SECTION( "reserving bigger changes capacity but not size" ) {
		m.reserve(10);

		REQUIRE( m.size() == 5);
		REQUIRE( m.capacity() >= 10 );
	}
	SECTION( "reserving smaller does not change size or capacity" ) {
		m.reserve(0);

		REQUIRE(m.size());
		REQUIRE( m.capacity() >= 5 );
	}
}
