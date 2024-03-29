# Download and install Yocto SDK

```
$ wget https://engineering.bcmcom.com/CustomerDL/AR8MXMQ/fsl-imx-xwayland-glibc-x86_64-core-image-minimal-aarch64-toolchain-4.14-sumo.sh
$ sh fsl-imx-xwayland-glibc-x86_64-core-image-minimal-aarch64-toolchain-4.14-sumo.sh

$ wget https://engineering.bcmcom.com/CustomerDL/AR8MXMQ/fsl-imx-xwayland-glibc-x86_64-core-image-minimal-aarch64-imx8mnevk-toolchain-5.4-zeus.sh
$ sh fsl-imx-xwayland-glibc-x86_64-core-image-minimal-aarch64-imx8mnevk-toolchain-5.4-zeus.sh
```

# Remove -wl in LDFLAGS

```
sudo sed -i 's/-Wl,//g' /opt/fsl-imx-xwayland/5.4-zeus/environment-setup-aarch64-poky-linux
```

# How to use i.MX8M Cross compile

```
cd ws
mkdir build && cd build
. /opt/fsl-imx-xwayland/5.4-zeus/environment-setup-aarch64-poky-linux
cmake ..
make -j`nproc` && make install
```

# 交叉编译的环境变量配置

```sh
# Check for LD_LIBRARY_PATH being set, which can break SDK and generally is a bad practice
# http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html#AEN80
# http://xahlee.info/UnixResource_dir/_/ldpath.html
# Only disable this check if you are absolutely know what you are doing!
if [ ! -z "$LD_LIBRARY_PATH" ]; then
    echo "Your environment is misconfigured, you probably need to 'unset LD_LIBRARY_PATH'"
    echo "but please check why this was set in the first place and that it's safe to unset."
    echo "The SDK will not operate correctly in most cases when LD_LIBRARY_PATH is set."
    echo "For more references see:"
    echo "  http://tldp.org/HOWTO/Program-Library-HOWTO/shared-libraries.html#AEN80"
    echo "  http://xahlee.info/UnixResource_dir/_/ldpath.html"
    return 1
fi
export SDKTARGETSYSROOT=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/aarch64-poky-linux
export PATH=/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin:/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/sbin:/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/bin:/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/sbin:/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/../x86_64-pokysdk-linux/bin:/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux:/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/bin/aarch64-poky-linux-musl:$PATH
export PKG_CONFIG_SYSROOT_DIR=$SDKTARGETSYSROOT
export PKG_CONFIG_PATH=$SDKTARGETSYSROOT/usr/lib/pkgconfig:$SDKTARGETSYSROOT/usr/share/pkgconfig
export CONFIG_SITE=/opt/fsl-imx-xwayland/5.4-zeus/site-config-aarch64-poky-linux
export OECORE_NATIVE_SYSROOT="/opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux"
export OECORE_TARGET_SYSROOT="$SDKTARGETSYSROOT"
export OECORE_ACLOCAL_OPTS="-I /opt/fsl-imx-xwayland/5.4-zeus/sysroots/x86_64-pokysdk-linux/usr/share/aclocal"
export OECORE_BASELIB="lib"
export OECORE_TARGET_ARCH="aarch64"
export OECORE_TARGET_OS="linux"
unset command_not_found_handle
export CC="aarch64-poky-linux-gcc  -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=$SDKTARGETSYSROOT"
export CXX="aarch64-poky-linux-g++  -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=$SDKTARGETSYSROOT"
export CPP="aarch64-poky-linux-gcc -E  -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security --sysroot=$SDKTARGETSYSROOT"
export AS="aarch64-poky-linux-as "
export LD="aarch64-poky-linux-ld  --sysroot=$SDKTARGETSYSROOT"
export GDB=aarch64-poky-linux-gdb
export STRIP=aarch64-poky-linux-strip
export RANLIB=aarch64-poky-linux-ranlib
export OBJCOPY=aarch64-poky-linux-objcopy
export OBJDUMP=aarch64-poky-linux-objdump
export READELF=aarch64-poky-linux-readelf
export AR=aarch64-poky-linux-ar
export NM=aarch64-poky-linux-nm
export M4=m4
export TARGET_PREFIX=aarch64-poky-linux-
export CONFIGURE_FLAGS="--target=aarch64-poky-linux --host=aarch64-poky-linux --build=x86_64-linux --with-libtool-sysroot=$SDKTARGETSYSROOT"
export CFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types "
export CXXFLAGS=" -O2 -pipe -g -feliminate-unused-debug-types "
export LDFLAGS="-Wl,-O1 -Wl,--hash-style=gnu -Wl,--as-needed -fstack-protector-strong -Wl,-z,relro,-z,now"
export CPPFLAGS=""
export KCFLAGS="--sysroot=$SDKTARGETSYSROOT"
export OECORE_DISTRO_VERSION="5.4-zeus"
export OECORE_SDK_VERSION="5.4-zeus"
export ARCH=arm64
# 这个环境变量设置时，在编译openssl的时候需要屏蔽这个
export CROSS_COMPILE=aarch64-poky-linux-

# Append environment subscripts
if [ -d "$OECORE_TARGET_SYSROOT/environment-setup.d" ]; then
    for envfile in $OECORE_TARGET_SYSROOT/environment-setup.d/*.sh; do
	    . $envfile
    done
fi
if [ -d "$OECORE_NATIVE_SYSROOT/environment-setup.d" ]; then
    for envfile in $OECORE_NATIVE_SYSROOT/environment-setup.d/*.sh; do
	    . $envfile
    done
fi
export CLANGCC="aarch64-poky-linux-clang  -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -mlittle-endian --sysroot=$SDKTARGETSYSROOT"
export CLANGCXX="aarch64-poky-linux-clang++  -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -mlittle-endian --sysroot=$SDKTARGETSYSROOT"
export CLANGCPP="aarch64-poky-linux-clang -E  -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -mlittle-endian --sysroot=$SDKTARGETSYSROOT"
export CLANG_TIDY_EXE="aarch64-poky-linux-clang-tidy  -mcpu=cortex-a53+crc+crypto -fstack-protector-strong  -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -mlittle-endian --sysroot=$SDKTARGETSYSROOT"
```

# oecore-x86\_64-aarch64-toolchain-nodistro.0.sh文件

```
#默认安装路径/usr/local/oecore-x86_64，可以使用-d指定安装目录安装在/opt目录下
./oecore-x86_64-aarch64-toolchain-nodistro.0.sh -d /opt
#最新版本的imx交叉编译链设置
source /opt/environment-setup-cortexa7hf-neon-vfpv4-pokymllib32-linux-gnueabi
source /opt/environment-setup-aarch64-poky-linux
```

# 文件备份

```
/mnt/d/code/bak/imx8
```

# 编译警告

- armv7程序移植到armv8程序主要问题:
  - 0x86这种数据需要修改为显示类型变换(char)0x86
  - ofstream运算符重载，需要将类型变为str()
  - std::string中用find\_last\_of(".")返回值是std::string::size\_type, 不能使用uint32\_t
