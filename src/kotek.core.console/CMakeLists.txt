cmake_minimum_required(VERSION 3.21)

project(kotek.core.console VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Console SHUTDOWN ShutdownModule_Core_Console
	"include/kotek_console.h"
	"src/kotek_console.cpp"
	"include/kotek_core_console.h"
	"src/main_core_console_dll.cpp")

if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_map)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.queue)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.pair)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.function)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.ecs)