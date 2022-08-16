# 智能指针
- unique\_ptr完全拥有所有权，解决的是帮我释放的问题;
- shared\_ptr拥有共享的所有权，解决的是谁最后负责释放的问题;
- weak\_ptr完全没有所有权，解决的是在某一时刻能不能获得所有权的问题;
> 参考: 在workfow的世界观里，所有我(task)分配的资源都是属于我(task)的,所以理应都由我来管理，
并且保证所有资源都会在确定的时刻正确释放，用户只能在我(task)指定的时候使用这些资源，所以不
存在共享所有权的问题，也不存在让用户猜测某个时刻是否有所有权的问题。
- shared\_ptr与weak\_ptr
```cpp
template<typename _Tp>
class enable_shared_from_this{
protected:
	//...
public:
	shared_ptr<_Tp>
	shared_from_this(){
		return shared_ptr<_Tp>(this->_M_weak_this);
	}
	shared_ptr<const _Tp>
	shared_from_this()const{
		return shared_ptr<const _Tp>(this->_M_weak_this);
	}
private:
	mutable weak_ptr<_Tp> _M_weak_this;
}
```
- 成员变量为什么是weak\_ptr类型：因为如果是std::shared\_ptr类型，那么就永远无法析构对象自身。
- weak\_ptr是为了解决std::shared\_ptr循环引用而生，构造std::weak\_ptr对象只能通过std::shared\_ptr来构造，但是std::weak_\ptr对象的生命周期对相应的std::shared\_ptr的引用计数不产生影响，即不增加或者减少引用计数。
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
# 类型转换运算符
- static\_cast: 用于良性转换，一般不会导致意外发生，风险很低；
- const\_cast: 用于const与非const,volatile与非volatile之间的转换;
- reinterpret\_cast:高度危险的转换，这种转换仅仅是对二进制的重新解释;
- dynamic\_cast:借助RTTI,用于类型安全的向下转型(Downcasting).
> static\_cast是在编译期完成类型转换，能更加及时地发现错误. dynamic\_cast是运行期间借助RTTI进行类型转换，这就要类必须要求基类包含虚函数
dynamic\_cast用于在类的继承层次之间进行类型转换，它既允许向上转型，也允许向下转型。向上转型是无条件的，不会进行任何检测，所以都能成功；向下转型的前提必须是安全的，要借助 RTTI 进行检测，所有只有一部分能成功。
> static\_cast:向上转换(把子类指针或引用转换成基类表示)是安全的,向下转换(把基类指针或引用准换成子类表示)是，由于没有动态类型检查，所以是不安全的。
> dynamic\_cast主要用于类层次间的上行转换和下行转换，还可以用于类之间的交叉转换，类层次间进行上行转换时，dynamic\_cast与static\_cast效果相同。向下转换时dynamic\_cast具有类型检查功能，比static\_cast更加安全。
```cpp
class B
{
	public:
    int m_iNum;
    virtual void foo();
};
 
class D : public B
{
	public:
    char *m_szName[100];
};
 
void func(B *pb)
{
    D *pd1 = static_cast(pb);
    D *pd2 = dynamic_cast(pb);
}
/***如果pb指向一个D类型的对象，pd1和pd2是一样的，并且对这两个指针执行D类型的任何操作都是安全的；
但是，如果pb指向的是一个B类型的对象，那么pd1将是一个指向该对象的指针，对它进行D类型的操作将是不安全的（如访问m_szName），
而pd2将是一个空指针。
另外要注意：B要有虚函数，否则会编译出错；static_cast则没有这个限制。
***/
```

## BPMNm Business Process Modeling Notation 业务流程建模与标注，可以用其定义的一些列业务组件，组成业务流程图


# c++实现反射
![参考《c++t如何实现反射机制》](https://zhuanlan.zhihu.com/p/70044481) 
- 参考reflect.cpp

# 模板编程函数
- std::enable\_if

# 类中定义该类的指针用途
```cpp
class Node{
	public:
		int data;
		Node* next;
};
```
如果不采用Node的指针，那么意味着当你通过Node类来指向链表的下一个节点，你就会发现数据类型错误。
通过一个指针来表明下一个节点的地址，主要作用是节省内存。
- 主要问题：
是否可以在一个类中实例化一个该类的对象呢？
假设这样做，发现程序会崩溃，因为在你这样定义一个该类之后，你在类外实例化一个对象时，该对象会自动获得该类的所有成分，但是类中又存在一个对象。该对象会继续执行下去，从而造成一个死循环。为什么实例化一个对象指针却不会造成这个问题，对于一个指针来说，他只是一个地址，至于他的数据类型时怎样的，并不是在定义的时候，就必须给出。

# 函数内的变量问题
- 基础的小错误:函数内的变量，将变量的地址复给另一个变量的支持，这个指针在函数外用了，那么这个变量可能被释放掉了，就是说，这块地址中的数据变了可能。
# 控制double精度
- stringstream 中的setf()和precision()方法.
# 栈与调用惯例，堆
- 栈(stack),栈是一个特殊的容器，用户可以将数据压入栈中(push),也可以将已经入栈的数据弹出，但是必须遵循先入先出。栈总是向下增长的。压栈的操作使栈顶的地址减小，弹出的操作使栈顶地址增加。
- 调用惯例:函数的调用方与被调用方对于函数如何调用需要有一个明确的约定，双方都遵循这个约定，只有双方都遵守同样的约定，函数才能被正确的调用，这样的约定称为调用惯例。
- 函数的参数通过栈传递。函数的返回值传递也是分配在栈上的内存
- 堆:因为栈上的数据在函数返回的时候就会被释放，所以在无法将数据传递至函数外部。而全局变量没有办法动态地产生，只能在编译的时候定义，有很多情况下缺乏表现力，在这种情况下，堆(Heap)是唯一的选择。malloc的内存在堆上。


# fread()函数
- 可以读取二进制文件，有时用字符的方式不能完整的读取整个文件，但是二进制的方式是可以的。


# 清空数组
```cpp
template<typename T>
void empty(T &input) {
    T empty{};
    std::swap(input, empty);
}
```
# 对象生命周期
1. 出生: malloc分配结构体内存，并初始化
2. 使用: 对于内存使用
3. 销毁:free释放掉这块内存

# ZLMediaKit在跨线程共享RTP/RTMP包时，是通过批量线程切换的方式进行的，也是通过智能指针共享数据：
- 批量切换线程，指的是，如果1000个播放器在同一个线程中，但是推流器在其他线程中，那么只会切换一次线程。一次线程切换时间间隔为合并写时间长度，默认关闭合并写，也就是每帧画面切换一次线程然后再分发，如果合并写时间为300毫秒，那么每300毫秒才会触发一次线程切换。
- 通过上述表达，ZLMediaKit能极致压制硬件和内核性能，目前测试结果发现，性能瓶颈已经不在应用层，而是在内核层面，因为每次写socket，都要把数据写入socket缓存，这个存在内存拷贝，这个是目前无法避免的，当客户端很多时，这个内存写入量是非常夸张的，已经触发了内存写速度瓶颈。
```
for(auto& ptr:_dispatcher_map){
	auto& second=pr.second;
	pr.first->async([second,in,is_key](){
			second->write(in,is_key);
			},false);
}
```
# ZLMediaKit中使用shared\_ptr和weak\_ptr
- weak\_ptr是为了防止shared\_ptr循环引用 
- 传递参数的时候，shared\_ptr就要变为weak\_ptr，主要原因是一是不想延长变量的生命周期，有可能导致资源不掉; 一个允许销毁 一个不允许

