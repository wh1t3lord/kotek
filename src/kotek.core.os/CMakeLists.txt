cmake_minimum_required(VERSION 3.21)

project(kotek.core.os VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_os.h"
	"src/main_core_os_dll.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/os")
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os.win32)
endif()

if (UNIX)
    target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os.linux)
endif()
