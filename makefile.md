# makefile中的变量

- 系统变量
  - $*不包括扩展名的目标文件
  - $+所有的依赖文件
  - $<规则中的第一个条件
  - $?所有时间戳比目标文件晚的依赖的文件，以空格分离
  - $@目标文件的完整名称
  - $^所有不重复的目标文件，以空格区分
  - $%如果目标是归档成员，则该变量表示目标的归档成员名称

- 系统常量(可以通过make -p查看)
  - AS汇编程序的名称，默认为as
  - CC c编译器名称,默认为cc
  - CPP c预处理名称 cc -E
  - CXX c++编译器名称 默认为g++
  - RM 文件删除程序别名

- 自定义定量
  - 定义: 变量名=变量值
  - 使用: ${变量名}/${变量名}

# 参考书

- [跟我一起学Makefile](https://seisman.github.io/how-to-write-makefile/index.html#)

# 条件判断 相等

- ifeq() endif
- strip是去掉空字符语句

# PHONY伪目标

- 伪目标是这样一个目标:它不代表有一个真正的文件，在执行make时可以指定这个目标来执行所在规则定义的命令,有时也可以将一个伪目标称为标签
- 如果我们有一个clean文件夹,并且makefile中有一条命令

```makefile
clean:
    rm *.o temp
```

我们希望输入"make clean"后，执行rm这条命令,但是当目录中存在一个和指定目标重名的文件时，这时输入clean文件，结果就不执行rm命令了，所以需要一个PHONY来指定一个伪目标。

- 这种做法的好处有，提高了make的执行效率，因此将clean定义成伪目标后，make的执行程序不会试图寻找clean的隐含规则。PHONY可以确保源文件(\*\.c
  \*\.h)修改后，对应的目标文件会被重构

- local-make学习
  - 基础:定义了当前模块的相对路径;
  ```
  ```

# 定义一个变量LOCAL_PATH, 它的值是通过调用local-dir函数得到的. local-dir函数是Makefile中中的内置函数,用于获取当前Makefile所在的目录路径.

LOCAL_PATH:=$(call local-dir):

```
- 清空环境变量
```

include$(CLEAR_VARS)

```
- 编译所生成的目标文件格式
- 项目中引用系统的库:
```

# 将系统库文件名添加到Android.mk

    LOCAL_SHARED_LIBRARIES += libxxxx:

```
- 引入第三方库文件:
```

LOCAL_LDFLAGS:=-L/Path -lxxx

```
- sysroot设置后,就去sysroot目录搜索pthread, rypto, ssl, m,tinyalsa,stdc++库，而不是去默认的/usr/lib,/usr/lib,
LD\_LIBRARY\_PATH
- include $(LOCAL\_PATH)/sub.mk
```

作用是使用include指令将LOCAL_PATH变量指向的目录下的sub.mk文件包含进来。sub.Mk文件中可能包含了一些他的变量和规则

```
- MFILES\_DIR是一个变量，用于指定包含其他Makefile文件中的目录路径, 通常在Makefile中定义这个变量:export MFILES\_DIR:=$(TOP\_DIR)/build/mfiles


- include $(EXECUTABLE\_MFILE):这行代码使用include指令将EXECUTABLE\_MFILE文件包含进来，EXECUTABLE\_MFILE是一个预设定变量.

- include$(CLEAR\_MFILE)这个代码使用了include指令将CLEAR\_MFILE文件包含进来.用于清除Makefile中定义的所有变量和规则
```

- TOP\_ALL\_NECESSARY\_MODULES
  TOP\_ALL\_NECESSARY\_MODULES是一个变量，它通常用于指定一组必需的模块。这些模块是构建整个项目所必需的，因此在编译过程中需要包含它们。

# Makefile中的 目标(target)和规则(rule)是构建软件项目时非常重要的概念

- 一个简单的规则通常包括以下几个部分:
  - 目标:需要生成的文件或者动作的名称
  - 依赖关系: 生成目标所需要的文件或者其他目标
  - 命令: 生成目标的具体命令

```
main.o: main.c utils.h
    gcc -c main.c -o main.o

    utils.o: utils.c utils.h
        gcc -c utils.c -o utils.o
在这个例子中，main.o和utils.o是目标，main.c、utils.c和utils.h是依赖关系，gcc -c main.c -o main.o和gcc -c utils.c -o utils.o是命令。
```

# Makefile 基础语法

- 变量赋值:采用`=`进行赋值时, 变量的值会在整个Makfile中都可见，这意味着无论变量在何处被定义，其值在整个Makefile中都会生效.
- 变量赋值:采用`:=`,变量的值只有在当前被赋值的那一行以及其后续引用中有效。这种方式是简单赋值，它可以避免一些意外的副作用，更符合变量作用域的概念
- `$(filter false,$(SD_BUILD_SOC))`是一个条件判断语句，用于检查`SD_BUILD_SOC`中是否包含字符串flase
- ifeq用于判断两个字符串是否相等
- `$(if $(genpac_emmc_target),$(call build-emmc-pac-cmd),$(info No need to generate global pac!!))`表示如果变量`genpac_emmc_target`的值存在(非空)，那么执行`build-emmc-pac-cmd`函数;否则输出消息"No
  need to ..."
- makefile中的call是一个函数，用于调用自定义的函数。语法`$(call function_name, parameters).`
- 函数:`sd_cp = $(sd_cp_cmd) $(1) $(2)`
  表示这个是一个参数化的宏，它会将`sd_cp_cmd`和两个参数连接在一起当调用这个函数时，实际上会展开为:`$(sd_cp_cmd) param1 param2`
- `test $$? -eq 0 || exit 1`表示这是个条件语句,如果是执行的命令的退出状态是0(即成功),那什么都不做，否则退出

# 应用程序万能Makefile

```
####################################################
# Generic makefile - 万能Makefile
# for compiling and linking C++ projects on Linux
# Author: George Foot  Modified:Jackie Lee
####################################################
### Customising
#
# Adjust the following if necessary; EXECUTABLE is the target
# executable's filename, and LIBS is a list of libraries to link in
# (e.g. alleg, stdcx, iostr, etc). You can override these on make's
# command line of course, if you prefer to do it that way.
#
#
EXECUTABLE := test-makefile# 可执行文件名
LIBDIR:= # C:/sfml2.5/lib              # 静态库目录
LIBS := # sfml-audio sfml-graphics  sfml-main sfml-network sfml-system  sfml-window  # 静态库文件
INCLUDES:=. #C:/sfml2.5/include          # 头文件目
SRCDIR:=  #./src         # 除了当前目录外，其他的源代码文件目录
#
# # Now alter any implicit rules' variables if you like, e.g.:

CC:=gcc
CFLAGS := -g -Wall  #-std=c++14 -O3
CPPFLAGS := $(CFLAGS)
CPPFLAGS += $(addprefix -I,$(INCLUDES))
#CPPFLAGS += -MMD
#
# # The next bit checks to see whether rm is in your djgpp bin
# # directory; if not it uses del instead, but this can cause (harmless)
# # `File not found' error messages. If you are not using DOS at all,
# # set the variable to something which will unquestioningly remove
# # files.
#
RM-F := rm -rf#del

# # You shouldn't need to change anything below this point.
#
SRCS := $(wildcard *.cpp) $(wildcard $(addsuffix /*.cpp, $(SRCDIR)))
SRCS := $(wildcard *.c) $(wildcard $(addsuffix /*.c, $(SRCDIR)))
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
OBJS := $(patsubst %.c,%.o,$(SRCS))
DEPS := $(patsubst %.o,%.d,$(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)),$(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d,%.cpp,$(MISSING_DEPS)))

.PHONY : all deps objs clean veryclean rebuild info

all: $(EXECUTABLE)

deps : $(DEPS)

objs : $(OBJS)

clean :
        @$(RM-F) *.o
        @$(RM-F) *.d

veryclean: clean
        @$(RM-F) $(EXECUTABLE)

rebuild: veryclean all
ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS) :
        @$(RM-F) $(patsubst %.d,%.o,$@)
endif
-include $(DEPS)

$(EXECUTABLE) : $(OBJS)
        $(CC) -o $(EXECUTABLE) $(OBJS) $(addprefix -L,$(LIBDIR)) $(addprefix -l,$(LIBS))


info:
        @echo "srcs:" $(SRCS)
        @echo "objs" $(OBJS)
        @echo "deps" $(DEPS)
        @echo "missing_deps:" $(MISSING_DEPS)
        @echo "missing_deps_sources:" $(MISSING_DEPS_SOURCES)
```
