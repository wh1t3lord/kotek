project('kotek.core.memory.gpu', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_core_memory_gpu.h', 'src/main_core_memory_gpu_dll.cpp')
if '${KOTEK_MEMORY_LEAK_DETECTION}', 'STREQUAL', 'ON'
  if '${KOTEK_CPP_MEMORY_LEAK_LIBRARY}', 'STREQUAL', 'VLD'
    # target_link_libraries([project_name, 'PUBLIC', 'kotek.core.memory.vld'])
  endif
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.memory.gpu.vulkan'])
