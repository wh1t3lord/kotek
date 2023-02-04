cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.vk VERSION 1 LANGUAGES CXX)

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

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render_vk.h"
    "include/kotek_render_allocator_ring.h"
    "include/kotek_render_allocator_ring_with_tabs.h"
    "src/kotek_render_allocator_ring.cpp"
    "include/kotek_render_command_list_ring.h"
    "src/kotek_render_command_list_ring.cpp"
    "include/kotek_render_device.h"
    "src/kotek_render_device.cpp"
    "include/kotek_render_device_properties.h"
    "src/kotek_render_device_properties.cpp"
    "src/kotek_render_instance_properties.cpp"
    "include/kotek_render_instance_properties.h"
    "src/kotek_render_swapchain.cpp"
    "include/kotek_render_swapchain.h"
    "include/kotek_render_resource_manager.h"
    "src/kotek_render_resource_manager.cpp"
    "include/kotek_render_static_buffer_pool.h"
    "src/kotek_render_static_buffer_pool.cpp"
    "include/kotek_render_static_buffer_pool_with_linear_allocator.h"
    "src/kotek_render_static_buffer_pool_with_linear_allocator.cpp"
    "include/kotek_render_resource_view_heap.h"
    "src/kotek_render_resource_view_heap.cpp"
    "src/kotek_render_dynamic_buffer_ring.cpp"
    "include/kotek_render_dynamic_buffer_ring.h"
    "src/kotek_render_upload_heap.cpp"
    "include/kotek_render_upload_heap.h"
    "src/kotek_render_imgui_manager.cpp"
    "include/kotek_render_imgui_manager.h"
    "src/kotek_render_texture_manager.cpp"
    "include/kotek_render_texture_manager.h"
    "src/kotek_render_shader_manager.cpp"
    "include/kotek_render_shader_manager.h"
    "src/kotek_render_shader_cache_manager.cpp"
    "include/kotek_render_shader_cache_manager.h"
    "include/kotek_render_graph.h"
    "src/kotek_render_graph.cpp"
    "include/kotek_render_graph_resource_manager.h"
    "src/kotek_render_graph_resource_manager.cpp"
    "include/kotek_render_graph_builder.h"
    "src/kotek_render_graph_builder.cpp"
    "include/kotek_render_graph_data_types.h"
    "src/kotek_render_graph_data_types.cpp"
    "src/kotek_render_test_shader_manager.cpp"
    "src/kotek_render_test_render_device.cpp"
    "src/kotek_render_test_swapchain.cpp"
    "include/kotek_render_helper_device.h"
    "src/kotek_render_helper_device.cpp"
    "include/kotek_render_helper_debug.h"
    "src/kotek_render_helper_debug.cpp"
    "include/kotek_render_helper_stats.h"
    "src/kotek_render_helper_stats.cpp"
    "src/spirv_reflect.cpp"
    "include/spirv_reflect.h"
    "include/vk_enum_string_helper.h"
    "src/main_render_vk_dll.cpp"
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_compile_definitions(${PROJECT_NAME} PUBLIC KHRONOS_STATIC)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.model)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC KTX::ktx)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
    if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
        target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
    else()
    endif()
endif()
