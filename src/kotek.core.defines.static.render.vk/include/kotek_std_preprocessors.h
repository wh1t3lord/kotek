#pragma once

#ifdef KOTEK_VULKAN
	#define KOTEK_USE_VULKAN

	#ifdef KOTEK_DEBUG
		#define VMA_DEBUG_LOG
	#endif

	#define KOTEK_USE_VULKAN_VERSION VK_API_VERSION_1_0
#endif
