cmake_minimum_required(VERSION 3.19.3)

project(kotek.core.defines.static.os.linux VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ("${KOTEK_WINDOW_LIBRARY}" STREQUAL "")
	set(KOTEK_WINDOW_LIBRARY "GLFW" CACHE INTERNAL "")
endif()

list(APPEND KOTEK_OUTPUT_FLAGS -DKOTEK_WINDOW_LIBRARY_${KOTEK_WINDOW_LIBRARY} -DKOTEK_PLATFORM_LINUX)
set(KOTEK_WINDOW_LIBRARY_NAME "${KOTEK_WINDOW_LIBRARY}")

message("[${PROJECT_NAME}]: window library is [${KOTEK_WINDOW_LIBRARY}]")

if (UNIX)
	message("[${PROJECT_NAME}]: platform is 'UNIX'")

	file(WRITE ${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS} "#pragma once

	#if defined(__linux__)
                #define KOTEK_USE_PLATFORM_LINUX

		#ifdef KOTEK_WINDOW_LIBRARY_GLFW
			#define KOTEK_USE_WINDOW_LIBRARY_GLFW
		#endif

		#ifdef KOTEK_WINDOW_LIBRARY_SDL
			#define KOTEK_USE_WINDOW_LIBRARY_SDL
			#error TODO connect sdl to project and add switching between libraries
		#endif

		#define KOTEK_WINDOW_LIBRARY_NAME ${KOTEK_WINDOW_LIBRARY_NAME}

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
	
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/core/macros/independent")
if (UNIX)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ${KOTEK_OUTPUT_FLAGS})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC kotek.core.defines.static.cpp)
