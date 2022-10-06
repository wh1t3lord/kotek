#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <atomic>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

// TODO: create preprocessor for this namespace
namespace mt
{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	template <typename Type>
	using atomic = std::atomic<Type>;
#else
#endif
} // namespace mt

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK