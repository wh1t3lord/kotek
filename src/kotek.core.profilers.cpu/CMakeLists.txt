cmake_minimum_required(VERSION 3.21)

project(kotek.core.profilers.cpu VERSION 1 LANGUAGES CXX)




kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Profilers_CPU SHUTDOWN ShutdownModule_Core_Profilers_CPU
	"include/kotek_core_profilers_cpu.h"
	"src/main_core_profilers_cpu_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/profilers")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.profilers)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory)