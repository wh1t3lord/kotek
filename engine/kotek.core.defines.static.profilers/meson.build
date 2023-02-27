project('kotek.core.defines.static.profilers', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_CPU_PROFILER}', 'STREQUAL', ''
  if '${CMAKE_BUILD_TYPE}', 'STREQUAL', 'Debug'
    kotek_cpu_profiler = ['OFF', 'CACHE', 'INTERNAL', '']
  else
    kotek_cpu_profiler = ['ON', 'CACHE', 'INTERNAL', '']
  endif
endif
# message('[${PROJECT_NAME}]: CPU Profiler is '${KOTEK_CPU_PROFILER}'')
if '${KOTEK_CPU_PROFILER}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_CPU_PROFILER'])
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DTRACY_ENABLE'])
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DTRACY_DELAYED_INIT'])
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DTRACY_MANUAL_LIFETIME'])
endif
if '${KOTEK_GPU_PROFILER}', 'STREQUAL', ''
  if '${CMAKE_BUILD_TYPE}', 'STREQUAL', 'Debug'
    kotek_gpu_profiler = ['OFF', 'CACHE', 'INTERNAL', '']
  else
    kotek_gpu_profiler = ['ON', 'CACHE', 'INTERNAL', '']
  endif
endif
# message('[${PROJECT_NAME}]: GPU Profiler is '${KOTEK_GPU_PROFILER}'')
if '${KOTEK_GPU_PROFILER}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_GPU_PROFILER'])
endif
if '${KOTEK_CPU_PROFILER}', 'STREQUAL', 'ON'
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

#ifdef KOTEK_CPU_PROFILER
	#define KOTEK_USE_CPU_PROFILER
#endif
	'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
if '${KOTEK_GPU_PROFILER}', 'STREQUAL', 'ON'
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

#ifdef KOTEK_GPU_PROFILER
	#define KOTEK_USE_GPU_PROFILER
#endif
	'])
else
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_profilers.h', 'src/main_core_defines_static_profilers_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
