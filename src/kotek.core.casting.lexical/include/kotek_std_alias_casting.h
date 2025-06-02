#pragma once

#include <boost/lexical_cast.hpp>
#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

template <typename T, typename S>
T lexical_cast(const S& args)
{
#ifdef KOTEK_USE_BOOST_LIBRARY
	return boost::lexical_cast<T, S>(args);
#else
	#error not implemented
#endif
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
