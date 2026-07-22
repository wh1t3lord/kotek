cmake_minimum_required(VERSION 3.21)

project(kotek.core.window_manager VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Window_Manager SHUTDOWN ShutdownModule_Core_Window_Manager
	"include/kotek_window_manager.h"
	"src/kotek_window_manager.cpp"
	"include/kotek_core_window_manager.h"
	"src/main_core_window_manager_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/window management")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)