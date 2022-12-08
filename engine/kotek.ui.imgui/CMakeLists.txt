cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.imgui VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		find_package(imgui CONFIG REQUIRED)
		find_package(implot CONFIG REQUIRED)
		find_package(imguizmo CONFIG REQUIRED)
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_imgui.h"
	"include/kotek_ui_imgui_wrapper.h"
	"src/kotek_ui_imgui_wrapper.cpp"
	"src/main_ui_imgui_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.os)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.render.gl)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.math)
target_link_libraries(${PROJECT_NAME} PUBLIC imgui::imgui)
target_link_libraries(${PROJECT_NAME} PUBLIC implot::implot)
target_link_libraries(${PROJECT_NAME} PUBLIC imguizmo::imguizmo)