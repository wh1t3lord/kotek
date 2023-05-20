#pragma once

#include <kotek.core.types.string/include/kotek_core_types_string.h>
#include <kotek.core.casting.string/include/kotek_core_casting_string.h>
#include <kotek.core.casting.lexical/include/kotek_core_casting_lexical.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

std::size_t hash_value(const ktk::ustring& instance);
void to_lower(cstring& str);
cstring to_lower(const cstring& str);

#else   
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
