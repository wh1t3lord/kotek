cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.format_custom_types VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_format_custom_types.h"
	"include/kotek_core_format_custom_types_string.h"
	"src/main_core_format_custom_types_dll.cpp")


target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.format)