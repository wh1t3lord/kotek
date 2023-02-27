project('kotek.core.engine_config', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_config.h', 'src/kotek_std_config.cpp', 'include/kotek_core_engine_config.h', 'src/main_core_engine_config_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.api'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.assert'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.dll'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.unordered_set'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.main_manager'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.constants.string'])
