project('kotek.core.defines.static.sdk', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# TODO: add wxWidgets, Qt and other SDK for including
if '${KOTEK_SDK}', 'STREQUAL', 'ON'
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

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
	'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_sdk.h', 'src/main_core_defines_static_sdk_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
