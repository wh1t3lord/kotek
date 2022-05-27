cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_defines_static.h"
	"src/main_core_defines_static_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.git)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.math)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.profilers)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.sdk)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.tests)