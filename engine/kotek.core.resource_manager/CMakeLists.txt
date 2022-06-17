cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.resource_manager VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_resource_manager.h"
	"include/kotek_resource_manager.h"
	"src/kotek_resource_manager.cpp"
	"src/main_core_resource_manager_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.resource_manager.loader)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.resource_manager.saver)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)