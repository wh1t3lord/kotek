cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers SHUTDOWN ShutdownModule_Core_Containers
	"include/kotek_core_containers.h"
	"src/main_core_containers_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.any)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.array)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.hash)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.deque)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.dll)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.function)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.io)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.json)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.map)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.microsoft)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.pair)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.queue)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.shared_ptr)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unique_ptr)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_map)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_set)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.variant)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.list)