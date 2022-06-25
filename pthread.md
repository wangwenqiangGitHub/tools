# sched\_setaffinity 将线程绑定到cpu核
> 通过sched\_setaffinity设置CPU亲和力的掩码，从而将该线程或者进程和指定的CPU绑定。
> 头文件 sched.h
> sched\_setaffinity(pid\_t pid, unsigned int cpusetsize, cpu\_set\_t* mask)
> 该函数设置进程为PID的这个进程，让它运行在mask所设定的CPU上
> - 如果pid的值为0，则表示指定的是当前进程，使当前进程运行在mask所设定的那些CPU上
> - 第二个参数cpusize是masksize是mask所指定的数的长度，
> - mask即用户通过CPU_SET接口

# 
<++>
