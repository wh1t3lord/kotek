cmake_minimum_required(VERSION 3.21)

project(kotek.core.window.glfw VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_package(glfw3 CONFIG REQUIRED)
	else()
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_window_glfw.h"
	"include/kotek_std_window.h"
	"src/kotek_std_window.cpp"
	"src/main_core_window_glfw_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/window management/vendor")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
else()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
