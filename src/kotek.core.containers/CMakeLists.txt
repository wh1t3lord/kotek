cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_containers.h"
	"src/main_core_containers_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.any)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.array)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.hash)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.deque)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.dll)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.function)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.io)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.json)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.map)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.microsoft)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.pair)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.queue)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.shared_ptr)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unique_ptr)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_map)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_set)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.variant)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.list)