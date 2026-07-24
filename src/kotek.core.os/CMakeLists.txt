cmake_minimum_required(VERSION 3.21)

project(kotek.core.os VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_OS SHUTDOWN ShutdownModule_Core_OS
	"include/kotek_core_os.h"
	"src/main_core_os_dll.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/os")
if (WIN32)
    kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os.win32)
endif()

if (UNIX)
    kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os.linux)
endif()
