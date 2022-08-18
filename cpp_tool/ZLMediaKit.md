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
mkdir build && cd build && cmake - cmake -DENABLE_OPENSSL=1 .. && make && sudo make
# ZLMediaKit开启webrtc
cmake -DENABLE_WEBRTC=true ..
# 浏览器打开网页输入本机ip。默认端口是80
```

<++>
# 多线程与智能指针

# weak\_ptr和shared\_ptr


# 关于 C++ 接口多线程安全的问题
- 构造和析构其实是线程安全的，可以在其他线程调用。析构的线程在使用shared\_ptr时是线程安全的，但是用裸指针，也要确保析构的线程安全。zlm里面TCPSession类是绑定Poller线程的，它的生命周期内，只有一个线程操作它(其他线程操作时要切换到它的线程).比较棘手的是全局变量的线程安全问题，比如说单例，这个一般用锁保护。其他情况下，例如MultiMediaSourceMuxer这种对象，它可以通过http api多线程操作它，但是也没有用锁，而是通过拷贝智能指针确保线程安全。有些情况下，不用锁，多线程下也能做到线程安全，一般是借助智能指针拷贝时的原子性来确保。线程安全是门难题，要自己清醒的知道 哪些函数单线程操作 哪些是多线程的 针对不同的情况做不同的处理。
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
- sdp(session description protocol)
```
m line到下一个m line之间就是一个track;
```
- sdp里面传输sps pps; 但是rtp中不传输 -- 摄像头中有这个
- sdp里面不传输sps, pps，但是rtp中传输 ---- webrtc
- sdp和rtp中都传输sps pps; --- ZLMediaKit 
- acc

- rtp是视频文件的；


# 高质量博客
![框架](../images/ZLMediaKit_muti_thread.png)
