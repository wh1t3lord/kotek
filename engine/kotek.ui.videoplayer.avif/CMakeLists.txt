cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.videoplayer.avif VERSION 1 LANGUAGES CXX)

# TODO: try to find the stuff from vcpkg, but you should add guard because it depends dav1d doesn't use cmake at all

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	file(GLOB nuget_dav1d_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Dav1d.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
	if ("${nuget_dav1d_folder}" MATCHES "Kotek.Packages.Dav1d.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
		message("[${PROJECT_NAME}][nuget]: package dav1d exists!")
	else()
		message(FATAL_ERROR "failed to find dav1d package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
	endif()
elseif("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(dav1d REQUIRED IMPORTED_TARGET dav1d)
else()
	message(FATAL_ERROR "provide implementation")
endif()


add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_videoplayer_avif.h"
	"src/main_ui_videoplayer_avif_dll.cpp"
	"include/kotek_ui_videoplayer.h"
	"src/kotek_ui_videoplayer.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
		message("[${PROJECT_NAME}]: dav1d package included directory")
		target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
	endif()

	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/dav1d.lib")
		message("[${PROJECT_NAME}][Debug]: adding dav1d.lib to Debug configuration")
		target_link_libraries(${PROJECT_NAME} PUBLIC debug ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/dav1d.lib)
	endif()

	if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/dav1d.lib")
		message("[${PROJECT_NAME}][None-Debug]: adding dav1d.lib to not Debug configurations")
		target_link_libraries(${PROJECT_NAME} PUBLIC optimized ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/dav1d.lib)
	endif()

	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND if $<CONFIG:Debug> ("${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Debug/dav1d.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/")

		COMMAND if $<CONFIG:Release> ("${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_dav1d_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Release/dav1d.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release/")

		COMMENT "copying dlls after compilation of project"
   )

elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::dav1d)
else()
	message(FATAL_ERROR "provide implementation")
endif()
