project('kotek.core.enum.core', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_enum.h', 'include/kotek_translation.h', 'include/kotek_core_enum_core.h', 'src/kotek_translation.cpp', 'src/main_core_enum_core_dll.cpp', 'tests/kotek_core_enum_core_test_translation.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.types.numerics'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.string'])
