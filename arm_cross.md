# gdb arm_linux_gnuabi

```shell
./configure --target=arm-linux-gnueabihf --host=arm-linux-gnueabihf --program-prefix=arm-linux-gnueabihf- CC=arm-linux-gnueabihf-gcc --prefix=/opt/arm-linux-gnueabihf-gdb-8.2
```

# cmake设置优化等级

- -O3 是 CMAKE_CXX_FLAGS_RELEASE 这个变量引入的，把它改了就行

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
