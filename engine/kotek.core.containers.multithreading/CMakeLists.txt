cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.multithreading VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_containers_multithreading.h"
	"src/main_core_containers_multithreading_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.atomic)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.mutex)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.shared_mutex)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.semaphore)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.thread)