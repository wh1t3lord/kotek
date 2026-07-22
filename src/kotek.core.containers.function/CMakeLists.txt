cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.function VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_Function SHUTDOWN ShutdownModule_Core_Containers_Function
	"include/kotek_std_alias_function.h"
	"include/kotek_core_containers_function.h"
	"src/main_core_containers_function_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)