cmake_minimum_required(VERSION 3.21)

project(kotek.render.shared.gl VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)


set(to_include_render_graph_simplified_files
	"include/kotek_render_graph_simplified_types.h"
	"include/kotek_render_graph_simplified_types_input.h"
	"include/kotek_render_graph_simplified_types_output.h"
	"src/kotek_render_graph_simplified_types.cpp"
	"src/kotek_render_graph_simplified_types_input.cpp"
	"src/kotek_render_graph_simplified_types_output.cpp")

# framework glue shared by the gl backend plugin and user render passes
# (moved out of kotek.render.gl: a plugin must not own symbols that user
# code calls directly — in PLUGIN mode plugin dlls have no link edges)
set(to_include_render_glue_files
	"include/kotek_render_graph_simplified.h"
	"include/kotek_render_graph_simplified_render_pass.h"
	"src/kotek_render_graph_simplified.cpp"
	"src/kotek_render_graph_simplified_render_pass.cpp"
	"include/kotek_render_shader_manager.h"
	"src/kotek_render_shader_manager.cpp"
	"include/kotek_render_buffer.h"
	"src/kotek_render_buffer.cpp"
	"include/kotek_render_geometry_manager.h"
	"src/kotek_render_geometry_manager.cpp")

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Render_Shared_GL SHUTDOWN ShutdownModule_Render_Shared_GL
	${to_include_render_graph_simplified_files}
	${to_include_render_glue_files}
	"include/kotek_render_shared_gl.h"
	"include/kotek_render_data_types.h"
	"include/kotek_render_format.h"
	"src/kotek_render_data_types.cpp"
	"src/main_render_shared_gl_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/shared")

if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

source_group("Render Graph/Simplified" FILES ${to_include_render_graph_simplified_files})
source_group("Render Glue" FILES ${to_include_render_glue_files})

kotek_target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl.glad)
# ktkRenderStats (used by ktkRenderBuffer) lives in the backend-agnostic
# shared leaf
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared)
