#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container_hash/extensions.hpp>
#else
	#include <type_traits>
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		template <typename Type>
		using hash = boost::hash<Type>;
#else
		template <typename Type>
		using hash = std::hash<Type>;
#endif
	} // namespace ktk
} // namespace Kotek