cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.memory VERSION 1 LANGUAGES CXX)

if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


message("DETECTING LIBRARIES for ${PROJECT_NAME}")

find_package(mimalloc REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/mimalloc/${CMAKE_BUILD_TYPE}/")
find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

add_library(${PROJECT_NAME} STATIC 
	"src/main_core_memory_dll.cpp"
	"include/kotek_core_memory.h"
)

target_link_libraries(${PROJECT_NAME} mimalloc-static)
target_link_libraries(${PROJECT_NAME} TBB::tbb)