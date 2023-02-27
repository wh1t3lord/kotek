    project('kotek.core.memory.vld', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
    cmake_cxx_standard = '20'
    cmake_cxx_standard_required = 'ON'
    PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_memory.h', 'include/kotek_core_memory_vld.h', 'src/main_core_memory_vld_dll.cpp')
    # add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
    if 'WIN32'
      if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
        if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
          # message('[${PROJECT_NAME}]: vcpkg doesn't support VLD package yet')
        else
          # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_VLD_FOUND'])
          # target_include_directories([project_name, 'PUBLIC', '../../${KOTEK_DEPS_FOLDER}/vld/include/'])
          # target_link_directories([project_name, 'PUBLIC', '../../${KOTEK_DEPS_FOLDER}/vld/lib/Win64/'])
        endif
      endif
    endif
    # target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
    # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
