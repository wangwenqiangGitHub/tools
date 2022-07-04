# 智能指针
- unique\_ptr完全拥有所有权，解决的是帮我释放的问题;
- shared\_ptr拥有共享的所有权，解决的是谁最后负责释放的问题;
- weak\_ptr完全没有所有权，解决的是在某一时刻能不能获得所有权的问题;
> 参考: 在workfow的世界观里，所有我(task)分配的资源都是属于我(task)的,所以理应都由我来管理，
并且保证所有资源都会在确定的时刻正确释放，用户只能在我(task)指定的时候使用这些资源，所以不
存在共享所有权的问题，也不存在让用户猜测某个时刻是否有所有权的问题。
# 静多态与动多态
- 动态性按照发生的时间段分为静多态和动多态。其中静多态就是绑定发生在编译期(compile-time),此种绑定是静态绑定
动态绑定就是绑定发生在运行期，此种绑定称为动态绑定(dynamic-binding);

- 静多态是通过模板和函数重载来实现，可以分为：1.非参数化多态：函数重载，运算符重载；2.参数化多态:模板
非参数化多态和参数化多态并不冲突，而且相辅相成，他们混合使用灵活性更好
```cpp
template<typename T>
T max(const T& lhs, const T& rhs)
{
	return lhs > rhs? lhs : rhs;
}
```

- 多态是通过继承,虚函数，指针来实现；动多态在c++中是通过虚函数实现的，即在基类中存在一些接口(一般为纯虚函数),子类必须重载这些接口，这样通过使用基类的指针或者引用指向子类的对象，
就可以实现调用的子类对应的函数的功能，动多态的函数调用机制是执行期才能进行确定，所以是动态的。

- 动多态代码
```cpp
#include <iostream>

class Base
{
public:
	virtual void method()=0;
	virtual ~Base(){}
};

class Derived : public Base
{
public:
	virtual void method(){
		std::cout << "Derived" << std::endl;
	}
};

class Derived2 : public Base
{
public:
	virtual void  method(){
		std::cout << "Derived2" << std::endl;
	}
};

int main()
{
	Base* pBase = new Derived;
	pBase->method();//输出:"Derived"
	delete pBase;
	Base* pBase2 = new Derived2;
	pBase2->method();
	delete pBase2;
	return 0;
}
```
- CRTP奇异递归模板模式 来实现上面对应的静多态代码:
```cpp
#include <iostream>
template <class Derived>
class Base
{
public:
	void method()
	{
		static_cast<Derived*>(this)->implementation();
	}
};

class Derived : public Base<Derived>
{
public:
	void implementation()
	{
		std::cout << "Derived" << std::endl;
	}
};

class Derived2 : public Base<Derived2> 
{
public:
	void implementation()
	{
		std::cout << "Derived2" << std::endl;
	}
};

int main()
{
	Base<Derived> *pBase = new Base<Derived>();
	pBase->method();//输出:"Derived"
	delete pBase;
	Base<Derived2> *pBase2 = Base<Derived2>();
	pBase2->method();
	delete pBase2;
}
```

