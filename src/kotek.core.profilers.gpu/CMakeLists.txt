cmake_minimum_required(VERSION 3.21)

project(kotek.core.profilers.gpu VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Profilers_GPU SHUTDOWN ShutdownModule_Core_Profilers_GPU
	"include/kotek_core_profilers_gpu.h"
	"src/main_core_profilers_gpu_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/profilers")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.profilers)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
