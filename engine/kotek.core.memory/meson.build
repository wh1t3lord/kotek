project('kotek.core.memory', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_core_memory.h', 'src/main_core_memory_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.memory.cpu'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.memory.gpu'])
