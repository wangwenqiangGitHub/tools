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
