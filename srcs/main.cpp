#include "../includes/vector.hpp"
#include "catch.hpp"
#include <vector>

TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

// For each section, vector v is anew:

std::vector<int> v;
ft::Vector<int> mine;

std::vector<int>::iterator Iv;
ft::Vector<int>::iterator	Imine;

for (size_t i = 0; i < 5; ++i) {
	v.push_back(i + 5);
	mine.push_back(i + 5);
}
Iv = v.begin();
Imine = mine.begin();

REQUIRE( v.size() == mine.size() );
REQUIRE( v.capacity() == mine.capacity() );

//SECTION( "resizing bigger changes size and capacity" ) {
//v.resize( 10 );
//
//REQUIRE( v.size() == 10 );
//REQUIRE( v.capacity() >= 10 );
//}
//SECTION( "resizing smaller changes size but not capacity" ) {
//v.resize( 0 );
//
//REQUIRE( v.size() == 0 );
//REQUIRE( v.capacity() >= 5 );
//}
//SECTION( "reserving bigger changes capacity but not size" ) {
//v.reserve( 10 );
//
//REQUIRE( v.size() == 5 );
//REQUIRE( v.capacity() >= 10 );
//}
//SECTION( "reserving smaller does not change size or capacity" ) {
//v.reserve( 0 );
//
//REQUIRE( v.size() == 5 );
//REQUIRE( v.capacity() >= 5 );
//}
}

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define RST  "\x1B[0m"

