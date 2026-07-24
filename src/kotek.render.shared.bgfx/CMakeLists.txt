cmake_minimum_required(VERSION 3.21)

project(kotek.render.shared.bgfx VERSION 1 LANGUAGES CXX)




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

# framework glue shared by the bgfx backend plugin and user render passes
# (moved out of kotek.render.bgfx: a plugin must not own symbols that user
# code calls directly — in PLUGIN mode plugin dlls have no link edges)
set(to_include_render_glue_files
	"include/kotek_render_graph_simplified.h"
	"include/kotek_render_graph_simplified_render_pass.h"
	"src/kotek_render_graph_simplified.cpp"
	"src/kotek_render_graph_simplified_render_pass.cpp")

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Render_Shared_BGFX SHUTDOWN ShutdownModule_Render_Shared_BGFX
	${to_include_render_graph_simplified_files}
	${to_include_render_glue_files}
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

kotek_target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
