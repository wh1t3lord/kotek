cmake_minimum_required(VERSION 3.21)

project(kotek.core.enum.render.gl VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Enum_Render_GL SHUTDOWN ShutdownModule_Core_Enum_Render_GL
	"include/kotek_enum.h"
	"include/kotek_translation.h"
	"include/kotek_core_enum_render_gl.h" 
	"src/main_core_enum_render_gl_dll.cpp"
	"src/kotek_translation.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/enum")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)