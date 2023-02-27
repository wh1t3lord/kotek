project('kotek.core.defines.static.render.vk', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_VULKAN}', 'STREQUAL', ''
  kotek_vulkan = ['ON', 'CACHE', 'INTERNAL', '']
endif
if '${KOTEK_VULKAN}', 'STREQUAL', 'ON'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_VULKAN'])
endif
if '${KOTEK_VULKAN_VERSION}', 'STREQUAL', ''
  kotek_vulkan_version = '1_0'
endif
# message('[${PROJECT_NAME}]: Vulkan is '${KOTEK_VULKAN}'')
# file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

#ifdef KOTEK_VULKAN
	#define KOTEK_USE_VULKAN

	#ifdef KOTEK_DEBUG
		#define VMA_DEBUG_LOG
	#endif

	#define KOTEK_USE_VULKAN_VERSION VK_API_VERSION_${KOTEK_VULKAN_VERSION}
#endif
'])
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_render_vk.h', 'src/main_core_defines_static_render_vk_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
