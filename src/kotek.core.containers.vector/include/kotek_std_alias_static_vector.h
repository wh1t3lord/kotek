#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/vector.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, size_t Size>
using static_vector = etl::vector<Type, Size>;
#endif
KOTEK_END_NAMESPACE_KTK

template <typename Type, KUN_KOTEK KUN_KTK size_t Size>
using static_vector_t = KUN_KOTEK KUN_KTK static_vector<Type, Size>;

KOTEK_END_NAMESPACE_KOTEK