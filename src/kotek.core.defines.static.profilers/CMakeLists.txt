cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.profilers VERSION 1 LANGUAGES CXX)




if ("${KOTEK_CPU_PROFILER}" STREQUAL "")
	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		set(KOTEK_CPU_PROFILER "OFF" CACHE INTERNAL "")
	else()
		set(KOTEK_CPU_PROFILER "ON" CACHE INTERNAL "")
	endif()
endif()

message("[${PROJECT_NAME}]: CPU Profiler is '${KOTEK_CPU_PROFILER}'")
if ("${KOTEK_CPU_PROFILER}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_CPU_PROFILER)
	list(APPEND KOTEK_OUTPUT_FLAGS -DTRACY_ENABLE)
	list(APPEND KOTEK_OUTPUT_FLAGS -DTRACY_DELAYED_INIT)
	list(APPEND KOTEK_OUTPUT_FLAGS -DTRACY_MANUAL_LIFETIME)
endif()

if ("${KOTEK_GPU_PROFILER}" STREQUAL "")
	if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
		set(KOTEK_GPU_PROFILER "OFF" CACHE INTERNAL "")
	else()
		set(KOTEK_GPU_PROFILER "ON" CACHE INTERNAL "")
	endif()
endif()

message("[${PROJECT_NAME}]: GPU Profiler is '${KOTEK_GPU_PROFILER}'")
if ("${KOTEK_GPU_PROFILER}" STREQUAL "ON")
	list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_GPU_PROFILER)
endif()

if ("${KOTEK_CPU_PROFILER}" STREQUAL "ON")
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "

#ifdef KOTEK_CPU_PROFILER
	#define KOTEK_USE_CPU_PROFILER
#endif
	")
else()
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "")
endif()

if ("${KOTEK_GPU_PROFILER}" STREQUAL "ON")
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "

#ifdef KOTEK_GPU_PROFILER
	#define KOTEK_USE_GPU_PROFILER
#endif
	")	
else()
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "")
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static_Profilers SHUTDOWN ShutdownModule_Core_Defines_Static_Profilers
	"${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
	"include/kotek_core_defines_static_profilers.h"
	"src/main_core_defines_static_profilers_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})

kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)