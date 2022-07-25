#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>

#ifdef KOTEK_USE_BOOST_LIBRARY
	#include <boost/container/deque.hpp>
#elif defined(KOTEK_USE_STD_LIBRARY)
	#include <deque>
#else
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		template <typename Type, typename Allocator = KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>
		using deque = boost::container::deque<Type, Allocator>;
#elif defined(KOTEK_USE_STD_LIBRARY)
		template <typename Type, typename Allocator = KOTEK_USE_MEMORY_ALLOCATOR_CLASS<Type>>
		using deque = std::deque<Type, Allocator>;
#else
#endif
	} // namespace ktk
} // namespace Kotek