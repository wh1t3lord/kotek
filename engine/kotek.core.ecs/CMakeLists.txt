cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.ecs VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
	"include/kotek_component_allocator.h"
	"include/kotek_core_ecs.h"
	"src/kotek_component_camera.cpp"
	"include/kotek_component_camera.h"
	"src/kotek_component_input.cpp"
	"include/kotek_component_input.h"
	"src/kotek_component_transform.cpp"
	"include/kotek_component_transform.h"
	"src/kotek_component_visibility.cpp"
	"include/kotek_component_visibility.h"
	"include/kotek_component_geometry.h"
	"src/kotek_component_geometry.cpp"
	"src/main_core_ecs_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.unordered_map)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)