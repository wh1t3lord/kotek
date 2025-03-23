cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.resource_manager.streaming VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_DEPS_FOLDER_ENABLE}" STREQUAL "ON")
	if ("${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg")
		if ("${KOTEK_TESTS}" STREQUAL "ON")
			find_package(GTest CONFIG REQUIRED)
		endif()
	elseif ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
		if ("${KOTEK_TESTS}" STREQUAL "ON")
			find_package(GTest CONFIG REQUIRED)
		endif()
	else()
		if ("${KOTEK_TESTS}" STREQUAL "ON")
			find_package(GTest REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/")
		endif()
	endif()
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_core_resource_manager_streaming.h"
	"include/kotek_resource_manager_streaming.h"
	"tests/kotek_core_resource_manager_test_streaming.cpp"
	"src/kotek_resource_manager_streaming.cpp"
	"src/main_core_resource_manager_streaming_dll.cpp")

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if ("${KOTEK_TESTS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			GTest::gtest 
			GTest::gmock
		)
	endif()
else()
	if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
		target_link_libraries(${PROJECT_NAME} PUBLIC glm::glm)
	elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
		target_link_libraries(${PROJECT_NAME} PUBLIC Microsoft::DirectXMath)
	endif()

	if ("${KOTEK_TESTS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			GTest::gtest 
			GTest::gmock
		)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.filesystem.file_text)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.multithreading.mutex)