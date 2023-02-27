cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.videoplayer.avif VERSION 1 LANGUAGES CXX)

find_package(libdav1d CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_videoplayer_avif.h"
	"src/main_ui_videoplayer_avif_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC libdav1d)