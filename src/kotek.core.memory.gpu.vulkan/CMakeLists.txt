cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.memory.gpu.vulkan VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_memory_gpu_vulkan.h"
	"include/vk_mem_alloc.h"
	"src/main_core_memory_gpu_vulkan_dll.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/memory/render")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.vk)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)