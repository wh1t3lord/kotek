cmake_minimum_required(VERSION 3.19.3)

project(kotek.render VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../../deps/ktx/include/")

if (WIN32)
include_directories("../../deps/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

link_directories("../../deps/ktx/lib/")

find_package(Vulkan REQUIRED)

find_package(TBB REQUIRED PATHS "../../deps/")
find_package(glfw3 3.3 REQUIRED PATHS "../../deps/")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	find_package(glm REQUIRED PATHS "../../deps/")
endif()
 
add_library(${PROJECT_NAME} STATIC
	"kotek_render.h"
	"main_render_dll.cpp"
)

 
target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} kotek.render.gltf)
target_link_libraries(${PROJECT_NAME} glfw)

if (WIN32)
	# DEPRECATED: until you write the whole vulkan renderer
#target_link_libraries(${PROJECT_NAME} kotek.render.dx12)
endif()

target_link_libraries(${PROJECT_NAME} kotek.render.vk)
target_link_libraries(${PROJECT_NAME} ktx)
target_link_libraries(${PROJECT_NAME} TBB::tbb)