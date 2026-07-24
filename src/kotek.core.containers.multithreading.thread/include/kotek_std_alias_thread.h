#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <thread>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MT
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
using thread = std::thread;
namespace this_thread = std::this_thread;
#else
#endif

KOTEK_END_NAMESPACE_MT
KOTEK_END_NAMESPACE_KTK

KOTEK_BEGIN_NAMESPACE_MT
using thread_t = KUN_KOTEK KUN_KTK KUN_MT thread;
namespace this_thread = KUN_KOTEK KUN_KTK KUN_MT this_thread;
KOTEK_END_NAMESPACE_MT
KOTEK_END_NAMESPACE_KOTEK