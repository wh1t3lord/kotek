cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.render.dx VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DIRECTX}" STREQUAL "")
	set(KOTEK_DIRECTX "ON")
endif()

if ("${KOTEK_DIRECTX}" STREQUAL "ON")
	add_definitions(-DKOTEK_DIRECTX)

	# if you set 12 it means we will add all directx versions or those who is equal or lower to "x" value
	set(KOTEK_DIRECTX_VERSION 12)
endif()

message("[Engine]: DirectX is '${KOTEK_DIRECTX}'")

if ("${KOTEK_DIRECTX}" STREQUAL "ON")

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#ifdef KOTEK_DIRECTX
		#define KOTEK_USE_DIRECTX
		#define KOTEK_USE_DIRECTX_VERSION ${KOTEK_DIRECTX_VERSION}
	#endif
	")

else()

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")

endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_defines_static_render_dx.h"
	"include/kotek_std_preprocessors.h"
	"src/main_core_defines_static_render_dx_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static)