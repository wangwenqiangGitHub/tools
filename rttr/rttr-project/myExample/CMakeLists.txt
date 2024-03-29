# set(CMAKE_C_COMPILER /mnt/d/code/r14_ltev2x_app/build/toolchain/gcc-4.9-2016.02-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-gcc)
# set(CMAKE_CXX_COMPILER /mnt/d/code/r14_ltev2x_app/build/toolchain/gcc-4.9-2016.02-x86_64_arm-linux-gnueabi/bin/arm-linux-gnueabi-g++)
cmake_minimum_required(VERSION 3.0)
project(myExample)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -pthread ")
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	# ${CMAKE_CURRENT_SOURCE_DIR}/../
	)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../build
	${CMAKE_CURRENT_SOURCE_DIR}/../build/OUT/lib
	)
file(GLOB SRC
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries("${PROJECT_NAME}" rttr_core)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../build/OUT/include)
