cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.casting.lexical VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(Boost REQUIRED)
		else()
			find_package(Boost REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_casting.h"
	"include/kotek_core_casting_lexical.h"
	"src/main_core_casting_lexical_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)