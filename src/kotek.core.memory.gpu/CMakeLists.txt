cmake_minimum_required(VERSION 3.21)

project(kotek.core.memory.gpu VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Memory_GPU SHUTDOWN ShutdownModule_Core_Memory_GPU
	"include/kotek_core_memory_gpu.h"
	"src/main_core_memory_gpu_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/memory/render")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.gpu.vulkan)