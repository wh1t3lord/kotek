cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static SHUTDOWN ShutdownModule_Core_Defines_Static
	"include/kotek_core_defines_static.h"
	"src/main_core_defines_static_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.git)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.math)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.profilers)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.sdk)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.tests)