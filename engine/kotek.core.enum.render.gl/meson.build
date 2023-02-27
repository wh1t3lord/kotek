project('kotek.core.enum.render.gl', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_enum.h', 'include/kotek_translation.h', 'include/kotek_core_enum_render_gl.h', 'src/main_core_enum_render_gl_dll.cpp', 'src/kotek_translation.cpp')
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.types.numerics'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers.string'])
