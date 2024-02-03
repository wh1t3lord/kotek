#pragma once

#include <kotek.core.containers.deque/include/kotek_core_containers_deque.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <queue>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/queue.h>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
template <typename Type, size_t NotInUseArgument = 0>
using queue = std::queue<Type, deque<Type>>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, size_t Size>
using static_queue = etl::queue<Type, Size>;
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_queue \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_queue
	#define KTK_QUEUE \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_queue
	#define ktkQueue \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_queue
#else
	#define ktk_queue KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK queue
	#define KTK_QUEUE KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK queue
	#define ktkQueue KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK queue
#endif