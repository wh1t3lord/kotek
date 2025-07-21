#pragma once

#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/unordered_set.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <unordered_set>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/unordered_set.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
template <class Key, size_t NotInUseArgument = 0, class Hash = hash<Key>,
	class Predicate = std::equal_to<Key>,
	class Allocator = KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Key>>
using unordered_set = boost::unordered_set<Key, Hash, Predicate, Allocator>;
#elif defined(KOTEK_USE_STD_LIBRARY)
template <class Key, class Hash = hash<Key>,
	class Predicate = std::equal_to<Key>,
	class Allocator = KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Key>>
using unordered_set = std::unordered_set<Key, Hash, Predicate, Allocator>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <class Key, size_t Size>
using static_unordered_set = etl::unordered_set<Key, Size>;
#endif

KOTEK_END_NAMESPACE_KTK

template <class Key, size_t NotInUseArgument = 0,
	class Hash = KUN_KOTEK KUN_KTK hash<Key>,
	class Predicate = std::equal_to<Key>,
	class Allocator = KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Key>>
using unordered_set_t = KUN_KOTEK KUN_KTK
	unordered_set<Key, NotInUseArgument, Hash, Predicate, Allocator>;

template <class Key, size_t Size>
using static_unordered_set_t =
	KUN_KOTEK KUN_KTK static_unordered_set<Key, Size>;

KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_unordered_set \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_set
	#define KTK_UNORDERED_SET \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_set
	#define ktkUnorderedSet \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_unordered_set
#else
	#define ktk_unordered_set \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_set
	#define KTK_UNORDERED_SET \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_set
	#define ktkUnorderedSet \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_set
#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(std::is_same_v<kun_kotek kun_ktk static_unordered_set<bool, 1>,
				  ktk_unordered_set<bool, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ prefix it means that "
	"this unordered_set "
	"container is expected as static_unordered_set implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(std::is_same_v<kun_kotek kun_ktk unordered_set<bool, 1>,
				  ktk_unordered_set<bool, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ prefix and hybrid_ "
	"prefix it means that "
	"this unordered_set "
	"container is expected as unordered_set implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(std::is_same_v<kun_kotek kun_ktk hybrid_unordered_set<bool, 1>,
				  ktk_unordered_set<bool, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ prefix it means that "
	"this unordered_set "
	"container is expected as hybrid_unordered_set implementation");
#else
	#error unknown configuration, kotek supports three configurations: DYN (dynamic), EMB (static), HYB (hybrid)
#endif