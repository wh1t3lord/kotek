cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.render.vk VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(WRITE ./include/kotek_std_preprocessors.h "#pragma once

#ifdef KOTEK_VULKAN
	#define KOTEK_USE_VULKAN
#endif
")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_render_vk.h"
	"src/main_core_defines_render_vk_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static)