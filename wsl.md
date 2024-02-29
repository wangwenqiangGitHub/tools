# 将本机wsl迁移至其他机器

```shell
#host备份机器操作:
wsl --shutdown
#windowsterminall
 C:\Users\戴尔\Downloads\LxRunOffline.exe e -n Ubuntu-20.04 -f D:\wsl_Ubuntu.tar.gz
 #类似但不等同于wsl --export <WSL名称> <压缩包路径>.tar。LxRunOf­fline 备份完会生成一个.xml后缀的同名配置文件，比如WSL.tar.gz.xml。
#target机器操作
lxrunoffline i -n <WSL名称> -d <安装路径> -f <压缩包路径>.tar.gz
#类似但不等同于wsl --import <WSL名称> <安装路径> <压缩包路径>.tar。LxRunOf­fline 会读取备份时生成的配置文件并写入配置，前提是同目录且同名。否则你需要加入-c参数指定配置文件。
```

# 将备份的wsl文件安装到新的机器

```
D:\tools\LxRunOffline-v3.5.0-33-gbdc6d7d-msvc\LxRunOffline.exe i -n Ubuntu-20.04 -d D:\wsl -f D:\tools\wsl_Ubuntu_patch_new.tar.gz

# 进入linux ubuntu2004
id -u kingwq
# 一般uid为1000
lxrunoffline su -n <WSL名称> -v 1000(UID)
```

# 一些由于特殊字符引起的文件不能删除问题

```bat
DEL /F /A /Q \\?\%1
RD /S /Q \\?\%1
# 新建一个fiel_del.bat脚本，将文件移动到这个脚本就可以删除
```

# 关于LxRunOffLine我提出的问题并解决的

- [采用LxRunOffline工具导出wsl2后](https://github.com/DDoSolitary/LxRunOffline/issues/187)
- 迁移到其他盘后，需要修改.wslconfig文件

```
#I find the cause ; have to modify C:\Users\戴尔.wslconfig file;
[wsl2]
#kernel=C:\\temp\\myCustomKernel
memory=4GB # Limits VM memory in WSL 2 to 4 GB
processors=2 # Makes the WSL 2 VM use two virtual processors
```

# 注意下载LxRunOffline的路径，下载最新的，要不wsl转移貌似会出问题

- [下载](https://ddosolitary-builds.sourceforge.io/LxRunOffline/)

# LxRunOffline 基础命令

```
# 查看所有wsl
LxRunOffline l
# 查看安装的路径
LxRunOffline di -n Ubuntu
lxrunoffline ur -n <wsl名称>
```

# wsl出现wsl --update后显示未注册，问题解决

- 首先在设置---应用----(搜索linux)会找到最新更新的子系统，卸载掉就可以了

# 将wsl2的某个镜像设为wsl1

```
wsl -l -v
wsl --set-version  Ubuntu-18.04 1
```

# wsl2最新版本支持静态ip

- 参考:https://zhuanlan.zhihu.com/p/593263088
- 更新wsl:

```
wsl --update --pre-release
```

- 在用户目录:`%USERPROFILE%`下配置`.wslconfig`:

```
[experimental]
networkingMode=mirrored
dnsTunneling=true
firewall=true
autoProxy=true

# 备注:果你遇到 docker 无法从 Windows 访问的问题，这个是 iptables 的问题，在 /etc/docker/daemon.json 里添加一句 "iptables": false 就好了
```

# 删除wsl

```
wsl --unregister Ubuntu
```

# 导出wsl

```
wsl --export Ubuntu-22.04 C:\wsl_ws\ubuntu2204-tools.tar
```

# 导入wsl

```
wsl --import Ubuntu22.04 D:\wsl_ws\ubuntuww C:\wsl_ws\ubuntu2204-tools.tar
```

# wsl 导入后配置用户

```
su -kingwq#可以切入
cat /etc/passwd 可以看到kingwq的uuid为1000
# 默认进入wsl的用户会是root，修改DefaultUid; 修改注册表:
计算机\HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Lxss\{...}
DefaultUid值设置为子系统用户对应的gid值;十进制为1000
```

# wsl问题

```
# 安装nodejs问题
https://learn.microsoft.com/en-us/windows/dev-environment/javascript/nodejs-on-wsl
```

# wsl的配置wslconfig

```
https://learn.microsoft.com/zh-cn/windows/wsl/wsl-config#configure-settings-with-wslconfig-and-wslconf
wsl1或者wsl2采用/etc/wsl.conf
```

# wsl配置显示的语言

```
sudo dpkg-reconfigure locales
sudo apt-get install fonts-arphic-bsmi00lp fonts-arphic-gbsn00lp fonts-arphic-gkai00mp
sudo vim /etc/default/locale
# LANG=zh_CN.UTF-8 可以显示终端输出的中文
sudo apt install zh-autoconvert
sudo apt install zhcon
sudo apt install language-pack-zh-hans
locale -a || locale
```

# wsl 终端下 vim block <ctrl-v> 不生效

- 需要设置一下windows terminal的ctrl-v使用为粘贴快捷键删除。
