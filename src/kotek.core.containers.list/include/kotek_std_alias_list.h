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
template <typename Type, size_t NotInUseArgument = 0>
using list = std::list<Type, KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, size_t Size>
using static_list = etl::list<Type, Size>;
#else
#endif

KOTEK_END_NAMESPACE_KTK

template <typename Type, size_t NotInUseArgument = 0>
using list_t = KUN_KOTEK KUN_KTK list<Type, NotInUseArgument>;

template <typename Type, size_t Size>
using static_list_t = KUN_KOTEK KUN_KTK static_list<Type, Size>;

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

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(
	std::is_same_v<kun_kotek kun_ktk static_list<bool, 1>, ktk_list<bool, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ postfix it means that "
	"this list "
	"container is expected as static_list implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(
	std::is_same_v<kun_kotek kun_ktk list<bool, 1>, ktk_list<bool, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ postfix and hybrid_ "
	"postfix it means that "
	"this list "
	"container is expected as list implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_list<bool, 1>, ktk_list<bool, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ postfix it means that "
	"this list "
	"container is expected as hybrid_list implementation");
#else
	#error unknown configuration, kotek supports three configurations: DYN (dynamic), EMB (static), HYB (hybrid)
#endif