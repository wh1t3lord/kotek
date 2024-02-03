cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.format VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if (UNIX)
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(fmt CONFIG REQUIRED)
		endif()
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_format.h"
	"include/kotek_core_format.h"
	"src/main_core_format_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem.path)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.text)

if (UNIX)
	target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)
endif()

if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
	target_include_directories(${PROJECT_NAME} PUBLIC ${ETL_INCLUDE_DIRS})
endif()