#pragma once

#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/unordered_map.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <unordered_map>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/unordered_map.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
#ifdef KOTEK_USE_BOOST_LIBRARY

template <class Key, class Type, size_t NotInUseArgument = 0,
	class Hash = hash<Key>, class Predicate = std::equal_to<Key>,
	class Allocator =
		KOTEK_USE_MEMORY_ALLOCATOR_CLASS<std::pair<const Key, Type>>>
using unordered_map =
	boost::unordered::unordered_map<Key, Type, Hash, Predicate, Allocator>;
#elif defined(KOTEK_USE_STD_LIBRARY)
template <class Key, class Type, class Hash = std::hash<Key>,
	class Predicate = std::equal_to<Key>,
	class Allocator =
		KOTEK_USE_MEMORY_ALLOCATOR_CLASS<std::pair<const Key, Type>>>
using unordered_map = std::unordered_map<Key, Type, Hash, Predicate, Allocator>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <class Key, class Type, size_t Size>
using static_unordered_map = etl::unordered_map<Key, Type, Size>;
#endif

KOTEK_END_NAMESPACE_KTK

template <class Key, class Type, size_t NotInUseArgument = 0,
	class Hash = KUN_KOTEK KUN_KTK hash<Key>,
	class Predicate = std::equal_to<Key>,
	class Allocator =
		KOTEK_USE_MEMORY_ALLOCATOR_CLASS<std::pair<const Key, Type>>>
using unordered_map_t = KUN_KOTEK KUN_KTK
	unordered_map<Key, Type, NotInUseArgument, Hash, Predicate, Allocator>;

template <class Key, class Type, size_t Size>
using static_unordered_map_t =
	KUN_KOTEK KUN_KTK static_unordered_map<Key, Type, Size>;

KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_unordered_map \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_map
	#define KTK_UNORDERED_MAP \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_map
	#define ktkUnorderedMap \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_map
#else
	#define ktk_unordered_map \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_map
	#define KTK_UNORDERED_MAP \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_map
	#define ktkUnorderedMap \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_mapkds
#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(
	std::is_same_v<kun_kotek kun_ktk static_unordered_map<bool, int, 1>,
		ktk_unordered_map<bool, int, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this unordered_map "
	"container is expected as static_unordered_map implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(std::is_same_v<kun_kotek kun_ktk unordered_map<bool, int, 1>,
				  ktk_unordered_map<bool, int, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this unordered_map "
	"container is expected as unordered_map implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_unordered_map<bool, int, 1>,
		ktk_unordered_map<bool, int, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this hybrid_unordered_map "
	"container is expected as hybrid_unordered_map implementation");
#else
	#error unknown configuration, kotek supports three configurations: DYN (dynamic), EMB (static), HYB (hybrid)
#endif