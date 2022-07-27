# valgrind编译
```shell
wget http://valgrind.org/downloads/valgrind-3.12.0.tar.bz2
wget https://sourceware.org/pub/valgrind/valgrind-3.19.0.tar.bz2 
tar xvf valgrind-3.12.0.tar.bz2
cd valgrind-3.12.0 
./autogen.sh
# 交叉编译
# 修改configure中的armv7*)改成armv7*|arm)
./configure --host=arm-linux CC=${GCC_ARM_GCC} CXX=${GCC_ARM_GXX} --prefix=/mnt/d/github_ws/github_ws/valgrind-3.19.0/OUT
maka -j9 && make install
```

# copy文件
```shell
# valgrind运行的依赖放在这个文件夹下
cd /mnt/d/github_ws/github_ws/valgrind-3.19.0/OUT/libexec \
&& scp scp memcheck-arm-linux *.so root@192.2.23.13:/system/etc
```

# 运行
```shell
export VALGRIND_LIB=/system/etc

valgrind --leak-check=full  --log-file=reportleak /system/bin/app


```

# 运行中报错问题及解决
- valgrind: failed to start tool 'memcheck' for platform 'arm-linux': No such file or directory'
> 未找到memcheck-arm-linux工具根据命令:valgrind -d -v 
```
--15615:1:debuglog DebugLog system started by Stage 1, level 1 logging requested
--15615:1:launcher no tool requested, defaulting to 'memcheck'
--15615:1:launcher no client specified, defaulting platform to 'arm-linux'
--15615:1:launcher launching /mnt/d/github_ws/github_ws/valgrind-3.19.0/OUT/libexec/valgrind/memcheck-arm-linux
valgrind: failed to start tool 'memcheck' for platform 'arm-linux': No such file or directory'
# 解决方法是步骤2 copy文件  和 步骤3 运行
```
- 找不到default.supp 文件
```
cd /system/etc && touch default.supp
```
# valgrind打印消息含义
- HEAP SUMMARY表示程序在堆上分配的内存
- total heap usage: 8,739 allocs, 8,520 frees, 1### 51,653 bytes allocated; allocs边是程序分配内存次数,frees表示程序释放了0次，bytes allocated表示分配了4字节的内存。
-  276 (92 direct, 184 indirect) bytes in 1 blocks are definitely lost in loss record 79 of 82； 程序发生内存泄漏的位置
- 对于没有发生内存泄漏的程序
```cpp
#include <string>
int main()
{
    auto ptr = new std::string("Hello, World!");
    delete ptr;
    return 0;
}
```

```
 valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./main_cpp
==31438== Memcheck, a memory error detector
==31438== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31438== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==31438== Command: ./main_cpp
==31438==
==31438==
==31438== HEAP SUMMARY:
==31438==     in use at exit: 72,704 bytes in 1 blocks
==31438==   total heap usage: 2 allocs, 1 frees, 72,736 bytes allocated
==31438==
==31438== 72,704 bytes in 1 blocks are still reachable in loss record 1 of 1
==31438==    at 0x4C2DBF6: malloc (vg_replace_malloc.c:299)
==31438==    by 0x4EC3EFF: ??? (in /usr/lib/x86_64-linux-gnu/libstdc++.so.6.0.21)
==31438==    by 0x40104E9: call\_init.part.0 (dl-init.c:72)
==31438==    by 0x40105FA: call\_init (dl-init.c:30)
==31438==    by 0x40105FA: \_dl\_init (dl-init.c:120)
==31438==    by 0x4000CF9: ??? (in /lib/x86_64-linux-gnu/ld-2.23.so)
==31438==
==31438== LEAK SUMMARY:
==31438==    definitely lost: 0 bytes in 0 blocks
==31438==    indirectly lost: 0 bytes in 0 blocks
==31438==      possibly lost: 0 bytes in 0 blocks
==31438==    still reachable: 72,704 bytes in 1 blocks
==31438==         suppressed: 0 bytes in 0 blocks
==31438==
==31438== For counts of detected and suppressed errors, rerun with: -v
==31438== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)'
```
> 实际上这段代码没有出现内存泄漏,但是从HEAP SUMMARY中可以看出，程序分配了两次内存，但是确只释放一次内存；出现这个问题的原因在于c++在分配内存时，为了提高效率，使用了自己的内存池，当程序终止时，内存池的内存才会被操作系统收回，所以Valgrind会将这部分内存报告为reachable的，需要注意，reachable的内存并不代表内存泄漏

```cpp
/* author :hjjdebug
 * date: 2018年 01月 26日 星期五 09:24:02 CST
 */
#include <stdio.h>
#include <stdlib.h>
 
void *g_p1;
int *g_p2;
int ** fun1(void)
{
	//内存分配指针付给了局部变量, 函数结束而不释放,为肯定丢失.
	//把函数尾部语句return p; 改为return 0;更能说明这个问题.
	int **p=(int **)malloc(16);
	p[1]=(int *)malloc(40); //如果p丢失了,则p[1]为间接丢失.
	g_p1=malloc(110);  //付给了全局变量, 内存可以访问
	g_p2=(int *)malloc(120);
	g_p2++;            //付给了全局变量, 内存可以访问,但是指针被移动过,为可能丢失
	return p;
}
int main()
{
 
	int **p;
//	for(int i=0;i<5;i++)  // 可以研究一下5次循环循环所报的结果,全局指针也能引起肯定丢失.
	{
		p=fun1();
		printf("p is %p\n",p);
	}
	//    free(g_p1);  //如果不free, 将会有 still reachable 内存泄露
	//    free(--g_p2);//如果不free, 将会有 possibly lost 内存泄露
	//    free(p[1]);  //如果不free, 将会有 indirectly lost 内存泄露
	//    free(p);     //如果不free, 将会有 definitely lost内存泄露
	return 0;
}
```
# 指针几种泄漏情况
- "definitely lost" 确认丢失
> 程序中存在内存泄露，应尽快修复。当程序结束时如果一块动态分配的内存没有被释放且通过程序内的指针变量均无法访问这块内存则会报这个错误。
- "indirectly lost"：间接丢失
> 当使用了含有指针成员的类或结构时可能会报这个错误。这类错误无需直接修复，他们总是与"definitely lost"一起出现，只要修复"definitely lost"即可。例子可参考我的例程。

- "possibly lost"：可能丢失。
> 大多数情况下应视为与"definitely lost"一样需要尽快修复，除非你的程序让一个指针指向一块动态分配的内存（但不是这块内存起始地址），然后通过运算得到这块内存起始地址，再释放它。例子可参考我的例程。当程序结束时如果一块动态分配的内存没有被释放且通过程序内的指针变量均无法访问这块内存的起始地址，但可以访问其中的某一部分数据，则会报这个错误。
- "still reachable"：可以访问
> 未丢失但也未释放。如果程序是正常结束的，那么它可能不会造成程序崩溃，但长时间运行有可能耗尽系统资源，因此笔者建议修复它。如果程序是崩溃（如访问非法的地址而崩溃）而非正常结束的，则应当暂时忽略它，先修复导致程序崩溃的错误，然后重新检测。

- "suppressed"：已被解决
> 出现了内存泄露但系统自动处理了。可以无视这类错误。这类错误我没能用例程触发，看官方的解释也不太清楚是操作系统处理的还是valgrind

# 参考文章
- [编译](https://blog.csdn.net/dengcanjun6/article/details/54958359) 
- [valgrind打印消息含义](http://senlinzhan.github.io/2017/12/31/valgrind/) 

