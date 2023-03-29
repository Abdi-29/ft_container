#include <vector>
#include "../includes/vector.hpp"
#include "../includes/is_integral.hpp"
#include <iterator>
#include <vector>

using namespace std;

void print(int id, ft::vector<int>& container)
{
	std::cout << id << ". ";
	for ( ft::vector<int>::iterator x = container.begin(); x != container.cend(); x++)
		std::cout << *x << ' ';
	std::cout << '\n';
}

int main(void) {
	std::vector<int> stdvec(3, 42);
	{
		ft::vector<int> ftvec(stdvec.begin(), stdvec.end());
		ft::vector<int>::iterator ftit = ftvec.begin();
		print(1, ftvec);
		for (std::vector<int>::iterator stdit = stdvec.begin();
			 stdit != stdvec.end(); ++stdit, ++ftit) {
			assert(*stdit == *ftit);
		}
	}

}
