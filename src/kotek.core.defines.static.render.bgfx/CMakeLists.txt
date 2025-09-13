cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.render.bgfx VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_BGFX}" STREQUAL "")
	set(KOTEK_BGFX "ON" CACHE INTERNAL "")
endif()

if ("${KOTEK_BGFX}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_BGFX)
endif()

message("[${PROJECT_NAME}]: BGFX is '${KOTEK_BGFX}'")

file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

#ifdef KOTEK_BGFX
	#define KOTEK_USE_BGFX
#endif
")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_render_bgfx.h"
	"src/main_core_defines_static_render_bgfx_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)