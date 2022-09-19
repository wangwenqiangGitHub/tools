# 安装mysql
sudo apt install mysql-server
- archlinux
sudo pacman -Si mysql


- 初始化mysql
```sh
sudo mysqld --initialize --user=mysql --basedir=/usr --datadir=/tmp/mysql
#输出:
#❯ mysqld --initialize --user=mysql --basedir=/usr --datadir=/tmp/mysql
#2022-09-16T04:51:10.418855Z 0 [Warning] [MY-010915] [Server] 'NO_ZERO_DATE', 'NO_ZERO_IN_DATE' and 'ERROR_FOR_DIVISION_BY_ZERO' sql modes should be used with strict mode. They will be merged with strict mode in a future release.
#2022-09-16T04:51:10.418977Z 0 [System] [MY-013169] [Server] /usr/bin/mysqld (mysqld 8.0.29) initializing of server in progress as process 9682
#2022-09-16T04:51:10.421589Z 0 [Warning] [MY-010122] [Server] One can only use the --user switch if running as root
#2022-09-16T04:51:10.486949Z 1 [System] [MY-013576] [InnoDB] InnoDB initialization has started.
#2022-09-16T04:51:19.652879Z 1 [System] [MY-013577] [InnoDB] InnoDB initialization has ended.
#2022-09-16T04:51:44.485504Z 6 [Note] [MY-010454] [Server] A temporary password is generated for root@localhost: N2f(wgx_rC*u)
```

- 库安装
```sh
  wget https://github.com/unicode-org/icu/releases/download/release-71-1/icu4c-71_1-src.tgz
  cd icu/source && make && sudo make install
  sudo ln -s /usr/local/lib/libicuuc.so.71 /usr/lib/libicuuc.so.71
  sudo ln -s /usr/local/lib/libicui18n.so.71  /usr/lib/libicui18n.so.71
  sudo ln -s /usr/local/lib/libicudata.so.71  /usr/lib/libicudata.so.71
```
- 开机启动
```
sudo systemctl enable mysqld.service
```

- 启动mysql服务
```
sudo systemctl start mysqld.service
```

- 查看mysql状态
```
systemctl status mysqld.service
```

- 连接数据库
```
mysql -uroot -p
```

# 刚安装mysql问题MySQL 的 ERROR 1698 (28000): Access denied for user 'root'@'localhost'
- [会通过系统用户认证](https://blog.csdn.net/jlu16/article/details/82809937)
```
# 方法1
$ sudo mysql -u root # I had to use "sudo" since is new installation

mysql> USE mysql;
mysql> UPDATE user SET plugin='mysql_native_password' WHERE User='root';
mysql> FLUSH PRIVILEGES;
mysql> exit;

$ service mysql restart
# 方法2 用你的操作系统用户名代替YOUR_SYSTEM_USER
$ sudo mysql -u root # I had to use "sudo" since is new installation

mysql> USE mysql;
mysql> CREATE USER 'YOUR_SYSTEM_USER'@'localhost' IDENTIFIED BY '';
mysql> GRANT ALL PRIVILEGES ON *.* TO 'YOUR_SYSTEM_USER'@'localhost';
mysql> UPDATE user SET plugin='auth_socket' WHERE User='YOUR_SYSTEM_USER';
mysql> FLUSH PRIVILEGES;
mysql> exit;

$ service mysql restart
```
- 使用的命令:
```
# 使用这个命令进入mysql
sudo mysql -u root # I had to use "sudo" since is new installation
# 设置密码
 mysqladmin -uroot password "uplooking"==>设置密码
#登录
 mysql -uroot -p==>登陆
```

<++>
# mysql学习文档
[参考文档](https://github.com/BoobooWei/booboo_mysql/blob/master/01-MySQL%E5%92%8CMariaDB%E6%95%B0%E6%8D%AE%E5%BA%93%E4%BB%8B%E7%BB%8D.md)

