cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.resource_manager.loader VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_resource_manager_loader.h"
	"include/kotek_resource_manager_loader.h"
	"src/kotek_resource_manager_loader.cpp"
	"src/main_core_resource_manager_loader_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.filesystem.file_text)