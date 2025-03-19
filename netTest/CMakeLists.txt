# set(CMAKE_C_COMPILER /home/kingwq/toolchains/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc)
# set(CMAKE_CXX_COMPILER /home/kingwq/toolchains/gcc-linaro-7.5.0-2019.12-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++)
# set(CMAKE_C_COMPILER arm-buildroot-linux-gnueabi-gcc)
# set(CMAKE_CXX_COMPILER arm-buildroot-linux-gnueabi-g++)


cmake_minimum_required(VERSION 3.0)
project(netTest)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pthread ")
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# include_directories(
# 	${CMAKE_CURRENT_SOURCE_DIR}
# 	${CMAKE_CURRENT_SOURCE_DIR}/../
# 	)


add_executable(tcp_server tcp_server.cpp)
add_executable(tcp_client tcp_client.cpp)
add_executable(udp_server udp_server.cpp)
add_executable(udp_client udp_client.cpp)
