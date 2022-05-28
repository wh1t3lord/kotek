#pragma once

#include <kotek.core.containers.deque/include/kotek_core_containers_deque.h>
#include <queue>

namespace Kotek
{
	namespace ktk
	{
		template <typename Type>
		using queue = std::queue<Type, deque<Type>>;
	}
} // namespace Kotek