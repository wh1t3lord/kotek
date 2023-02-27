project('kotek.core.filesystem.file_text', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_loader_file_text_json.h', 'src/kotek_loader_file_text_json.cpp', 'include/kotek_loader_file_text.h', 'src/kotek_loader_file_text.cpp', 'include/kotek_saver_file_text.h', 'src/kotek_saver_file_text.cpp', 'include/kotek_saver_file_text_json.h', 'src/kotek_saver_file_text_json.cpp', 'include/kotek_file_text.h', 'src/kotek_file_text.cpp', 'include/kotek_core_filesystem_file_text.h', 'src/main_core_filesystem_file_text_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.memory.cpu'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.json'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.io'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.enum'])
