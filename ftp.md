# ftp采用curl

- https://curl.se/libcurl/c/example.html

# WSL安装ftp服务器并配置frp内网穿透

- 1 安装ftp

```
sudo apt install vsftpd
```

- 2 ftp服务器设置

```
vim /etc/vsftpd.conf

# 按以下的配置修改
listen=YES
listen_ipv6=NO
anonymous_enable=NO
local_enable=YES
write_enable=YES
local_umask=022
anon_upload_enable=YES
anon_mkdir_write_enable=YES
dirmessage_enable=YES
use_localtime=YES
xferlog_enable=YES
connect_from_port_20=NO
chroot_local_user=YES
chroot_local_user=YES
chroot_list_enable=YES
chroot_list_file=/etc/vsftpd.chroot_list
secure_chroot_dir=/var/run/vsftpd/empty
pam_service_name=vsftpd
rsa_cert_file=/etc/ssl/certs/ssl-cert-snakeoil.pem
rsa_private_key_file=/etc/ssl/private/ssl-cert-snakeoil.key
ssl_enable=NO

#主要修改以下内容：
#配置服务器端口
listen_port=21
#配置服务器共享目录
local_root=/mnt/g
#配置服务器访问用户
userlist_deny=NO
userlist_enable=YES
userlist_file=/etc/vsftp_allowed_users
#配置服务器被动模式
pasv_enable=YES
pasv_min_port=50000
pasv_max_port=50002
pasv_promiscuous=YES
pasv_addr_resolve=YES
#解决WSL报错问题
seccomp_sandbox=NO
isolate_network=NO
tcp_wrappers=YES
```

- 新建/etc/vsftp\_allowed\_users文件，向里面添加用户

```
sudo vim /etc/vsftp_allowed_users

#加入你自己的ftp用户名
your_ftp_user
```

- 3 重启ftp服务

```
sudo service vsftpd restart
```

- 4 连接FTP服务器

```
#命令行输入ftp命令,进入ftp交互
ftp
#开启被动模式,多次运行可以开关,on:打开, off:关闭
ftp> passive mode
#连接服务器
ftp> open ip port
#查看服务器文件
ftp> ls
```

# 5 frp内网穿透

```
sudo vim /etc/frp/frpc.ini

#加入以下内容
[range:windows10_ftp]
type = tcp
local_ip = 127.0.0.1
local_port = 21,50000-50002
remote_port = 2121,50000-50002
use_compression = true
```

# 6 参考以前的贴子配置frp.并在外网测试

```
远程访问ftp
ftp
ftp> passive mode#on才可以
ftp> open xx.xx.xx.xx port
ftp> ls
ftp> get remote_file local_file#测试下载文件
```

# 7.ipad下使用ISH访问ftp服务器

```
#ISH中没有ftp命令， 可以安装lftp
apk add lftp

#使用lftp连接ftp服务器
lftp username:password@ip:port

#设置ftp为被动模式，不然端口映射无法访问
lftp> set ftp:passive-mode 1

#查看远程服务器文件
lftp> ls
```

注： username：ftp用户名 password：ftp用户密码 ip：ftp服务器IP地址 port：ftp服务器端口号

# ftp问题记录

```
# 本机lftp命令验证ftp服务器是否正常
# ftp白名单问题
ping 可以ping通
telnet ip port
默认端口21
nc ip port
USER <用户名>
PASS <PASSWORD>
230 Login successful
```

- 抓包过程: ![抓包](./images/ftp抓包.png)
  - `46857 -> 21` [SYN]：这表示源端口为46857的主机向目标端口21（FTP默认端口）的主机发送了一个SYN包，用于请求建立一个TCP连接。
  - `21 -> 46857` [SYN,ACK]：目标主机以端口21回应了一个SYN,ACK包，表示愿意建立连接。
  - `46857 -> 21` [ACK]：源主机发送了一个ACK包，表示对目标主机的SYN,ACK包的确认。
  - `21 -> 46857` [RST,ACK]：然后目标主机发送了一个RST,ACK包，这表示它拒绝了源主机的连接请求。
  - 分析:在正常情况下，FTP的数据传输需要建立两个TCP连接，一个用于控制（端口21），另一个用于数据传输（端口20）。根据抓包看起来在建立数据传输连接时出现了问题，可能是由于防火墙、路由器配置或FTP服务器配置等原因导致的连接失败.
