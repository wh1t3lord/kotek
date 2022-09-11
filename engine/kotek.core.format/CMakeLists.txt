cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.format VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(fmt REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

if(fmt_FOUND)
	message("[${PROJECT_NAME}][+]: FMT")
else()
	message("[${PROJECT_NAME}][-]: FMT")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_format.h"
	"include/kotek_core_format.h"
	"src/main_core_format_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt-header-only)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.text)