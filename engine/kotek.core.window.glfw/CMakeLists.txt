cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.window.glfw VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_window_glfw.h"
	"include/kotek_std_window.h"
	"src/kotek_std_window.cpp"
	"src/main_core_window_glfw_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os.win32)