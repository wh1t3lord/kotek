project('kotek.render.model.assimp', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
    assimp_dep = dependency('assimp')
  else
    assimp_dep = dependency('assimp')
  endif
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_render_model_assimp.h', 'include/kotek_model.h', 'src/kotek_model.cpp', 'src/main_render_model_assimp_dll.cpp')
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
# target_link_libraries([project_name, 'PUBLIC', 'assimp::assimp'])
