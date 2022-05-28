#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/deque.hpp>
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		template <typename Type, typename Allocator = mi_stl_allocator<Type>>
		using deque = boost::deque<Type, Allocator>;
#else
		template <typename Type, typename Allocator = mi_stl_allocator<Type>>
		using deque = std::deque<Type, Allocator>;
#endif
	} // namespace ktk
} // namespace Kotek