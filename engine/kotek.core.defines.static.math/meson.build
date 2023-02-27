project('kotek.core.defines.static.math', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_MATH_LIBRARY}', 'STREQUAL', ''
  if 'WIN32'
    kotek_math_library = ['DXM', 'CACHE', 'INTERNAL', '']
  else
    kotek_math_library = ['GLM', 'CACHE', 'INTERNAL', '']
  endif
endif
if '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'GLM'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_MATH_LIBRARY_GLM'])
elif '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'DXM'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_MATH_LIBRARY_DXM'])
elif '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'EIGEN'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_MATH_LIBRARY_EIGEN'])
endif
# message('[${PROJECT_NAME}]: math library is '${KOTEK_MATH_LIBRARY}'')
if 'NOT', '${KOTEK_MATH_LIBRARY}', 'STREQUAL', ''
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

	#ifdef KOTEK_MATH_LIBRARY_GLM
		#define KOTEK_USE_MATH_LIBRARY_GLM
	#elif defined(KOTEK_MATH_LIBRARY_DXM)
		#define KOTEK_USE_MATH_LIBRARY_DXM
	#else
		#error undefined math library. So it doesn't support by engine now
	#endif
	'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_math.h', 'src/main_core_defines_static_math_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
