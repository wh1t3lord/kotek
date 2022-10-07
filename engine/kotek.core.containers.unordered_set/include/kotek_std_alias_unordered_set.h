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

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
template <class Key, class Hash = hash<Key>,
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

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KTK