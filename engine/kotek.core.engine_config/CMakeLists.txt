cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.engine_config VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_config.h"
	"src/kotek_std_config.cpp"
	"include/kotek_core_engine_config.h"
	"src/main_core_engine_config_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.dll)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_set)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.string)