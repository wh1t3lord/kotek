project('kotek.render.shared.gl', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
to_include_render_graph_simplified_files = ['include/kotek_render_graph_simplified_types.h', 'include/kotek_render_graph_simplified_types_input.h', 'include/kotek_render_graph_simplified_types_output.h', 'src/kotek_render_graph_simplified_types.cpp', 'src/kotek_render_graph_simplified_types_input.cpp', 'src/kotek_render_graph_simplified_types_output.cpp']
PROJECT_NAME_lib = static_library(project_name, to_include_render_graph_simplified_files, 'include/kotek_render_shared_gl.h', 'include/kotek_render_data_types.h', 'include/kotek_render_format.h', 'src/kotek_render_data_types.cpp', 'src/main_render_shared_gl_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# source_group(['Render Graph/Simplified', 'FILES', to_include_render_graph_simplified_files])
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.gl.glad'])
