cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.hash VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	find_package(Boost COMPONENTS headers container REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_hash.h"
	"include/kotek_core_containers_hash.h"
	"src/main_core_containers_hash_dll.cpp")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	target_link_libraries(${PROJECT_NAME} PUBLIC Boost::headers Boost::container)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)