#include <iostream>
#include <vector>

template<class T>
std::ostream &operator<< (std::ostream & os, std::vector<T> const &a)
{
	os << __PRETTY_FUNCTION__ << std::endl;

	os << "{";
	for (std::size_t i = 0; i < a.size(); i++) {
		os << a[i];
		if (i != a.size() - 1)
			os << ",";
	}
	os << "}";
	return os;
}

#include <string.h>
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

int main(int argc, char *argv[])
{
	std::vector<int> a = {1, 2, 4, 5, 7};
	std::cout << a << std::endl;
	printf("<%s %s %d>\n",__FILENAME__, __func__, __LINE__);
	return 0;
}
