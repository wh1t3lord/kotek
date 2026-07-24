cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.multithreading.mutex VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_MultiThreading_Mutex SHUTDOWN ShutdownModule_Core_Containers_MultiThreading_Mutex
	"include/kotek_std_alias_mutex.h"
	"include/kotek_core_containers_multithreading_mutex.h"
	"src/main_core_containers_multithreading_mutex_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/multithreading")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)