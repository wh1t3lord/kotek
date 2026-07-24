cmake_minimum_required(VERSION 3.21)

project(kotek.core.constants.window VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Constants_Window SHUTDOWN ShutdownModule_Core_Constants_Window
	"include/kotek_std_constants.h"
	"include/kotek_core_constants_window.h"
	"src/main_core_constants_window_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/constants")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)