cmake_minimum_required(VERSION 3.21)

project(kotek.core.input VERSION 1 LANGUAGES CXX)




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


kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Input SHUTDOWN ShutdownModule_Core_Input
	"include/kotek_input.h"
	"src/kotek_input.cpp"
	"include/kotek_core_input.h"
	"src/main_core_input_dll.cpp"
	"tests/kotek_core_test_input.cpp"
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

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.api)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.constants.window)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.main_manager)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines_dependent.assert)
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.memory.cpu)