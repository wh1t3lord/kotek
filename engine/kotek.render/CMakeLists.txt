cmake_minimum_required(VERSION 3.19.3)

project(kotek.render VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("../../${KOTEK_DEPS_FOLDER}/ktx/include/")

if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

link_directories("../../${KOTEK_DEPS_FOLDER}/ktx/lib/")

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(glfw3 3.3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
 
add_library(${PROJECT_NAME} STATIC
	"include/kotek_render.h"
    "include/kotek_render_imgui.h"
    "src/kotek_render_imgui.cpp"
	"src/main_render_dll.cpp"
)

 
target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE OpenGL::OpenGL)

target_link_libraries(${PROJECT_NAME} kotek.core)
target_link_libraries(${PROJECT_NAME} kotek.render.model)
target_link_libraries(${PROJECT_NAME} glfw)

if (WIN32)
	# DEPRECATED: until you write the whole vulkan renderer
#target_link_libraries(${PROJECT_NAME} kotek.render.dx12)
endif()

target_link_libraries(${PROJECT_NAME} kotek.render.gl)
target_link_libraries(${PROJECT_NAME} kotek.render.vk)
target_link_libraries(${PROJECT_NAME} ktx)
target_link_libraries(${PROJECT_NAME} TBB::tbb)