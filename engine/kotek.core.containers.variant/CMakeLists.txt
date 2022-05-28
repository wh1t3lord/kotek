cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.variant VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_variant.h"
	"include/kotek_core_containers_variant.h"
	"src/main_core_containers_variant_dll.cpp")