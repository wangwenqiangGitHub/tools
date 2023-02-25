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
    - 基础:定义了当前模块的相对路径
    ```
    LOCAL_PATH:=$(call my-dir):
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

- sysroot设置后,就去sysroot目录搜索pthread, rypto, ssl, m,tinyalsa,stdc++库，而不是去默认的/usr/lib,/usr/lib, LD\_LIBRARY\_PATH
