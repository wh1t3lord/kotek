cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.unordered_set VERSION 1 LANGUAGES CXX)

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

if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
	find_path(ETL_INCLUDE_DIRS "etl/.vscode/settings.json")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_unordered_set.h"
	"include/kotek_core_containers_unordered_set.h"
	"src/main_core_containers_unordered_set_dll.cpp")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	target_link_libraries(${PROJECT_NAME} PUBLIC 
		Boost::boost 
		Boost::container
	)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.hash)

if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
	target_include_directories(${PROJECT_NAME} PUBLIC ${ETL_INCLUDE_DIRS})
endif()