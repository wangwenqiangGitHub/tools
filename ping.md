### 测试MTU

使用ping命令来测试MTU时, 是测试从你的设备到目标设备之间的网络路径上的MTU大小, 而不是单独目标设备的MTU大小.

- linux命令

```
ping -s 1472 -M do 192.168.1.1
```

- windows命令

```
ping -l  1472 -f 192.148.1.1
```

命令中的参数解释如下：

- s（Linux）或 -l（Windows）指定数据包的大小。
- M do（Linux）或 -f（Windows）设置不分片标志（Don't Fragment bit）。
- 设置mtu值

```
# 1. 临时设置
sudo ifconfig eth0 mtu 1480
sudo ip link set dev eth0 mtu 1480
# 2. 永久修改
# Debian/Ubuntu vi /etc/network/interfaces
auto eth0
iface eth0 inet static
    address 192.168.1.100
    netmask 255.255.255.0
    gateway 192.168.1.1
    mtu 1480
# centOS/RHEL vim /etc/sysconfig/network-scripts/ifcfg-eth0
MTU="1480"
```
