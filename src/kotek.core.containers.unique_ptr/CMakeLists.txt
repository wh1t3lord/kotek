cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.unique_ptr VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_unique_ptr.h"
	"include/kotek_core_containers_unique_ptr.h"
	"src/main_core_containers_unique_ptr_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)