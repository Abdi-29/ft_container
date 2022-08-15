#include "../includes/vector.hpp"
#include <vector>

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define RST  "\x1B[0m"

void testEmpty() {
//	std::vector<int> test;
//	std::vector<int> test1;
	ft::Vector<int> container;

    container.push_back(2);

//	std::cout << "done testing " << test.capacity() << " second test " << tmp << " " << a << "\n";
	//TODO implement rezize fuction for integers and string so I can just use a template that handle that
}

int main(void)
{
	testEmpty();
}