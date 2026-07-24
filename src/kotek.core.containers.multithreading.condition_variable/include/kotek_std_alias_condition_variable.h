#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <condition_variable>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MT

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
using condition_variable = std::condition_variable;
#else
#endif

KOTEK_END_NAMESPACE_MT
KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_MT
using condition_variable = kun_kotek kun_ktk kun_mt condition_variable;
KOTEK_END_NAMESPACE_MT

KOTEK_END_NAMESPACE_KOTEK