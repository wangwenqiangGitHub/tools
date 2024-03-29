#include <rttr/registration.h>
#include <string>
#include <iostream>
using namespace rttr;
using namespace std;
 
struct MyStruct {
	MyStruct() {};
	void func(double a) {printf("----%f\n",a);};
	void test1(int a) {printf("for test %d\n", a);}
	int data;
};
 
RTTR_REGISTRATION
{
    registration::class_<MyStruct>("MyStruct")
         .constructor<>()
         .property("data", &MyStruct::data)
         .method("func", &MyStruct::func)
		 .method("test1", &MyStruct::test1)
		 ;
}

int main()
{
	type t = type::get<MyStruct>();
	for (auto& prop : t.get_properties())
		    std::cout << "name: " << prop.get_name() << std::endl;

	for (auto& meth : t.get_methods())
		    std::cout << "name: " << meth.get_name() << std::endl;
	
	{
		type t = type::get_by_name("MyStruct");
		variant var = t.create();    // will invoke the previously registered ctor

		constructor ctor = t.get_constructor();  // 2nd way with the constructor class
		var = ctor.invoke();
		std::cout << var.get_type().get_name() << std::endl; // prints 'MyStruct'	
	}

	MyStruct obj;

	method meth = type::get(obj).get_method("func");
	meth.invoke(obj, 42.0);

	auto mtest = type::get(obj).get_method("test1");
	mtest.invoke(obj, 12);

	variant var = type::get(obj).create();
	meth.invoke(var, 42.0);
}
