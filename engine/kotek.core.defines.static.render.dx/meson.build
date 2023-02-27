project('kotek.core.defines.static.render.dx', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if 'WIN32'
  if '${KOTEK_DIRECTX}', 'STREQUAL', ''
    kotek_directx = ['ON', 'CACHE', 'INTERNAL', '']
  endif
  if '${KOTEK_DIRECTX}', 'STREQUAL', 'ON'
    # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_DIRECTX'])
    # if you set 12 it means we will add all directx versions or those who is equal or lower to "x" value
    kotek_directx_version = ['12', 'CACHE', 'INTERNAL', '']
  endif
  # message('[${PROJECT_NAME}]: DirectX is '${KOTEK_DIRECTX}'')
  if '${KOTEK_DIRECTX}', 'STREQUAL', 'ON'
    # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

		#ifdef KOTEK_DIRECTX
			#define KOTEK_USE_DIRECTX
			#define KOTEK_USE_DIRECTX_VERSION ${KOTEK_DIRECTX_VERSION}
		#endif
		'])
  else
    # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
  endif
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_core_defines_static_render_dx.h', 'include/kotek_std_preprocessors.h', 'src/main_core_defines_static_render_dx_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
