cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.profilers VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_CPU_PROFILER}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
		find_package(Tracy REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/Tracy")
	else()
		find_package(Tracy REQUIRED)
	endif()
else()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_profilers.h"
	"include/kotek_profiler.h"
	"src/kotek_profiler.cpp"
	"src/main_core_profilers_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.profilers)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.profilers.cpu)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.profilers.gpu)
target_link_libraries(${PROJECT_NAME} PUBLIC Tracy::TracyClient)