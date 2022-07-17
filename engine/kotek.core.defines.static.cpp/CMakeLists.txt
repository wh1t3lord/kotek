cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.cpp VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_DEBUG)
endif()

if ("${KOTEK_STD_LIBRARY}" STREQUAL "")
	set(KOTEK_STD_LIBRARY "BOOST" CACHE INTERNAL "")
endif()

message("[Engine]: KOTEK_STD_LIBRARY=${KOTEK_STD_LIBRARY}")

if ("${KOTEK_STD_LIBRARY}" STREQUAL "BOOST")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_BOOST_LIBRARY)

	set(KOTEK_STD_LIBRARY_NAME "Boost")
else()
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_STD_LIBRARY)

	set(KOTEK_STD_LIBRARY_NAME "Standard library")
endif()

if ("${KOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_HIDE_DISABLE_WARNINGS_PREPROCESSOR)
endif()

if ("${KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR)
endif()

if ("${KOTEK_CPP_KEYWORD_NOEXCEPT}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_NOEXCEPT "noexcept")
endif()

if ("${KOTEK_CPP_KEYWORD_INLINE}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_INLINE "inline")
endif()

if ("${KOTEK_CPP_KEYWORD_CONSTEXPR}" STREQUAL "")
	set(KOTEK_CPP_KEYWORD_CONSTEXPR "constexpr")
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

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
#ifndef KOTEK_HIDE_CPP_DISABLE_ALL_WARNINGS_PREPROCESSOR
	#ifdef _WIN32
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH _Pragma(\"warning(push,0)\")
	#elif __clang__
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH           \
			_Pragma(\"clang diagnostic push\")                  \
				_Pragma(\"clang diagnostic ignored \"-Wall\"\") \
					_Pragma(\"clang diagnostic ignored \"-Wextra\"\")
	#elif __GNUC__
		#error Not implemented for GCC
	#else
		#error Unknown compiler send the issue to authors!
	#endif

	#ifdef _WIN32
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP _Pragma(\"warning(pop)\")
	#elif __clang__
		#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP \
			_Pragma(\"clang diagnostic pop\")
	#elif __GNUC__
		#error Not implemented for GCC
	#else
		#error Unknown compiler send the issue to authors!
	#endif
#else
	#define KOTEK_CPP_DISABLE_ALL_WARNINGS_PUSH
	#define KOTEK_CPP_DISABLE_ALL_WARNINGS_POP
#endif
	")

	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "
	#ifndef KOTEK_HIDE_CPP_KEYWORD_PREPROCESSOR
		#define KOTEK_CPP_KEYWORD_CONSTEXPR ${KOTEK_CPP_KEYWORD_CONSTEXPR}
		#define KOTEK_CPP_KEYWORD_INLINE ${KOTEK_CPP_KEYWORD_INLINE}
		#define KOTEK_CPP_KEYWORD_NOEXCEPT ${KOTEK_CPP_KEYWORD_NOEXCEPT} 
	#else
		#define KOTEK_CPP_KEYWORD_CONSTEXPR
		#define KOTEK_CPP_KEYWORD_INLINE
		#define KOTEK_CPP_KEYWORD_NOEXCEPT
	#endif
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_cpp.h"
	"src/main_core_defines_static_cpp_dll.cpp")

target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})