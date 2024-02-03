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