cmake_minimum_required(VERSION 3.21)

project(kotek.core.utility VERSION 1 LANGUAGES CXX)




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

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Utility SHUTDOWN ShutdownModule_Core_Utility
	"include/kotek_std_utility.h"
	"src/kotek_std_utility.cpp"
	"include/kotek_std_utility_variant.h"
	"include/kotek_std_utility_function.h"
	"include/kotek_std_utility_hash.h"
	"include/kotek_core_utility.h"
	${to_include_unit_tests}
	"src/main_core_utility_dll.cpp"
)
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core")
if ("${KOTEK_DEPS_FOLDER}" STREQUAL "nuget")
	if ("${KOTEK_TESTS}" STREQUAL "ON")
		kotek_target_link_libraries(${PROJECT_NAME} PUBLIC 
			GTest::gtest 
			GTest::gmock
		)
	endif()
else()
	if ("${KOTEK_TESTS}" STREQUAL "ON")
		kotek_target_link_libraries(${PROJECT_NAME} PUBLIC 
			GTest::gtest 
			GTest::gmock
		)
	endif()
endif()

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.math)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.variant)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.function)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.vector)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.string)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.queue)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.containers.filesystem.path)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.message)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)