project('kotek.core.profilers', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_CPU_PROFILER}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
    if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
      Tracy_dep = dependency('Tracy')
    else
      Tracy_dep = dependency('Tracy')
    endif
  endif
else
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_core_profilers.h', 'include/kotek_profiler.h', 'src/kotek_profiler.cpp', 'src/main_core_profilers_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.profilers'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.profilers.cpu'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.profilers.gpu'])
if '${KOTEK_CPU_PROFILER}', 'STREQUAL', 'ON'
  # target_link_libraries([project_name, 'PUBLIC', 'Tracy::TracyClient'])
endif
