project('kotek.core.window.glfw', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
    glfw3_dep = dependency('glfw3')
  else
  endif
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_core_window_glfw.h', 'include/kotek_std_window.h', 'src/kotek_std_window.cpp', 'src/main_core_window_glfw_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
  # target_link_libraries([project_name, 'PRIVATE', 'glfw'])
else
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.api'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.memory.cpu'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.os'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.assert'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.main_manager'])
