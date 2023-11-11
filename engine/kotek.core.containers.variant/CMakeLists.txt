cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.variant VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
	find_path(ETL_INCLUDE_DIRS "etl/.vscode/settings.json")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_variant.h"
	"include/kotek_core_containers_variant.h"
	"src/main_core_containers_variant_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)

if ("${KOTEK_STD_LIBRARY_STATIC_CONTAINERS}" STREQUAL "ON")
	target_include_directories(${PROJECT_NAME} PUBLIC ${ETL_INCLUDE_DIRS})
endif()