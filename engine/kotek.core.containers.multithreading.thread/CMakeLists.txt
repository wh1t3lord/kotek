cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.multithreading.thread VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_thread.h"
	"include/kotek_core_containers_multithreading_thread.h"
	"src/main_core_containers_multithreading_thread_dll.cpp")