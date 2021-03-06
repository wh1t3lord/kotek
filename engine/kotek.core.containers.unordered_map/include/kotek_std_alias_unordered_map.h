#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/unordered_map.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <unordered_map>
#else
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		template <class Key, class Type, class Hash = boost::hash<Key>,
			class Predicate = std::equal_to<Key>,
			class Allocator =
				KOTEK_USE_MEMORY_ALLOCATOR_CLASS<std::pair<const Key, Type>>>
		using unordered_map = boost::unordered::unordered_map<Key, Type, Hash,
			Predicate, Allocator>;
#elif defined(KOTEK_USE_STD_LIBRARY)
		template <class Key, class Type, class Hash = std::hash<Key>,
			class Predicate = std::equal_to<Key>,
			class Allocator =
				KOTEK_USE_MEMORY_ALLOCATOR_CLASS<std::pair<const Key, Type>>>
		using unordered_map =
			std::unordered_map<Key, Type, Hash, Predicate, Allocator>;
#else
#endif
	} // namespace ktk
} // namespace Kotek