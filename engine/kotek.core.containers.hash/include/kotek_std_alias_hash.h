#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container_hash/extensions.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <type_traits>
#else
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		template <typename Type>
		using hash = boost::hash<Type>;
#elif defined(KOTEK_USE_STD_LIBRARY)
		template <typename Type>
		using hash = std::hash<Type>;
#else
#endif
	} // namespace ktk
} // namespace Kotek