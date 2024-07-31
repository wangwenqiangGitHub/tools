# [buffer设计](http://www.cppblog.com/Solstice/archive/2011/04/17/144378.html)

- 为什么non-blocking网络编程中应用层buffer是必需的 non-blocking IO的核心思想是避免阻塞在read()或者write()上或者其他系统调用上，
  这样可以最大限度地复用thread-of-control,让一个线程可以服务于多个socket连接。 IO线程只能在IO
  multiplexing函数上，如select/poll/epoll\_wait。\n这样一来，应用层 的缓冲区是必须的, 每个TCP的 socket都要有stateful的input
  buffer 和 output buffer (TCP Socket Stateful 意味着 TCP
  连接是一种状态化的连接，它需要在客户端和服务器之间建立一个持久的连接，以便在数据传输过程中保持连接状态。这种连接状态包括连接的建立、数据传输和连接的关闭等过程)

- buffer的设计要点:
  - 对外表现为一块连续的内存(char* p, int len),以便客户代码的编写;
  - 其size()是可以自动增长的, 以适用于不同大小的消息，他不是一个fixed size array(例如:char buf[8192])
  - 内部以std::vector<char>来保存数据，并提供相应的
  - buffer的设计是从末尾写入数据，并从头部读出数据
  - input output是针对客户而言，客户从input读数据，从output写数据
  - readIndex 和 writeIndex将vector分成三块: 0 <= readIndex <= writeIndex <= size()

# EventLoop对象

    - one loop per thread一个线程只能有一个EventLoop对象,EventLoop的构造函数会检查当前线程是否已经创建了其他EventLoop对象。
    - 每个线程中至多有一个EventLoop对象。

# Channel

    - 每一个Channel对象自始至终只属于一个EventLoop,因此每个Channeld对象自始至终只负责一个文件描述符(fd)的IO事件分发，但是它并不拥有这个fd，也不会在析构的时候关闭这个fd。Channel会把不同的IO事件分发给不同的回调函数。例如ReadCallback，WriteCallback等。而且"回调"用function表示，用户不继承，channel不是基类，muduo用户一般不直接适用channel，而是上层封装，如TcpConnection。Channel的声明周期由其owner class负责管理,它一般是其他的直接或者间接成员。

# Poller

    - Poller是IO multiplexing的封装,它现在是一个具体类,在muduo中是一个抽象类，因为muduo同时支持poll(2)和epoll(4)两种IO multiplexing机制.Poller是EventLoop的间接成员，只提供其owner EventLoop在IO线程中调用,因此无需加锁，其生命周期与EventLoop相等。Poller并不拥有channel，Channel在析构之前必须自己unregister(EventLoop::removeChanennel()),避免空悬指针。
    - epoll:
    ```
    epoll_create1(EPOLL_CLOEXE)创建epoll 实例时，可以通过检查返回的文件描述符是否为 close-on-exec 来确定是否设置了 EPOLL_CLOEXEC 标志。如果文件描述符是 close-on-exec，则在调用 exec() 系统调用时会自动关闭该文件描述符
    ```

# TCP网络编程中的本质是处理三个半事件:

- 连接的建立: 服务器accept(被动)接受连接，客户端connected(主动)发起连接。
- 连接的断开: 主动断开(close, shutdown), 被动断开(read 返回0，指对等端主动断开连接)，netsat查看到网络状态是TIME\_WAIT是主动关闭，CLOSED:
  被动关闭端在接受到ACK后，就进入了closed的状态。
- 消息到达: 文件描述符可读。
- 消息发送完毕: 这个对于低流量的服务，这个事件不必关系，这里指的是数据写入操作系统缓冲区。将由TCP协议栈负责数据的发送与重传，不代表对方已经接收到数据。

# 套接字的属性

- `SO_REUSEPORT`支持多个进程或者线程绑定到同一端口，提高服务器程序的性能，解决的问题:
  - 允许多个套接字bind()/listen()同一个TCP/UDP端口
  - 每一个线程拥有自己的服务器套接字
  - 在服务器套接字上没有了锁的竞争
  - 内核层面实现负载均衡
  - 安全层面，监听同一个端口的套接字只能位于同一个用户下面

- `SO_REUSEPORT`是端口重用，`SO_REUSEADDR`是地址重用。两者的区别:
  - `SO_REUSEPORT`是允许多个socket绑定到同一个ip+port，`SO_REUSEADDR`用于对TCP套接字处于`TIME_WAIT`状态下的socket，才可以复用绑定使用。
  - 两者使用场景完全不同。`SO_REUSEADDR`这个套接字选项通知内核，如果端口忙，但TCP状态处于`TIME_WAIT`,可以重用端口。这个一般用于你的程序停止后想立即重启的时候，如果没设定这个选项，会报EADDRINUSE,需要等到`TIME_WAIT`结束才能重新绑定到同一个ip+port上。而`SO_REUSEPORT`用于多核环境下，允许多个线程或者进程绑定和监听同一个ip+port，无论UDP,TCP(以及TCP状态是什么);

# 带宽计算

```
数据包大小为1000k字节（1000 * 1024字节），并且我们希望计算在5秒内传输这个数据包所需的带宽。
首先，我们将数据包的大小转换为比特数：
1000k字节 = 1000 * 1024 * 8比特 = 8# 92,000比特
接下来，我们可以使用带宽的公式来计算：
带宽 = 字节数 / 时间
带宽 = 8# 92,000比特 / 5秒
带宽 = 1,638#### 00比特/秒 或 1.6384 Mbps（兆比特每秒）
因此，在这个例子中，传输1000k字节的数据包在5秒内所需的带宽为1.6384 Mbps。
```
