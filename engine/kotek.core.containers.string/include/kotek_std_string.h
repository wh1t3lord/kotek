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
int sprintf(char* const p_string, const std::size_t buffer_count,
	char const* const p_format,...);
#else
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
// TODO: add static version of strings containers respect to char8_t model
// architecture !
// TODO: add predefined versions size of static strings like
// 2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536

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
using static_cstring_ext = etl::string_ext;

template <size_t Size>
	#ifdef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
using static_ustring = static_cstring<Size>;
using static_ustring_view = static_cstring_view;
	#else
using ustring = static_string<Size>;
using ustring_view = static_string_view;
	#endif

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

// TODO: create default size of stack static string size
template <size_t Size = 128>
inline static_cstring<Size> convert_wchar_to_char(const wstring_view& str)
{
	assert(str.size() <= Size && "can't convert try to change the size!");

	ktk::size_t written;
	static_cstring<Size> stack{};
	wcstombs_s(&written, stack.data(), Size, str.data(), str.size());
	return stack;
}

KOTEK_END_NAMESPACE_KTK

using cstring_t = KUN_KOTEK KUN_KTK cstring;

template <KUN_KOTEK KUN_KTK size_t Size>
using static_u8string_t = KUN_KOTEK KUN_KTK static_u8string<Size>;

template <KUN_KOTEK KUN_KTK size_t Size>
using static_u16string_t = KUN_KOTEK KUN_KTK static_u16string<Size>;

template <KUN_KOTEK KUN_KTK size_t Size>
using static_u32string_t = KUN_KOTEK KUN_KTK static_u32string<Size>;

template <KUN_KOTEK KUN_KTK size_t Size>
using static_wstring_t = KUN_KOTEK KUN_KTK static_wstring<Size>;

template <KUN_KOTEK KUN_KTK size_t Size>
using static_cstring_t = KUN_KOTEK KUN_KTK static_cstring<Size>;

template <KUN_KOTEK KUN_KTK size_t Size>
using static_ustring_t = KUN_KOTEK KUN_KTK static_ustring<Size>;

using static_u8string_view_t = KUN_KOTEK KUN_KTK static_u8string_view;
using static_u16string_view_t = KUN_KOTEK KUN_KTK static_u16string_view;
using static_u32string_view_t = KUN_KOTEK KUN_KTK static_u32string_view;
using static_wstring_view_t = KUN_KOTEK KUN_KTK static_wstring_view;
using static_cstring_view_t = KUN_KOTEK KUN_KTK static_cstring_view;
using static_ustring_view_t = KUN_KOTEK KUN_KTK static_ustring_view;

KOTEK_END_NAMESPACE_KOTEK
