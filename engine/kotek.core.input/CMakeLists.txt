cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.input VERSION 1 LANGUAGES CXX)

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
	"include/kotek_input.h"
	"src/kotek_input.cpp"
	"include/kotek_core_input.h"
	"src/main_core_input_dll.cpp"
	"tests/kotek_core_test_input.cpp"
)

if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if ("${KOTEK_TESTS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			GTest::gtest 
			GTest::gmock
		)
	endif()
else()
	if ("${KOTEK_TESTS}" STREQUAL "ON")
		target_link_libraries(${PROJECT_NAME} PUBLIC 
			GTest::gtest 
			GTest::gmock
		)
	endif()
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.window)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)