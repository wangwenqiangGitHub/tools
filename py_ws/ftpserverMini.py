#! /usr/bin/env python
# -*- coding: utf-8 -*-
#======================================================================
#
# test.py - 
#
# Created by wwq on 2023/06/01
# Last Modified: 2023/06/01 08:47:20
#
#======================================================================
from pyftpdlib.authorizers import DummyAuthorizer
from pyftpdlib.handlers import FTPHandler, ThrottledDTPHandler
from pyftpdlib.servers import FTPServer

FTP_PORT = 2121
FTP_USER = "wangwenqiang"
FTP_PASSWORD = "123456789"
FTP_DIRECTORY = "."
'''
FTP服务的主动模式和被动模式
在开始之前，先聊一下FTP的主动模式和被动模式，两者的区别 ， 用两张图来表示可能会更加清晰一些：
主动模式：

主动模式工作过程：
1.
客户端以随机非特权端口N，就是大于1024的端口，对server端21端口发起连接
2.
客户端开始监听
N + 1
端口；
3.
服务端会主动以20端口连接到客户端的N + 1
端口。
主动模式的优点：
服务端配置简单，利于服务器安全管理，服务器只需要开放21端口
主动模式的缺点：
如果客户端开启了防火墙，或客户端处于内网（NAT网关之后）， 那么服务器对客户端端口发起的连接可能会失败
被动模式：

被动模式工作过程：
1.
客户端以随机非特权端口连接服务端的21端口
2.
服务端开启一个非特权端口为被动端口，并返回给客户端
3.
客户端以非特权端口 + 1
的端口主动连接服务端的被动端口
被动模式缺点：
服务器配置管理稍显复杂，不利于安全，服务器需要开放随机高位端口以便客户端可以连接，因此大多数FTP服务软件都可以手动配置被动端口的范围
被动模式的优点：对客户端网络环境没有要求
了解了FTP之后，开始使用python来实现FTP服务

mac中需要安装ftp客户端测试:brew Install tnftp
~
╰─ ftp 127.0.0.1 2121
Connected to 127.0.0.1.
220 pyftpdlib based ftpd ready.
Name (127.0.0.1:wangwenqiang): wangwenqiang
331 Username ok, send password.
Password:
    230 Login successful.
    Remote system type is UNIX.
    Using binary mode to transfer files.
    ftp> rest 100
    Restarting at 100 for next get, put or append
    ftp> q
    ?Ambiguous command.
    ftp> exit
    221 Goodbye.

从 rest100 返回值可以看出
'''

def main():
    authorizer = DummyAuthorizer()

    # Define a new user having full r/w permissions.
    authorizer.add_user(FTP_USER, FTP_PASSWORD, FTP_DIRECTORY, perm='elradfmw')

    dtp_handler = ThrottledDTPHandler
    dtp_handler.read_limit = 30720  # 30 Kb/sec (30 * 1024)
    dtp_handler.write_limit = 30720  # 30 Kb/sec (30 * 1024)

    handler = FTPHandler
    handler.authorizer = authorizer
    handler.dtp_handler = dtp_handler

    # Define a customized banner (string returned when client connects)
    handler.banner = "pyftpdlib based ftpd ready."

    # Optionally specify range of ports to use for passive connections.
    # handler.passive_ports = range(60000, 65535)

    address = ('', FTP_PORT)
    server = FTPServer(address, handler)

    server.max_cons = 256
    server.max_cons_per_ip = 5

    server.serve_forever()


if __name__ == '__main__':
    main()
