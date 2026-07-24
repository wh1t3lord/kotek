#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <utility>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
template <class K, class V>
using pair = std::pair<K, V>;
#else
#endif
KOTEK_END_NAMESPACE_KTK

template <class K, class V>
using pair_t = KUN_KOTEK KUN_KTK pair<K, V>;

KOTEK_END_NAMESPACE_KOTEK