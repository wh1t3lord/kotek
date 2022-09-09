cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.gl.glad4.6 VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND KOTEK_OUTPUT_PRIVATE_FLAGS -DGLAD_GLAPI_EXPORT_BUILD)
list(APPEND KOTEK_OUTPUT_FLAGS -DGLAD_GLAPI_EXPORT)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render_gl_glad4.6.h"
	"include/glad/glad.h"
	"include/KHR/khrplatform.h"
	"src/glad.c"
	"src/main_render_gl_glad4.6_dll.cpp")

target_compile_definitions(${PROJECT_NAME} PRIVATE ${KOTEK_OUTPUT_PRIVATE_FLAGS})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.gl)