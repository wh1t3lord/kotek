cmake_minimum_required(VERSION 3.21)

project(kotek.core.constants.ecs VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Constants_ECS SHUTDOWN ShutdownModule_Core_Constants_ECS
	"include/kotek_std_constants.h"
	"include/kotek_core_constants_ecs.h"
	"src/main_core_constants_ecs_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/constants")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)