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
        
        file(GLOB nuget_shaderc_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Shaderc.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
        if ("${nuget_shaderc_folder}" MATCHES "Kotek.Packages.Shaderc.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
            message("[${PROJECT_NAME}][nuget]: package shaderc exists!")
        else()
            message(FATAL_ERROR "failed to find shaderc package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
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
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/vk")
target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_compile_definitions(${PROJECT_NAME} PUBLIC KHRONOS_STATIC)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.model)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.ui.imgui)


if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
    if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
        target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
    else()
    endif()

    target_link_libraries(${PROJECT_NAME} PUBLIC KTX::ktx)
elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
    if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
        target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
    else()
    endif()

    if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
        message("[${PROJECT_NAME}]: ktx package included directory")
        target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
    endif()

    if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
        message("[${PROJECT_NAME}]: shaderc package included directory")
        target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
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

        set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

        set(copy_local_command_debug_1 ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Debug/ktx.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)
        set(copy_local_command_debug_2 ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Debug/ktx.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/)

        set(copy_local_command_release_1 ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Release/ktx.dll" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)
        set(copy_local_command_release_2 ${CMAKE_COMMAND} -E copy_if_different "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Release/ktx.pdb" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/)

        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_1}>"
            COMMAND "$<$<CONFIG:Debug>:${copy_local_command_debug_2}>"
        
            COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_1}>"
            COMMAND "$<$<CONFIG:Release>:${copy_local_command_release_2}>"
        
            COMMAND_EXPAND_LISTS

            COMMENT "copying dlls after compilation of ${PROJECT_NAME}"
        )


        if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/shaderc.lib" 
        AND EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/shaderc_util.lib"
        )
            message("[${PROJECT_NAME}][Debug]: adding ktx.lib to Debug configuration")
            target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/shaderc.lib)
            target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/shaderc_util.lib)
        endif()
        
        if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/shaderc.lib"
            AND EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/shaderc_util.lib"
        )
            message("[${PROJECT_NAME}][None-Debug]: adding ktx.lib to not Debug configurations")
            target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/shaderc.lib)
            target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_shaderc_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/shaderc_util.lib)
        endif()

    else()
    endif()

else()
    message(FATAL_ERROR "provide implementation")
endif()
