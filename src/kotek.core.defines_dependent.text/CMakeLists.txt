cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines_dependent.text VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Dependent_Text SHUTDOWN ShutdownModule_Core_Defines_Dependent_Text
	"include/kotek_std_dependent_preprocessors.h"
	"include/kotek_core_defines_dependent_text.h"
	"src/main_core_defines_dependent_text_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/dependent")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)