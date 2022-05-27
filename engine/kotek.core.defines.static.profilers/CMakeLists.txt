cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.profilers VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_CPU_PROFILER}" STREQUAL "")
	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		set(KOTEK_CPU_PROFILER "OFF")
	else()
		set(KOTEK_CPU_PROFILER "ON")
	endif()
endif()

message("[Engine]: CPU Profiler is '${KOTEK_CPU_PROFILER}'")
if ("${KOTEK_CPU_PROFILER}" STREQUAL "ON")
	add_definitions(-DKOTEK_CPU_PROFILER)
	add_definitions(-DTRACY_ENABLE)
	add_definitions(-DTRACY_DELAYED_INIT)
	add_definitions(-DTRACY_MANUAL_LIFETIME)
endif()

if ("${KOTEK_GPU_PROFILER}" STREQUAL "")
	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		set(KOTEK_GPU_PROFILER "OFF")
	else()
		set(KOTEK_GPU_PROFILER "ON")
	endif()
endif()

message("[Engine]: GPU Profiler is '${KOTEK_GPU_PROFILER}'")
if ("${KOTEK_GPU_PROFILER}" STREQUAL "ON")
	add_definitions(-DKOTEK_GPU_PROFILER)
endif()

if ("${KOTEK_CPU_PROFILER}" STREQUAL "ON")
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

#ifdef KOTEK_CPU_PROFILER
	#define KOTEK_USE_CPU_PROFILER
#endif
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

if ("${KOTEK_GPU_PROFILER}" STREQUAL "ON")
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

#ifdef KOTEK_GPU_PROFILER
	#define KOTEK_USE_GPU_PROFILER
#endif
	")	
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_profilers.h"
	"src/main_core_defines_static_profilers_dll.cpp")