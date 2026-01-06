cmake_minimum_required(VERSION 3.21)

project(kotek.core.main_manager VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_main_manager.h"
	"src/kotek_main_manager.cpp"
	"include/kotek_core_main_manager.h"
	"src/main_core_main_manager_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.engine_config)