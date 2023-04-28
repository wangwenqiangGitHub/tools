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
cd ~/poky/build/tmp/deploy/images
runqemu qemux86-64
```

- [构建Yocto](https://blog.csdn.net/u013921164/article/details/111941111)

# 编译Yocto环境

- 需要在vmware下构建系统,目录选择linux的目录(~),不要选择mount下的linux中的共享目录，有问题,可能是windows的共享目录不支持文件大小区分。

# Yocto流程

```
开始---解析配方文件----do_fetch(获取源码)---do_unpack(解压源码)---do_patch(给源码打patch)---do_configure(配置源码编译选项)---do_compile(编译源码)---do_install(成果安装)---do_package(成果打包)---do_rootfs(生成镜像文件)---do_image(生成镜像)---开始
```

# lisence生成工具安装

```
https://github.com/azu/license-generator
curl https://sh.rustup.rs -sSf | sh
cargo install license-generator
#生成MIT LICENSE
license-generator MIT --author "azu"
```

# Yocto中创建自己的helloworld应用程序

- 1.创建一个新的 Layer

```
$ yocto-layer create mylayer
#或者采用
$ bitbake-layers create-layer /path/to/mylayer
$ bitbake-layers add-layer /path/to/mylayer
```

该命令会在当前目录下创建一个名为 mylayer 的新 Layer。

- 2.在 Layer 中添加 Hello World 程序 接下来，在 mylayer 目录下创建一个名为 helloworld 的子目录，用于存放 Hello World
  程序。在该目录下创建一个名为 helloworld.c 的源代码文件，内容如下：

```
#include <stdio.h>

int main() {
    printf("Hello, world!\n");
    return 0;
}
```

- 3.创建Helloword软件包 在 mylayer 目录下创建一个名为 helloworld_1.0.bb 的 recipe 文件，用于描述如何构建 helloworld
  软件包。该文件内容如下：

```
SUMMARY = "Hello World Application"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e60cdcbbed556f6a5e8aea"
SRC_URI = "file://helloworld.c"

S = "${WORKDIR}"

do_compile() {
    ${CC} helloworld.c -o helloworld
}

do_install() {
    install -d ${D}${bindir}
    install -m 0755 helloworld ${D}${bindir}
}
```

该 recipe 文件指定了软件包的摘要 (SUMMARY)、许可证 (LICENSE)、源代码 URI (SRC_URI) 等信息，以及如何编译 (do_compile) 和安装
(do_install) Hello World 程序。

- 4.添加 mylayer 到 Yocto 的 Layer 列表中 将新创建的 mylayer 加入到 Yocto 的 Layer 列表中，可以将其添加到
  build/conf/bblayers.conf 文件中，例如：

```
BBLAYERS ?= " \
             /path/to/poky/meta \
             /path/to/poky/meta-poky \
             /path/to/poky/meta-yocto-bsp \
             /path/to/mylayer \
             "
```

这里 /path/to/mylayer 表示 mylayer 的根目录。

- 5.构建并生成 helloworld 软件包

```
$ bitbake helloworld
```

运行成功后，helloworld 软件包会被生成到 tmp/deploy/rpm 目录下。 可以将生成的 helloworld 软件包通过 SCP
等方式传输到目标设备中，然后在目标设备上安装和运行软件包：

```
$ rpm -i helloworld-1.0-r0.armv7a.rpm
$ helloworld
Hello, world!
```

- 6 遇到的问题
  - file://找不到跟bb文件相同路径下的文件，修改为绝对路路径后，可以do_fetch找到文件
  - do_compile时，还是找不到文件，修改为绝对路径后，可以编译通过
  - 编译出的文件位置tmp/deploy文件太多了，通过`find . -name "*helloworld*"`找到在core2_64目录下

# Yocto中的一些专有名词，及术语

- 1.配方(recipe): 只的是一个用于软件构建包的脚本，通常以.bb文件为后缀名。配方文件中包含了软件的源代码，依赖关系，编译选项等信息，可以使用bitbake工具自动化地进行构建和安装。
- 2.层(layer)指的是 Yocto 的组成部分之一，用于管理和组织不同的软件包、配置文件、补丁、镜像等资源。每个层都包含了一个或多个配方文件和其他相关文件，并可以随时添加到 Yocto
  构建系统中以扩展功能或定制化配置。
