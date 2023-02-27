project('kotek.render', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_render.h', 'src/main_render_dll.cpp')
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.model'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.shared'])
if 'WIN32'
  # DEPRECATED: until you write the whole vulkan renderer
  #target_link_libraries(${PROJECT_NAME} kotek.render.dx12)
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.gl'])
# TODO: Vulkan you implement in the last stage of development. First gl and gl without shaderc!
#target_link_libraries(${PROJECT_NAME} PUBLIC kotek.render.vk) 
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.software'])
