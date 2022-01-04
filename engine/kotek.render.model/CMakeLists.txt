cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.model VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

 
find_package(glfw3 3.3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(assimp REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/assimp/${CMAKE_BUILD_TYPE}")
find_package(Vulkan REQUIRED)

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    find_package(directxmath REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

message("DETECTING LIBRARIES for ${PROJECT_NAME}")
 

add_library(${PROJECT_NAME} STATIC
	"kotek_render_model.h"
	"kotek_model.h"
	"kotek_model.cpp"
	"main_render_model_dll.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${ASSIMP_INCLUDE_DIRS})

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_link_libraries(${PROJECT_NAME} glm::glm)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    target_link_libraries(${PROJECT_NAME} Microsoft::DirectXMath)
endif()

target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} TBB::tbb)
target_link_libraries(${PROJECT_NAME} ${ASSIMP_LIBRARIES}) 