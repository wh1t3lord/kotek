cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.os VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static_OS SHUTDOWN ShutdownModule_Core_Defines_Static_OS
	"include/kotek_core_defines_static_os.h"
	"src/main_core_defines_static_os_dll.cpp")
    
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
if (WIN32)
    kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os.win32)
endif()

if (UNIX)
    kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os.linux)
endif()
