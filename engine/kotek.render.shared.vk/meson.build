project('kotek.render.shared.vk', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
Vulkan_dep = dependency('Vulkan')
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_render_shared_vk.h', 'src/main_render_shared_vk_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
