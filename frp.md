# frp所在的github地址

```
https://github.com/fatedier/frp
```

# 下载

```shell
wget https://github.com/fatedier/frp/releases/download/v0.38.0/frp_0.38.0_linux_amd64.tar.gz
```

# 安装(服务器和客户端都要安装)

安装前需要有一台具备公网IP的机器或云服务器，我用的是腾讯云服务器。 具有公网IP的机器（云服务器等）安装服务端frps，需要内网穿透的机器安装客户端frpc。

```
#解压缩
tar -vxzf frp_0.38.0_linux_amd64.tar.gz
cd frp_0.38.0_linux_amd64
#复制执行文件
sudo cp frpc frps /usr/bin/
#复制配置文件
sudo mkdir /etc/frp
sudo cp frp*.ini /etc/frp
#复制系统服务文件
sudo cp systemd/* /lib/systemd/system/
#启动frp客户端
sudo systemctl start frpc
#启动frp服务端
sudo systemctl start frps
#配置开机启动
sudo systemctl enable frpc
sudo systemctl enable frps
```

# 客户端frpc.ini配置文件

```
[common]
server_addr = xx.xx.xx.xx       #公网服务器ip
server_port = xxxx#服务器端口号
token = 123456                  #服务器和客户端协商的密码，不一致无法登录
tls_enable = true               #使用tls加密

[windows10_rdp]
type = tcp
local_ip = 127.0.0.1#本地映射的应用的IP
local_port = 3389#本地映射的应用的端口
remote_port = 13389             #远端访问端口
use_compression = true          #启用数据压缩

[range:windows10_ftp]
type = tcp
local_ip = 127.0.0.1
local_port = 21,50000-50002
remote_port = 2121,50000-50002
use_compression = true

[windows10_web]
type = http
local_port = 80
custom_domains = yourdomain.cn
use_compression = true

[windows10_smb]
type = tcp
local_ip = 127.0.0.1
local_port = 445
remote_port = 6000
use_compression = true

[ubuntu20.04_ssh]
type = tcp
local_ip = 192.168.1.122
local_port = 22
remote_port = 2222
use_compression = true

[ubuntu20.04_desktop]
type = tcp
local_ip = 192.168.1.122
local_port = 3389
remote_port = 23389
use_compression = true
```

```
#客户端是本机电脑或者同一局域网内的电脑都可以，启动frp：
sudo systemctl restart frpc
```

# 服务器端frps.ini文件

```
[common]
bind_port = xxxx#服务端端口号，和客户端的server_port一致
dashboard_port = 7500#frp管理页面端口
vhost_http_port = 8080#http端口
token = 123456#服务器和客户端协商的密码，不一致无法登陆
dashboard_user = 123#frp管理页面用户名
dashboard_pwd = 123#frp管理页面用户密码
```

```
#服务器需要具有公网IP，可以使用腾讯云或者阿里云，操作前需要先配置防火墙打开使用的端口
sudo systemctl restart frps
```

# 6 访问

```
#win10远程登陆，手机或平板下载RD Client软件，windows直接使用远程桌面
登陆：服务器IP:13389

#访问ftp
ftp name@xx.xx.xx.xx:2121

#远程登陆ubuntu的ssh
ssh -o port=2222 name@xx.xx.xx.xx

#远程登陆ubuntu的桌面
#1.ubuntu安装xrdp
sudo apt install xrdp
#2.win10远程桌面登陆ubuntu
登陆：服务器IP：23389
```

# 7.附：win10平台下安装方法

win10下配置frp与ubuntu类似，配置方法都是一样的，只需下载对应的windows版本安装。配置完成后可以双击exe执行，也可以在win10中创建启动脚本来自动启动：

```
'start_frpc.vbs
'请根据实际情况修改路径
CreateObject("WScript.Shell").Run """D:\Program Files\frp_0.38.0_windows_amd64\frpc.exe""" & "-c" & """D:\Program Files\frp_0.38.0_windows_amd64\frpc.ini""",0
```

将上述内容用记事本另存为start\_frpc.vbs文件。 启动方法： 1.双击就可启动frpc，可在资源管理器中看到frpc.exe已启动;
2.或将其放到开机启动文件夹中C:\ProgramData\Microsoft\Windows\Start
Menu\Programs\Startup，开机后会自启动。同时按住“win+r”，输入shell:startup就会自动打开启动文件夹。
