cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.any VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_Any SHUTDOWN ShutdownModule_Core_Containers_Any
	"include/kotek_std_alias_any.h"
	"include/kotek_core_containers_any.h"
	"src/main_core_containers_any_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)