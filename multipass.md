## 查询系统镜像清单

```shell
multipass find
```

## 查询已创建实例

```shell
multipass list
```

## 安装实例

```shell
multipass launch --name ubuntu22 22.04
multipass launch --name ubuntu22 22.04 -c 4 -m 4G -d 20G
```

## 实现虚拟机与主机文件共享

- 由于ubuntu系统下并没有丰富的可视化操作界面，代码编辑也不方便。我们希望ubuntu仅作为运行环境，具体的代码编辑在主机环境下完成，这时候就涉及到虚拟机与主机的文件共享

```shell
//挂在共享 D:\workspace目录下的文件共享给虚拟机
multipass mount D:\workspace ubuntu22
# https://www.shuzhiduo.com/A/Ae5RKnaMdQ/
# 重启
multipass restart ubuntu2204
# 宿主机卸载虚拟机
multipass unmount ubuntu2204
```

- windows下，还需先执行一步骤

> 在windows上，挂载默认是禁用的，因为任何对localhost(127.0.0.1)具有TCP访问权限的人都可以使用Mutipass,并且通过扩展，可以访问整个文件系统。

```shell
# 命令范例multipass set [options] <key>=<value>
multipass set local.privileged-mounts=true
```

## 进入虚拟机

```shell
multipass shell ubuntu2204
# 设置密码
sudo passwd
# 切换root
su root
```

## 挂载数据卷

```shell
multipass mount 宿主机目录 实例名:虚拟机目录
mkdir hello
multipass mount /Users/wangwenqiang/hello ubuntu2204:/hello
```

## 如果不需要用到挂载了，可以使用unmount命令卸载

```shell
multipass umount 容器名
```

## 传输文件

```shell
multipass transfer 主机文件 容器名:容器目录
multipass transfer hello.txt vm01:/home/ubuntu/
```

## 删除和释放实例

```shell
# 启动实例
multipass start ubuntu2204
# 停止实例
multipass stop ubuntu2204
# 删除实例(删除后，还会存在)
multipass delete ubuntu2204
# 释放实例(彻底删除)
multipass delete --purge ubuntu2204
```

## 容器配置自动化

- 为了保持开发环境和线上环境一致性同时节省部署时间multipass给我们提供了--cloud-init选项进行容器启动初始化配置:

```shell
multipass launch --name ubuntu2204 --cloud-init config.yaml
```

- config.yaml则是容器的初始化配置文件，如果我们想在初始化容器的时候，自动下载安装node.js, 内容如下：

```yaml
runcmd:
	- curl -sL https://deb.nodesource.com/setup_12.x|sudo -E bash -
	- sudo apt-get install -y nodejs
```

- runcmd 可以指定容器 首次启动 时运行的命令
- yaml 配置文件可以参照:

> https://cloudinit.readthedocs.io/en/latest/topics/examples.html?highlight=lock-passwd#including-users-and-groups

## 停止容器后设置容器参数

```
# 先停止 multipassd 服务
sudo launchctl unload /Library/LaunchDaemons/com.canonical.multipassd.plist
# 修改配置文件
sudo su
vim /var/root/Library/Application\ Support/multipassd/qemu/multipassd-vm-instances.json
# 再启动 multipassd
sudo launchctl load /Library/LaunchDaemons/com.canonical.multipassd.plist
# 格式
{
    "primary": {
        "deleted": false,
        "disk_space": "10737418240",// 10G
        "mac_addr": "52:54:00:5d:ed:45",
        "mem_size": "4294967296",//4096M
        "metadata": {
        },
        "mounts": [
        ],
        "num_cores": 2,
        "ssh_username": "ubuntu",
        "state": 0
    }
}

# 重新设置硬盘大小
```

# https://github.com/canonical/multipass/issues/29

How to increase the image size in ubuntu: sudo apt-get install qemu-utils find the location of your
multipass by find . -type d -name multipassd. for me it was in:
/var/snap/multipass/common/data/multipassd/vault/instances. cd
/var/snap/multipass/common/data/multipassd/vault/instances/instance-name stop the vs by multipass
stop instance-name resize the image by sudo qemu-img resize ubuntu-20.04-server-cloudimg-amd64.img
+20G start the instance again by multipass start instance-name

# mac

Here is an example of what I did on a macOS 11.1 host: first make sure the multipass VM is shut
down, then open a local terminal brew install qemu install the qemu CLI tools sudo su - become root
cd '/var/root/Library/Application Support/multipassd/vault/instances/primary' move into directory
where the virtual disk files are stored qemu-img resize ubuntu-20.04-server-cloudimg-amd64.img +10G
(I only needed 10 more gigs, but you can use however much you want) Then start up the multipass VM.
A df -h will show you that the root filesystem has auto-expanded to consume the newly allocated
space.

```
```
