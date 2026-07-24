cmake_minimum_required(VERSION 3.21)

project(kotek.core.main_manager VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Main_Manager SHUTDOWN ShutdownModule_Core_Main_Manager
	"include/kotek_main_manager.h"
	"src/kotek_main_manager.cpp"
	"include/kotek_plugin_invoke.h"
	"src/kotek_plugin_invoke.cpp"
	"include/kotek_plugin_override.h"
	"src/kotek_plugin_override.cpp"
	"include/kotek_core_main_manager.h"
	"src/main_core_main_manager_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.engine_config)
