cmake_minimum_required(VERSION 3.21)

project(kotek.core.types.numerics VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Types_Numerics SHUTDOWN ShutdownModule_Core_Types_Numerics
	"include/kotek_std_alias_numerics.h"
	"include/kotek_core_types_numerics.h"
	"src/main_core_numerics_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/aliases")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)