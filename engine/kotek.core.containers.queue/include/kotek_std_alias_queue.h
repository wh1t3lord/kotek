#pragma once

#include <kotek.core.containers.deque/include/kotek_core_containers_deque.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <queue>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
template <typename Type>
using queue = std::queue<Type, deque<Type>>;
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_KOTEK