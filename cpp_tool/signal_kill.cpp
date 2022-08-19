//=====================================================================
//
// signal_kill.cpp - 
//
// Created by wwq on 2022/08/19
// Last Modified: 2022/08/19 15:11:26
//
//=====================================================================

// SIGHUB是从终端中发出的结束信号
// SIGINT 是来自键盘终端信号
// SIGKILL 该信号结束接收信号
// SIGTERM kill命令发出的信号
// SIGCHILD 标识子进程停止或者结束的信号
// SIGSTOP 来自键盘ctrl+z 或者调试程序的停止执行信号
#include <csignal>
#include <cstdio>
#include <cstdlib> //exit()
#include <unistd.h> //sleep()

int main()
{
	printf("test signal\n");

	signal(SIGINT,[](int){
			printf("in signal\n");
			exit(0);
			});
	while(1)
	{
		printf("in loop\n");
		sleep(1);
	}
	return 0;
}
