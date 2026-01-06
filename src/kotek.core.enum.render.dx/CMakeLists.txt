cmake_minimum_required(VERSION 3.21)

project(kotek.core.enum.render.dx VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_enum_7.h"
	"include/kotek_enum_8.h"
	"include/kotek_enum_9.h"
	"include/kotek_enum_10.h"
	"include/kotek_enum_11.h"
	"include/kotek_enum_12.h"
	"include/kotek_core_enum_render_dx.h" 
	"src/main_core_enum_render_dx_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/enum")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.dx)