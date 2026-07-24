cmake_minimum_required(VERSION 3.21)

project(kotek.core.window.glfw VERSION 1 LANGUAGES CXX)




if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_package(glfw3 CONFIG REQUIRED)
	else()
	endif()
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Window_GLFW SHUTDOWN ShutdownModule_Core_Window_GLFW
	"include/kotek_core_window_glfw.h"
	"include/kotek_std_window.h"
	"src/kotek_std_window.cpp"
	"src/main_core_window_glfw_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/window management/vendor")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	kotek_target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
else()
endif()

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
