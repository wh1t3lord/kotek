cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.api VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
include_directories("../../${KOTEK_DEPS_FOLDER}/vld/include/")
endif()

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

find_package(glfw3 3.3 REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
find_package(TBB REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	find_package(glm REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
endif()

add_library(${PROJECT_NAME} STATIC 
	"main_api_dll.cpp"
	"kotek_api.h"
	"kotek_sdk_ui_element.h"
)

if (UNIX)
target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
endif()

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} TBB::tbb)

