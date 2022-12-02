cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.os.linux VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (UNIX)
	message("[${PROJECT_NAME}]: platform is 'UNIX'")

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#if defined(__linux__)
		#define KOTEK_PLATFORM_LINUX

		#ifdef KOTEK_USE_SDK
			#define WXUSINGDLL
			#define wxUSE_LISTCTRL 1

			#include <wx/wxprec.h>

			#ifndef WX_PRECOMP
				#include <wx/wx.h>
			#endif

			#include <wx/listctrl.h>
			#include <wx/aui/aui.h>
		#endif
	#endif
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_os_linux.h"
	"src/main_core_defines_static_os_linux_dll.cpp")

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)