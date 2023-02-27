project('kotek.render.software', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
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
to_include_render_graph_simplified_files = 
to_include_managers_files = 
to_include_core_files = 
to_include_module_files = ['include/kotek_render_software.h', 'src/main_render_software_dll.cpp']
to_include_memory_management_files = 
PROJECT_NAME_lib = static_library(project_name, to_include_render_graph_simplified_files, to_include_managers_files, to_include_core_files, to_include_module_files, to_include_memory_management_files)
# source_group(['Render Graph/Simplified', 'FILES', to_include_render_graph_simplified_files])
# source_group(['Managers', 'FILES', to_include_managers_files])
# source_group(['Core', 'FILES', to_include_core_files])
# source_group(['Module', 'FILES', to_include_module_files])
# source_group(['Memory management', 'FILES', to_include_memory_management_files])
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_compile_definitions([project_name, 'PUBLIC', 'KHRONOS_STATIC'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render.model'])
# target_link_libraries([project_name, 'PUBLIC', 'KTX::ktx'])
if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
  if '${KOTEK_DEVELOPMENT_TYPE_PACKAGES}', 'STREQUAL', 'STATIC', 'OR', 'UNIX'
    # target_link_libraries([project_name, 'PUBLIC', 'zstd::libzstd_static'])
    # target_link_libraries([project_name, 'PUBLIC', 'Threads::Threads'])
  else
  endif
endif
