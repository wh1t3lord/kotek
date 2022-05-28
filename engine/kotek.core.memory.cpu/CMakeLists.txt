cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.memory.cpu VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(mimalloc REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/mimalloc/${CMAKE_BUILD_TYPE}/")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_memory.h"
	"include/kotek_core_memory_cpu.h" 
	"src/main_core_memory_cpu_dll.cpp"
	"src/kotek_std_memory.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC mimalloc-static)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.vld)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.os)