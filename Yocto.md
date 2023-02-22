# Yocto不能使用Windows Linux子系统(WSL)的构建主机, Yocto与WSL不兼容

- 本次开发环境vmware ubuntu18.04

# 构建所需要的软件包

```shell
sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib \
           build-essential chrpath socat cpio python3 python3-pip python3-pexpect \
           xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev \ pylint3 xterm
```

# git克隆poky

```shell
git clone git://git.yoctoproject.org/poky
cd poky
git checkout tags/yocto-3.1.1 -b yocto-3.1.1
source oe-init-build-env
```

# 构建image

> 注意: 如果打开防火墙，并没设置代理构建主机，则在获取源码时可能会遇到构建过程的问题(git失败)

# 检查本地的配置文件

```shell
vim conf/local.conf
#ubuntu20.20
DL_DIR ?= "${TOPDIR}/downloads"

SSTATE_DIR ?= "${TOPDIR}/sstate-cache"

TMPDIR ?= "${TOPDIR}/tmp"

PACKAGE_CLASSES ?= "package_rpm"

SDKMACHINE ?= "i686"
```

- 编译

```
bitbake core-image-minimal
```

- 运行

```
runqemu qemux86-64
```

- [构建Yocto](https://blog.csdn.net/u013921164/article/details/111941111)

# 编译Yocto环境

- 需要在vmware下构建系统,目录选择linux的目录(~),不要选择mount下的linux中的共享目录，有问题,可能是windows的共享目录不支持文件大小区分。