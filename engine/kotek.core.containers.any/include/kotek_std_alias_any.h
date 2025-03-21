#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <any>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

using handle = uintptr_t;
using handle_t = handle;

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
using any = std::any;
#else
#endif

KOTEK_END_NAMESPACE_KTK

using any_t = KUN_KOTEK KUN_KTK any;
using handle_t = KUN_KOTEK KUN_KTK handle_t;

KOTEK_END_NAMESPACE_KOTEK
