cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.cpp VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_DEBUG)
endif()

if ("${KOTEK_STD_LIBRARY}" STREQUAL "")
	set(KOTEK_STD_LIBRARY "BOOST")
endif()

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_BOOST_LIBRARY)

	set(KOTEK_STD_LIBRARY_NAME "Boost")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_STD_LIBRARY)

	set(KOTEK_STD_LIBRARY_NAME "Standard library")
endif()

message("[Engine]: standard library is ${KOTEK_STD_LIBRARY_NAME}")

if (NOT "${CMAKE_BUILD_TYPE}" STREQUAL "")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_BUILD_TYPE)

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#ifdef KOTEK_BUILD_TYPE
		#define KOTEK_USE_CURRENT_BUILD_TYPE ${CMAKE_BUILD_TYPE}
	#endif
	")

	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
		#ifdef KOTEK_BUILD_TYPE
			#define KOTEK_USE_BUILD_TYPE_DEBUG
		#endif
		")
	endif()

	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
		file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
		#ifdef KOTEK_BUILD_TYPE
			#define KOTEK_USE_BUILD_TYPE_RELEASE
		#endif
		")
	endif()

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
		#ifdef KOTEK_BOOST_LIBRARY
			#define KOTEK_USE_BOOST_LIBRARY
		#endif

		#ifdef KOTEK_STD_LIBRARY
			#define KOTEK_USE_STD_LIBRARY
		#endif

		#define KOTEK_USE_STD_LIBRARY_NAME ${KOTEK_STD_LIBRARY_NAME}
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_cpp.h"
	"src/main_core_defines_static_cpp_dll.cpp")

target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})