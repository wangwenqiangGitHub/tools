## gdb基本调试
```shell
gdb -tui <程序的路径>
b <file_name><line>
run 重新启动程序
next # 越过这个函数
step # 进入函数之中
info
list
print
continue #恢复程序执行，直到遇到断点
finish fin # 当不小心step进入函数之中需要执行fin跳出

```

## gdb 打印string
```shell
p (char*)argc
# 打印完整字符串string
set print elements 0
```

## gdb 回车
- 重复上一条命令

## 打印stl变量名
-  stl-views-1.0.3.gdb
- 步骤
```sh
gdb app
source /path/stl-views-1.0.3.gdb
pvector var_vector
pmap var_map
```
##  gdb高级
```shell
# 反向执行
reverse-next
# 
```

<++>
