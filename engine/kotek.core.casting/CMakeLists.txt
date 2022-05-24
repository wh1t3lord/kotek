cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.casting VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS headers REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_casting.h"
	"include/kotek_core_casting.h"
	"src/main_core_casting_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC Boost::headers)