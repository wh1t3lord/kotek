#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <variant>
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/variant.h>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
template <typename... Args>
using variant = std::variant<Args...>;
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
template <typename... Args>
using static_variant = etl::variant<Args...>;
#else
#endif

KOTEK_END_NAMESPACE_KTK

template <typename... Args>
using variant_t = KUN_KOTEK KUN_KTK variant<Args...>;

template <typename... Args>
using static_variant_t = KUN_KOTEK KUN_KTK static_variant<Args...>;

KOTEK_END_NAMESPACE_KOTEK