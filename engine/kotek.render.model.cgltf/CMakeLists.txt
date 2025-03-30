cmake_minimum_required(VERSION 3.19.3)

project(kotek.render.model.cgltf VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_path(CGLTF_INCLUDE_DIRS "cgltf.h")
	else()

	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_loader_model.h"
	"src/kotek_loader_model.cpp"
	"include/kotek_render_model_cgltf.h"
	"src/main_render_model_cgltf_dll.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/render/model loaders/vendor")
target_precompile_headers(${PROJECT_NAME} PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>")

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	target_include_directories(${PROJECT_NAME} PUBLIC ${CGLTF_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core)