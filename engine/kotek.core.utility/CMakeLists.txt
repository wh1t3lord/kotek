cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.utility VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_utility.h"
	"src/kotek_std_utility.cpp"
	"include/kotek_core_utility.h"
	"src/main_core_utility_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.math)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)