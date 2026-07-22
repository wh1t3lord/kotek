cmake_minimum_required(VERSION 3.21)

project(kotek.core.memory.gpu.vulkan VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Memory_GPU_Vulkan SHUTDOWN ShutdownModule_Core_Memory_GPU_Vulkan
	"include/kotek_core_memory_gpu_vulkan.h"
	"include/vk_mem_alloc.h"
	"src/main_core_memory_gpu_vulkan_dll.cpp")
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/memory/render")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.vk)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)