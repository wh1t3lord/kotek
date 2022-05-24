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

add_library(${PROJECT_NAME} STATIC 
	"src/main_api_dll.cpp"
	"include/kotek_api.h"
	"include/kotek_sdk_ui_element.h"
)

if (UNIX)
target_include_directories(${PROJECT_NAME} PRIVATE "${glfw3_DIR}/../../../include")
endif()

target_link_libraries(${PROJECT_NAME} TBB::tbb)
