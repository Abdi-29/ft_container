#include <vector>
#include "../includes/vector.hpp"
#include "../includes/is_integral.hpp"
#include <iterator>
#include <vector>

using namespace std;

int main() {
	{
		ft::vector<int> vec;
		vec.assign(3, 42);
		assert(vec.size() == 3);
		assert(vec.capacity() >= 3);
		assert(vec[0] == 42);
		assert(vec[1] == 42);
		assert(vec[2] == 42);
	}

}
