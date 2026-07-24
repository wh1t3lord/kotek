cmake_minimum_required(VERSION 3.21)

project(kotek.core.api VERSION 1 LANGUAGES CXX)




add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_API SHUTDOWN ShutdownModule_Core_API 
	"src/main_api_dll.cpp"
	"include/kotek_api.h"
	"include/kotek_api_no_std.h"
	"include/kotek_sdk_ui_element.h"
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.enum)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.shared_ptr)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.any)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem.path)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.io)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.ecs)