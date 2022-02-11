cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.gl VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/include/")

if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

link_directories("../../${KOTEK_DEPS_FOLDER}/ktx/lib/")
link_directories("../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/lib/")

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(Boost COMPONENTS unit_test_framework REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(glfw3 3.3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    find_package(directxmath REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

message("DETECTING LIBRARIES for ${PROJECT_NAME}")

message("${CMAKE_CURRENT_SOURCE_DIR}")
message("OpenGL Headers: " + OpenGL::OpenGL)
message("OpenGL libraries: " + OpenGL::OpenGL)

add_library(${PROJECT_NAME} STATIC
	"kotek_render_gl.h"
    "kotek_render_device.h"
    "kotek_render_device.cpp"
    "kotek_render_swapchain.h"
    "kotek_render_swapchain.cpp"
    "kotek_render_resource_manager.h"
    "kotek_render_resource_manager.cpp"
    "kotek_render_graph.h"
    "kotek_render_graph.cpp"
    "kotek_render_graph_types.h"
    "kotek_render_graph_types.cpp"
    "kotek_render_graph_builder.h"
    "kotek_render_graph_builder.cpp"
    "main_render_gl_dll.cpp"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
target_include_directories(${PROJECT_NAME} PRIVATE OpenGL::OpenGL)

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
    target_link_libraries(${PROJECT_NAME} glm::glm)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
    target_link_libraries(${PROJECT_NAME} Microsoft::DirectXMath)
endif()

target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} kotek.render.model)
target_link_libraries(${PROJECT_NAME} shaderc_combined)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} ktx)
target_link_libraries(${PROJECT_NAME} TBB::tbb)