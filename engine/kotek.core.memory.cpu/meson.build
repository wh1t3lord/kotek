project('kotek.core.memory.cpu', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
    if '${KOTEK_MEMORY_ALLOCATOR_CPU}', 'STREQUAL', 'MIMALLOC'
      mimalloc_dep = dependency('mimalloc')
    endif
  else
    if '${KOTEK_MEMORY_ALLOCATOR_CPU}', 'STREQUAL', 'MIMALLOC'
      mimalloc_dep = dependency('mimalloc')
    endif
  endif
endif
# message('[${PROJECT_NAME}]: memory allocator for CPU = ${KOTEK_MEMORY_ALLOCATOR_CPU}')
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_memory.h', 'include/kotek_core_memory_cpu.h', 'src/main_core_memory_cpu_dll.cpp', 'src/kotek_std_memory.cpp')
if '${KOTEK_DEVELOPMENT_TYPE_PACKAGES}', 'STREQUAL', 'STATIC'
  if '${KOTEK_MEMORY_ALLOCATOR_CPU}', 'STREQUAL', 'MIMALLOC'
    # target_link_libraries([project_name, 'PUBLIC', 'mimalloc-static'])
  endif
else
  if '${KOTEK_MEMORY_ALLOCATOR_CPU}', 'STREQUAL', 'MIMALLOC'
    # target_link_libraries([project_name, 'PUBLIC', 'mimalloc'])
  endif
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
if '${KOTEK_MEMORY_LEAK_DETECTION}', 'STREQUAL', 'ON'
  if '${KOTEK_CPP_MEMORY_LEAK_LIBRARY}', 'STREQUAL', 'VLD'
    # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.memory.vld'])
  endif
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.os'])
