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

