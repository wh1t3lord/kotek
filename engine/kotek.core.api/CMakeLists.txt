cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.api VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_library(${PROJECT_NAME} STATIC 
	"src/main_api_dll.cpp"
	"include/kotek_api.h"
	"include/kotek_sdk_ui_element.h"
)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.shared_ptr)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.any)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem.path)