cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.vk VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/include/")

if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

link_directories("../../${KOTEK_DEPS_FOLDER}/ktx/lib/")
link_directories("../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/lib/")

find_package(Vulkan REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(glfw3 3.3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    find_package(directxmath REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

message("DETECTING LIBRARIES for ${PROJECT_NAME}")

message("${CMAKE_CURRENT_SOURCE_DIR}")
message("Vulkan Headers: " + Vulkan::Headers)
message("Vulkan libraries: " + Vulkan::Vulkan)

add_library(${PROJECT_NAME} STATIC
	"kotek_render_vk.h"
    "kotek_render_allocator_ring.h"
    "kotek_render_allocator_ring_with_tabs.h"
    "kotek_render_allocator_ring.cpp"
    "kotek_render_command_list_ring.h"
    "kotek_render_command_list_ring.cpp"
    "kotek_render_device.h"
    "kotek_render_device.cpp"
    "kotek_render_device_properties.h"
    "kotek_render_device_properties.cpp"
    "kotek_render_instance_properties.cpp"
    "kotek_render_instance_properties.h"
    "kotek_render_swapchain.cpp"
    "kotek_render_swapchain.h"
    "kotek_render_resource_manager.h"
    "kotek_render_resource_manager.cpp"
    "kotek_render_static_buffer_pool.h"
    "kotek_render_static_buffer_pool.cpp"
    "kotek_render_static_buffer_pool_with_linear_allocator.h"
    "kotek_render_static_buffer_pool_with_linear_allocator.cpp"
    "kotek_render_resource_view_heap.h"
    "kotek_render_resource_view_heap.cpp"
    "kotek_render_dynamic_buffer_ring.cpp"
    "kotek_render_dynamic_buffer_ring.h"
    "kotek_render_upload_heap.cpp"
    "kotek_render_upload_heap.h"
    "kotek_render_imgui_manager.cpp"
    "kotek_render_imgui_manager.h"
    "kotek_render_texture_manager.cpp"
    "kotek_render_texture_manager.h"
    "kotek_render_shader_manager.cpp"
    "kotek_render_shader_manager.h"
    "kotek_render_shader_cache_manager.cpp"
    "kotek_render_shader_cache_manager.h"
    "kotek_render_graph.h"
    "kotek_render_graph.cpp"
    "kotek_render_graph_resource_manager.h"
    "kotek_render_graph_resource_manager.cpp"
    "kotek_render_graph_builder.h"
    "kotek_render_graph_builder.cpp"
    "kotek_render_graph_data_types.h"
    "kotek_render_graph_data_types.cpp"
    "kotek_render_test_shader_manager.cpp"
    "kotek_render_test_render_device.cpp"
    "kotek_render_test_swapchain.cpp"
    "kotek_render_helper_device.h"
    "kotek_render_helper_device.cpp"
    "kotek_render_helper_debug.h"
    "kotek_render_helper_debug.cpp"
    "kotek_render_helper_stats.h"
    "kotek_render_helper_stats.cpp"
    "kotek_spirv.h"
    "kotek_spirv_reflect.c"
    "kotek_spirv_reflect.h"
    "vk_enum_string_helper.h"
    "main_render_vk_dll.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
target_include_directories(${PROJECT_NAME} PRIVATE Vulkan::Headers)

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_link_libraries(${PROJECT_NAME} glm::glm)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    target_link_libraries(${PROJECT_NAME} Microsoft::DirectXMath)
endif()

target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} kotek.render.model)
target_link_libraries(${PROJECT_NAME} shaderc_combined)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ktx)
target_link_libraries(${PROJECT_NAME} TBB::tbb)