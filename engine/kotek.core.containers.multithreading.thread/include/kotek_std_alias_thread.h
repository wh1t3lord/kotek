#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <thread>
#else
#endif

namespace Kotek
{
	namespace ktk
	{
		namespace mt
		{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
			using thread = std::thread;
#else
#endif
		} // namespace mt
	}     // namespace ktk
} // namespace Kotek