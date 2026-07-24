#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <shared_mutex>
#else
#endif

// TODO: implement some functionality here
KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MT
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
#else
#endif
KOTEK_END_NAMESPACE_MT
KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_MT

KOTEK_END_NAMESPACE_MT

KOTEK_END_NAMESPACE_KOTEK