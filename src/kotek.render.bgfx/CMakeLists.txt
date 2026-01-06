cmake_minimum_required(VERSION 3.21)

project(kotek.render.bgfx VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

find_package(bgfx CONFIG REQUIRED)

set(to_include_render_graph_simplified_files
	"include/kotek_render_graph_simplified.h"
    "src/kotek_render_graph_simplified.cpp"
    "include/kotek_render_graph_simplified_render_pass.h"
    "src/kotek_render_graph_simplified_render_pass.cpp")

set(to_include_managers_files
    "include/kotek_render_shader_manager.h"
    "src/kotek_render_shader_manager.cpp"
    "include/kotek_render_texture_manager.h"
    "src/kotek_render_texture_manager.cpp"
    "include/kotek_render_resource_manager.h"
    "src/kotek_render_resource_manager.cpp"
    "include/kotek_render_buffer.h"
    "src/kotek_render_buffer.cpp"
    "include/kotek_render_geometry_manager.h"
    "src/kotek_render_geometry_manager.cpp"
)

set(to_include_core_files
    "include/kotek_render_device.h"
    "src/kotek_render_device.cpp"
    "include/kotek_render_swapchain.h"
    "src/kotek_render_swapchain.cpp")

set(to_include_module_files
	"include/kotek_render_bgfx.h"
    "src/main_render_bgfx_dll.cpp")

set(to_include_memory_management_files
    "include/kotek_render_static_buffer_pool.h"
    "src/kotek_render_static_buffer_pool.cpp"
    "include/kotek_render_static_buffer_pool_with_linear_allocator.h"
    "src/kotek_render_static_buffer_pool_with_linear_allocator.cpp"
    "include/kotek_render_allocator_ring.h"
    "include/kotek_render_allocator_ring_with_tabs.h"
    "src/kotek_render_allocator_ring_with_tabs.cpp"
    "src/kotek_render_allocator_ring.cpp")

add_library(${PROJECT_NAME} STATIC
    ${to_include_render_graph_simplified_files}
    ${to_include_managers_files}
    ${to_include_core_files}
    ${to_include_module_files}
    ${to_include_memory_management_files}
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/bgfx")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

source_group("Render Graph/Simplified" FILES ${to_include_render_graph_simplified_files})
source_group("Managers" FILES ${to_include_managers_files})
source_group("Core" FILES ${to_include_core_files})
source_group("Module" FILES ${to_include_module_files})
source_group("Memory management" FILES ${to_include_memory_management_files})

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

#target_compile_definitions(${PROJECT_NAME} PUBLIC KHRONOS_STATIC)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    bgfx::bx 
    bgfx::bgfx 
    bgfx::bimg 
    bgfx::bimg_decode
)