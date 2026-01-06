cmake_minimum_required(VERSION 3.21)

project(kotek.core.constants VERSION 1 LANGUAGES CXX)




add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_constants.h"
	"src/main_core_constants_dll.cpp")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/constants")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.math)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.ecs)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.window)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.render)