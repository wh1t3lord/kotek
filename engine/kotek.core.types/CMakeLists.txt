cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.types VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_types.h"
	"src/main_core_types_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/aliases")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.char)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.string)