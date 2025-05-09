cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.model VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render_model.h"
	"src/main_render_model_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/model loaders")
target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.model.assimp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.model.cgltf)