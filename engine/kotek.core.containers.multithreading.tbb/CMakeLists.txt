cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.multithreading.tbb VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
else()
	find_package(TBB REQUIRED)
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_tbb.h"
	"include/kotek_core_containers_multithreading_tbb.h"
	"src/main_core_containers_multithreading_tbb_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC TBB::tbb)