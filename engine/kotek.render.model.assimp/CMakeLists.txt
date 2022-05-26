cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.model.assimp VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
	include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

find_package(assimp REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/assimp/${CMAKE_BUILD_TYPE}")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render_model_assimp.h"
	"src/main_render_model_assimp_dll.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC assimp::assimp) 