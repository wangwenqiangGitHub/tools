- 系统调用中的时间问题
  - 系统调用中需要指定`CLOCK_MONOTONIC`
    还是`CLOCK_REALTIME`,嵌入式设备需要对时操作，为了防止发生系统跳变，可以采用`CLOCK_MONOTONIC`,而`CLOCK_REALTIME`是wall
    time;monotonic time字面意思是单调时间，实际上它指的是系统启动以后流逝的时间，这是这个变量jiffies来记录的。系统每次启动时jiffies初始化为0，每来一个timer
    interrupt, jiffies加1，也就是它代表系统启动后流逝的tick数. jiffies一定是单调递增的, 因为时间不可逆。`wait_time`
    字面意思是挂钟时间,实际上就是指的是现实时间。举例:用户去任意修改系统时间，这个被修改的时间应该就是wall time, 即xtime,
    它甚至可以被写入RTC而永久保存。一些应用软件用到的就是`wait_time`,一启动软件后，提示试用期已过。但是只要把系统时间调整一下提前一年,
    再启动就不会再有提示了，这个很可能就应为启动时，gettimeofday用的时wall time, 然后判断是否过期，只要将wall time修改一下，就可以使用
- [参考](https://linux.die.net/man/3/clock_gettime)
  - man `clock_gettime` 然后查找`CLOCK_MONOTONIC`
