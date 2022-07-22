#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <semaphore>
#else
#endif

// TODO: implement some functionality here
namespace Kotek
{
	namespace ktk
	{
		namespace mt
		{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
#else
#endif
		} // namespace mt
	}     // namespace ktk
} // namespace Kotek