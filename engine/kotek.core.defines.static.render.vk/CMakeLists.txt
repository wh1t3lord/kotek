cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.render.vk VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_VULKAN}" STREQUAL "")
	set(KOTEK_VULKAN "ON" CACHE INTERNAL "")
endif()

if ("${KOTEK_VULKAN}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_VULKAN)
endif()

message("[Engine]: Vulkan is '${KOTEK_VULKAN}'")

file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

#ifdef KOTEK_VULKAN
	#define KOTEK_USE_VULKAN

	#ifdef KOTEK_DEBUG
		#define VMA_DEBUG_LOG
	#endif
#endif
")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_render_vk.h"
	"src/main_core_defines_static_render_vk_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)

target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})