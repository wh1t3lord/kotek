cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.containers.string VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"tests/kotek_core_test_string.cpp"
	"include/kotek_std_string.h"
	"include/kotek_core_containers_string.h"
	"src/main_core_containers_string_dll.cpp"
	"src/kotek_std_string.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting.lexical)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.casting.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.hash)