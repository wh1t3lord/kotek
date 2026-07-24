cmake_minimum_required(VERSION 3.21)

project(kotek.core.types.char VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Types_Char SHUTDOWN ShutdownModule_Core_Types_Char
	"include/kotek_std_alias_char_model.h"
	"include/kotek_core_types_char.h"
	"src/main_core_types_char_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/aliases")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)