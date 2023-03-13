#include <vector>
#include "vector.hpp"

using namespace std;

int main() {
	ft::vector<int> m(5);

	for(int i = 0; i < 5; ++i) {
		m.push_back(i);
	}
	std::cout << m.at(6);
	cout << "size: " << m.size() << endl;
}