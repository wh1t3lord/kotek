cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.pair VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_pair.h"
	"include/kotek_core_containers_pair.h"
	"src/main_core_containers_pair_dll.cpp")