cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.multithreading VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_containers_multithreading.h"
	"src/main_core_containers_multithreading_dll.cpp")


set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/multithreading")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.atomic)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.mutex)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.shared_mutex)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.semaphore)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.thread)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.tbb)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.queue)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.condition_variable)