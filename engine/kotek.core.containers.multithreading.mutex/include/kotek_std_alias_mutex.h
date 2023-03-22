#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <mutex>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace mt
{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	using mutex = std::mutex;

	template <typename Mutex>
	using lock_guard = std::lock_guard<Mutex>;

	using condition_variable = std::condition_variable;

	template<typename Mutex>
	using unique_lock = std::unique_lock<Mutex>;
#else
#endif
} // namespace mt

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK