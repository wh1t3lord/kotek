project('kotek.core.format', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if 'UNIX'
    if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
      fmt_dep = dependency('fmt')
    endif
  endif
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_alias_format.h', 'include/kotek_core_format.h', 'src/main_core_format_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.string'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.filesystem.path'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.text'])
if 'UNIX'
  # target_link_libraries([project_name, 'PUBLIC', 'fmt::fmt-header-only'])
endif
