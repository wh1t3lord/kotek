cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.os.win32 VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	# TODO: add SDL
	if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(glfw3 REQUIRED)
			find_package(unofficial-angle CONFIG REQUIRED)

			if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
				find_package(zstd CONFIG REQUIRED)
				find_package(Threads REQUIRED)
			elseif("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "SHARED")
				find_package(ZLIB REQUIRED)
			endif()

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
	"include/kotek_core_os_win32.h"
	"src/main_core_os_win32_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os.win32)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render)

# TODO: flag for using gles detection like for vulkan KOTEK_VULKAN but KOTEK_GLES and specify what version of gles and shipping
if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
		find_package(zstd CONFIG REQUIRED)
		find_package(Threads REQUIRED)
	elseif("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "SHARED")
		find_package(ZLIB REQUIRED)
	endif()

	target_link_libraries(${PROJECT_NAME} PUBLIC 
		 unofficial::angle::libEGL
		 unofficial::angle::libANGLE
		 unofficial::angle::libGLESv2)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl.glad)

if ("${KOTEK_VULKAN}" STREQUAL "ON")
	target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
endif()

if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "GLFW")
	target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endif()