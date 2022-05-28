#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/dll.hpp>
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		namespace dll = boost::dll;
#else
	#error add replacement for boost::dll
#endif
	} // namespace ktk
} // namespace Kotek