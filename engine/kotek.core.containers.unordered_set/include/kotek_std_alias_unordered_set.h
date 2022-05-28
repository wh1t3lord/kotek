#pragma once

#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/unordered_set.hpp>
#else
	#include <unordered_set>
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		template <class Key, class Hash = hash<Key>,
			class Predicate = std::equal_to<Key>,
			class Allocator = mi_stl_allocator<Key>>
		using unordered_set =
			boost::unordered_set<Key, Hash, Predicate, Allocator>;
#else
		template <class Key, class Hash = hash<Key>,
			class Predicate = std::equal_to<Key>,
			class Allocator = mi_stl_allocator<Key>>
		using unordered_set =
			std::unordered_set<Key, Hash, Predicate, Allocator>;
#endif
	} // namespace ktk
} // namespace Kotek