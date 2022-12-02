#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_DEBUG
		#ifdef KOTEK_USE_MEMORY_LEAK_DETECTION_VLD
			#ifdef KOTEK_VLD_FOUND
				#include <vld.h>
			#endif
		#endif
	#endif
#endif