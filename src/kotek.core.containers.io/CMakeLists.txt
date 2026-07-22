cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.io VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_IO SHUTDOWN ShutdownModule_Core_Containers_IO
	"include/kotek_std_alias_io.h"
	"include/kotek_core_containers_io.h"
	"src/main_core_containers_io_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.char)