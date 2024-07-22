/*********************************************************************************
* @file        new_delete.cpp
* @brief       内存泄漏问题排查
* @details     
* @author      wwq
* @date        2024/06/22
* @copyright   Copyright (c) 2024 
* @verbatim
*
*  Change History:
*  Date          Author       Version       Description
*  ------------------------------------------------------------------------------
*  2024/06/22     wwq         1.0           Create this file
*
* @endverbatim
********************************************************************************/
#include <cinttypes>
#include <cstdio>
struct AllocInfo{
	size_t size;
	void *alloct;
};
void *operator new(size_t size) {
	static bool was_enable = false;
	return (void *)&was_enable;
}

int main(int argc, char *argv[])
{
	return 0;
}
