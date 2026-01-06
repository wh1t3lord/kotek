cmake_minimum_required(VERSION 3.21)

project(kotek.core.constants.math VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_constants.h"
	"include/kotek_core_constants_math.h"
	"src/main_core_constants_math_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/constants")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)