cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.render VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_defines_render.h"
	"src/main_core_defines_render_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.dx)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.gl)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.vk)