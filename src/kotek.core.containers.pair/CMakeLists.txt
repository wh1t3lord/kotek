cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.pair VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Containers_Pair SHUTDOWN ShutdownModule_Core_Containers_Pair
	"include/kotek_std_alias_pair.h"
	"include/kotek_core_containers_pair.h"
	"src/main_core_containers_pair_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)