project('kotek.core.os.linux', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  # TODO: add SDL
  if '${KOTEK_WINDOW_LIBRARY}', 'STREQUAL', 'GLFW'
    if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
      glfw3_dep = dependency('glfw3')
    else
      glfw3_dep = dependency('glfw3')
    endif
  endif
endif
if '${KOTEK_VULKAN}', 'STREQUAL', 'ON'
  Vulkan_dep = dependency('Vulkan')
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_os.h', 'include/kotek_core_os_linux.h', 'src/main_core_os_linux_dll.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.render'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.os.linux'])
if '${KOTEK_VULKAN}', 'STREQUAL', 'ON'
  # target_link_libraries([project_name, 'PUBLIC', 'Vulkan::Vulkan'])
endif
if '${KOTEK_WINDOW_LIBRARY}', 'STREQUAL', 'GLFW'
  # target_link_libraries([project_name, 'PUBLIC', 'glfw'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.gl.glad'])
