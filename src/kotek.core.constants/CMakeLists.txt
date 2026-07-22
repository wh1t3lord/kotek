cmake_minimum_required(VERSION 3.21)

project(kotek.core.constants VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Constants SHUTDOWN ShutdownModule_Core_Constants
	"include/kotek_core_constants.h"
	"src/main_core_constants_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/constants")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.math)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.ecs)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.window)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.render)