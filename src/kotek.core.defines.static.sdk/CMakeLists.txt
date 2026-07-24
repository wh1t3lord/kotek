cmake_minimum_required(VERSION 3.21)

project(kotek.core.defines.static.sdk VERSION 1 LANGUAGES CXX)




# TODO: add wxWidgets, Qt and other SDK for including
if ("${KOTEK_SDK}" STREQUAL "ON")
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "

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
	file(APPEND ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "")
endif()

kotek_add_library(${PROJECT_NAME} INIT InitializeModule_Core_Defines_Static_SDK SHUTDOWN ShutdownModule_Core_Defines_Static_SDK
	"${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}"
	"include/kotek_core_defines_static_sdk.h"
	"src/main_core_defines_static_sdk_dll.cpp")
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
kotek_target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)