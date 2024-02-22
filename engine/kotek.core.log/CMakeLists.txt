cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.log VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_package(spdlog CONFIG REQUIRED)
	else()
		find_package(spdlog REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/") 
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_log.h"
	"include/kotek_core_log.h"
	"src/main_core_log_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog_header_only)