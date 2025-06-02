cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.math VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "")
	if (WIN32)
		set(KOTEK_MATH_LIBRARY "DXM" CACHE INTERNAL "")
	else()
		set(KOTEK_MATH_LIBRARY "GLM" CACHE INTERNAL "")
	endif()
endif()

if ("${KOTEK_MATH_LIBRARY}" STREQUAL "GLM")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_LIBRARY_GLM)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "DXM")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_LIBRARY_DXM)
elseif("${KOTEK_MATH_LIBRARY}" STREQUAL "EIGEN")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_MATH_LIBRARY_EIGEN)
endif()

message("[${PROJECT_NAME}]: math library is '${KOTEK_MATH_LIBRARY}'")

if (NOT "${KOTEK_MATH_LIBRARY}" STREQUAL "")
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#ifdef KOTEK_MATH_LIBRARY_GLM
		#define KOTEK_USE_MATH_LIBRARY_GLM
	#elif defined(KOTEK_MATH_LIBRARY_DXM)
		#define KOTEK_USE_MATH_LIBRARY_DXM
	#else
		#error undefined math library. So it doesn't support by engine now
	#endif
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_math.h"
	"src/main_core_defines_static_math_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)