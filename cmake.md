# cmake版本升级

```shell
# 不要使用sudo apt automove。会清除ros的依赖
sudo ln -s ~/cmake-3.23.0-rc4-linux-x86_64/bin/cmake /usr/bin/cmake
```

# srs CmakeLists.txx文件剖析

- 执行系统命令

```
execute_process(
		        COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}/../../ && pwd"
				        OUTPUT_VARIABLE SRS_DIR
		)


EXEC_PROGRAM("cd ${SRS_DIR} && ./configure --jobs=${JOBS}")
# EXEC_PROGRAM是执行系统命令
```

- 调试cmake

```cmake
#退出编译
message(FATAL_ERROR "stop exit")
#打印变量
SET(USER_KEY, "Hello World")
MESSAGE( STATUS "this var key = ${USER_KEY}.")
```

- ProcessorCount是CMake的内部函数;获取机器的cpu个数，赋值给JOBS

```
# Start to configure SRS with jobs of number of CPUs.
include(ProcessorCount)
ProcessorCount(JOBS)
```

- 宏

```
ADD_DEFINITIONS("-g -O0")
```

- Makefile makefile的规则是第一个不以.开头的targe就是默认的target.

- librtsp库

```
git clone --depth=1 https://gitee.com/micrors/sico/librtsp

make distclean
```

# 静态编译

```
set(CMAKE_EXE_LINKER_FLAGS "-static")
```

| 标准库链接方式 | 选项                                | 优点                           | 缺点                      |
| ------- | --------------------------------- | ---------------------------- | ----------------------- |
| 全静态     | -static -pthread -lrt -ldl        | 不会发生在应用程序在不同Linux版本上的标准库兼容问题 | 生成的文件比较大，应用程序受限，不能调用动态库 |
| 全动态     | -pthread -lrt -ldl                | 文件小                          | 不兼容问题                   |
| 全静态     | -static-libgcc -pthread -lrt -ldl | 灵活性大                         | 比较难识别哪些库容易发生不兼容问题       |

# target\_include\_directories的PUBLIC，PRIVATE, INTERFACE

```
target_include_directories里面的关键字控制头文件目录传递。
target_link_libraries里的关键字控制头文件目录以及链接库传递。

PUBLIC:对内对外都公开，可将头文件目录以及链接库传递给连接者。
PRIVATE:对内公开，对外不公开，不可传递头文件目录以及链接库。
INTERFACE:对外公开，对内不公开，可传递头文件目录以及链接库，但内部不可使用头文件及连接库，只能接口传递
```

# 编译选项

- -fPIC是作用与编译阶段，告诉编译器产生与位置无关代码(position Independent Code)则产生的代码中没有绝对地址，全部使用相对地址

# protobuf编译选项

```cmake
add_custom_command(OUTPUT rpc.pb.cc rpc.pb.h
        COMMAND protoc
        ARGS --cpp_out . ${CMAKE_CURRENT_SOURCE_DIR}/rpc.proto -I${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS rpc.proto
        VERBATIM )

set_source_files_properties(rpc.pb.cc PROPERTIES COMPILE_FLAGS "-Wno-conversion")
```

# 编译文件输出路径

```
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/static)
```

# cmake中的`target_link_libraries`中的PUBLIC和PRIVATE关键字作用:

- PUBLIC:关键字指定的库将会被链接到目标上，并且这个链接对目标的依赖项也是公开的.这意味着，如果有其他目标链接到当前目标，那么这个库也会被连接到这些目标上。
- PRIVATE: 关键字是指定的库会被链接到目标上，但是这个链接对于目标的依赖项是私有的。这意味着，如果有其他目标链接到当前目标，这个库不会被传递到这些目标上
- Makefiel中有个LDLIBS的宏

```Makefile
LDLIBS = -lmylib
```

- 例子

```cmake
假设我们有一个名为myapp的可执行文件目标，它依赖于一个名为mylib的库目标，并且mylib又依赖于lib1和lib2这两个库。
add_library(mylib ...)
target_link_libraries(mylib PRIVATE lib1)
target_link_libraries(mylib PUBLIC lib2)
add_executable(myapp ...)
target_link_libraries(myapp PRIVATE mylib)

当构建myapp时，它会链接mylib和lib2;但不会链接lib1.这种机制可以帮助我们控制依赖关系的传递。确保每个目标都能正确的链接到所需要的库中。
```
