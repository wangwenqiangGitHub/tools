# 基于libpcap数据抓包
```shell
wget -c http://www.tcpdump.org/release/libpcap-1.7.4.tar.gz
./configure
make && make install
```
# 参考
- https://github.com/samarjit98/Computer-Networks

# libpcap库接口
- pcap_loop(); 与pcap_next()和pcap_next_ex()两个函数一样用来捕获数据包
- pcap_next_ex(pcap_t* p, struct pcap_pkthdr** pkt_header,const u_char** pkt_data)
```shell
	功能：从interface或离线记录文件获取一个报文
	参数: p: 已打开的捕捉实例的描述符
         pkt_header: 报文头
         pkt_data: 报文内容
	返回值: 1: 成功
            0: 获取报文超时
            -1: 发生错误
            -2: 获取到离线记录文件的最后一个报文
- struct pcap_pkthdr
	{
		struct timeval ts;   ts是一个结构struct timeval，它有两个部分，第一部分是1900开始以来的秒数，第二部分是当前秒之后的毫秒数
			bpf_u_int32 caplen;  表示抓到的数据长度
			bpf_u_int32 len;    表示数据包的实际长度
	}
```
- 设置pcap抓包的方向
```cpp
pcap_setdirection(handle,PCAP_D_OUT);
- 参数：设备句柄，输出，输入
```
- 设备嗅探
pcap_t* pcap_open_live(char* device,int snaplen, int promisc, int to_ms, char* ebuf);
device:指定的设备；snaplen:定义pcap捕捉的最大字节数，promisc设为true，将指定接口为混杂模式，to_ms是读取时的超时值，单位是毫秒，ebuf是一个我们可以存入任何错误信息的字符串
- 过滤通信
pcap_compile()与pcap_setfilter()

# 时间打印时间戳问题
```cpp
void now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int64_t step = ((int64_t)tv.tv_sec) * 1000 * 1000 + tv.tv_usec;
	printf("now: %lld\n", step);
}

```
