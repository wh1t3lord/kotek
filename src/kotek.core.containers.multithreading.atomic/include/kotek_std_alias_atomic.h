#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <atomic>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MT

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
template <typename Type>
using atomic = std::atomic<Type>;

using atomic_flag = std::atomic_flag;
#else
#endif

KOTEK_END_NAMESPACE_MT
KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_MT
template <typename Type>
using atomic_t = KUN_KOTEK KUN_KTK KUN_MT atomic<Type>;

using atomic_flag_t = KUN_KOTEK KUN_KTK KUN_MT atomic_flag;
KOTEK_END_NAMESPACE_MT

KOTEK_END_NAMESPACE_KOTEK