cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.filesystem VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_filesystem.h"
	"include/kotek_filesystem_native.h"
	"include/kotek_filesystem_zlib.h"
	"include/kotek_virtualfilemapper.h"
	"include/kotek_core_filesystem.h"
	"src/kotek_filesystem.cpp"
	"src/kotek_filesystem_native.cpp"
	"src/kotek_filesystem_zlib.cpp"
	"src/kotek_virtualfilemapper.cpp"
	"src/main_core_filesystem_dll.cpp"
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/filesystem")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.filesystem.file_text)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_map)