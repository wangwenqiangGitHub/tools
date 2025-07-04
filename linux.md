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

# pthread\_setschedparam线程的调度策略

- int pthread_setschedparam(pthread_t target_thread, int policy, const struct sched_param \*param)
  - target_thread是使用pthread_create所获得的线程ID
  - 线程的三种调度策略：SCHED_OTHER,SCHED_RR和SCHED_FIFO，Policy
- SCHED_OTHER线程分时调度策略，所有的线程的优先级都是0，线程的调度是通过分时来完成的。
- SCHED_FIFO它是一种实时的先进先出调用策略，且只能在超级用户下运行，这种调度策略仅仅被适用于优先级大于0的线程。
  它意味着，使用SCHED\_FIFO的可运行线程将一直抢占使用SCHED\_OTHER的运行线程。非分时的简单调度策略，当一个线程变成可
  运行状态，它将被追加到对应优先级队列的尾部。当所有高优先级的线程终止或者阻塞时，它将被运行。相同优先级的线程，按
  先进先出的规则。一种坏的情况，如果有若干相同优先级的线程等待执行，然后最早执行的线程无终止或者阻塞动作，那么其他 线程是无法执行的。
- SCHED\_RR 鉴于SCHED\_FIFO调度策略的一些缺点，它还是SCHED\_FIFO调用的策略。它使用最大运行时间来限制当前进程的运行，
  当运行时间等于大于运行时间的时候，当前线程将被切换并放置于相同优先级队列的最后，-时间片轮转。

# gcc静态编译

```shell
-static-libstdc++
-static-libgcc
```

# linux /var/run目录下pid文件

> linux系统中的\*.pid文件是一个文本文件，其内容只有一行，即某个进程的PID.\*.pid文件的作用是防止进程启动多个副本，只有获得特定pid文件(固定路径和文件名)的
> 读写权限(F\_WRLCK)的进程才能正常启动并将自身的进程PID写入该文件，其他同一进程的多余进程则自动退出。

# cpp头文件相互引用问题

- 导致定义的类型，或者函数找不到。

# 消息队列

- 多生产者多消费者消息队列;
- 设计概况:内部使用两个队列，分别拆开了生产者与消费者之间的争夺，提升了吞吐的同时，依然维持了比较优秀的长尾，兼顾保序与代码极简的优良传统。
- 特点:

1. 内部有两个list，生产者把消息放到生产队列，消费者从消费队列取消息；
2. 使用了两把锁分别管理两个队列；
3. 使用了两个条件变量分别管理生产者和消费者的等待唤醒；
4. 队列可以有block / nonblock两种状态； 如果为block，则生产者队列最大长度为maxlen，如果为nonblock，不限制最大长度；

- 算法步骤:
  - 当get\_list(消费者队列)不为空，消费者就可以拿到一个消息;
  - 否则消费者会等待，直到put\_list(生产者队列)不为空，然后交换两个队列;

# 路由

route add default gw 192.216.223.1 dev eth0

- 增加一个路由 route add -net 172.20.36.0 netmask 255.255.255.0 gw 172.20.65.254 eth0
- 追踪路由 到ip的路由 tracert 192.216.223.1 #windows traceroute 192.216.223.1 # linux

- 路由是三层；交换机是二层
- 二层网络是通过mac地址。发送arp包; 三层网络是根据ip.路由寻址发包了;
- 一般是同一网段下交换信息用交换机，不同网段之间交换信息用路由器;
- Gateway值是0.0.0.0或者\*表示不需要路由，目标地址和自己同属于二层网络，
- 通过ARP查询目标路由器的MAC地址; ARP用于根据IP地址查询相应的以太网MAC地址

# 以太网

- 以太网是一种为多台计算机能够彼此自由和廉价地相互通信而设计的通信技术， 通过MAC头部中的接收方MAC地址，就知道包发给谁的；而通过发送方MAC地址，就
  知道包是谁发的;以太网三个特性:将包发送到MAC头部的接收方MAC地址代表的目的地, 用发送方MAC地址识别发送方，用以太类型识别的内容。

# 最大缓存数据

- cat /proc/sys/net/core/rmem\_max

# apt install proxy set up

```
# clash 中选择上允许局域网
cd /etc/apt/apt.conf.d
vim 05proxy
Acquire::http::Proxy "http://0.0.0.0:7890";
```

# 防火墙

```shell
#查看端口开启状态
sudo ufw status
#开启某个端口
sudo ufw allow 80
#开启防火墙
sudo ufw enable
#关闭防火墙
sudo ufw disable
#查看端口IP
netstat -ltn
```

# 高级IO之readv和writev函数

- 因为使用read()将数据读到不连续的内存，使用write()将不连续的内存发送出去，要经过多次的调用read,write，如果要从文件中读一片连续的数据至进程的不同区域，有两种方案，1.
  使用read()一次将它们读至一个较大的缓冲区中，然后将它们分成若干部分复制到不同的区域；2.调用read()若干次分批将他们读至不同的区域。
- 如何解决多次系统调用+拷贝带来的开销？
  UNIX提供了另外两个函数-readv()和writev(),它们只需要一次系统调用就可以实现在文件和进程的多个缓冲区之间传送数据，免除了多次系统调用或者复制数据的开销。

# 线程 进程

- 进程是对运行时程序的封装，是系统进行资源调度和分配的基本单元，实现了操作系统的并发。
- 线程是进程的子任务，是CPU调度和分派的基本单元，用于保证程序的实时性，实现进程内部的并发；线程是操作系统可识别的最小执行和调度单元。每个线程都独享一个虚拟处理器.
- 协程：对于高并发的问题，为了解决操作系统在等待IO的时候，会阻塞当前线程，切换到其他线程，这样当系统线程非常多的时候，出现问题:1.系统线程会占用非常多的内存空间，2.过多的线程切换会占用大量的系统事件。协程需要解决上述两个问题，协程在线程之上，当一个协程执行完后，可以选择主动让出，让另一个写成运行在当前线程之上。协程没有增加线程数量，只是在线程的基础之上通过分时复用的方式运行多个协程，而且协程的切换在用户态完成，切换的代价比从用户态到内核态的代价小很多。

# 五元组

- 源IP地址，源端口，目的ip地址，目的端口，和传输层协议这五个量组成一个集合

# 查看DNS

- nslookup hcos

# 查看IP

- route -n

# linux内核编译问题

- 不应该在mnt路径下编译内核代码

```
make mrproper时make[1]:***Documentation/Kbuild:是一个目录；停止；

make[1]: *** Documentation/Kbuild:是一个目录。停止。
Makefile:1759: recipe for target ‘_clean_Documentation’ failedmake: *** [_clean_Documentation] Error 2

的报错。

我这里在编译源码是通过VMware提供的VMware tools 借助主机与虚拟机文件共享实现的。这个似乎就会导致这个报错，我之前有尝试切换系统版本与linux源码的版本，都没有效果。但是将源码改为在linux虚拟机中操作，而非主机虚拟机共享的方式，就解决了该问题。

自己在网上搜索的时候，其实并没有找到类似的情况，特此记录，以供后来者参考。
```

# 查看linux下库的头文件位置，库文件位置

```shell
dpkg -L libavcodec-dev
pkg-config --cflags libavcodec
dpkg -S libavcodec-dev
#cmake 可以直接 find_package(PkgConfig)
```

# linux设置用户名密码

```shell
passwd yonghuming
# 新机
sudo passwd root
```

# 终端显示不正常后输入reset解决输入乱码问题

# wget下载网页所有html

```
wget -nv -c -p -k -H -i
```

# 设置程序运行时链接库的路径

```
export LD_LIBRARY_PATH=/home/wwq:$LD_LIBRARY_PATH
```

# locale设置系统语言

- sudo apt install language-pack-zh-hans
- `sudo vim /etc/default/locale`

```
LANG=zh_CN.UTF-8
```

# linux系统函数system命令出现父子进程继承问题

- system函数调用顺序

```
fork()->execv()->waitpid()
socket fd 端口等会继承并且system函数是阻塞的
```

- 对于socket继承问题的解决方式:

```
flags = fcntl(fd, F_GETFD);
flags |= FD_CLOEXEC;
fcntl(fd, F_SETFD, flags);
```

# 查看库编译采用的gcc版本

```
strings libpugixml.so | grep GCC
```

# 修改文件编码

```
utf8-bom
```

# 二进制文件编辑工具

- hexdump
- xxd
- bed: 基于go语言开发的跨平台二进制编辑器
- od
- hexedit: 功能比较强大的命令行二进制编辑器
- hexer: 模仿vi操作和命令的二进制编辑器
- ncurses-hexedit 又名hexeditor,支持hjkl移动等少量vi操作的二进制编辑器
- hexed: windows console-based hex editor

# 白名单网络攻击方案

- iptables: 通过脚本实现
- 入侵检测系统Snort

# filesystem

- 刷写次数(flash-10w eeprom-100w emmc-3w)

# linux-sys消息队列

- 相关接口

```
#include <sys/msg.h>

int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
int msgrcv ...
其中 msgflg = 0 是阻塞 , 非阻塞是NOWAIT_IPC
修改消息队列大小: /proc/sys/kernel/msgmnb
struct msg_buf {
    long mtype;   // 必须为 long 类型且 >0
    char mtext[100]; // 消息正文
};
const void* msgp必须首long大于0
1. 消息大小限制
系统对单个消息有最大长度限制（可通过 cat /proc/sys/kernel/msgmax 查看）
典型值为 8192 字节
2. 队列容量限制
消息队列总容量有限制（可通过 cat /proc/sys/kernel/msgmnb 查看）
```

# free命令

- `free -m` 命令用于显示系统物理内存(RAM) 和交换控件(swap)的使用情况, 包括总量,已用,空闲等
- Mem行是物理内存:total表示系统总的物理内存,
  used是已使用的内存(包括应用程序和缓冲/缓冲区),free：完全未被使用的内存。shared：被多个进程共享的内存(如共享库)。buff/cache：被内核缓冲区（buffers）和页面缓存（cache）占用的内存。这部分内存可以被应用程序快速回收。available：系统可用内存（估算值，包括空闲内存和可回收的缓存/缓冲区）。这是新进程可用的内存量。
