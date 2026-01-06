cmake_minimum_required(VERSION 3.21)

project(kotek.core.enum.render.bgfx VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_enum.h"
	"include/kotek_translation.h"
	"include/kotek_core_enum_render_bgfx.h" 
	"src/main_core_enum_render_bgfx_dll.cpp"
	"src/kotek_translation.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/enum")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)