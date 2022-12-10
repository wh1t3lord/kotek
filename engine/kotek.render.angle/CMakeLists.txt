cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.angle VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
    if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
        find_package(KTX CONFIG REQUIRED)
        
        if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC")
            find_package(zstd CONFIG REQUIRED)
        else()
            find_package(SPIRV-Tools CONFIG REQUIRED)
            find_package(SPIRV-Tools-opt CONFIG REQUIRED)
        endif()

        find_package(ZLIB REQUIRED)
        find_package(glslang CONFIG REQUIRED)
        find_package(unofficial-shaderc_util CONFIG REQUIRED)
        find_package(unofficial-shaderc CONFIG REQUIRED)
        find_package(unofficial-spirv-reflect CONFIG REQUIRED)
        find_package(unofficial-angle CONFIG REQUIRED)
    else()
        find_package(KTX REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/ktx/${CMAKE_BUILD_TYPE}/")
    endif()
endif()

set(to_include_render_graph_simplified_files)

set(to_include_managers_files)

set(to_include_core_files)

set(to_include_module_files
	"include/kotek_render_angle.h"
    "src/main_render_angle_dll.cpp")

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
target_link_libraries(${PROJECT_NAME} PUBLIC KTX::ktx)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
    # Spirv-Tools, TODO: add when you will change all projects to SHARED, STATIC and HYBRID (most of them static, but sandbox.game is shared and glad projects too!)
    # if ("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "SHARED")
    #     target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-shared)
    # elseif("${KOTEK_DEVELOPMENT_TYPE}" STREQUAL "STATIC")
    #     target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-static)
    # else()
    #     message(FATAL_ERROR "[${PROJECT_NAME}]: you must specify development type as 'SHARED' or 'STATIC'")
    # endif()

if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC")
    target_link_libraries(${PROJECT_NAME} PUBLIC zstd::libzstd_static)
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-shared)
    target_link_libraries(${PROJECT_NAME} PUBLIC SPIRV-Tools-opt)
endif()

    target_link_libraries(${PROJECT_NAME} PUBLIC unofficial::shaderc::shaderc)
    target_link_libraries(${PROJECT_NAME} PUBLIC unofficial::shaderc_util::shaderc_util)
    target_link_libraries(${PROJECT_NAME} PUBLIC unofficial::spirv-reflect::spirv-reflect)
    target_link_libraries(${PROJECT_NAME} PUBLIC unofficial::angle::libEGL unofficial::angle::libANGLE unofficial::angle::libGLESv2 unofficial::angle::angle_common)
endif()