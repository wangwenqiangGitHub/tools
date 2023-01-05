# 当访问某个端口失败后,重启windows网络
```
net stop winnat
net start winnat
```

# windows文件夹区分文件命名大小写
```
#终端管理员权限
#设置文件名字大小写
fsutil.exe file setCaseSensitiveInfo <path> enable
# 关闭
fsutil.exe file setCaseSensitiveInfo <path> disable
```
