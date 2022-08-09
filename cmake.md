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

- Makefile
makefile的规则是第一个不以.开头的targe就是默认的target.

