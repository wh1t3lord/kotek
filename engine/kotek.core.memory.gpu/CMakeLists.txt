cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.memory.gpu VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_memory_gpu.h"
	"src/main_core_memory_gpu_dll.cpp")

if ("${KOTEK_MEMORY_LEAK_DETECTION}" STREQUAL "ON")
	if ("${KOTEK_CPP_MEMORY_LEAK_LIBRARY}" STREQUAL "VLD")
		target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.vld)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.gpu.vulkan)