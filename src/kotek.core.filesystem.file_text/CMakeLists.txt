cmake_minimum_required(VERSION 3.21)

project(kotek.core.filesystem.file_text VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_file_text.h"
	"src/kotek_file_text.cpp"
	"include/kotek_core_filesystem_file_text.h"
	"src/main_core_filesystem_file_text_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/filesystem")
if (UNIX)
    set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.json)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.io)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum)
