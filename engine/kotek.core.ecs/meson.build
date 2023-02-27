project('kotek.core.ecs', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
EnTT_dep = dependency('EnTT')
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_component_allocator.h', 'include/kotek_core_ecs.h', 'src/main_core_ecs_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.api'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.vector'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.unordered_map'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.assert'])
# target_link_libraries([project_name, 'PUBLIC', 'EnTT::EnTT'])
