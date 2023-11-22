//=====================================================================
//
// static_storage_area.c - 
//
// Created by wwq on 2023/10/26
// Last Modified: 2023/10/26 14:46:00
// 静态存储区不是存储在堆上。静态存储区主要存放静态数据，全局数据和常量所以getMessage函数中char* msg指向的是静态存储区;
// "hello"存储在静态存储区，所以不会释放 char a[]是局部变量，所以出错了
//
// 在c语言中, 函数中定义的char* a和char a[]之间有什么区别:
// 1. char* a是一个指针变量a, 它指向一个字符(char)类型的数据。这种定义方式通常用于指向字符串的指针。指针变量a可以指向任何char类型的数据
// 包括字符串的首字符。需要注意的是，char* a只是一个指针的声明,并没有为其分配内存空间。在使用之前，需要确保指针a指向有效的内存地址。
// 2. char a[]是一个字符数组a,它是一个固定大小的字符序列。数组a在定义时需要指定其大小，并且在编译时分配了相应大小的内存空间。这种定义
// 方式通常用于存储字符串或字符序列。数组 a 的大小是固定的，无法改变。
//=====================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * get()
{
	char a[] = "wolrd";
	return a;
}

char* getMessage()
{
	char* msg = (char*)malloc(sizeof(char)*6);
	strcpy(msg,"hello");
	return msg;
}
int main(int argc, char *argv[])
{
	char*s = getMessage();
	printf("%s\n",s);
	free(s);
	s = NULL;
	printf("%s\n",get());
	return 0;
}
