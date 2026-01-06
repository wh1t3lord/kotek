cmake_minimum_required(VERSION 3.21)

project(kotek.core.enum.core VERSION 1 LANGUAGES CXX)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)




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

add_library(${PROJECT_NAME} STATIC
	"include/kotek_enum.h"
	"include/kotek_translation.h"
	"include/kotek_core_enum_core.h"
	"src/kotek_translation.cpp"
	"src/main_core_enum_core_dll.cpp"
	"tests/kotek_core_enum_core_test_translation.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/enum")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.types.numerics)
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)

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