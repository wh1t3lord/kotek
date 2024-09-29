cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.filesystem.path VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(etl CONFIG REQUIRED)
		elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			file(GLOB nuget_etl_folder RELATIVE ${PROJECT_SOURCE_DIR}/../../nuget/packages ${PROJECT_SOURCE_DIR}/../../nuget/packages/Kotek.Packages.Etl.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}*)
			if ("${nuget_etl_folder}" MATCHES "Kotek.Packages.Etl.Vcpkg.Runtimes.${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER}")
				message("[${PROJECT_NAME}][nuget]: package etl exists!")
			else()
				message(FATAL_ERROR "failed to find etl package! (${KOTEK_NUGET_PLATFORM_NAME}.${KOTEK_NUGET_COMPILER_NAME}.${KOTEK_NUGET_ARCH_BIT_NUMBER})")
			endif()
		else()
			find_package(etl REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_filesystem_path.h"
	"include/kotek_core_containers_filesystem_path.h"
	"src/main_core_containers_filesystem_path_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if (EXISTS "${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_etl_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include")
			message("[${PROJECT_NAME}]: etl package included directory")
			target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/../../nuget/packages/${nuget_etl_folder}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/include)
		endif()
	else()
		target_link_libraries(${PROJECT_NAME} PUBLIC etl::etl)
	endif()
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)