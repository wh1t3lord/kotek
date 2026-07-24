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
template <
	typename Type,
	size_t NotInUseArgument = 0,
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

template <typename Type, KUN_KOTEK KUN_KTK size_t NotInUseArgument = 0,
	typename Allocator = KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>
using deque_t = KUN_KOTEK KUN_KTK deque<Type, NotInUseArgument, Allocator>;

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, KUN_KOTEK KUN_KTK size_t Size>
using static_deque_t = KUN_KOTEK KUN_KTK static_deque<Type, Size>;
#endif

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

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(
	std::is_same_v<kun_kotek kun_ktk static_deque<bool, 1>, ktk_deque<bool, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ postfix it means that "
	"this deque "
	"container is expected as static_deque implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(
	std::is_same_v<kun_kotek kun_ktk deque<bool, 1>, ktk_deque<bool, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ postfix and hybrid_ "
	"postfix it means that "
	"this deque "
	"container is expected as deque implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_deque<bool, 1>, ktk_deque<bool, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ postfix it means that "
	"this deque "
	"container is expected as hybrid_deque implementation");
#else
	#error unknown configuration, kotek supports three configurations for library: DYN (dynamic), EMB (static), HYB (hybrid)
#endif