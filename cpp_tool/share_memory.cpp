//=====================================================================
//
// share_memory.cpp - 
//
// Created by wwq on 2022/08/19
// Last Modified: 2022/08/19 14:40:52
// 问题:share_ptr会出现内存泄漏么？
//=====================================================================
#include <memory>
#include <iostream>
// #include <string>

struct B;
struct A
{
    ~A() { std::cout << "~A" << std::endl; }
	std::shared_ptr<B> b;
};
struct B 
{
    ~B() { std::cout << "~B" << std::endl; }
	std::shared_ptr<A> a;
};

int main() {
	std::shared_ptr<A> a (new A);
	std::shared_ptr<B> b (new B);
    a->b = b;
    b->a = a;

    return 0;
}

// 程序发生内存泄漏.因为两个类相互引用，造成堆内存不能释放，主要原因是析构智能指针时所调用的析构函数发现引用计数仍不为0。就不会释放。
// 可以通过weak_ptr代理shared_ptr。从而解决智能指针循环引用的问题。
// shared_ptr智能指针循环引用问题：要释放的堆对象被该堆对象自己内部的智能指针成员变量增加引用计数阻止了。
