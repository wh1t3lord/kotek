project('kotek.game', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
if '${KOTEK_DEVELOPMENT_TYPE}', 'STREQUAL', 'STATIC'
  if '${KOTEK_USER_GAME_PROJECT_NAME}', 'STREQUAL', ''
    # message(['FATAL_ERROR', 'specify KOTEK_USER_GAME_PROJECT_NAME of folder where your root source directory is located. e.g. see sandbox example https://gitlab.com/wh1t3lord/sandbox'])
  endif
  # include_directories('../../../${KOTEK_USER_GAME_PROJECT_NAME}')
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_engine.h', 'include/kotek_game.h', 'src/kotek_update.cpp', 'include/kotek_callbacks.h', 'src/main_game_dll.cpp')
# target_precompile_headers([project_name, 'PRIVATE', '$<$<COMPILE_LANGUAGE:CXX>:<kotek.pch/pch.h>>'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.render'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.ui'])
if '${KOTEK_DEVELOPMENT_TYPE}', 'STREQUAL', 'STATIC'
  if '${KOTEK_USER_GAME_MODULE_FOR_LINK_NAME}', 'STREQUAL', ''
    # message(['FATAL_ERROR', 'you must specify KOTEK_USER_GAME_MODULE_FOR_LINK_NAME for linking to kotek.game project. See sandbox example https://gitlab.com/wh1t3lord/sandbox'])
  endif
  # target_link_libraries([project_name, 'PUBLIC', kotek_user_game_module_for_link_name])
endif
