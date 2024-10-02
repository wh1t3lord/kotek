cmake_minimum_required(VERSION 3.19.3)

project(kotek.ui.videoplayer.avif VERSION 1 LANGUAGES CXX)

# TODO: try to find the stuff from vcpkg, but you should add guard because it depends dav1d doesn't use cmake at all

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")

elseif("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(dav1d REQUIRED IMPORTED_TARGET dav1d)
else()
	message(FATAL_ERROR "provide implementation")
endif()


add_library(${PROJECT_NAME} STATIC
	"include/kotek_ui_videoplayer_avif.h"
	"src/main_ui_videoplayer_avif_dll.cpp"
	"include/kotek_ui_videoplayer.h"
	"src/kotek_ui_videoplayer.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")

elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
	target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::dav1d)
else()
	message(FATAL_ERROR "provide implementation")
endif()
