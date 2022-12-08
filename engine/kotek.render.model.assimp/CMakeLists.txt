cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.model.assimp VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)


if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_package(assimp REQUIRED)
	else()
		find_package(assimp REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/assimp/${CMAKE_BUILD_TYPE}")
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_render_model_assimp.h"
	"include/kotek_model.h"
	"src/kotek_model.cpp"
	"src/main_render_model_assimp_dll.cpp"
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp::assimp) 