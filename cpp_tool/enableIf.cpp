#include<iostream>
#include <type_traits>

// template <class T>
// void foo(T)
// {
// 	std::cout << " T is signed" << std::endl;
// }

template<class T, class= typename std::enable_if<std::is_unsigned<T>::value>::type>
void foo(T)
{
	std::cout << "T is unsignd"<< std::endl;
}

struct A{};

struct B : A{};

template<class T, class = typename std::enable_if<std::is_base_of<A, T>::value>::type>
struct C : T{};

struct D{};

int main(int argc, char** argv)
{
	// int x = 5;
	// foo(x);
	// float y = 6.000;
	// foo(y);
	// unsigned int z = 888;
	int z = 888;
	foo(z);
	C<B> c;
	// C<D> d;
	return 0;
}
