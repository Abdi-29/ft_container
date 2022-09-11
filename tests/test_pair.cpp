#define CATCH_CONFIG_MAIN
#if 0
	#include <vector>
	#include <utility>
	namespace ft = std;
#else
	#include "vector.hpp"
	#include "pair.hpp"
#endif
#include "catch2.hpp"
#include <algorithm>

TEST_CASE("testing pair", "[pair]") {
	ft::vector<ft::pair<int, std::string>> v;
	v.push_back(ft::make_pair(1, "uno"));
}