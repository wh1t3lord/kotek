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
    elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
        if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
            find_package(zstd CONFIG REQUIRED)
            find_package(Threads REQUIRED)
        else()
        endif()

        file(GLOB nuget_ktx_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Ktx.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
        if ("${nuget_ktx_folder}" MATCHES "Kotek.Packages.Ktx.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
            message("[${PROJECT_NAME}][nuget]: package ktx exists!")
        else()
            message(FATAL_ERROR "failed to find ktx package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
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


if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
    if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
        target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
    else()
    endif()

    target_link_libraries(${PROJECT_NAME} PUBLIC KTX::ktx)

elseif("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
    if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
        target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
    else()
    endif()

    if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
        message("[${PROJECT_NAME}]: ktx package included directory")
        target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
    endif()

    if (WIN32)
        if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/tbb12_debug.lib")
            message("[${PROJECT_NAME}][Debug]: adding ktx.lib to Debug configuration")
            target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/ktx.lib)
        endif()
        
        if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/tbb12.lib")
            message("[${PROJECT_NAME}][None-Debug]: adding ktx.lib to not Debug configurations")
            target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/ktx.lib)
        endif()

        set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_boost_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

        set(copy_local_command_debug_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/ktx.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
        set(copy_local_command_debug_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Debug/ktx.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
        
        set(copy_local_command_release_1 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/ktx.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
        set(copy_local_command_release_2 ${CMAKE_COMMAND} -E copy_if_different "${path_to_bins}/bin/Release/ktx.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)

        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD

            COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_1}>"
            COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_2}>"
    
            COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_1}>"
            COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_2}>"

            COMMAND_EXPAND_LISTS

            COMMENT "copying dlls after compilation of ${PROJECT_NAME}"
        )
    else()
    endif()
else()
    message(FATAL_ERROR "provide implementation")
endif()
