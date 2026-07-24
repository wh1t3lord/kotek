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
template <typename Type, unsigned char NotInUseArgument = 0>
using queue = std::queue<Type, deque<Type>>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, size_t Size>
using static_queue = etl::queue<Type, Size>;
#else
#endif

KOTEK_END_NAMESPACE_KTK

template <typename Type, unsigned char NotInUseArgument = 0>
using queue_t = KUN_KOTEK KUN_KTK queue<Type, NotInUseArgument>;

template <typename Type, size_t Size>
using static_queue_t = KUN_KOTEK KUN_KTK static_queue<Type, Size>;

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

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(
	std::is_same_v<kun_kotek kun_ktk static_queue<bool, 1>, ktk_queue<bool, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this queue "
	"container is expected as static_queue implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(
	std::is_same_v<kun_kotek kun_ktk queue<bool, 1>, ktk_queue<bool, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this queue "
	"container is expected as queue implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_queue<bool, 1>, ktk_queue<bool, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this queue "
	"container is expected as hybrid_queue implementation");
#else
	#error unknown configuration, kotek supports three configurations: DYN (dynamic), EMB (static), HYB (hybrid)
#endif