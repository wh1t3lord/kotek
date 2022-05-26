cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.multithreading.tbb VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_containers_multithreading_tbb.h"
	"src/main_core_containers_multithreading_tbb_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines)
target_link_libraries(${PROJECT_NAME} TBB::tbb)