cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.gl.glad3 VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render_gl_glad3.h"
	"include/glad/glad.h"
	"include/KHR/khrplatform.h"
	"src/glad.c"
	"src/main_render_gl_glad3_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.gl)