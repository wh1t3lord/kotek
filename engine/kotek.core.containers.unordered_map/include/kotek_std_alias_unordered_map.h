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
		template <class K, class T, class H = boost::hash<K>,
			class P = std::equal_to<K>,
			class A = mi_stl_allocator<std::pair<const K, T>>>
		using unordered_map = boost::unordered::unordered_map<K, T, H, P, A>;
#elif defined(KOTEK_USE_STD_LIBRARY)
		template <class K, class T, class H = std::hash<K>,
			class P = std::equal_to<K>,
			class A = mi_stl_allocator<std::pair<const K, T>>>
		using unordered_map = std::unordered_map<K, T, H, P, A>;
#else
#endif
	} // namespace ktk
} // namespace Kotek