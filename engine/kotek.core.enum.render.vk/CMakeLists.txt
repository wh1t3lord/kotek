cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.enum.render.vk VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_enum.h"
	"include/kotek_core_enum_render_vk.h" 
	"src/main_core_enum_render_vk_dll.cpp"
)

if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
