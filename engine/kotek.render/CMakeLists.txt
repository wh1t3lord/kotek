cmake_minimum_required(VERSION 3.19.3)

project(kotek.render VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render.h"
	"src/main_render_dll.cpp"
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.model)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.shared)

if (WIN32)
	# DEPRECATED: until you write the whole vulkan renderer
#target_link_libraries(${PROJECT_NAME} kotek.render.dx12)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.vk)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.software)