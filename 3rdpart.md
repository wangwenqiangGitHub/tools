# tinyxml

- 编译成静态库
  - 1 进入目录tinyxml，用vim命令打开Makefile文件
  - 2 将其中一行 OUTPUT := xmltest 修改为 OUTPUT := libtinyxml.a 表示编译出的静态库文件名字为 libtinyxml.a
  - 3 将其中一行 SRCS :=tinyxml.cpp tinyxml-parser.cpp xmltest.cpp tinyxmlerror.cpp tinystr.cpp
    中的xmltest.cpp删掉 因为不需要编译该测试文件
  - 4 将其中一行 ${LD} -o $@ ${LDFLAGS} ${OBJS} ${LIBS} ${EXTRA_LIBS} 修改为 ${AR} $@ ${LDFLAGS} ${OBJS}
    ${LIBS} ${EXTRA_LIBS} 表示链接成静态库
  - 5 将其中一行 xmltest.o：tinyxml.h tinystr.h 删除，因为不需要编译测试文件
  - 6 保存Makefile文件
  - 7 回退到上一层目录即目录tinyxml中，执行make命令，即可在该目录得到编译出来的静态库文件libtinyxml.a

- 编译成动态库
  - 1 进入目录tinyxml，用vim命令打开Makefile文件
  - 2 在其中一行 DEBUG_CFLAGS := -Wall -Wno-format -g -DDEBUG -fPIC 的末尾添加上 -fPIC 表示编译与位置无关的代码，PIC的意思即
    Position Independent Code，
  - 3 在其中一行 RELEASE_CFLAGS := -Wall -Wno-unknown-pragmas -Wno-format -O3 的末尾添加上 -fPIC 原因同上
  - 4 将其中一行 OUTPUT := xmltest 修改为 OUTPUT := libtinyxml.so 表示编译出的动态库文件名字为 libtinyxml.so
  - 5 将其中一行 SRCS :=tinyxml.cpp tinyxml-parser.cpp xmltest.cpp tinyxmlerror.cpp tinystr.cpp
    中的xmltest.cpp删掉 因为不需要编译该测试文件
  - 6 将其中一行 ${LD} -o $@ ${LDFLAGS} ${OBJS} ${LIBS} ${EXTRA_LIBS} 修改为 ${LD} -shared -o $@ ${LDFLAGS}
    ${OBJS} ${LIBS} ${EXTRA_LIBS} 表示链接成动态库
  - 7 将其中一行 xmltest.o：tinyxml.h tinystr.h 删除，因为不需要编译测试文件
  - 8 保存Makefile文件
  - 9 回退到上一层目录即目录tinyxml中，执行make命令，即可在该目录得到编译出来的动态库文件libtinyxml.so
