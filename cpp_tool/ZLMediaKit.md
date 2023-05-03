# 编译

- 查看编译脚本，需要下载子工程

```
git submodule update --init --recursive
```

# mac编译支持webrtc

```
# openssl配置
brew list openssl
echo 'export PATH="/opt/homebrew/Cellar/openssl@1.1/1.1.1q/bin:$PATH"' >> ~/.zshrc
echo 'export PATH="/opt/homebrew/Cellar/openssl@1.1/1.1.1q/include:$PATH"' >> ~/.zshrc
echo 'export PATH="/opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib:$PATH"' >> ~/.zshrc
./configure --enable-openssl
source ~/.zshrc
pkg-config --libs openssl
pkg-config --list-all | grep open
ln -s /opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib/pkgconfig/openssl.pc /opt/homebrew/lib/pkgconfig
./configure --enable-openssl
cd /opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib
ln -s /opt/homebrew/Cellar/openssl@1.1/1.1.1q/lib/pkgconfig/libcrypto.pc /opt/homebrew/lib/pkgconfig
./configure --enable-openssl
# libsrtp
wget https://codeload.github.com/cisco/libsrtp/tar.gz/refs/tags/v2.3.0
mkdir build && cd build && cmake -DENABLE_OPENSSL=1 .. && make && sudo make
# ZLMediaKit开启webrtc
cmake -DENABLE_WEBRTC=true ..
# 浏览器打开网页输入本机ip。默认端口是80
```

<++>

# 多线程与智能指针

# weak\_ptr和shared\_ptr

# 关于 C++ 接口多线程安全的问题

- 构造和析构其实是线程安全的，可以在其他线程调用。析构的线程在使用shared\_ptr时是线程安全的，但是用裸指针，也要确保析构的线程安全。zlm里面TCPSession类是绑定Poller线程的，它的生命周期内，只有一个线程操作它(其他线程操作时要切换到它的线程).比较棘手的是全局变量的线程安全问题，比如说单例，这个一般用锁保护。其他情况下，例如MultiMediaSourceMuxer这种对象，它可以通过http
  api多线程操作它，但是也没有用锁，而是通过拷贝智能指针确保线程安全。有些情况下，不用锁，多线程下也能做到线程安全，一般是借助智能指针拷贝时的原子性来确保。线程安全是门难题，要自己清醒的知道
  哪些函数单线程操作 哪些是多线程的 针对不同的情况做不同的处理。

# 协程的网络库

-ZLMediaKit的设计模式是异步回调式，跟协程差别很大。协程是用户态轻量级线程，用阻塞的思想编程

# [断连续推播放器不断开](https://github.com/ZLMediaKit/ZLMediaKit/issues/1300)

-

# 批量数据转发

- 网络编程中，经常使用的是send/sendto/write函数，但是writev/sendmsg函数应该是用的不多，ZLMediaKit采用sendmsg函数来做批量数据发送，这样不是很好或者服务器负载比较高时，可以明显减少系统调用(系统调用开销比较大)次数，提高程序性能

```
int BufferList::send_l(int fd, int flagsm bool udp)
{
	int n;
	do{
		struct msghdr msg;
		msg.msg_name = null;
		msg.msg_namelen = 0;
		msg.msg_iov = &(_iovec[_iovec_off]);
		msg.msg_flags = flags;
		n = udp ? send_iovec(fd, &msg, flags):sendmsg(fd,&msg, flags);
	}while(-1 == n && UV_EINTR == get_uv_error(true));
	if(n >= _remainSize)
	{
		_iovec_off = _iovec.size();
		_remainSize = 0;
		return n;
	}

	if(n > 0)
	{
		// 部分发送
		reOffset(n);
		return n;
	}
	// 一个字节未发送
	return n;
}
```

# MediaSource基类

- ZLMediaKit中一切媒体的数据源;定位一个MediaSource通过定义一个4元组schema/vhost/app/stream\_id确定的。
- 目前主要的媒体源主要分为RtspMediaSource.RtmpMediaSource,FMP4MediaSource,TSMediaSource;主要是rtmp rtsp h264等子类的基类
- 通过map定义一些唯一MediaSource的唯一标识，

```
// 通过stream的类型，基类一个记录值，是一个插槽，包含四个成员函数，定位mediaSource的类型，主要有协议，虚拟主机(不同公司有streamid冲突，一个公司可以用a.com 另一个用b.com；两个公司可以共享一个物理主机，通过vhost进行隔离，app是采用与rtmp中的概念，流id就是streamId的概念:rtsp::a.com/live/test; rtsp就是schema, a.com就是vhost;live就是app, test就是streamId了，没有这个streamId会有一个问题， )
using StreamMap = std::unordermap_map<std::string, weak_ptr<MediaSource>>;
using AppStreamMap = std::unordermap_map<std::string, StreamMap>;
using VhostAppStreamMap = std::unordermap_map<std::string,AppStreamMap>;
using SchemaVhostAppStreamMap = std::unordermap_map<std::string, VhostAppStreamMap>;

// 注册，注销的概念; 注册是指将本身注册在一个全局的map中，将这个对象删除，就是将这个对象在map中清除。

// 监听void setListener(const std::weak_ptr<MediaSource>& listenner);

// 同步异步查找流
find()
findAsync()
```

## rtsp MediaSource中最重要的两个元素;RTP是实时传输协议，传输层，Real-time Transport Protocol是用于Internet上针对多媒体数据流的一种传输协议。RTP协议详细说明了互联网上传输的音频和视频的标准数据包格式。SDP包中描述了一个Session中包含哪些媒体数据。

## rtsp中最重要的两个元素

- sdp(session description protocol)

```
m line到下一个m line之间就是一个track;
```

> sdp里面传输sps pps; 但是rtp中不传输 -- 摄像头中有这个 sdp里面不传输sps, pps，但是rtp中传输 ---- webrtc sdp和rtp中都传输sps pps; ---
> ZLMediaKit acc adts头

- rtp是视频文件的；

## rtmp中最重要的两个元素

- metadata(一些描述信息，包括音视频codec id宽高，采样率等信息)
- config frame(sps和pps,aac adts头)
- rtmp packet(h264/acc等)

## ts MediaSource

- ts中可以存放媒体的原数据

媒体中最重要的两个概念

- track (轨道， 描述音视频codec信息，还有其他的元数据，包括sps, pps, aac, config)
- Frame(帧数据，h264/h265/aac/G711)

# 假设一个场景

- 一个主播推流，但是有10000个用户同时观看。
- 主播推rtp, rtmp的包，这种情况下需要分发多少次。----10000次
- 假设服务器是64核，这10000个用户可能随机分布在64核上，线程切换，这个包要给分布在64核上的10000个用户。
- 实现线程安全有两种方式，一种是互斥锁，一种是线程切换；如果使用互斥锁，一是性能问题，二是死锁。----线程切换
- A线程产生数据，B线程去消费这个线程。每个用户都消费这个数据，10000个用户这要是分布在64核上，每个包切换一次线程，那就需要切换10000次线程，
- 因为有64核，所以换一个思路就是切换64次，RingBuffer::\_dispatcher\_map中通过:

```
under_map<EventPoller::ptr, typename RingReaderDispatcher::ptr, HashOfPtr> _dispatcher_map;
// 操作 数据，function就是一个任务
async([])
```

# 高质量博客

![框架](../images/ZLMediaKit_muti_thread.png)

# webrtc部分参考easy\_webrtc\_server

- libsrtp库安装

```
mkdir build && cd build && cmake -DENABLE_OPENSSL=1 -DCMAKE_INSTALL_PREFIX=/mnt/d/github_ws/github_ws/xiachu/libsrtp/build .. && make -j8
```

- boost库安装

```
sudo apt install boost-dev
```

- muduo库安装

```
./build.sh
```

- 运行程序

```
# 开启webrtc服务
./rtp_src_example 127.0.0.1
# ffmplay推桌面流
ffmpeg -f gdigrab -i desktop -framerate 25 -s 640x480 -pix_fmt yuv420p  -vcodec libx264 -profile baseline -tune zerolatency  -g 25 -f rtp rtp://127.0.0.1:56000
# 打开easy_webrtc_server/webrtchtml/index.html既可以观看流
```

### clion调试代码

- 程序运行

```shell
#1.本机clion启动mediaServer程序
#2.命令行运行ffmpeg推流
ffmpeg -stream_loop -1 -re -i ~/Downloads/source.200kbps.768x320.flv -acodec copy -vcodec copy -f flv  rtmp://127.0.0.1:1935/live/test
#3.命令行拉流
ffplay rtsp://127.0.0.1:554/live/test
```

- clion调试

```
//RingBuffer类中的write方法会分发，就是先切换线程，查看函数的调用栈比较困难，需要重写一下write方法
 for (auto &pr : _dispatcher_map) {
            auto &second = pr.second;
            //切换线程后触发onRead事件
//            pr.first->async([second, in, is_key]() { second->write(std::move(const_cast<T &>(in)), is_key); }, false);
            second->write(std::move(const_cast<T &>(in)), is_key);
        }
// RtspSession中的sendRtpPacket方法是对客户端发送数据包,可以在pSock-send()函数处打断点调试
// 1 Socket::onRead触发可读事件
// 2 Rtmp::onRecv触发
// 3 RtmpProtocal::onParseRtmp
// 4 HttpRequestSplitter::input
// RtmpProtocol::handle_chunk用于处理RTMP协议的数据块(chunk)。在rtmp协议中，数据被分成一个固定大小的数据块，每个数据块包含了一些元数据和实际数据，这个函数的作用就是解析这些数据块，提取元数据和实际数据，根据协议规定的顺序和方式将它们组合成完成的数据流。
具体操作:解析数据块头部，提取出数据块的长度，类型时间戳等元数据；根据协议规定的时间戳顺序，将数据块组合成完整的数据流交给上层的应用程序或者媒体数据播放器进行处理。
```

### 基本概念

- rtsp mediaSource
  - pps是Picture Parameter
    Set图像参数集，PPS包含了编码图像的特定参数，如量化参数，运动补偿等参考帧，在视频编码时，每个图像都需要使用一个pps进行编码。解码时，需要解码器使用的pps进行解码，以便可以正确的还原出原始图像/
  - SPS是Sequenece Parameter
    Set序列参数集，一起构成了视频编码标准的参数集。SPS包含了视频序列的参数，如帧数据大小，帧率，比特率等信息，PPS和SPS一起传输给解码器，可以解码器能够正确地解码视频流。
  - SDP代表会话描述协议(Session Description
    Protocal),是一种文本格式的协议，用于描述多媒体会话的参数，SDP通常用于VoIP和视频会议等应用中，以便在参与者之间之间交换会话信息。
  - GOP代表“group of pictures，即一组图像，GOP是视频编码中的一个重要概念，它定义了视频序列中的图像帧的组织方式。
