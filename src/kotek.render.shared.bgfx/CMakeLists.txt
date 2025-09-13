cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.shared.bgfx VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(bgfx REQUIRED)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(to_include_render_graph_simplified_files
#	"include/kotek_render_graph_simplified_types.h"
#	"include/kotek_render_graph_simplified_types_input.h"
#	"include/kotek_render_graph_simplified_types_output.h"
#	"src/kotek_render_graph_simplified_types.cpp"
#	"src/kotek_render_graph_simplified_types_input.cpp"
#	"src/kotek_render_graph_simplified_types_output.cpp"
)

add_library(${PROJECT_NAME} STATIC
	${to_include_render_graph_simplified_files}
	"include/kotek_render_shared_bgfx.h"
	"include/kotek_render_data_types.h"
	"src/kotek_render_data_types.cpp"
	"include/kotek_render_format.h"
	"src/main_render_shared_bgfx_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/shared")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
