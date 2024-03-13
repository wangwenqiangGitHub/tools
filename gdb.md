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

## 多线程调试

```
info t
t 1
return
bt
r
s
```

<++>

## 内存调试

```
# coredump问题
bt
# 查看内存内容
x 0x123456
# 查看一块连续地址 x/nfu 
x/8xw 0x123456
# 8要查看的内存单元,x是以十六进制格式显示。w表示以四字节为单位长度.

n:是正整数，表示需要显示的内存单元的个数，即从当前地址向后显示n个内存单元的内容，
一个内存单元的大小由第三个参数u定义。

f:表示addr指向的内存内容的输出格式，s对应输出字符串，此处需特别注意输出整型数据的格式：
    x 按十六进制格式显示变量.
    d 按十进制格式显示变量。
    u 按十进制格式显示无符号整型。
    o 按八进制格式显示变量。
    t 按二进制格式显示变量。
    a 按十六进制格式显示变量。
    c 按字符格式显示变量。
    f 按浮点数格式显示变量。

u:就是指以多少个字节作为一个内存单元-unit,默认为4。u还可以用被一些字符表示:
    如b=1 byte, h=2 bytes
```

# GDB打印结构体数组
- 通过bt命令
```
# 结构体StruBuf 成员 Buf即可以查看
p ((StruBuf*)0xaf8feb60)->Buf
p ((StruBuf*)0xaf9ccb60)->Len
$9 = 7
x /7xb 0xaf9ccb60
0xaf9ccb60:     0x06    0x81    0x02    0x00    0x21    0x20    0xca
7 个单元 x是16个进制 b是每个单元是一个字节(byte)
```
# core文件
```
#正确生成core文件, 可选记录pid echo <pid> /proc/sys/kernel/core_uses_pid
ulimit -c unlimited
echo /mnt/mmc/core-%e-%p-%t> /proc/sys/kernel/core_pattern
```
