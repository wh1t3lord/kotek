cmake_minimum_required(VERSION 3.21)

project(kotek.ui VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_UI SHUTDOWN ShutdownModule_UI
	"include/kotek_ui.h"
	"src/main_ui_dll.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/ui")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.imgui)

if ("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "CEF")
	kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.cef)
elseif("${KOTEK_UI_GAME_LIBRARY}" STREQUAL "RMLUI")
	kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.rmlui)
endif()

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.videoplayer)