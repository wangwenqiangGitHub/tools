## gdb基本调试
```shell
gdb -tui <程序的路径>
b <file_name><line>
run
next
step
info
list
print
```

<++>
## gdb 打印string
```shell
p (char*)argc
# 打印完整字符串string
set print elements 0
```

## gdb 回车
- 重复上一条命令


