cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.memory.cpu VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
			find_package(mimalloc REQUIRED)
		endif()
	else()
		if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
			find_package(mimalloc REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/mimalloc/${CMAKE_BUILD_TYPE}/")
		endif()
	endif()
endif()

message("[${PROJECT_NAME}]: memory allocator for CPU = ${KOTEK_MEMORY_ALLOCATOR_CPU}")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_memory.h"
	"include/kotek_core_memory_cpu.h" 
	"src/main_core_memory_cpu_dll.cpp"
	"src/kotek_std_memory.cpp"
)

if ("${KOTEK_DEVELOPMENT_TYPE_PACKAGES}" STREQUAL "STATIC")
	if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
		target_link_libraries(${PROJECT_NAME} PUBLIC mimalloc-static)
	endif()
else()
	if ("${KOTEK_MEMORY_ALLOCATOR_CPU}" STREQUAL "MIMALLOC")
		target_link_libraries(${PROJECT_NAME} PUBLIC mimalloc)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)

if ("${KOTEK_MEMORY_LEAK_DETECTION}" STREQUAL "ON")
	if ("${KOTEK_CPP_MEMORY_LEAK_LIBRARY}" STREQUAL "VLD")
		target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.vld)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)