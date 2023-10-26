//=====================================================================
//
// static_storage_area.c - 
//
// Created by wwq on 2023/10/26
// Last Modified: 2023/10/26 14:46:00
// 静态存储区不是存储在堆上。静态存储区主要存放静态数据，全局数据和常量所以getMessage函数中char* msg指向的是静态存储区;
// "hello"存储在静态存储区，所以不会释放 char a[]是局部变量，所以出错了
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
