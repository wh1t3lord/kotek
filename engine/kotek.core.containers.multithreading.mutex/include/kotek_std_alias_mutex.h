#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <mutex>
#else
#endif

namespace Kotek
{
	namespace ktk
	{
		namespace mt
		{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
			using mutex = std::mutex;

			template <typename Mutex>
			using lock_guard = std::lock_guard<Mutex>;
#else
#endif
		} // namespace mt
	}     // namespace ktk
} // namespace Kotek