#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#if defined(KOTEK_USE_BOOST_LIBRARY) || \
	defined(KOTEK_USE_STD_LIBRARY)
	// by our standard if user doesn't specify custom as their
    // 'override' then we use only boost.json library for
    // representing json backend in our framework/engine
	#undef Bool
	#include <boost/json.hpp>

#ifdef KOTEK_USE_STD_LIBRARY
namespace boost
{
	namespace json
	{
		using error_code = boost::system::error_code;
	}
}
	#endif

#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#if defined(KOTEK_USE_BOOST_LIBRARY) || \
	defined(KOTEK_USE_STD_LIBRARY)

// TODO: replace this with KN_JSON
namespace json = boost::json;

#else
#endif

KOTEK_END_NAMESPACE_KTK

// TODO: provide KN_JSON thing
namespace json = KUN_KOTEK KUN_KTK json;

KOTEK_END_NAMESPACE_KOTEK
