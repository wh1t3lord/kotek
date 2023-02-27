project('kotek.core.console', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_console.h', 'src/kotek_console.cpp', 'include/kotek_core_console.h', 'src/main_core_console_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.api'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.vector'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.unordered_map'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.queue'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.pair'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.function'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.string'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.message'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.assert'])
