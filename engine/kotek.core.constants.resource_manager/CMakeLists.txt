cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.constants.resource_manager VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_constants.h"
	"include/kotek_core_constants_resource_manager.h"
	"src/main_core_constants_resource_manager_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/constants")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)