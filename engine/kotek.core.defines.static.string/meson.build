project('kotek.core.defines.static.string', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_UNICODE}', 'STREQUAL', ''
  kotek_unicode = 'ON'
endif
# message('[${PROJECT_NAME}]: UNICODE is '${KOTEK_UNICODE}'')
if '${KOTEK_UNICODE}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DUNICODE', '-D_UNICODE', '-DKOTEK_UNICODE'])
endif
if '${KOTEK_UNICODE}', 'STREQUAL', 'ON'
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

	#ifdef KOTEK_UNICODE
		#define KOTEK_USE_UNICODE
	#endif
	'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_string.h', 'src/main_core_defines_static_string_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
