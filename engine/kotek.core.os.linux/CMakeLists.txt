cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.os.linux VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	# TODO: add SDL
	if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(glfw3 REQUIRED)
		else()
			find_package(glfw3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

if ("${KOTEK_VULKAN}" STREQUAL "ON")
	find_package(Vulkan REQUIRED)
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_os.h"
	"include/kotek_core_os_linux.h"
	"src/main_core_os_linux_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os.linux)

if ("${KOTEK_VULKAN}" STREQUAL "ON")
	target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
endif()

if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
	target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl.glad)
