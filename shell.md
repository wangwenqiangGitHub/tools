## 库中查找函数名字
```shell
find <file_path> -name "*.h" | xargs grep "find_word"
```

## Makefile脚本
```Makefile
.PHONY: xx

"":
	if [ -d "build" ]; then \
		cd build && make -j4; \
	else \
		mkdir build; \
		cd build && cmake -DCMAKE_CXX_COMPILER:FILEPATH=$(shell which arm-linux-gnueabi-g++) -DCMAKE_C_COMPILER:FILEPATH=$(shell which arm-linux-gnueabi-gcc) ..; \
	fi

%:
	if [ -d "build" ]; then \
		cd build && make $@; \
	else \
		mkdir build; \
		cd build && cmake -DCMAKE_CXX_COMPILER:FILEPATH=$(shell which arm-linux-gnueabi-g++) -DCMAKE_C_COMPILER:FILEPATH=$(shell which arm-linux-gnueabi-gcc) $@ ..; \
	fi
```
## 生成库文件，提取库，头文件
```shell
# 把头文件拷贝到 /usr/include/xxx  xxx.so库拷贝到 /usr/lib
if [ ! -d /usr/include/xxx]; then
    mkdir /usr/include/xxx
fi

for header in `ls *.h`
do
    cp $header /usr/include/xxx
done

cp `pwd`/lib/xxx.so /usr/lib

ldconfig
```
## head命令
```shell
head -n 5 test.txt #打印前5行
head -c 5 test.txt #打印第一个5字节
```


<++>
