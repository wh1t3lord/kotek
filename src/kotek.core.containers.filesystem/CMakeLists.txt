cmake_minimum_required(VERSION 3.21)

project(kotek.core.containers.filesystem VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_alias_filesystem.h"
	"include/kotek_core_containers_filesystem.h"
	"src/kotek_std_alias_filesystem.cpp"
	"src/main_core_containers_filesystem_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/containers")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem.path)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)

if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
	target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
endif()