cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.os.win32 VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
	message("[Engine]: platform 'WIN32'")

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#if defined(_WIN32) || defined(_WIN64)
		#define KOTEK_PLATFORM_WINDOWS
		#define WIN32_LEAN_AND_MEAN
	#endif
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_os_win32.h"
	"src/main_core_defines_static_os_win32_dll.cpp")