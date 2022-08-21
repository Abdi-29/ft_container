#include "vector.hpp"
#include "catch_amalgamated.hpp"
#include <vector>

TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

// For each section, vector v is anew:

	std::vector<int> v( 5 );
	ft::Vector<int>	mine(5);

//	REQUIRE( v.size() == mine.size() );
//	REQUIRE( v.capacity() == mine.capacity());

	SECTION( "resizing bigger changes size and capacity" ) {
		v.resize( 10 );

		REQUIRE( v.size() == mine.size() );
		REQUIRE( v.capacity() == mine.capacity());
	}
//
	SECTION( "resizing smaller changes size but not capacity" ) {
		v.resize( 0 );

		REQUIRE( v.size() == mine.size() );
		REQUIRE( v.capacity() == mine.capacity());
	}

//	SECTION( "reserving bigger changes capacity but not size" ) {
//		v.reserve( 10 );
//
//		REQUIRE( v.size() == mine.size() );
//		REQUIRE( v.capacity() == mine.capacity());
//	}
//
//	SECTION( "reserving smaller does not change size or capacity" ) {
//		v.reserve( 0 );
//
//		REQUIRE( v.size() == mine.size() );
//		REQUIRE( v.capacity() == mine.capacity());
//	}
}
