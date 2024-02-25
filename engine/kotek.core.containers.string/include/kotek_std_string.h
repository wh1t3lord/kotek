#pragma once

#include <kotek.core.types.string/include/kotek_core_types_string.h>
#include <kotek.core.casting.string/include/kotek_core_casting_string.h>
#include <kotek.core.casting.lexical/include/kotek_core_casting_lexical.h>
#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	#include <etl/string.h>
	#include <etl/wstring.h>
	#include <etl/u8string.h>
	#include <etl/u16string.h>
	#include <etl/u32string.h>
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

std::size_t hash_value(const ktk::ustring& instance);
void to_lower(cstring& str);
cstring to_lower(const cstring& str);

#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
// TODO: add static version of strings containers respect to char8_t model
// architecture !
using string = std::u8string;
using string_view = std::u8string_view;

using u8string = std::u8string;
using u8string_view = std::u8string_view;

template <size_t Size>
using static_u8string = etl::u8string<Size>;
using static_u8string_view = etl::u8string_view;

template <size_t Size>
using static_u16string = etl::u16string<Size>;
using static_u16string_view = etl::u16string_view;

template <size_t Size>
using static_u32string = etl::u32string<Size>;
using static_u32string_view = etl::u32string_view;

template <size_t Size>
using static_wstring = etl::wstring<Size>;
using static_wstring_view = etl::wstring_view;

template <size_t Size>
using static_cstring = etl::string<Size>;
using static_cstring_view = etl::string_view;

template <size_t Size>
	#ifdef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
using static_ustring = static_cstring<Size>;
using static_ustring_view = static_cstring_view;
	#else
using ustring = static_string<Size>;
using ustring_view = static_string_view;
	#endif

#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
