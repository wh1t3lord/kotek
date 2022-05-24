cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.filesystem.file_text VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_text_file.h"
	"src/kotek_text_file.cpp"
	"include/kotek_core_filesystem_file_text.h"
	"src/main_core_filesystem_file_text_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.json)