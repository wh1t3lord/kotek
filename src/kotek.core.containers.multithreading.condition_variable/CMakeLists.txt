cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.multithreading.condition_variable VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_condition_variable.h"
	"include/kotek_core_containers_multithreading_condition_variable.h"
	"src/main_core_containers_multithreading_condition_variable_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers/multithreading")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)