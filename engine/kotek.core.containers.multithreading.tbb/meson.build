project('kotek.core.containers.multithreading.tbb', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
    TBB_dep = dependency('TBB')
  else
    TBB_dep = dependency('TBB')
  endif
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_tbb.h', 'include/kotek_core_containers_multithreading_tbb.h', 'src/main_core_containers_multithreading_tbb_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
# target_link_libraries([project_name, 'PUBLIC', 'TBB::tbb'])
