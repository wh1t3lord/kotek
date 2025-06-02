cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.videoplayer VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_videoplayer.h"
	"src/main_ui_videoplayer_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/ui")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.videoplayer.avif)