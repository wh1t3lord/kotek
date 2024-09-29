cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.casting VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(Boost REQUIRED)
		elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
			# Nothing here probably
		else()
			find_package(Boost REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_casting.h"
	"src/main_core_casting_dll.cpp")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	if (NOT "${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting.lexical)