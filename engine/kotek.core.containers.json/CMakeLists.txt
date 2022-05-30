cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.json VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	find_package(Boost COMPONENTS headers json REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_json.h"
	"include/kotek_std_json.h"
	"src/kotek_std_json.cpp"
	"include/kotek_core_containers_json.h"
	"src/main_core_containers_json_dll.cpp")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	target_link_libraries(${PROJECT_NAME} PUBLIC Boost::headers Boost::json)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.any)