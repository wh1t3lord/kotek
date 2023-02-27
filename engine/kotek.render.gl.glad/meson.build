project('kotek.render.gl.glad', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEVELOPMENT_TYPE}' == 'SHARED'
  # list(['APPEND', 'KOTEK_OUTPUT_PRIVATE_FLAGS', '-DGLAD_GLAPI_EXPORT_BUILD'])
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DGLAD_GLAPI_EXPORT'])
endif
# This is for preventing other projects that doesn't need a glad at all search for <glad/glad.h> header, because it means that we break the connection between libraries and we need to create some sort of visibility where other libraries that doesn't have a target_link_libraries with this library search for glad/glad.h
# list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_GLAD_PREPROCESSOR_VISIBILITY'])
PROJECT_NAME_lib = library(project_name, kotek_development_type, 'include/glad/glad.h', 'include/KHR/khrplatform.h', 'src/glad.cpp', 'include/kotek_render_gl_glad.h', 'src/main_render_gl_glad_dll.cpp')
if '${KOTEK_DEVELOPMENT_TYPE}' == 'SHARED'
  # target_compile_definitions([project_name, 'PRIVATE', kotek_output_private_flags])
endif
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_include_directories([project_name, 'PUBLIC', '${CMAKE_CURRENT_SOURCE_DIR}/include/'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.render.gl'])
