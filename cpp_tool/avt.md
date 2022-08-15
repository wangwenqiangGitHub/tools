# 音视频学习参照[雷神的csdn](https://blog.csdn.net/leixiaohua1020?type=blog) 
主要是学习时的笔记
# 视频播放器的原理
- 视频播放器播放视频文件主要原理是:解协议，解封装，解码视音频，视音频同步。
- ![音视频播放流程](../images/av_flow.jpg) 
	- 解协议的作用，就是将流媒体协议的数据，解析为标准的相应的封装格式数据。视音频在网络上传播的时候，常常采用各种流媒体协议，例如HTTP,RTMP.或者是MMS等等，这些数据在传输音视频数据的同时，也会传输一些信令数据，这些信令数据包括对播放的控制(播放，暂停，停止),或者对网络状态的描述等。解协议的过程中会去除信令数据而只保留音视频数据，例如，采用RTMP协议传输的数据，经过解协议操作后，会输出FLV格式的数据。
	- 解封装的操作，就是将输入的封装格式的数据，分离成音频流压缩编码数据和视频流压缩编码数据。封装格式有很多种类，例如MP4,MKV,RMVB,TS,FLV,AVI等，它的作用就是将已经压缩编码的视频数据和音频数据按照一定的格式放在一起，例如：FLV格式的数据，经过解封装操作后，输出H.264编码的视频码流和AAC编码的音频码流。
	- 解码的作用就是将视频/音频压缩编码数据，解码成为非压缩的视频/音频原始数据，音频的压缩编码标准包含ACC,MP3,AC-3等等，视频的压缩编码标准则是包含H.264,MPEG2,VC-1等等。解码是整个系统中最重要也是最复杂的环节。通过解码，压缩编码的视频数据输出成为非压缩的颜色数据，例如：YUV420P, RGB等等；压缩编码的音视频数据输出成为非压缩编码的音频抽样数据，例如PCM数据。
	- 视音频同步的作用：就是根据解封装模块处理过程中获取到的参数信息，同步解码出来的视频和音频数据，并将视频音频数据送至系统的显卡和声卡播放出来。
# rtmp分析
- ![RTMP规范简单分析](https://blog.csdn.net/leixiaohua1020/article/details/11694129)
rtmp传输媒体数据的过程中，发送端首先把媒体数据封装成消息，然后把消息分割成消息块，最后将分割后的消息块通过TCP协议发送出去，接收端在通过TCP协议收到数据后，先把消息块重新组合成消息，然后通过对消息进行封装处理就可以恢复出媒体数据。
# UDP-RTP协议分析

# SDL配置
- SDL(Simple DirectMedia Layer)库的作用是封装了复杂的视音频低层交互工作，简化视音频处理的难度。
# ts流格式介绍
- ts流最早应用于数字电视领域，视频格式主要是mpeg2，苹果公司的(http live stream)hls流媒体是基于ts，主要的封装格式是h264/mpeg4,音频为aac/mp3.
- ts格式:ts层，pes层，es层。es层就是音视频数据。pes层是在音视频数据上加了时间戳等对数据帧的说明信息。ts层就是在pes层上加了数据流标识和传输的必要信息。
- ts header  

| 名称                         | 字节 | 含义                                                                                          |
| ---                          | ---  | ---                                                                                           |
| sync\_byte                   | 8b   | 同步字节，固定为0x47                                                                          |
| tranport\_erro\_indicator    | 1b   | 传输错误指示，通常为0                                                                         |
| payload_unit_start_indicator | 1b   | 负载单元起始标示符，一个完整的数据包开始时标记为1                                             |
| transport_priority           | 1b   | 传输优先级，0为低优先级，1为高优先级，通常取0                                                 |
| pid                          | 13b  | pid值                                                                                         |
| transport_scrambling_control | 2b   | 传输加扰控制，00表示未加密                                                                    |
| adaption_filed_control       | 2b   | 是否包含自适应00保留，01无自适应，仅含负载，10自适应，无有效负载； 11同时具有自适应和有效负载 |
| cibtinuity_counter           | 4b   | 递增计数器，从0-f，起始值不一定取0，但必须是连续的                                            |
[参考文章](https://blog.csdn.net/yhc223/article/details/43952681)

pts是显示时间戳，dts是解码时间戳，视频数据两种时间戳都需要，音频数据的pts和dts相同，所以只需要pts.有pts和dts两种时间戳是B帧(双向探测帧),I帧和P帧的pts等于dts。如果同一个视频没有B帧，则pts永远和dts相同，从文件中顺序读取视频帧，取出的帧顺序和dts顺序相同。dts算法比较简单，就是直接初始值+增量即可，pts计算比较复杂，需要dts的基础上加偏移量。

# ZLNediaKit高并发原理
该框架基于c++11开发，避免使用裸指针，减少内存拷贝，代码精简可靠，并发性能优异，在linux平台下，单一进程既可以充分利用多核cpu的优势，最大限度的榨干CPU,网卡性能；轻松达到万兆网卡极限，同时也高性能的同时，做到极低延时，画面秒开。
- 网络模型:不同于SRS的单线程多协程、node.js/redis的单线程、NGINX的多进程模型；ZLMediaKit采用的是单进程多线程模型。那么为什么ZLMediaKit要采用这样的编程模型呢？
作为一个多年的C++服务器后台开发工程师，多年的工作经验告诉我，作为一个服务器程序，对于稳定性要求极高；一个服务器可以性能差点，但是绝不能轻易core dump；服务中断、重启、异常，对于一个线上已运营项目来说结果是灾难性的。那么我们该怎么确保服务器的稳定？目前有以下手段：

单线程模型
单线程+协程
单线程+多进程
多线程+锁
弃用C/C++

- 采用单线程模型的优点是，服务器简单可靠，不用考虑资源竞争互斥的问题，这样可以比较容易做到高稳定性；采用此模型的典型代表项目有 redis、node.js。但是由于是单线程模型，所以弊端也比较明显；那就是在多核cpu上不能充分利用多核CPU的算力，性能瓶颈主要在于CPU(大家应该有过在redis中执行keys 慢慢等待的经历)。

- 单线程+协程的方案本质上与纯单线程模型无区别，它们的区别主要编程风格上。纯单线程模型使用的是非阻塞式处处回调方式实现高并发，这种模型会有所谓的回调地狱的问题，编程起来会比较麻烦。而单线程+协程的方案是简化编程方式，采用自然的阻塞式编程风格，在协程库内部管理任务调度，本质也是非阻塞的。但是协程库涉及的比较底层，跟系统息息相关，所以跨平台不是很好做，而且设计实现一个协程库门槛较高。SRS采用就是这编程模型，由于协程库的限制，SRS不能在windows上运行.
- 为了解决上述单线程模型的问题，很多服务器采用单线程多进程的编程模型；在这种模型下，既有单线程模型的简单可靠的特性，又能充分发挥多核CPU的性能，而且某个进程挂了也不会影响其他进程，像NGINX就是这种编程模型；但是这种模型也有其局限性。在这种模型下，会话间是相互隔离的，两个会话可能运行在不同的进程上；这样就导致了会话间通信的困难。比如说A用户连接在服务器A进程上，B用户连接在服务器B进程上；如果两者之间要完成某种数据交互，那么会异常困难，这样必须通过进程间通信来完成。而进程间通信代价和开销比较大，编程起来也比较困难。但是如果会话间无需数据交互(例如http服务器)，那么这种模型是特别适合的，所以NGINX作为http服务器也是非常成功的，但是如果是譬如即时聊天的那种需要会话间通信的服务，那么这种开发模型不是很适合。不过现在越来越多的服务都需要支持分布式集群部署，所以单线程多进程方案的缺陷越来越不明显。

由于C/C++是种强类型静态语言，异常处理简单粗暴，动不动就core dump。C/C++的设计理念就是发现错误及早暴露，在某种意义上来说，崩溃也是种好事，因为这样会引起你的重视，让你能及早发现定位并解决问题，而不是把问题拖延到无法解决的时候再暴露给你。但是这么做对一般人来说，C/C++就不是很友好了，人类并不像机器那样严谨，有点疏忽在所难免，况且有些小问题也无伤大雅，并不需要毁灭式的core dump来应对。而且C/C++的学习曲线异常艰难困苦，很多人好几年也不得要领，所以很多人表示纷纷弃坑，转投 go / erlang / node.js之类。

但是C/C++由于其性能优越性，以及历史原因，在某些场景下是不二选择，而且C/C++才是真正的跨平台语言；况且随着智能指针的推出，内存管理不再是难题；而lambad语法的支持，让程序上下文绑定不再困难。随着C++新特性的支持，编译器静态反射机制的完善，现代C++编程愈发简便快捷。ZLMediaKit采用的就是C++11新标准以及相关理念完成的高性能流媒体服务框架。

与上面其它编程模型不同，ZLMediaKit采用的是多线程开发模型；与传统的多线程模型不同；ZLMediaKit采用了C++11的智能指针来做内存管理，在线程切换时可以完美的管理内存在多线程下共享以及其生命周期。同时互斥锁的粒度消减至极致，几乎可以忽略不计。所以采用多线程模型的ZLMediaKit性能损耗极低，每条线程的性能几乎可以媲美单线程模型，同时也可以充分榨干CPU的每一核心性能.

- 采用右值引用拷贝:ZLMediaKit中也尽量使用右值引用拷贝来规避内存拷贝

- [参考ZLMediaKit](https://www.jianshu.com/p/f1c9964b8cf1)