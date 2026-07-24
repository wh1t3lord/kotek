#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/array.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <array>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/array.h>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
#ifdef KOTEK_USE_BOOST_LIBRARY

template <class T, ktk::size_t N>
using array = boost::array<T, N>;
#elif defined(KOTEK_USE_STD_LIBRARY)
template <class T, ktk::size_t N>
using array = std::array<T, N>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, size_t Size>
using static_array = etl::array<Type, Size>;
#else
#endif

KOTEK_END_NAMESPACE_KTK

template <class Type, KUN_KOTEK KUN_KTK size_t Size>
using array_t = KUN_KOTEK KUN_KTK array<Type, Size>;

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename Type, size_t Size>
using static_array_t = KUN_KOTEK KUN_KTK static_array<Type, Size>;
#endif

KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)
	#define ktk_array \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_array
	#define ktkArray \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_array
	#define KTK_ARRAY \
		KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK static_array
#else
	#define ktk_array KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK array
	#define ktkArray KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK array
	#define KTK_ARRAY KOTEK_USE_NAMESPACE_KOTEK KOTEK_USE_NAMESPACE_KTK array
#endif

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
static_assert(
	std::is_same_v<kun_kotek kun_ktk static_array<bool, 1>, ktk_array<bool, 1>>,
	"If library type was defined as EMB (aka static) it means that all "
	"containers that "
	"kotek framework provides to use ARE with static_ postfix it means that "
	"this array "
	"container is expected as static_array implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_DYN)
static_assert(
	std::is_same_v<kun_kotek kun_ktk array<bool, 1>, ktk_array<bool, 1>>,
	"If library type was defined as DYN (aka dynamic) it means that all "
	"containers that "
	"kotek framework provides to use ARE WITHOUT static_ postfix and hybrid_ "
	"postfix it means that "
	"this array"
	"container is expected as array implementation");
#elif defined(KOTEK_USE_LIBRARY_TYPE_HYB)
static_assert(
	std::is_same_v<kun_kotek kun_ktk hybrid_array<bool, 1>, ktk_array<bool, 1>>,
	"If library type was defined as HYB (aka hybrid) it means that all "
	"containers that "
	"kotek framework provides to use ARE with hybrid_ postfix it means that "
	"this array "
	"container is expected as hybrid_array implementation");
#else
	#error unknown configuration, kotek supports three configurations of std library: DYN (dynamic), EMB (static), HYB (hybrid)
#endif