#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <memory>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
template <typename T>
using unique_ptr = std::unique_ptr<T>;
#else
#endif

KOTEK_END_NAMESPACE_KTK

template <typename Type>
using unique_ptr_t = KUN_KOTEK KUN_KTK unique_ptr<Type>;

KOTEK_END_NAMESPACE_KOTEK