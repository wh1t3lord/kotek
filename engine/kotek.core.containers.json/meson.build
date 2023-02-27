project('kotek.core.containers.json', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
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
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_alias_json.h', 'include/kotek_std_json.h', 'src/kotek_std_json.cpp', 'include/kotek_core_containers_json.h', 'src/main_core_containers_json_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
if '${KOTEK_STD_LIBRARY}', 'STREQUAL', 'BOOST'
  # target_link_libraries([project_name, 'PUBLIC', 'Boost::boost', 'Boost::json'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.message'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.assert'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.string'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.vector'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.any'])
