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
	char const* const p_format, ...);
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
using static_cstring_base = etl::ibasic_string<char>;

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

	{
		char temp[Size];
		wcstombs_s(&written, temp, Size, str.data(), str.size());
		stack = temp;
	}

	return stack;
}

KOTEK_END_NAMESPACE_KTK

using cstring_t = KUN_KOTEK KUN_KTK cstring;
using cstring_view_t = KUN_KOTEK KUN_KTK cstring_view;

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS

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
using static_cstring_base_t = KUN_KOTEK KUN_KTK static_cstring_base;

template <KUN_KOTEK KUN_KTK size_t Size>
using static_ustring_t = KUN_KOTEK KUN_KTK static_ustring<Size>;

using static_u8string_view_t = KUN_KOTEK KUN_KTK static_u8string_view;
using static_u16string_view_t = KUN_KOTEK KUN_KTK static_u16string_view;
using static_u32string_view_t = KUN_KOTEK KUN_KTK static_u32string_view;
using static_wstring_view_t = KUN_KOTEK KUN_KTK static_wstring_view;
using static_cstring_view_t = KUN_KOTEK KUN_KTK static_cstring_view;
using static_ustring_view_t = KUN_KOTEK KUN_KTK static_ustring_view;

#endif

KOTEK_END_NAMESPACE_KOTEK

#if defined(KOTEK_USE_LIBRARY_TYPE_EMB) && \
	defined(KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS)

	#define ktk_cstring kun_kotek kun_ktk static_cstring
	#define KTK_CSTRING kun_kotek kun_ktk static_cstring
	#define ktkCString kun_kotek kun_ktk static_cstring

	#define ktk_cstring_view kun_kotek kun_ktk static_cstring_view
	#define KTK_CSTRING_VIEW kun_kotek kun_ktk static_cstring_view
	#define ktkCStringView kun_kotek kun_ktk static_cstring_view

	#define ktk_wstring kun_kotek kun_ktk static_wstring
	#define KTK_WSTRING kun_kotek kun_ktk static_wstring
	#define ktkWString kun_kotek kun_ktk static_wstring

	#define ktk_wstring_view kun_kotek kun_ktk static_wstring_view
	#define KTK_WSTRING_VIEW kun_kotek kun_ktk static_wstring_view
	#define ktkWStringView kun_kotek kun_ktk static_wstring_view

	#define ktk_u8string kun_kotek kun_ktk static_u8string
	#define KTK_U8STRING kun_kotek kun_ktk static_u8string
	#define ktkU8String kun_kotek kun_ktk static_u8string

	#define ktk_u8string_view kun_kotek kun_ktk static_u8string_view
	#define KTK_U8STRING_VIEW kun_kotek kun_ktk static_u8string_view
	#define ktkU8StringView kun_kotek kun_ktk static_u8string_view

	#define ktk_u16string kun_kotek kun_ktk static_u16string
	#define KTK_U16STRING kun_kotek kun_ktk static_u16string
	#define ktkU16String kun_kotek kun_ktk static_u16string

	#define ktk_u16string_view kun_kotek kun_ktk static_u16string_view
	#define KTK_U16STRING_VIEW kun_kotek kun_ktk static_u16string_view
	#define ktkU16StringView kun_kotek kun_ktk static_u16string_view

	#define ktk_u32string kun_kotek kun_ktk static_u32string
	#define KTK_U32STRING kun_kotek kun_ktk static_u32string
	#define ktkU32String kun_kotek kun_ktk static_u32string

	#define ktk_u32string_view kun_kotek kun_ktk static_u32string_view
	#define KTK_U32STRING_VIEW kun_kotek kun_ktk static_u32string_view
	#define ktkU32StringView kun_kotek kun_ktk static_u32string_view

	#define ktk_ustring kun_kotek kun_ktk static_ustring
	#define KTK_USTRING kun_kotek kun_ktk static_ustring
	#define ktkUString kun_kotek kun_ktk static_ustring

	#define ktk_ustring_view kun_kotek kun_ktk static_ustring_view
	#define KTK_USTRING_VIEW kun_kotek kun_ktk static_ustring_view
	#define ktkUStringView kun_kotek kun_ktk static_ustring_view

#else

	#define ktk_string kun_kotek kun_ktk cstring
	#define KTK_STRING kun_kotek kun_ktk cstring
	#define ktkString kun_kotek kun_ktk cstring

	#define ktk_string_view kun_kotek kun_ktk cstring_view
	#define KTK_STRING_VIEW kun_kotek kun_ktk cstring_view
	#define ktkStringView kun_kotek kun_ktk cstring_view

	#define ktk_wstring kun_kotek kun_ktk wstring
	#define KTK_WSTRING kun_kotek kun_ktk wstring
	#define ktkWString kun_kotek kun_ktk wstring

	#define ktk_wstring_view kun_kotek kun_ktk wstring_view
	#define KTK_WSTRING_VIEW kun_kotek kun_ktk wstring_view
	#define ktkWStringView kun_kotek kun_ktk wstring_view

	#define ktk_u8string kun_kotek kun_ktk u8string
	#define KTK_U8STRING kun_kotek kun_ktk u8string
	#define ktkU8String kun_kotek kun_ktk u8string

	#define ktk_u8string_view kun_kotek kun_ktk u8string_view
	#define KTK_U8STRING_VIEW kun_kotek kun_ktk u8string_view
	#define ktkU8StringView kun_kotek kun_ktk u8string_view

	#define ktk_u16string kun_kotek kun_ktk u16string
	#define KTK_U16STRING kun_kotek kun_ktk u16string
	#define ktkU16String kun_kotek kun_ktk u16string

	#define ktk_u16string_view kun_kotek kun_ktk u16string_view
	#define KTK_U16STRING_VIEW kun_kotek kun_ktk u16string_view
	#define ktkU16StringView kun_kotek kun_ktk u16string_view

	#define ktk_u32string kun_kotek kun_ktk u32string
	#define KTK_U32STRING kun_kotek kun_ktk u32string
	#define ktkU32String kun_kotek kun_ktk u32string

	#define ktk_u32string_view kun_kotek kun_ktk u32string_view
	#define KTK_U32STRING_VIEW kun_kotek kun_ktk u32string_view
	#define ktkU32String kun_kotek kun_ktk u32string_view

	#define ktk_ustring kun_kotek kun_ktk ustring
	#define KTK_USTRING kun_kotek kun_ktk ustring
	#define ktkUString kun_kotek kun_ktk ustring

	#define ktk_ustring_view kun_kotek kun_ktk ustring_view
	#define KTK_USTRING_VIEW kun_kotek kun_ktk ustring_view
	#define ktkUStringView kun_kotek kun_ktk ustring_view

#endif