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

#数组 buf打印数组中的内容
x/256 buf

x /32c buf
x /32s buf
```

# core文件

```
#正确生成core文件, 可选记录pid echo <pid> /proc/sys/kernel/core_uses_pid
ulimit -c unlimited
echo /mnt/mmc/core-%e-%p-%t> /proc/sys/kernel/core_pattern
# gdb attach pid生成core文件，新版本的gdb工具可以使用 generate-core-file命令, 或者 kill -3
# 调试core文件
gdb <executable> <coredumpfile>
bt
```

# gdb打印命令 查看命令

```
(gdb) info args
this = 0x5555555c9390
conn = std::shared_ptr<sfl::net::TcpConnection> (use count 2, weak count 1) = {get() = 0x5555555ca040}
buf = 0x5555555ca098
(gdb) info locals
head = 0x5555555ca198
event = std::shared_ptr<Event> (use count 1442455055, weak count 1223002439) = {get() = 0x7fffffffd1d0}
(gdb) x /8xw 0x5555555ca198
0x5555555ca198: 0x00000021      0x00000000      0x00000000      0x00000000
0x5555555ca1a8: 0x00000000      0x00000000      0x00000000      0x00000000
```

# 压缩core文件

- 写在sh.snippets中

# 本地gdb 调试core文件

```
# 打包设备根文件系统
arm-linux-gdb  program core
set sysroot

# 新方式
# 使用ldd递归查找依赖（示例）
ldd /path/app | awk '{print $3}' | xargs -I{} cp --parents {} ./env-rootfs
# 使用交叉编译链的GDB
arm-none-eabi-gdb -q ./app.debug
(gdb) set sysroot ./env-rootfs  # 指定库搜索路径
(gdb) core-file ./core.1234     # 加载设备生成的core文件
```

# gdb watch

```
https://blog.csdn.net/tianyexing2008/article/details/129971711
当watch观察的是一个局部范围内的变量时, watch必须要和断电一起使用
```

# info registers

```
(gdb) info registers
r0             0x0      0
r1             0x1      1
r2             0x2      2
r3             0x3      3
r4             0x4      4
r5             0x5      5
r6             0x6      6
r7             0x7      7
r8             0x8      8
r9             0x9      9
r10            0xa      10
r11            0xb      11
r12            0xc      12
sp             0xbefffc 0xbefffc
lr             0x1044   0x1044
pc             0x1040   0x1040
cpsr           0x60000010 1610612752
fpscr          0x0      0
```

- registers输出讲解
  - 通用寄存器 r0 - r12这些是通用寄存器，用于存储数据和地址。它们可以在程序的任何地方被访问和修改
  - 专用寄存器 sp(stack pointer):栈指针寄存器，指向当前栈顶的位置。栈用于管理函数调用和局部变量。lr (Link Register): 链接寄存器,
    存储函数调用返回的地址.当一个函数被调用时,返回地址会被保存到lr中, 以便函数执行完毕后返回调用点. pc(Program Counter):程序计数器(也称为指令指针)
    当存储当前执行指定的地址。pc的值会随着每一条指令的执行而增加。
  - 状态寄存器: cpsr(Current Program Status Register):当前程序状态寄存器,存储当前程序的状态, 包括条件标志(如零标志, 负标志等),
    模式位(如用户模式,系统模式等)和中段状态. fpscr(Floating Point Status and Control
    Register):浮点状态和控制寄存器,存储浮点运算的状态和控制信息

- 根据寄存器排查问题的步骤 1.查看程序计数器(pc):
  - pc 寄存器指向当前正在执行的指令。如果程序崩溃或卡住，可以查看 pc 的值，定位到具体的代码位置。 2.查看栈指针 (sp):
  - sp 寄存器指向当前栈顶的位置。通过查看 sp 的值，可以了解当前栈的状态，检查是否发生了栈溢出等问题。 3.查看链接寄存器 (lr):
  - lr 寄存器存储函数调用返回的地址。如果函数调用出现问题，可以查看 lr 的值，确定调用链。 4.查看通用寄存器 (r0-r12):
  - 通用寄存器用于存储函数参数和返回值。在调试时，可以查看这些寄存器的值，了解函数调用过程中传递的参数和返回值。 5.查看状态寄存器 (cpsr):
  - cpsr 寄存器包含条件标志和模式位等信息。通过查看 cpsr 的值，可以了解程序当前的状态，检查是否发生了中断或模式切换。 6.查看浮点寄存器 (fpscr):
  - 如果程序涉及浮点运算，可以查看 fpscr 寄存器的值，了解浮点运算的状态和控制信息，检查是否发生了浮点异常等问题。

- 栈溢出问题排查

```
(gdb) info registers
r0             0x0      0
r1             0x1      1
r2             0x2      2
...
sp             0xbefffc 0xbefffc
lr             0x1044   0x1044
pc             0x1040   0x1040
cpsr           0x60000010 1610612752
...

cat /proc/$(pidof your_program)/maps | grep stack
befc0000-bf000000 rw-p 00000000 00:00 0          [stack]
如果栈范围是 0xbefc0000 到 0xbf000000，而 sp 的值是 0xbefffc，则说明栈指针已经接近栈的末尾，很可能发生了栈溢出。
```

# 分析core文件

```
gdb ./program core-file
bt full              #查看完整调用栈
info registers       #显示寄存器状态
x/10i &pc            #查看崩溃点附近汇编指令
printf variable_name #查看变量值
list #查看源码
(gdb) info threads             # 查看所有线程状态
(gdb) thread apply all bt     # 获取所有线程堆栈
(gdb) bt full                # 查看完整调用栈
(gdb) info registers         # 显示寄存器状态
(gdb) x/10i $pc              # 查看崩溃点附近汇编指令
(gdb) print variable_name    # 查看变量值
(gdb) list                   # 显示对应源代码
# 定位代码行
arm-linux-gnueabi-addr2line -e program 0x4005a8
# 反汇编
arm-linux-gnueabi-objdump -S -d program > disassembly.txt
# 查看符号表
arm-linux-gnueabi-nm -n program
常见崩溃类型分析
崩溃现象 排查方向	典型原因
Segmentation fault	空指针/野指针访问、内存越界	未初始化指针、数组越界
Bus error	内存对齐错误	强制类型转换不当
Floating point exception	浮点运算错误	除零操作、FPU配置错误
Stack overflow	栈空间不足	递归过深、大局部变量
Aborted (core dumped)	主动调用abort()	断言失败、手动触发
# 内存验证
cat /proc/$(pidof program)/maps  # 检查程序内存布局
```

# 分析函数

```
info locals
info args
# 查看结构体指针
info args 输出 structA = 0xb584b410
p *(structA*)0xb584b410
```

# gdb想让程序断点在执行100次后停住

```
gdb ./your_program
(gdb) break your_function   # 在your_function函数入口设置断点
(gdb) ignore 1 100          # 忽略前100次触发（断点编号1）
(gdb) run                   # 运行程序，当第101次调用your_function时暂停
```

# 查看程序中虚内存(vsz默认3G大小)和物理内存(rss)以及起了多少个线程

```
ps -T -A -o pid,ppid,pgid,vsz,rss,args
```

# gdb 反汇编排查strlen问题

```
打印断点break strlen if $r0 < 0x1000
让我们从lr地址开始，反汇编一些指令：gdb
(gdb) disassemble 0xb639ffec-20, 0xb639ffec+20
```
