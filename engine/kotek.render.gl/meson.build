project('kotek.render.gl', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
    Ktx_dep = dependency('Ktx')
    if '${KOTEK_DEVELOPMENT_TYPE_PACKAGES}', 'STREQUAL', 'STATIC', 'OR', 'UNIX'
      zstd_dep = dependency('zstd')
      Threads_dep = dependency('Threads')
    else
    endif
  else
    Ktx_dep = dependency('Ktx')
  endif
endif
to_include_render_graph_simplified_files = ['include/kotek_render_graph_simplified_node.h', 'src/kotek_render_graph_simplified_node.cpp', 'include/kotek_render_graph_simplified_resource_manager.h', 'src/kotek_render_graph_simplified_resource_manager.cpp', 'include/kotek_render_graph_simplified.h', 'src/kotek_render_graph_simplified.cpp', 'include/kotek_render_graph_simplified_render_pass.h', 'src/kotek_render_graph_simplified_render_pass.cpp', 'include/kotek_render_graph_simplified_builder.h', 'src/kotek_render_graph_simplified_builder.cpp']
to_include_managers_files = ['include/kotek_render_shader_manager.h', 'src/kotek_render_shader_manager.cpp', 'include/kotek_render_texture_manager.h', 'src/kotek_render_texture_manager.cpp', 'include/kotek_render_resource_manager.h', 'src/kotek_render_resource_manager.cpp']
to_include_core_files = ['include/kotek_render_device.h', 'src/kotek_render_device.cpp', 'include/kotek_render_swapchain.h', 'src/kotek_render_swapchain.cpp']
to_include_module_files = ['include/kotek_render_gl.h', 'src/main_render_gl_dll.cpp']
to_include_memory_management_files = ['include/kotek_render_static_buffer_pool.h', 'src/kotek_render_static_buffer_pool.cpp', 'include/kotek_render_static_buffer_pool_with_linear_allocator.h', 'src/kotek_render_static_buffer_pool_with_linear_allocator.cpp', 'include/kotek_render_allocator_ring.h', 'include/kotek_render_allocator_ring_with_tabs.h', 'src/kotek_render_allocator_ring_with_tabs.cpp', 'src/kotek_render_allocator_ring.cpp']
PROJECT_NAME_lib = static_library(project_name, to_include_render_graph_simplified_files, to_include_managers_files, to_include_core_files, to_include_module_files, to_include_memory_management_files)
if 'UNIX'
  # set_property(['TARGET', project_name, 'PROPERTY', 'POSITION_INDEPENDENT_CODE', 'ON'])
endif
# source_group(['Render Graph/Simplified', 'FILES', to_include_render_graph_simplified_files])
# source_group(['Managers', 'FILES', to_include_managers_files])
# source_group(['Core', 'FILES', to_include_core_files])
# source_group(['Module', 'FILES', to_include_module_files])
# source_group(['Memory management', 'FILES', to_include_memory_management_files])
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_compile_definitions([project_name, 'PUBLIC', 'KHRONOS_STATIC'])
# TODO: delete this
#target_include_directories(${PROJECT_NAME} PUBLIC "../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/include/")
#target_link_directories(${PROJECT_NAME} PUBLIC "../../${KOTEK_DEPS_FOLDER}/shaderc/${CMAKE_BUILD_TYPE}/lib/")
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.model'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.gl.glad'])
# target_link_libraries([project_name, 'PUBLIC', 'KTX::ktx'])
if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
  if '${KOTEK_DEVELOPMENT_TYPE_PACKAGES}', 'STREQUAL', 'STATIC', 'OR', 'UNIX'
    # target_link_libraries([project_name, 'PUBLIC', 'zstd::libzstd_static'])
    # target_link_libraries([project_name, 'PUBLIC', 'Threads::Threads'])
  else
  endif
endif
