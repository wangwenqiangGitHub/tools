# tinyxml

- 编译成静态库
  - 1 进入目录tinyxml，用vim命令打开Makefile文件
  - 2 将其中一行 OUTPUT := xmltest 修改为 OUTPUT := libtinyxml.a 表示编译出的静态库文件名字为 libtinyxml.a
  - 3 将其中一行 SRCS :=tinyxml.cpp tinyxml-parser.cpp xmltest.cpp tinyxmlerror.cpp tinystr.cpp
    中的xmltest.cpp删掉 因为不需要编译该测试文件
  - 4 将其中一行 ${LD} -o $@ ${LDFLAGS} ${OBJS} ${LIBS} ${EXTRA_LIBS} 修改为 ${AR} $@ ${LDFLAGS} ${OBJS}
    ${LIBS} ${EXTRA_LIBS} 表示链接成静态库
  - 5 将其中一行 xmltest.o：tinyxml.h tinystr.h 删除，因为不需要编译测试文件
  - 6 保存Makefile文件
  - 7 回退到上一层目录即目录tinyxml中，执行make命令，即可在该目录得到编译出来的静态库文件libtinyxml.a

- 编译成动态库
  - 1 进入目录tinyxml，用vim命令打开Makefile文件
  - 2 在其中一行 DEBUG_CFLAGS := -Wall -Wno-format -g -DDEBUG -fPIC 的末尾添加上 -fPIC 表示编译与位置无关的代码，PIC的意思即
    Position Independent Code，
  - 3 在其中一行 RELEASE_CFLAGS := -Wall -Wno-unknown-pragmas -Wno-format -O3 的末尾添加上 -fPIC 原因同上
  - 4 将其中一行 OUTPUT := xmltest 修改为 OUTPUT := libtinyxml.so 表示编译出的动态库文件名字为 libtinyxml.so
  - 5 将其中一行 SRCS :=tinyxml.cpp tinyxml-parser.cpp xmltest.cpp tinyxmlerror.cpp tinystr.cpp
    中的xmltest.cpp删掉 因为不需要编译该测试文件
  - 6 将其中一行 ${LD} -o $@ ${LDFLAGS} ${OBJS} ${LIBS} ${EXTRA_LIBS} 修改为 ${LD} -shared -o $@ ${LDFLAGS}
    ${OBJS} ${LIBS} ${EXTRA_LIBS} 表示链接成动态库
  - 7 将其中一行 xmltest.o：tinyxml.h tinystr.h 删除，因为不需要编译测试文件
  - 8 保存Makefile文件
  - 9 回退到上一层目录即目录tinyxml中，执行make命令，即可在该目录得到编译出来的动态库文件libtinyxml.so

# busybox

- 安装交叉编译链
  - 配置环境变量
- 下载busybox

```
wget http://busybox.net/downloads/busybox-2.23.tar.bz2
tar -xjf busybox-2.23.tar.bz2
cd busybox-2.23/
```

- 配置编译安装busybox

```
配置： 
 生成默认arm版配置文件.config：  
    make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- defconfig
 通过图形界面修改配置文件.config： 
    make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- menuconfig
 在编译选项中，一般选择静态方式
```

- 编译：

```
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
```

- 安装

```
make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- install
```

# protobuf3.8编译

```
sudo apt install autoreconf automake libtool
./automake.sh
./autogen.sh
make -j4 && make install
```

# sip库

## 先编译libosip

```
./configure --prefix=$(pwd)/OUT
```

## 编译libexosip2-5.1.2

```shell
./configure --prefix=$(pwd)/../libosip2-5.1.2/OUT PKG_CONFIG_PATH=$(pwd)/../libosip2-5.1.2/OUT/lib/pkgconfig/
```

- 如果不加PKG\_CONFIG\_PATH程序编译会出错

```
wget http://download.savannah.gnu.org/releases/exosip/libexosip2-5.1.2.tar.gz
wget http://ftp.twaren.net/Unix/NonGNU/osip/libosip2-5.1.2.tar.gz
```

- 减少文件体积

```
arm-linux-gnueabi-strip -s
/Users/wangwenqiang/Documents/code/r14_ltev2x_app/build/toolchain/gcc-4.9-2016.02-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-strings
```
