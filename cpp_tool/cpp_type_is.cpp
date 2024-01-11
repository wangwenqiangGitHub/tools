#include <iostream>
// #include <type_traits>
#include <iostream>
#include <cstdlib>
#include <string>
#if defined(__GNUC__) || defined(__clang__)
#include <cxxabi.h>
#endif
class A {
public:
	A() = default;
	virtual ~A() = default;
};

class B : public A {
public:
	B() = default;
	virtual ~B() = default;
};
class C : public A {
public:
	C() = default;
	virtual ~C() = default;
};

template <class T>
std::string cpp_type_name() {
    const char *name = typeid(T).name();
#if defined(__GNUC__) || defined(__clang__)
    int status;
    char *p = abi::__cxa_demangle(name, 0, 0, &status);
    std::string s = p;
    std::free(p);
#else
    std::string s = name;
#endif
    if (std::is_const<std::remove_reference_t<T>>::value)
        s += " const";
    if (std::is_volatile<std::remove_reference_t<T>>::value)
        s += " volatile";
    if (std::is_lvalue_reference<T>::value)
        s += " &";
    if (std::is_rvalue_reference<T>::value)
        s += " &&";
    return s;
}

#define SHOW(T) std::cout << cpp_type_name<T>() << std::endl;

int main(int argc, char *argv[])
{
	std::cout << std::is_same<const int, int>::value << std::endl;
	std::cout << std::is_same<const int, int const>::value << std::endl;
	std::cout << std::is_same<const int *, int * const>::value << std::endl;
	std::cout << "A:" << std::is_same<A, B>::value << std::endl;


	std::cout <<"name" <<typeid(B).hash_code() << std::endl;
	std::cout <<"name" <<typeid(C).hash_code() << std::endl;
	int a = 10;
	int b = 20;
	SHOW(int);
	SHOW(A&);
	const int * aa = &a;
	printf("%d\n", *aa);
	aa = &b;
	printf("%d\n", *aa);
	std::cout << std::is_base_of<A, B>::value << std::endl;
	return 0;
}
