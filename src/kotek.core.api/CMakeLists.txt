cmake_minimum_required(VERSION 3.21)

project(kotek.core.api VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

add_library(${PROJECT_NAME} STATIC 
	"src/main_api_dll.cpp"
	"include/kotek_api.h"
	"include/kotek_api_no_std.h"
	"include/kotek_sdk_ui_element.h"
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.shared_ptr)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.any)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem.path)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.io)