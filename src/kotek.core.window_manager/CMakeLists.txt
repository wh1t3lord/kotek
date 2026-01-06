cmake_minimum_required(VERSION 3.21)

project(kotek.core.window_manager VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_window_manager.h"
	"src/kotek_window_manager.cpp"
	"include/kotek_core_window_manager.h"
	"src/main_core_window_manager_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/window management")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)