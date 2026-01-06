cmake_minimum_required(VERSION 3.21)

project(kotek.core.profilers.gpu VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_profilers_gpu.h"
	"src/main_core_profilers_gpu_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/profilers")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.profilers)