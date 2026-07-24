cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.multithreading VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_MultiThreading SHUTDOWN ShutdownModule_Core_Containers_MultiThreading
	"include/kotek_core_containers_multithreading.h"
	"src/main_core_containers_multithreading_dll.cpp")


set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/multithreading")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.atomic)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.mutex)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.shared_mutex)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.semaphore)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.thread)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.tbb)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.queue)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.condition_variable)