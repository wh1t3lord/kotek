#pragma once

#include <kotek.core.containers.hash/include/kotek_core_containers_hash.h>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/unordered_map.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <class Key, class Type, size_t Size>
using static_unordered_map = etl::unordered_map<Key, Type, Size>;
#endif

KOTEK_END_NAMESPACE_KTK

template <class Key, class Type, size_t Size>
using static_unordered_map_t =
	KUN_KOTEK KUN_KTK static_unordered_map<Key, Type, Size>;

KOTEK_END_NAMESPACE_KOTEK