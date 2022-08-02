#include "../includes/vector.hpp"
#include <vector>

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define RST  "\x1B[0m"

void testEmpty() {
//	std::vector<int> test;
	std::vector<std::string> test1;
	ft::Vector<int> container;

	test1.push_back("hello");
	test1.push_back("hi");
	std::cout << "original: " << test1.max_size() << std::endl;
	std::cout << "mine: " << container.size() << std::endl;
//	test1.push_back("hi");
//	test1.push_back("hi");
//	test1.push_back("hi");
//	test1.push_back("hi");
//	test1.push_back("hi");
//	if(test.size() == container.size())
//		std::cout << GRN"pass\n" RST;
//	else
//		std::cout << RED"fail\n" RST;
//	test.reserve( 0);
//	size_t a = test.capacity();
//	int tmp;
//	for(int i = 0; i < 400; ++i) {
//		test.push_back(i);
//		tmp = test.capacity();
//	}
//	std::cout << "done testing " << test.capacity() << " second test " << tmp << " " << a << "\n";
	//TODO implement rezize fuction for integers and string so I can just use a template that handle that
//	test1.resize(10);
//	test1.resize(4, "te");
//	test1.resize(0);
//	std::cout << test1.size();
//	for (auto v : test1)
//		std::cout << v << "\n";
}

int main(void)
{
	testEmpty();
}