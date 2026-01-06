cmake_minimum_required(VERSION 3.21)

project(kotek.render.shared VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render_data_types.h"
	"src/kotek_render_data_types.cpp"
	"include/kotek_render_shared.h"
	"src/main_render_shared_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/shared")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared.gl)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared.dx)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared.vk)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared.bgfx)
