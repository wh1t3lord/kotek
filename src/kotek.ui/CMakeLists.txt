cmake_minimum_required(VERSION 3.21)

project(kotek.ui VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui.h"
	"src/main_ui_dll.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/ui")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.imgui)

if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
	target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.cef)
elseif("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "RMLUI")
	target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.rmlui)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.videoplayer)