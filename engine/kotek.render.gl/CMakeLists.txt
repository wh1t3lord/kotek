cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.gl VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
    if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
        find_package(Ktx CONFIG REQUIRED)
        if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
            find_package(zstd CONFIG REQUIRED)
            find_package(Threads REQUIRED)
        else()
        endif()

    else()
        find_package(Ktx REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/ktx/${CMAKE_BUILD_TYPE}/")
    endif()
endif()

set(to_include_render_graph_simplified_files
    "include/kotek_render_graph_simplified_node.h"
    "src/kotek_render_graph_simplified_node.cpp"
    "include/kotek_render_graph_simplified_resource_manager.h"
    "src/kotek_render_graph_simplified_resource_manager.cpp"
	"include/kotek_render_graph_simplified.h"
    "src/kotek_render_graph_simplified.cpp"
    "include/kotek_render_graph_simplified_render_pass.h"
    "src/kotek_render_graph_simplified_render_pass.cpp"
    "include/kotek_render_graph_simplified_builder.h"
    "src/kotek_render_graph_simplified_builder.cpp")

set(to_include_managers_files
    "include/kotek_render_shader_manager.h"
    "src/kotek_render_shader_manager.cpp"
    "include/kotek_render_texture_manager.h"
    "src/kotek_render_texture_manager.cpp"
    "include/kotek_render_resource_manager.h"
    "src/kotek_render_resource_manager.cpp"
    "include/kotek_render_buffer_manager.h"
    "src/kotek_render_buffer_manager.cpp"
    "include/kotek_render_geometry_manager.h"
    "src/kotek_render_geometry_manager.cpp"
    "include/offsetAllocator.hpp"
    "src/offsetAllocator.cpp"
)

set(to_include_core_files
    "include/kotek_render_device.h"
    "src/kotek_render_device.cpp"
    "include/kotek_render_swapchain.h"
    "src/kotek_render_swapchain.cpp")

set(to_include_module_files
	"include/kotek_render_gl.h"
    "src/main_render_gl_dll.cpp")

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

if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

source_group("Render Graph/Simplified" FILES ${to_include_render_graph_simplified_files})
source_group("Managers" FILES ${to_include_managers_files})
source_group("Core" FILES ${to_include_core_files})
source_group("Module" FILES ${to_include_module_files})
source_group("Memory management" FILES ${to_include_memory_management_files})

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_compile_definitions(${PROJECT_NAME} PUBLIC KHRONOS_STATIC)

# TODO: delete this
#target_include_directories(${PROJECT_NAME} PUBLIC "../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/include/")
#target_link_directories(${PROJECT_NAME} PUBLIC "../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/lib/")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.model)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.gl.glad)
target_link_libraries(${PROJECT_NAME} PUBLIC KTX::ktx)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
    if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
        target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
    else()
    endif()
endif()
