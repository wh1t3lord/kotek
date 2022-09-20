cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui.h"
	"src/main_ui_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.cef)