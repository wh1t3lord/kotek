project('kotek.core.casting', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_STD_LIBRARY}', 'STREQUAL', 'BOOST'
    if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
      Boost_dep = dependency('Boost')
    else
      Boost_dep = dependency('Boost')
    endif
  endif
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_core_casting.h', 'src/main_core_casting_dll.cpp')
if '${KOTEK_STD_LIBRARY}', 'STREQUAL', 'BOOST'
  # target_link_libraries([project_name, 'PUBLIC', 'Boost::boost'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.casting.string'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.casting.lexical'])
