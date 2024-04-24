cmake_minimum_required(VERSION 3.0)
project(eventc)

set(CMAKE_CXX_FLAGS "-std=c89 -Wall -pthread ")
set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	)
file(GLOB SRC
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	)

add_executable(${PROJECT_NAME} ${SRC})
