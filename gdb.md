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

- stl-views-1.0.3.gdb
- 步骤

```sh
gdb app
source /path/stl-views-1.0.3.gdb
pvector var_vector
pmap var_map
```

## gdb高级

```shell
# 反向执行
reverse-next
#
```

## 设置代码显示

```shell
set substitute-path from to
set substitute-path /mnt/d/code/test /var/log/test
next 
list
#这些命令就可以有代码了
```

## 程序挂掉bt查看调用栈

```shell
frame <n>
#切换当前栈，无参数时会打印信息当前的函数名，函数的参数值，函数所在的文件，行号，函数执行到的语句
f <n>#简写
```
