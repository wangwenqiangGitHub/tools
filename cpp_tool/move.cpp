//=====================================================================
//
// move.cpp - 
//
// Created by wwq on 2022/08/16
// Last Modified: 2022/08/16 10:49:50
// std::move学习参考:https://zhuanlan.zhihu.com/p/335994370
//=====================================================================
// 左右值的概念很清楚；有地址的变量就是左值，没有地址的字面变值，临时值就是右值。
#include <iostream>

int main(int argc, char** argv)
{
	int a = 5;
	int &ref_a=a; //左值引用指向左值;正确的
				  // int &ref_a = 5;错误
	std::cout<< ref_a<< std::endl;
	// 引用是变量的别名，由于右值没有地址，没法修改，所以左值引用无法指向右值。
	// const左值引用可以指向右值。
	const int& ref_c = 5; 
	std::cout << ref_c << std::endl;

	// const 左值引用不会修改指向值，因此可以指向右值
	// 这也是为什么要使用const& 作为函数参数的原因之一，
	// 如std::vector的push_back:
	// 如果没有const，vec.push_back(5)这样的代码就无法编译通过了
	
	// 右值引用：右值引用的标志是&&;
	int &&ref_r = 5;
	std::cout << ref_r << std::endl;
	ref_r=6;
	std::cout << ref_r << std::endl; //右值引用的用途，可以修改右值
	// 右值引用有什么办法指向左值：std::move()
	int aa = 5; //aa是一个左值
	int& ref_a_left = aa; // 左值引用指向左值。
	int&& ref_a_right = std::move(aa); //通过std::move将左值转化为右值，可以被右值引用指向
	printf("<%s %d>\n",__func__, __LINE__);
	std::cout << aa << std::endl;
	// 左值引用和右值引用本身是左值还是右值
	// 被生命的左值和右值引用都是左值，因为被声明出来的左值和右值都是有地址的，也位于等号的左边。
	// 作为函数返回值的 && 是右值，直接声明出来的 && 是左值。
	// 从性能上讲，左右值引用没有区别，传参使用左右值引用都可以避免拷贝。
	// 右值引用可以直接指向右值，也可以通过std::move指向左值；而左值引用只能指向左值(const左值引用也能指向右值)。
	// 作为函数形参时，右值引用更灵活。虽然const左值引用也可以做到左右值都接受，但它无法修改，有一定局限性。

	return 0;
}
