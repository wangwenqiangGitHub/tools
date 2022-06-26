# top (busybox上的命令)
- PID 进程标识
- PPID 父进程
- USER 在其下创建的用户名
- STAT状态 S-睡眠 D-不间断睡眠 R-运行 W-换出过程 Z-僵尸进程 T-停止或跟踪 N具有nice值
- CPU-正在使用的物理处理器
- %CPU CPU正在使用的总CPU百分比
- COMMAND显示使用的命令函名称
- VSZ虚拟内存大小
# 线程与cpu核绑定-cpu亲和度
- CPU亲和性(affinity)就是进程要在某个给定的CPU上尽量长时间地运行而不被迁移到其他处理器的倾向性。
- linux代码
```cpp
cpu_set_t mask;
CPU_ZERO(&mask);
CPU_SET(0, &mask);
// 将cpu0加入到集合
if(sched_setaffinity(0, sizeof(mask), &mask) < 0) {
printf("bind core %d failure! -\n");
return NULL;
} else {
printf("bind core success! +\n");
}
```
# pthread_setschedparam线程的调度策略
- int pthread_setschedparam(pthread_t target_thread, int policy, const struct sched_param \*param)
	- target_thread是使用pthread_create所获得的线程ID
	- 线程的三种调度策略：SCHED_OTHER,SCHED_RR和SCHED_FIFO，Policy
- SCHED_OTHER线程分时调度策略，所有的线程的优先级都是0，线程的调度是通过分时来完成的。
- SCHED_FIFO它是一种实时的先进先出调用策略，且只能在超级用户下运行，这种调度策略仅仅被适用于优先级大于0的线程。
它意味着，使用SCHED_FIFO的可运行线程将一直抢占使用SCHED_OTHER的运行线程。非分时的简单调度策略，当一个线程变成可
运行状态，它将被追加到对应优先级队列的尾部。当所有高优先级的线程终止或者阻塞时，它将被运行。相同优先级的线程，按
先进先出的规则。一种坏的情况，如果有若干相同优先级的线程等待执行，然后最早执行的线程无终止或者阻塞动作，那么其他
线程是无法执行的。
- SCHED_RR 鉴于SCHED_FIFO调度策略的一些缺点，它还是SCHED_FIFO调用的策略。它使用最大运行时间来限制当前进程的运行，
当运行时间等于大于运行时间的时候，当前线程将被切换并放置于相同优先级队列的最后，-时间片轮转。

# gcc静态编译
```shell
-static-libstdc++
-static-libgcc
```

# linux /var/run目录下pid文件
> linux系统中的\*.pid文件是一个文本文件，其内容只有一行，即某个进程的PID.\*.pid文件的作用是防止进程启动多个副本，只有获得特定pid文件(固定路径和文件名)的
读写权限(F_WRLCK)的进程才能正常启动并将自身的进程PID写入该文件，其他同一进程的多余进程则自动退出。


# cpp头文件相互引用问题
- 导致定义的类型，或者函数找不到。

