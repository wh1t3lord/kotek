cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.types.string VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(etl CONFIG REQUIRED)
		else()
			find_package(etl REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_string.h"
	"include/kotek_core_types_string.h"
	"src/main_core_types_string_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.char)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.string)

if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
	target_link_libraries(${PROJECT_NAME} PUBLIC etl::etl)
endif()