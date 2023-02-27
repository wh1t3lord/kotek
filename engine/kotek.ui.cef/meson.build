  project('kotek.ui.cef', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
  cmake_cxx_standard = '20'
  cmake_cxx_standard_required = 'ON'
  CEF_dep = dependency('CEF')
  if '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'CEF'
    implementation_files_cef = ['include/kotek_ui_game_ui_manager.h', 'src/kotek_ui_game_ui_manager.cpp', 'include/kotek_ui_cef_application.h', 'src/kotek_ui_cef_application.cpp']
  else
    implementation_files_cef = ''
  endif
  PROJECT_NAME_lib = static_library(project_name, 'include/kotek_ui_cef.h', implementation_files_cef, 'src/main_ui_cef_dll.cpp')
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.main_manager'])
