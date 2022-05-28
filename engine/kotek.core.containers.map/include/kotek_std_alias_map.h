#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/map.hpp>
#else
	#include <map>
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		template <class K, class V, class P = std::less<K>,
			typename allocator = mi_stl_allocator<std::pair<const K, V>>>
		using map = boost::container::map<K, V, P, allocator>;
#else
		template <class K, class V, class P = std::less<K>,
			typename allocator = mi_stl_allocator<std::pair<const K, V>>>
		using map = std::map<K, V, P, allocator>;
#endif
	} // namespace ktk
} // namespace Kotek