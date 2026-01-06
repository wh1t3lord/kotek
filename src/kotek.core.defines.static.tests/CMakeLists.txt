cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.tests VERSION 1 LANGUAGES CXX)




if ("${KOTEK_TESTS}" STREQUAL "")
	set(KOTEK_TESTS "ON" CACHE INTERNAL "")
endif()

message("[${PROJECT_NAME}]: TESTS is '${KOTEK_TESTS}'")
if ("${KOTEK_TESTS}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_TESTS)
elseif("${KOTEK_TESTS}" STREQUAL "OFF")
	set(KOTEK_TESTS_RUNTIME "OFF" CACHE INTERNAL "")
endif()

if ("${KOTEK_TESTS_RUNTIME}" STREQUAL "")
	set(KOTEK_TESTS_RUNTIME "ON" CACHE INTERNAL "")
endif()

message("[${PROJECT_NAME}]: TESTS use in runtime is '${KOTEK_TESTS_RUNTIME}'")

if ("${KOTEK_TESTS}" STREQUAL "ON")
	if ("${KOTEK_TESTS_RUNTIME}" STREQUAL "ON")
		list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_TESTS_RUNTIME)
	endif()
endif()

if ("${KOTEK_TESTS}" STREQUAL "ON")
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#ifdef KOTEK_TESTS
		#define KOTEK_USE_TESTS
		
		#ifdef KOTEK_TESTS_RUNTIME
			#define KOTEK_USE_TESTS_RUNTIME
		#endif
	#endif
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
	"include/kotek_core_defines_static_tests.h"
	"src/main_core_defines_static_tests_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)