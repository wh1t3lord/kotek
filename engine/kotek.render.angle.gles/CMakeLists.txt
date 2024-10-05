cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.angle.gles VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
    if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
        find_package(Ktx CONFIG REQUIRED)
        
        if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
            find_package(zstd CONFIG REQUIRED)
            find_package(Threads REQUIRED)
        endif()
    elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
        if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
            find_package(zstd CONFIG REQUIRED)
            find_package(Threads REQUIRED)
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

set(to_include_render_graph_simplified_files)

set(to_include_managers_files)

set(to_include_core_files)

set(to_include_module_files
	"include/kotek_render_angle_gles.h"
    "src/main_render_angle_gles_dll.cpp")

set(to_include_memory_management_files)

add_library(${PROJECT_NAME} STATIC
    ${to_include_render_graph_simplified_files}
    ${to_include_managers_files}
    ${to_include_core_files}
    ${to_include_module_files}
    ${to_include_memory_management_files}
)

source_group("Render Graph/Simplified" FILES ${to_include_render_graph_simplified_files})
source_group("Managers" FILES ${to_include_managers_files})
source_group("Core" FILES ${to_include_core_files})
source_group("Module" FILES ${to_include_module_files})
source_group("Memory management" FILES ${to_include_memory_management_files})

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_compile_definitions(${PROJECT_NAME} PUBLIC KHRONOS_STATIC)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.model)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
    # Spirv-Tools, TODO: add when you will change all projects to SHARED, STATIC and HYBRID (most of them static, but sandbox.game is shared and glad projects too!)
    # if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "SHARED")
    #     target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-shared)
    # elseif("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
    #     target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-static)
    # else()
    #     message(FATAL_ERROR "[${PROJECT_NAME}]: you must specify development type as 'SHARED' or 'STATIC'")
    # endif()

    if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
        target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
    endif()
    
    target_link_libraries(${PROJECT_NAME} PUBLIC KTX::ktx)
elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
    if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC" OR UNIX)
        target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
        target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
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

        set(path_to_bins "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_ktx_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")

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
endif()
