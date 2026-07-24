cmake_minimum_required(VERSION 3.21)

project(kotek.core.types VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Types SHUTDOWN ShutdownModule_Core_Types
	"include/kotek_core_types.h"
	"src/main_core_types_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/aliases")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.char)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.string)