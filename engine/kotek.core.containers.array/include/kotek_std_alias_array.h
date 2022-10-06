#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/array.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <array>
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

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK