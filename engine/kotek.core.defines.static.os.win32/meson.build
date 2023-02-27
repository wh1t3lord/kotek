project('kotek.core.defines.static.os.win32', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_WINDOW_LIBRARY}', 'STREQUAL', ''
  kotek_window_library = ['GLFW', 'CACHE', 'INTERNAL', '']
endif
# list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_WINDOW_LIBRARY_${KOTEK_WINDOW_LIBRARY}', '-DKOTEK_PLATFORM_WINDOWS'])
kotek_window_library_name = '${KOTEK_WINDOW_LIBRARY}'
# message('[${PROJECT_NAME}]: window library is [${KOTEK_WINDOW_LIBRARY}]')
if 'WIN32'
  # message('[${PROJECT_NAME}]: platform 'Windows NT'')
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

	#if defined(_WIN32) || defined(_WIN64)
                #define KOTEK_USE_PLATFORM_WINDOWS
		#define WIN32_LEAN_AND_MEAN

		#ifdef KOTEK_WINDOW_LIBRARY_GLFW
			#define KOTEK_USE_WINDOW_LIBRARY_GLFW
		#endif

		#ifdef KOTEK_WINDOW_LIBRARY_SDL
			#define KOTEK_USE_WINDOW_LIBRARY_SDL
			#error TODO connect sdl to project and add switching between libraries
		#endif

		#define KOTEK_WINDOW_LIBRARY_NAME ${KOTEK_WINDOW_LIBRARY_NAME}
	#endif
	'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_os_win32.h', 'src/main_core_defines_static_os_win32_dll.cpp')
if 'WIN32'
  # target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
