cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines_dependent.assert VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_dependent_preprocessors.h"
	"include/kotek_core_defines_dependent_assert.h"
	"src/main_core_defines_dependent_assert_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/dependent")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)