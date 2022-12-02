cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.array VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
		if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
			find_package(Boost COMPONENTS container REQUIRED)
		else()
			find_package(Boost COMPONENTS container REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_array.h"
	"include/kotek_core_containers_array.h"
	"src/main_core_containers_array_dll.cpp")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	target_link_libraries(${PROJECT_NAME} PUBLIC Boost::container)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)