cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines_dependent VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Dependent SHUTDOWN ShutdownModule_Core_Defines_Dependent
	"include/kotek_core_defines_dependent.h"
	"src/main_core_defines_dependent_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/dependent")	
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.text)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.ecs)