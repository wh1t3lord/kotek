cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.render.gl VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_OPENGL}" STREQUAL "")
	set(KOTEK_OPENGL "ON")
endif()

if ("${KOTEK_OPENGL}" STREQUAL "ON")
	add_definitions(-DKOTEK_OPENGL)

	# TODO: think about supporting modern version and split two things, like if we specify for legacy version 3 it means will be added all project until modern
	# So if legacy = 1 it means from 1 version will be add to modern
	set(KOTEK_OPENGL_MODERN_VERSION "3")
	set(KOTEK_OPENGL_LEGACY_VERSION "3")
endif()

message("[Engine]: Vulkan is '${KOTEK_VULKAN}'")

file(WRITE ./include/kotek_std_preprocessors.h "#pragma once

#ifdef KOTEK_OPENGL
	#define KOTEK_USE_OPENGL
	#define KOTEK_USE_OPENGL_MODERN_VERSION ${KOTEK_OPENGL_MODERN_VERSION}
	#define KOTEK_USE_OPENGL_LEGACY_VERSION ${KOTEK_OPENGL_LEGACY_VERSION}
#endif
")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_render_gl.h"
	"src/main_core_defines_render_gl_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static)