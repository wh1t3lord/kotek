project('kotek.core.defines.static.render.gl', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_OPENGL}', 'STREQUAL', ''
  kotek_opengl = ['ON', 'CACHE', 'INTERNAL', '']
endif
if '${KOTEK_OPENGL}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_OPENGL'])
  # TODO: think about supporting modern version and split two things, like if we specify for legacy version 3 it means will be added all project until modern
  # So if legacy = 1 it means from 1 version will be add to modern
  kotek_opengl_modern_version = '3'
  kotek_opengl_legacy_version = '3'
endif
# file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

#ifdef KOTEK_OPENGL
	#define KOTEK_USE_OPENGL
	#define KOTEK_USE_OPENGL_MODERN_VERSION ${KOTEK_OPENGL_MODERN_VERSION}
	#define KOTEK_USE_OPENGL_LEGACY_VERSION ${KOTEK_OPENGL_LEGACY_VERSION}
#endif
'])
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_render_gl.h', 'src/main_core_defines_static_render_gl_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
