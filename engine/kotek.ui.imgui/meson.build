project('kotek.ui.imgui', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
    imgui_dep = dependency('imgui')
    implot_dep = dependency('implot')
    imguizmo_dep = dependency('imguizmo')
  endif
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_ui_imgui.h', 'include/kotek_ui_imgui_wrapper.h', 'src/kotek_ui_imgui_wrapper.cpp', 'src/main_ui_imgui_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.api'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.main_manager'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.os'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.render.gl'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.assert'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.math'])
# target_link_libraries([project_name, 'PUBLIC', 'imgui::imgui'])
# target_link_libraries([project_name, 'PUBLIC', 'implot::implot'])
# target_link_libraries([project_name, 'PUBLIC', 'imguizmo::imguizmo'])
