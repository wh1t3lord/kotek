cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.multithreading.semaphore VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_semaphore.h"
	"include/kotek_core_containers_multithreading_semaphore.h"
	"src/main_core_containers_multithreading_semaphore_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/multithreading")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)