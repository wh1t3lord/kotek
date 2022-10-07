cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.string VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_UNICODE}" STREQUAL "")
	set(KOTEK_UNICODE "ON")
endif()

message("[Engine]: UNICODE is '${KOTEK_UNICODE}'")

if("${KOTEK_UNICODE}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DUNICODE -D_UNICODE -DKOTEK_UNICODE)
endif()

if ("${KOTEK_UNICODE}" STREQUAL "ON")
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#ifdef KOTEK_UNICODE
		#define KOTEK_USE_UNICODE
	#endif
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_string.h"
	"src/main_core_defines_static_string_dll.cpp")

target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)