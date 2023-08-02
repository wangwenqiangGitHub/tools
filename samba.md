# samba基本使用

```shell
sudo apt-get install samba
sudo touch /etc/samba/smbpasswd
sudo smbpasswd -a <用户>
vi /etc/samba/smb.conf

[ubuntu]
	comment = ubuntu
	path = /home/kingwq
	writable = yes
	valid user = xugaoxiang
	available = yes
	create mask = 0777
	directory mask = 0777
	public = yes

sudo /etc/init.d/smbd restart
```

# 设置的smb的共享文件夹路径位置

```
mkdir /tmp/shared
chmod 777 /tmp/shared
```

# wsl中访问smb路径

```
smbclient //192.168.208.136/ubuntu136
put # 上传文件
get # 下载文件
obj_xfer_v2x_app_new\wangwenqiangq   # 退出
```

# shell脚本

```sh
#!/bin/bash

# 设置变量
smb_server="smb://server_ip/share_name"  # SMB服务器的IP地址和共享名称
username="your_username"  # SMB服务器的用户名
password="your_password"  # SMB服务器的密码
remote_file="path_to_remote_file"  # 远程文件的路径
local_file="path_to_local_file"  # 本地文件的路径

# 使用smbclient下载文件
smbclient "$smb_server" -U "$username" "$password" -c "get $remote_file $local_file"

smbclient //192.168.208.136/ubuntu136 -U kingwq 1 -c "get device.xml device.xml"

smbclient //10.255.20.17/10.255.17.26_aparm_dev/ -U wangwenqiang%password -c "get a a"
```
