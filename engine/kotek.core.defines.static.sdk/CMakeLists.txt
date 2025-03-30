cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.sdk VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# TODO: add wxWidgets, Qt and other SDK for including
if ("${KOTEK_SDK}" STREQUAL "ON")
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#ifdef KOTEK_SDK
		#define KOTEK_USE_SDK
	#endif

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
	")
else()
	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once")
endif()

add_library(${PROJECT_NAME} STATIC
	"include/kotek_std_preprocessors.h"
	"include/kotek_core_defines_static_sdk.h"
	"src/main_core_defines_static_sdk_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)