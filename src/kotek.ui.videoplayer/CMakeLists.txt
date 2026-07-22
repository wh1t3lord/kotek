cmake_minimum_required(VERSION 3.21)

project(kotek.ui.videoplayer VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_UI_VideoPlayer SHUTDOWN ShutdownModule_UI_VideoPlayer
	"include/kotek_ui_videoplayer.h"
	"src/main_ui_videoplayer_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/ui")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.videoplayer.avif)