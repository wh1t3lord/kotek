#pragma once

#include <kotek.core.containers.deque/include/kotek_core_containers_deque.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <queue>
#else
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
		template <typename Type>
		using queue = std::queue<Type, deque<Type>>;
#else
#endif
	} // namespace ktk
} // namespace Kotek