cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.filesystem.file_text VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_loader_file_text_json.h"
	"src/kotek_loader_file_text_json.cpp"
	"include/kotek_loader_file_text.h"
	"src/kotek_loader_file_text.cpp"
	"include/kotek_saver_file_text.h"
	"src/kotek_saver_file_text.cpp"
	"include/kotek_saver_file_text_json.h"
	"src/kotek_saver_file_text_json.cpp"
	"include/kotek_file_text.h"
	"src/kotek_file_text.cpp"
	"include/kotek_core_filesystem_file_text.h"
	"src/main_core_filesystem_file_text_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.json)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.io)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum)