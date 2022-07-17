cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.enum.render VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_enum_render.h" 
	"src/main_core_enum_render_dll.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render.dx)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render.gl)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum.render.vk)