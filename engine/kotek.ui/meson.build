project('kotek.ui', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_ui.h', 'src/main_ui_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.ui.imgui'])
if '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'CEF'
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.ui.cef'])
elif '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'RMLUI'
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.ui.rmlui'])
endif
