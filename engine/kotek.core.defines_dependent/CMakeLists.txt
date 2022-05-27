cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines_dependent VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_defines_dependent.h"
	"src/main_core_defines_dependent_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.text)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.ecs)