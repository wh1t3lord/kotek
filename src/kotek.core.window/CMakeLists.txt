cmake_minimum_required(VERSION 3.21)

project(kotek.core.window VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Window SHUTDOWN ShutdownModule_Core_Window
	"include/kotek_window_console.h"
	"src/kotek_window_console.cpp"
	"include/kotek_core_window.h"
	"src/main_core_window_dll.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/window management")
# exactly one backend module exists per configuration (see the root's
# KOTEK_WINDOW_LIBRARY switch)
if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "WIN32")
	kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window.win32)
else()
	kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.window.glfw)
endif()