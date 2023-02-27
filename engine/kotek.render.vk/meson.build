project('kotek.render.vk', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
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
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_render_vk.h', 'include/kotek_render_allocator_ring.h', 'include/kotek_render_allocator_ring_with_tabs.h', 'src/kotek_render_allocator_ring.cpp', 'include/kotek_render_command_list_ring.h', 'src/kotek_render_command_list_ring.cpp', 'include/kotek_render_device.h', 'src/kotek_render_device.cpp', 'include/kotek_render_device_properties.h', 'src/kotek_render_device_properties.cpp', 'src/kotek_render_instance_properties.cpp', 'include/kotek_render_instance_properties.h', 'src/kotek_render_swapchain.cpp', 'include/kotek_render_swapchain.h', 'include/kotek_render_resource_manager.h', 'src/kotek_render_resource_manager.cpp', 'include/kotek_render_static_buffer_pool.h', 'src/kotek_render_static_buffer_pool.cpp', 'include/kotek_render_static_buffer_pool_with_linear_allocator.h', 'src/kotek_render_static_buffer_pool_with_linear_allocator.cpp', 'include/kotek_render_resource_view_heap.h', 'src/kotek_render_resource_view_heap.cpp', 'src/kotek_render_dynamic_buffer_ring.cpp', 'include/kotek_render_dynamic_buffer_ring.h', 'src/kotek_render_upload_heap.cpp', 'include/kotek_render_upload_heap.h', 'src/kotek_render_imgui_manager.cpp', 'include/kotek_render_imgui_manager.h', 'src/kotek_render_texture_manager.cpp', 'include/kotek_render_texture_manager.h', 'src/kotek_render_shader_manager.cpp', 'include/kotek_render_shader_manager.h', 'src/kotek_render_shader_cache_manager.cpp', 'include/kotek_render_shader_cache_manager.h', 'include/kotek_render_graph.h', 'src/kotek_render_graph.cpp', 'include/kotek_render_graph_resource_manager.h', 'src/kotek_render_graph_resource_manager.cpp', 'include/kotek_render_graph_builder.h', 'src/kotek_render_graph_builder.cpp', 'include/kotek_render_graph_data_types.h', 'src/kotek_render_graph_data_types.cpp', 'src/kotek_render_test_shader_manager.cpp', 'src/kotek_render_test_render_device.cpp', 'src/kotek_render_test_swapchain.cpp', 'include/kotek_render_helper_device.h', 'src/kotek_render_helper_device.cpp', 'include/kotek_render_helper_debug.h', 'src/kotek_render_helper_debug.cpp', 'include/kotek_render_helper_stats.h', 'src/kotek_render_helper_stats.cpp', 'src/spirv_reflect.cpp', 'include/spirv_reflect.h', 'include/vk_enum_string_helper.h', 'src/main_render_vk_dll.cpp')
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_compile_definitions([project_name, 'PUBLIC', 'KHRONOS_STATIC'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.model'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.ui.imgui'])
# target_link_libraries([project_name, 'PUBLIC', 'KTX::ktx'])
if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
  if '${KOTEK_DEVELOPMENT_TYPE_PACKAGES}', 'STREQUAL', 'STATIC', 'OR', 'UNIX'
    # target_link_libraries([project_name, 'PUBLIC', 'zstd::libzstd_static'])
    # target_link_libraries([project_name, 'PUBLIC', 'Threads::Threads'])
  else
  endif
endif
