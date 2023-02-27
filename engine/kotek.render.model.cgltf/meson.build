project('kotek.render.model.cgltf', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
    # find_path(['CGLTF_INCLUDE_DIRS', 'cgltf.h'])
  else
  endif
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_loader_model.h', 'src/kotek_loader_model.cpp', 'include/kotek_render_model_cgltf.h', 'src/main_render_model_cgltf_dll.cpp')
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
  # target_include_directories([project_name, 'PUBLIC', cgltf_include_dirs])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
