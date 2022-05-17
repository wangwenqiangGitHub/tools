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


