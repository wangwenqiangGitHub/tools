# gdb `arm_linux_gnuabi`

```shell
./configure --target=arm-linux-gnueabihf --host=arm-linux-gnueabihf --program-prefix=arm-linux-gnueabihf- CC=arm-linux-gnueabihf-gcc --prefix=/opt/arm-linux-gnueabihf-gdb-8.2
```

# cmake设置优化等级

- -O3 是 `CMAKE_CXX_FLAGS_RELEASE` 这个变量引入的，把它改了就行
- -o0是不进行优化，编译器生成易于调试的代码，但是不做任何优化，主要用于调试目的。
- -o1是进行基本的优化，这个优化用于提高运行时的性能，同时保持调试信息的可能性。
- -o2进行更多的优化。这个级别的优化包括大多数在-o1中可以用的优化,并添加了更多的优化措施
- -o3进行所有的优化
- `注`: 当函数运行不一致时，修改优化的编译选项，并且采用`volatile`

# 最新的commit生成patch

```shell
git log -n 1 -p > what-a-fuck-patch
```

# mac docker ubuntu16.04安装gcc4.9交叉编译环境

```shell
apt install gcc-4.9-arm-linux-gnueabi
apt install g++-4.9-arm-linux-gnueabi 
apt install make cmake
```

## 交叉工具链下载地址

- 官网 https://releases.linaro.org/components/toolchain/binaries/
  https://launchpad.net/gcc-arm-embedded/+download
- 国内镜像 https://mirrors.tuna.tsinghua.edu.cn/armbian-releases/_toolchains/

## microcom

- microcom是一个串口调试指令，经常用于串口调试，相当于linux自带的串口调试助手
- 用例
  - 设置波特率
  ```
  microcom -s 115200 /dev/tty0
  ```

# windows配置交叉编译

```
cmake_minimum_required(VERSION 2.8)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc-7.3.1.exe")
set(CMAKE_CXX_COMPILER "aarch64-linux-gnu-g++.exe")
project(hello_world)
include_directories(inc INC_LIST)
aux_source_directory(src SRC_LIST)
add_executable(hello_world main.c ${SRC_LIST})
```

# 限制作用域

```
GCC的visibility属性用来控制.so文件的符号表，
也就是控制外部能不能找到符号调用，比如函数、变量、模板、类等。符号表分静态的
.symtab 和动态的 .dynsym，一个对应链接视图另一个对应执行视图。
设置为 hidden 符号将不导出，即不出现在 .dynsym 当中，不能为模块外所用。
默认是可见，这也就是“default”的含义。
在编译文件中：
1. 当-fvisibility=hidden时
动态库中的函数默认是隐藏的，除非代码中显示声明为__attribute__((visibility("default"))).
2. 当-fvisibility=default时
动态库中的函数默认是可见的，除非代码中显示声明为__attribute__((visibility("hidden"))).
```
