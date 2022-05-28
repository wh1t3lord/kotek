#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/vector.hpp>
#else
	#include <vector>
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		template <typename Type>
		using vector = boost::container::vector<Type, mi_stl_allocator<Type>>;
#else
		template <typename Type>
		using vector = std::vector<Type, mi_stl_allocator<Type>>;
#endif
	} // namespace ktk
} // namespace Kotek