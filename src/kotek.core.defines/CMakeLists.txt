cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_defines.h"
	"src/main_core_defines_dll.cpp")


set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent)