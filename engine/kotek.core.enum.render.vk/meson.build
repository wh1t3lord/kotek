project('kotek.core.enum.render.vk', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_enum.h', 'include/kotek_core_enum_render_vk.h', 'src/main_core_enum_render_vk_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.types.numerics'])
