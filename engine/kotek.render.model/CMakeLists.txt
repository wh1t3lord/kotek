cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.model VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render_model.h"
	"include/kotek_model.h"
	"src/kotek_model.cpp"
	"src/main_render_model_dll.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.model.assimp)