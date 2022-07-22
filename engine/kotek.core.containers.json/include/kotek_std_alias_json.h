#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/json.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#error add replacement for boost
#else
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		namespace json = boost::json;
#elif defined(KOTEK_USE_STD_LIBRARY)
	#error TODO add support for nlohmann json
#else
#endif
	} // namespace ktk
} // namespace Kotek