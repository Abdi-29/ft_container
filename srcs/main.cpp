#include <vector>
#include "vector.hpp"

using namespace std;

int main(void) {
	ft::vector<int> m(5);
	vector<int> v(5);
	cout << "my vector: " << m.size() << endl;
	cout << "vector: " << v.size() << endl;
	for(int i = 0; i < 5; ++i) {
		cout << "value: " << m.at(i);
	}
//	std::cout << m.at(6);
	cout << "my vector size: " << m.size() << endl;
	cout << "size: " << v.size() << endl;
}
