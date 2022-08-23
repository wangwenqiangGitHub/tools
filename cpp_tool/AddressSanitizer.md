# 内存泄漏检测工具
- 效率比valgrind高，是一个快速的内存错误检测工具，非常快，只拖慢程序两倍左右。
AddressSanitizer主要包括两部分：插桩(Instrumentation)和动态运行库(Run-time library)。插桩主要是针对在llvm编译器级别对访问内存的操作(store，load，alloca等)，将它们进行处理。动态运行库主要提供一些运行时的复杂的功能(比如poison/unpoison shadow memory)以及将malloc,free等系统调用函数hook住。该算法的思路是：如果想防住Buffer Overflow漏洞，只需要在每块内存区域右端（或两端，能防overflow和underflow）加一块区域（RedZone），使RedZone的区域的影子内存（Shadow Memory)设置为不可写即可

> 用-fsanitize=address选项编译和链接你的程序;
> 用-fno-omit-frame-pointer编译，以在错误消息中添加更好的堆栈跟踪。
> 增加-O1以获得更好的性能。
- camek中的设置
```
if(ENABLE_ASAN)
  list(APPEND COMPILE_OPTIONS_DEFAULT
    "-fsanitize=address;-fno-omit-frame-pointer")
  message(STATUS "已启用 Address Sanitize")
endif()
```
