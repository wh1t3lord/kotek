cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.console VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_console.h"
	"src/kotek_console.cpp"
	"include/kotek_core_console.h"
	"src/main_core_console_dll.cpp")

if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_map)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.queue)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.pair)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.function)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
