project('kotek.core.os', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_core_os.h', 'src/main_core_os_dll.cpp')
if 'WIN32'
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.os.win32'])
endif
if 'UNIX'
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.os.linux'])
endif
