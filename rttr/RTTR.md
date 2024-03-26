# 库测试步骤

- wget https://github.com/rttrorg/rttr/releases/download/v0.9.6/rttr-0.9.6-src.tar.gz
- add cxx flag in CMakeLists.txt
  `set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pthread -Wno-error=class-memaccess -Wno-error=pessimizing-move -Wno-error=init-list-lifetime")`

- export 环境变量`/mnt/c/sf_ws/rttr/rttr-0.9.6/build/lib`
