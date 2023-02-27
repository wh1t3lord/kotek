project('kotek.core.defines.static.tests', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_TESTS}', 'STREQUAL', ''
  kotek_tests = 'ON'
endif
# message('[${PROJECT_NAME}]: TESTS is '${KOTEK_TESTS}'')
if '${KOTEK_TESTS}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_TESTS'])
elif '${KOTEK_TESTS}', 'STREQUAL', 'OFF'
  kotek_tests_runtime = 'OFF'
endif
if '${KOTEK_TESTS_RUNTIME}', 'STREQUAL', ''
  kotek_tests_runtime = 'ON'
endif
# message('[${PROJECT_NAME}]: TESTS use in runtime is '${KOTEK_TESTS_RUNTIME}'')
if '${KOTEK_TESTS}', 'STREQUAL', 'ON'
  if '${KOTEK_TESTS_RUNTIME}', 'STREQUAL', 'ON'
    # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_TESTS_RUNTIME'])
  endif
endif
if '${KOTEK_TESTS}', 'STREQUAL', 'ON'
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

	#ifdef KOTEK_TESTS
		#define KOTEK_USE_TESTS
		
		#ifdef KOTEK_TESTS_RUNTIME
			#define KOTEK_USE_TESTS_RUNTIME
		#endif
	#endif
	'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_tests.h', 'src/main_core_defines_static_tests_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
