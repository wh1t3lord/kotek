#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/json.hpp>
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		namespace json = boost::json;
#else
	#error TODO add support for nlohmann json
#endif
	} // namespace ktk
} // namespace Kotek