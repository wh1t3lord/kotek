cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.utility VERSION 1 LANGUAGES CXX)

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

set(to_include_unit_tests "tests/kotek_std_utility_tests.cpp")

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_utility.h"
	"src/kotek_std_utility.cpp"
	"include/kotek_std_utility_variant.h"
	"include/kotek_std_utility_function.h"
	"include/kotek_std_utility_hash.h"
	"include/kotek_core_utility.h"
	${to_include_unit_tests}
	"src/main_core_utility_dll.cpp"
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

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.math)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.variant)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.function)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem.path)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)