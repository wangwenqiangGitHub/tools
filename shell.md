## 库中查找函数名字

```shell
find <file_path> -name "*.h" | xargs grep "find_word"
```

## Makefile脚本

```Makefile
.PHONY: xx

"":
	if [ -d "build" ]; then \
		cd build && make -j4; \
	else \
		mkdir build; \
		cd build && cmake -DCMAKE_CXX_COMPILER:FILEPATH=$(shell which arm-linux-gnueabi-g++) -DCMAKE_C_COMPILER:FILEPATH=$(shell which arm-linux-gnueabi-gcc) ..; \
	fi

%:
	if [ -d "build" ]; then \
		cd build && make $@; \
	else \
		mkdir build; \
		cd build && cmake -DCMAKE_CXX_COMPILER:FILEPATH=$(shell which arm-linux-gnueabi-g++) -DCMAKE_C_COMPILER:FILEPATH=$(shell which arm-linux-gnueabi-gcc) $@ ..; \
	fi
```

## 生成库文件，提取库，头文件

```shell
# 把头文件拷贝到 /usr/include/xxx  xxx.so库拷贝到 /usr/lib
if [ ! -d /usr/include/xxx]; then
    mkdir /usr/include/xxx
fi

for header in `ls *.h`
do
    cp $header /usr/include/xxx
done

cp `pwd`/lib/xxx.so /usr/lib

ldconfig
```

## head命令

```shell
head -n 5 test.txt #打印前5行
head -c 5 test.txt #打印第一个5字节
```

# 常用文件比较符

-e 判断对象是否存在 -d 判断对象是否存在，并且为目录 -f 判断对象是否存在，并且为常规文件 -L 判断对象是否存在，并且为符号链接 -h 判断对象是否存在，并且为软链接 -s
判断对象是否存在，并且长度不为0 -r 判断对象是否存在，并且可读 -w 判断对象是否存在，并且可写 -x 判断对象是否存在，并且可执行 -O 判断对象是否存在，并且属于当前用户 -G
判断对象是否存在，并且属于当前用户组 -nt 判断file1是否比file2新 [ "/data/file1" -nt "/data/file2" ] -ot 判断file1是否比file2旧 [
"/data/file1" -ot "/data/file2" ]

# 文件黑洞

- 2\>/dev/null 将文件描述符2(标准错误)重定向操作到文件黑洞中
  - 0-stdin 标准输入
  - 1-stdout 标准输出
  - 2-stderr 标准错误

# sed命令

- 找到以abc开头的，并替换整行

```shell
# /c表示替换整行
sed -i '/^abc/ccloud_server_ip = update.skyeye.360safe.com' test.txt
```

# 使用iptables配置NAT-(网络地址转换)

```
场景：Server A 运行着一个服务s1，只开放的本地地址连接，开放的端口号是6543。即Server A的服务s1监听的端口是127.0.0.1：6543。本地客户端Client想连接到服务s1去，这时可以修改s1的配置文件，让其监听所有的地址。也可以使用iptables配置NAT，使得可以访问6543的端口。

解决方案1：在Server A中执行iptables -t nat -A PREROUTING -p tcp --dport 1233 -j DNAT --to-destination 127.0.0.1:6543，让连接到Server A的1233的端口转发到本地的6543端口上去，完成了NAT的映射。

模拟：
step1： Server A执行 nc -l -p 6543 监听本地的6543端口
step2： Server A执行 iptables -t nat -A PREROUTING -p tcp --dport 1233 -j DNAT --to-destination 127.0.0.1:6543 进行地址映射
step3： 在Clinet 所在的机器访问Server A的1233端口，假设Server A的公网IP是22.23.34.1，nc 22.23.34.1 1233
step4: 在Client建立连接后，输入几个字符，在Server A监听的6543端口上有显示即可。

解决方案2：

iptables -t nat -A PREROUTING -p tcp --dport 5000 -j REDIRECT --to-ports 6543
使用REDIRECT的action，直接将Server A的5000端口数据转发到本地的6543端口中去。

上述提到的两个解决方案，在本地验证是通过不了的。即Server A和Client 都是同一台机器，因为使用lo网卡的时候，是没有PREROUTING这个阶段的，如果一定要在本地进行NAT的验证。可以使用此命令：iptables -t nat -I OUTPUT -p tcp -o lo --dport 1232 -j REDIRECT --to-ports 6543 。此命令是设置了，lo网卡的数据包的目的端口是1232的时候，转发到6543端口去。使用的是OUTPUT，因此从外部访问Server A的1232端口的话，不会转发的6543端口去，一定要是本地访问本地的时候才行。
后记

使用上述的NAT功能前，一定要先开启linux nat转发的功能：echo 1 > /proc/sys/net/ipv4/ip_forward ，重启后失效，如果需要重启后还开启，需要写到/etc/rc.local中去
上述提到的场景，可扩展为Server A的1233端口，转发到Server B（假设地址是8.8.8.8）的6543端口中去，Server A的角色是一个跳板，只要修改一下命令：把iptables -t nat -A PREROUTING -p tcp --dport 1233 -j DNAT --to-destination 127.0.0.1:6543 改成 iptables -t nat -A PREROUTING -p tcp --dport 1233 -j DNAT --to-destination 8.8.8.8:6543

场景使用: 目的地址变换
上位机------>板卡1------------->板卡2
通过iptables命令在板卡1上配置目的地址变换，实现上位机通过板卡1控制板卡2
```

```shell
#相关命令
iptables -t nat -L
vim /etc/iptables/iptables.rules
iptables -t nat -A PREROUTING -p tcp --dport 8080 -j DNAT --to-destination 192.168.12.1234
```

# 位置参量列表

| name  | 功能                                                                |
|-------|---------------------------------------------------------------------|
| $0    | 当前脚本文件名                                                      |
| $1~$9 | 第一到第9个位置参数                                                 |
| $10   | 第十个位置参数                                                      |
| $#    | 位置参量的个数                                                      |
| $*    | 以单字符串显示所有位置参数                                          |
| $@    | 未加双引号时与$*含义相同，加双引号后有差别                          |
| $$    | 脚本运行的进程号                                                    |
| $!    | 最后一个后台运行的进程的进程号                                      |
| $?    | 显示前面最后一个命令的退出状态,0 表示没有错误，其他任何值表示有错误 |


# 数组
- 定义
```
arr=(math english chinese)
```

- 数组初始化
```
arr=(math english chinese)
```
- 数组引用
    - 引用变量:${arr[0]}
    - 数组个数:${#arr[*]}
    - 所有元素:${arr[*]}

- 数组赋值
    - arr[0]=test

# 匹配模式

| 名称         | 解释                                            |
|--------------|-------------------------------------------------|
| ^            | 只匹配行首，可以看成是行首的标志                |
| &            | 只匹配行尾，行尾标志                            |
| *            | 一个单字符后紧跟一个*，匹配一个或者多个此字符   |
| []           | 匹配[]内的任意一个字符[^]反向匹配               |
| \w           | 匹配单词字母，等同于[o-9A-Za-z_]                |
| \W           | 匹配单词字母之外的任意字符，等同于[^0-9A-Za-z_] |
| \            | 用来屏蔽一个元字符的特殊含义                    |
| .            | 用来匹配任意字符                                |
| str1 \| str2 | 匹配str1或者str2                                |
| +            | 匹配一个多个前一个字符                          |
| ?            | 匹配零个或者一个字符                            |
| ()           | 字符组                                          |
