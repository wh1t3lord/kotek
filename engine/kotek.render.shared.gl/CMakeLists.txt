cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.shared.gl VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)


set(to_include_render_graph_simplified_files
	"include/kotek_render_graph_simplified_types.h"
	"include/kotek_render_graph_simplified_types_input.h"
	"include/kotek_render_graph_simplified_types_output.h"
	"src/kotek_render_graph_simplified_types.cpp"
	"src/kotek_render_graph_simplified_types_input.cpp"
	"src/kotek_render_graph_simplified_types_output.cpp")

add_library(${PROJECT_NAME} STATIC
	${to_include_render_graph_simplified_files}
	"include/kotek_render_shared_gl.h"
	"src/main_render_shared_gl_dll.cpp"
)

source_group("Render Graph/Simplified" FILES ${to_include_render_graph_simplified_files})

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)