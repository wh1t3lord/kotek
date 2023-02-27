  project('kotek.ui.rmlui', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
  cmake_cxx_standard = '20'
  cmake_cxx_standard_required = 'ON'
  RmlUi_dep = dependency('RmlUi')
  PROJECT_NAME_lib = static_library(project_name, 'include/kotek_ui_game_ui_manager.h', 'src/kotek_ui_game_ui_manager.cpp', 'include/kotek_ui_rmlui_system_interface_glfw.h', 'src/kotek_ui_rmlui_system_interface_glfw.cpp', 'include/kotek_ui_rmlui_render_interface_gl3.h', 'src/kotek_ui_rmlui_render_interface_gl3.cpp', 'include/kotek_ui_rmlui.h', 'src/main_ui_rmlui_dll.cpp')
  if 'UNIX'
    # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
  endif
  if '${KOTEK_DEVELOPMENT_TYPE}', 'STREQUAL', 'STATIC'
    # target_compile_definitions([project_name, 'PUBLIC', '-DRMLUI_STATIC_LIB'])
  endif
  # target_link_libraries([project_name, 'PUBLIC', 'RmlCore', 'RmlDebugger'])
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.main_manager'])
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.api'])
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.assert'])
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.os'])
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.render.gl'])
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.render.gl.glad'])
  # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.window'])
