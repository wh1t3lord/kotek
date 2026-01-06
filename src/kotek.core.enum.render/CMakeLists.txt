cmake_minimum_required(VERSION 3.21)

project(kotek.core.enum.render VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_enum_render.h" 
	"include/kotek_enum.h"
	"include/kotek_translation.h"
	"src/kotek_translation.cpp"
	"src/main_core_enum_render_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/enum")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render.dx)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render.gl)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render.vk)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render.bgfx)