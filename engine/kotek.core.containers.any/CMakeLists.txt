cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.any VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_any.h"
	"include/kotek_core_containers_any.h"
	"src/main_core_containers_any_dll.cpp")