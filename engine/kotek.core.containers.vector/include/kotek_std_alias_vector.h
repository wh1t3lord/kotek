#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/vector.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <vector>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/vector.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
template <typename Type>
using vector =
	boost::container::vector<Type, KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>;
#elif defined(KOTEK_USE_STD_LIBRARY)
template <typename Type>
using vector = std::vector<Type, KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template<typename Type, size_t Size>
using static_vector = etl::vector<Type, Size>;
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK