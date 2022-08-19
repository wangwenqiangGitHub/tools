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
