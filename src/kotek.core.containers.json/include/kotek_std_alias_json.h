#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#if defined(KOTEK_USE_JSON_LIBRARY_KOTEK_OWN)
	// kotek's own dependency-free json backend (task K4): a streaming
	// parser plus a small DOM that mirrors the subset of boost::json the
	// codebase uses. Selected with KOTEK_JSON_LIBRARY=KOTEK_OWN; the real
	// `json` namespace below comes from these headers.
	#include "kotek_own_json.h"
	#include "kotek_own_json_stream.h"
#elif defined(KOTEK_USE_BOOST_LIBRARY) || \
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

#if defined(KOTEK_USE_JSON_LIBRARY_KOTEK_OWN)

// the own backend defines the real namespace json inside KTK
// (kotek_own_json.h / kotek_own_json_stream.h, included above)

#elif defined(KOTEK_USE_BOOST_LIBRARY) || \
	defined(KOTEK_USE_STD_LIBRARY)

// TODO: replace this with KN_JSON
namespace json = boost::json;

#else
#endif

KOTEK_END_NAMESPACE_KTK

// TODO: provide KN_JSON thing
namespace json = KUN_KOTEK KUN_KTK json;

KOTEK_END_NAMESPACE_KOTEK
