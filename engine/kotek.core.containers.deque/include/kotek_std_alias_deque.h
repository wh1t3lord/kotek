#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/deque.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <deque>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/deque.h>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
template <typename Type, size_t NotInUseArgument = 0,
	typename Allocator = KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>
using deque = boost::container::deque<Type, Allocator>;
#elif defined(KOTEK_USE_STD_LIBRARY)
template <typename Type,
	typename Allocator = KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>
using deque = std::deque<Type, Allocator>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, size_t Size>
using static_deque = etl::deque<Type, Size>;
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_deque \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_deque
	#define ktkDeque \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_deque
	#define KTK_DEQUE \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_deque
#else
	#define ktk_deque KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK deque
	#define ktkDeque KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK deque
	#define KTK_DEQUE KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK deque
#endif