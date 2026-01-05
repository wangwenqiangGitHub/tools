# sched\_setaffinity 将线程绑定到cpu核

> 通过sched\_setaffinity设置CPU亲和力的掩码，从而将该线程或者进程和指定的CPU绑定。 头文件 sched.h sched\_setaffinity(pid\_t pid,
> unsigned int cpusetsize, cpu\_set\_t* mask) 该函数设置进程为PID的这个进程，让它运行在mask所设定的CPU上
>
> - 如果pid的值为0，则表示指定的是当前进程，使当前进程运行在mask所设定的那些CPU上
> - 第二个参数cpusize是masksize是mask所指定的数的长度，
> - mask即用户通过CPU_SET接口

# 翼辉与T3线程测试

- 问题背景: 由于创建线程时未detach或者join导致虚拟地址内存泄露问题排查

```
# 翼辉
cat /proc/kernel/objects
object      total    used     max-used
event       10000    428      455
eventset    500      0        0
heap        52       1        1
msgqueue    2000     20       22
partition   50       7        7
rms         32       0        0
thread      1000     74       1000
threadvar   16       0        0
timer       50       1        1
dpma        2        0        0
threadpool  2        0        0
#t3 线程数达到上限
系统级限制：cat /proc/sys/kernel/threads-max
用户级限制：ulimit -u
查看方法：grep Threads /proc/<pid>/status
```

# 为什么 `free -m` 无法检测线程栈内存泄露问题

`free -m` 命令无法检测线程栈内存泄露的根本原因在于它**监控的是物理内存使用情况**，而线程栈泄露主要影响**虚拟地址空间**而非物理内存。让我们深入分析原因：

## 核心区别：虚拟内存 vs 物理内存

| 特性    | 虚拟内存 (Virtual Memory)      | 物理内存 (Physical Memory) |
| ----- | -------------------------- | ---------------------- |
| 监控命令  | `pmap`, `/proc/<pid>/maps` | `free`, `top`          |
| 泄露类型  | 线程栈泄露影响此区域                 | 堆内存泄露影响此区域             |
| 分配机制  | 立即分配虚拟地址范围                 | 按需分配物理页面               |
| 大小限制  | 进程地址空间大小 (32位:3GB,64位:巨大)  | 实际RAM + swap空间         |
| 线程栈影响 | 每个线程消耗固定虚拟地址空间(默认8MB)      | 仅消耗实际使用的物理页面           |

## 为什么 `free -m` 无法显示问题

### 1. 按需分配物理内存 (Demand Paging)

```mermaid
graph LR
    A[创建线程] --> B[分配8MB虚拟地址空间]
    B --> C{线程使用栈内存}
    C -->|少量使用| D[分配少量物理页]
    C -->|大量使用| E[分配更多物理页]
```

- 操作系统只为实际使用的栈内存分配物理页
- 即使分配了8MB虚拟空间，物理内存可能只占用几KB

### 2. 内存统计差异

```bash
$ free -m
              total        used        free      shared  buff/cache   available
Mem:           15932        1523       11976         892        2432       13180
Swap:           2047           0        2047
```

- `used` 列包含所有进程实际使用的物理内存
- 不区分不同内存类型（堆、栈、共享内存等）
- 无法显示单个进程的虚拟地址空间使用

### 3. 共享内存的影响

- `buff/cache` 包含文件系统缓存
- `shared` 包含实际共享内存
- 这些因素会掩盖线程栈的微小物理内存占用

## 实际问题演示

假设程序创建了100个未回收的线程：

```c
// leaky_threads.c
#include <pthread.h>
#include <unistd.h>

void* thread_func(void* arg) {
    sleep(10); // 线程存活一段时间
    return NULL;
}

int main() {
    for(int i = 0; i < 100; i++) {
        pthread_t tid;
        pthread_create(&tid, NULL, thread_func, NULL);
        // 既没有join也没有detach!
    }
    sleep(3600); // 保持进程运行
    return 0;
}
```

### 监控结果对比

**`free -m` 输出:**

```
              total        used        free      shared  buff/cache   available
Mem:           15932        1528       11971         892        2432       13175
Swap:           2047           0        2047
```

(几乎看不到变化)

**`pmap` 输出:**

```
$ pmap -x $(pidof leaky_threads)
Address           Kbytes     RSS   Dirty Mode  Mapping
...
00007f3d80000000    8192       0       0 rw---   [ anon ] <-- 线程栈1
00007f3d80800000    8192       0       0 rw---   [ anon ] <-- 线程栈2
... (重复100次) ...
total kB         1032896    1584    1180
```

(虚拟内存增加约800MB，但RSS仅增加少量)

## 正确检测线程栈泄露的工具

### 1. 进程级虚拟内存监控

```bash
# 监控虚拟内存增长
watch -n 1 "ps -p $(pidof your_program) -o pid,vsz,rss,cmd"

# 示例输出:
  PID      VSZ   RSS CMD
 8812  1032896 1584 ./leaky_threads
```

### 2. 详细内存映射分析

```bash
# 统计匿名映射数量
watch -n 1 "grep -c 'rw.*anon' /proc/$(pidof your_program)/maps"

# 按类型统计虚拟内存
watch -n 1 "pmap -x $(pidof your_program) | tail -1"
```

### 3. 专用监控脚本

```bash
#!/bin/bash
# 线程泄露检测脚本

PID=$1
INTERVAL=${2:-1}

echo "Monitoring thread leak for PID: $PID"
echo "Press Ctrl+C to exit"
echo "------------------------------------"

while true; do
    # 获取虚拟内存和物理内存
    VSZ=$(ps -p $PID -o vsz=)
    RSS=$(ps -p $PID -o rss=)
    
    # 计算线程栈映射
    ANON_MAPS=$(grep -c 'rw-p.*anon' /proc/$PID/maps)
    STACK_MAPS=$(grep -c 'rw-p.*stack' /proc/$PID/maps)
    TOTAL_MAPS=$((ANON_MAPS + STACK_MAPS))
    
    # 估算泄露内存 (MB)
    LEAKED_VM=$((TOTAL_MAPS * 8))
    
    # 计算物理内存使用率
    if [ $VSZ -ne 0 ]; then
        PHYS_USAGE=$((RSS * 100 / VSZ))
    else
        PHYS_USAGE=0
    fi
    
    echo -n "[$(date +%T)] "
    echo -n "Virtual: $(($VSZ/1024))MB "
    echo -n "Physical: $(($RSS/1024))MB "
    echo -n "Stacks: $TOTAL_MAPS "
    echo -n "Leaked≈: ${LEAKED_VM}MB "
    echo -n "PhysUsage: ${PHYS_USAGE}% "
    
    # 告警逻辑
    if [ $TOTAL_MAPS -gt 100 ] && [ $PHYS_USAGE -lt 5 ]; then
        echo -e "\e[31m<< THREAD LEAK DETECTED!\e[0m"
    else
        echo
    fi
    
    sleep $INTERVAL
done
```

## 为什么物理内存使用率低是泄露指标

在线程栈泄露场景中，典型的模式是：

```
高虚拟内存 + 低物理内存使用率 = 线程泄露
```

计算示例：

```
100个线程 * 8MB = 800MB 虚拟内存
实际使用的物理内存可能只有：
  100线程 * 4KB (初始页) = 400KB
物理内存使用率 = 400KB / 800MB ≈ 0.05%
```

## 其他隐藏风险的检测

### 1. 内存碎片检测

```bash
# 计算地址空间碎片
awk '
BEGIN { last=0; total_gap=0; count=0 }
/rw-p.*anon/ {
    split($1, a, "-");
    start = strtonum("0x" a[1]);
    end = strtonum("0x" a[2]);
    if (last != 0) {
        gap = start - last;
        total_gap += gap;
        count++;
    }
    last = end;
}
END { 
    if (count > 0) 
        print "Fragmentation:", total_gap/1024/1024, "MB in", count, "gaps" 
}' /proc/$PID/maps
```

### 2. 线程数监控

```bash
# 监控线程数增长
watch -n 1 "grep Threads /proc/$(pidof your_program)/status"

# 系统级线程监控
watch -n 1 "cat /proc/sys/kernel/threads-max; echo; ps -eLf | wc -l"
```

## 真实案例分析

某生产服务器运行数周后崩溃：

```
$ free -m
              total        used        free      shared  buff/cache   available
Mem:           64236       15238       12560        8920       36438       39872  # 看似正常

$ pmap -x 12345 | tail -1
total kB        65498232   1523800   1453200  # 65GB虚拟内存!

$ grep -c 'rw-p.*anon' /proc/12345/maps
8190  # 约65,520MB虚拟内存泄露
```

结论：虽然物理内存使用正常，但虚拟地址空间已耗尽（32位进程上限3GB）。

## 解决方案

1. **修复代码**：
   ```c
   // 正确回收线程
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
   pthread_create(&tid, NULL, worker, NULL);
   pthread_detach(tid); // 或使用 pthread_join
   ```

2. **使用线程池**：
   ```c
   #define THREAD_POOL_SIZE 100
   pthread_t pool[THREAD_POOL_SIZE];

   for (int i = 0; i < THREAD_POOL_SIZE; i++) {
       pthread_create(&pool[i], NULL, worker, NULL);
   }
   ```

3. **设置栈大小**：
   ```c
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_attr_setstacksize(&attr, 128 * 1024); // 128KB
   pthread_create(&tid, &attr, worker, NULL);
   pthread_attr_destroy(&attr);
   ```

4. **系统级监控**：
   ```bash
   # 定期检查高虚拟内存进程
   ps -eo pid,vsz,rss,comm --sort=-vsz | head -20

   # 设置报警阈值
   alert_vsz_mb=1000000 # 1TB虚拟内存报警
   ```

总结：`free -m` 适用于监控物理内存使用，而要检测线程栈泄露这类虚拟地址空间问题，需要使用 `pmap`、`/proc/<pid>/maps` 等工具监控进程级虚拟内存分配。

# 虚拟内存耗尽可以通过dmesg 能看到 kill 进程信息

```
1. OOM Killer（内存不足杀手）
bash
$ dmesg | grep -i kill
[ 1234.567890] Out of memory: Kill process 12345 (chrome) score 789 or sacrifice child
[ 1234.567891] Killed process 12345 (chrome) total-vm:1234567kB, anon-rss:123456kB, file-rss:7890kB, shmem-rss:0kB
2. 段错误（Segmentation Fault）
bash
$ dmesg | grep -i segfault
[ 1234.567892] myapp[12345]: segfault at 123456 ip 00007f8e9a8b1234 sp 00007ffd12345678 error 4 in myapp[7f8e9a8a1000+1000]
3. 其他信号导致的进程终止
bash
$ dmesg | grep -i "traps"
[ 1234.567893] traps: myapp[12345] general protection fault ip:12345678 sp:12345678 error:0
```
