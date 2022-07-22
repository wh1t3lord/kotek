#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <functional>
#else
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
		template <class T>
		using function = std::function<T>;
#else
#endif
	} // namespace ktk
} // namespace Kotek