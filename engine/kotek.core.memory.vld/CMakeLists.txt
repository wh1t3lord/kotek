cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.memory.vld VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


message("DETECTING LIBRARIES for ${PROJECT_NAME}")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_memory.h"
	"include/kotek_core_memory_vld.h" 
	"src/main_core_memory_vld_dll.cpp"
)

if(WIN32)
	target_include_directories(${PROJECT_NAME} PUBLIC "../../${KOTEK_DEPS_FOLDER}/vld/include/")
	target_link_directories(${PROJECT_NAME} PUBLIC "../../${KOTEK_DEPS_FOLDER}/vld/lib/Win64/")
endif()