cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.os.win32 VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
	find_package(glfw3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_os.h"
	"include/kotek_core_os_win32.h"
	"src/main_core_os_win32_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os.win32)

if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
	target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endif()