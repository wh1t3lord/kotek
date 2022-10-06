#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/map.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <map>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
template <class K, class V, class P = std::less<K>,
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

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK