cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.cpp VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(
		-DKOTEK_DEBUG
	)
endif()

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "")
	add_definitions(-DKOTEK_BUILD_TYPE ${CMAKE_BUILD_TYPE})
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#ifdef KOTEK_BUILD_TYPE
		#define KOTEK_USE_BUILD_TYPE ${KOTEK_BUILD_TYPE}
	#endif
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_cpp.h"
	"src/main_core_defines_static_cpp_dll.cpp")