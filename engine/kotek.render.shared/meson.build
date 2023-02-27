project('kotek.render.shared', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_render_shared.h', 'src/main_render_shared_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.shared.gl'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.shared.dx'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.shared.vk'])
