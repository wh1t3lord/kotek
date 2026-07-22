cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines SHUTDOWN ShutdownModule_Core_Defines
	"include/kotek_core_defines.h"
	"src/main_core_defines_dll.cpp")


set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent)