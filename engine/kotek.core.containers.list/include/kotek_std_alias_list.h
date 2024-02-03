#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/list.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <list>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/list.h>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_BOOST_LIBRARY
template <typename Type, size_t NotInUseArgument = 0>
using list =
	boost::container::list<Type, KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>;
#elif defined(KOTEK_USE_STD_LIBRARY)
template <typename Type>
using list = std::list<Type, KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, size_t Size>
using static_list = etl::list<Type, Size>;
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_list \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_list
	#define KTK_LIST \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_list
	#define ktkList \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_list
#else
	#define ktk_list KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK list
	#define KTK_LIST KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK list
	#define ktkList KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK list
#endif