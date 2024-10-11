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