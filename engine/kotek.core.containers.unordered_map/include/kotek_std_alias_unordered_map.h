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
#define ktk_unordered_map KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_map
#define KTK_UNORDERED_MAP KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_map
#define ktkUnorderedMap KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK unordered_mapkds
#endif