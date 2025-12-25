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
int sprintf(char* const p_string, const std::size_t buffer_count,
	char const* const p_format, ...);
#else
#endif

/// @brief allocates memory because it is not embedded function on stack
/// @param str takes char16_t type (don't mistake with wchar_t)
/// @return char8_t based std::u8string container, then you can keep this type
/// or convert to std::string (char based string)
u8string convert_utf16_to_utf8(const u16string_view& str);
/// @brief allocates memory because it is not embedded function on stack
/// @param str takes char32_t string type
/// @return char8_t based std::u8string container, then you can keep this type
/// or convert to std::string (char based string)
u8string convert_utf32_to_utf8(const u32string_view& str);

/// @brief allocates memory because it is not std::pmr::xstring type so keep this in mind
/// @param str 
/// @return KUN_KOTEK KUN_KTK u8string
u8string convert_wchar_to_utf8(const wstring_view& str);

KOTEK_END_NAMESPACE_KTK

using cstring_t = KUN_KOTEK KUN_KTK cstring;
using cstring_view_t = KUN_KOTEK KUN_KTK cstring_view;

KOTEK_END_NAMESPACE_KOTEK