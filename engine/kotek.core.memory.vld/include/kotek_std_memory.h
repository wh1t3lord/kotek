#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_PLATFORM_WINDOWS
	#ifdef KOTEK_DEBUG
		#include <vld.h>
	#endif
#endif