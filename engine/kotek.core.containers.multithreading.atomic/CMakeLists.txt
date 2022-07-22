cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.multithreading.atomic VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_atomic.h"
	"include/kotek_core_containers_multithreading_atomic.h"
	"src/main_core_containers_multithreading_atomic_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)