project('kotek.core.defines.static.os.linux', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_WINDOW_LIBRARY}', 'STREQUAL', ''
  kotek_window_library = ['GLFW', 'CACHE', 'INTERNAL', '']
endif
# list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_WINDOW_LIBRARY_${KOTEK_WINDOW_LIBRARY}', '-DKOTEK_PLATFORM_LINUX'])
kotek_window_library_name = '${KOTEK_WINDOW_LIBRARY}'
# message('[${PROJECT_NAME}]: window library is [${KOTEK_WINDOW_LIBRARY}]')
if 'UNIX'
  # message('[${PROJECT_NAME}]: platform is 'UNIX'')
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

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
	'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_os_linux.h', 'src/main_core_defines_static_os_linux_dll.cpp')
if 'UNIX'
  # target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
