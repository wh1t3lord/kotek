cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.gltf VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
include_directories("../../deps/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

 
find_package(glfw3 3.3 REQUIRED PATHS "../../deps/")
find_package(TBB REQUIRED PATHS "../../deps/")

find_package(Vulkan REQUIRED)

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	find_package(glm REQUIRED PATHS "../../deps/")
endif()

message("DETECTING LIBRARIES for ${PROJECT_NAME}")
 

add_library(${PROJECT_NAME} STATIC
	"kotek_render_gltf.h"
	"kotek_gltf_model.h"
	"kotek_gltf_model.cpp"
	"kotek_gltf.h"
	"main_render_gltf_dll.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} TBB::tbb)

 