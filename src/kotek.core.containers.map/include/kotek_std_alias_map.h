#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/map.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <map>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/map.h>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
template <class K, class V, size_t NotInUseArgument = 0, class P = std::less<K>,
	typename allocator =
		KOTEK_USE_MEMORY_ALLOCATOR_CLASS<std::pair<const K, V>>>
using map = boost::container::map<K, V, P, allocator>;
#elif defined(KOTEK_USE_STD_LIBRARY)
template <class K, class V, class P = std::less<K>,
	typename allocator =
		KOTEK_USE_MEMORY_ALLOCATOR_CLASS<std::pair<const K, V>>>
using map = std::map<K, V, P, allocator>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <class K, class V, size_t Size>
using static_map = etl::map<K, V, Size>;
#else
#endif

KOTEK_END_NAMESPACE_KTK

template <class K, class V, size_t NotInUseArgument = 0, class P = std::less<K>,
	typename allocator =
		KOTEK_USE_MEMORY_ALLOCATOR_CLASS<std::pair<const K, V>>>
using map_t = KUN_KOTEK KUN_KTK map<K, V, NotInUseArgument, P, allocator>;

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <class K, class V, size_t Size>
using static_map_t = KUN_KOTEK KUN_KTK static_map<K, V, Size>;
#endif

KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_map KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_map
	#define ktkMap KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_map
	#define KTK_MAP KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_map
#else
	#define ktk_map KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK map
	#define ktkMap KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK map
	#define KTK_MAP KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK map
#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(std::is_same_v<kun_kotek kun_ktk static_map<bool, int, 1>,
				  ktk_map<bool, int, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this map "
	"container is expected as static_map implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(
	std::is_same_v<kun_kotek kun_ktk map<bool, int, 1>, ktk_map<bool, int, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this map "
	"container is expected as map implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(std::is_same_v<kun_kotek kun_ktk hybrid_map<bool, int, 1>,
				  ktk_map<bool, int, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this map "
	"container is expected as hybrid_map implementation");
#else

#endif