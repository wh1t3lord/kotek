#pragma once

#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>
#include <kotek.core.types.char/include/kotek_core_types_char.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>
#include <string>
#include <typeinfo>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_STD
using string = std::u8string;
using string_view = std::u8string_view;

using u8string = std::u8string;
using u8string_view = std::u8string_view;

using u16string = std::u16string;
using u16string_view = std::u16string_view;

using u32string = std::u32string;
using u32string_view = std::u32string_view;

using wstring = std::wstring;
using wstring_view = std::wstring_view;

using cstring = std::string;
using cstring_view = std::string_view;
#else
using string = std::basic_string<tchar, std::char_traits<tchar>,
    KOTEK_USE_MEMORY_ALLOCATOR_CLASS<tchar>>;
using u8string = std::basic_string<char8_t, std::char_traits<char8_t>,
    KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char8_t>>;
using u16string = std::basic_string<char16_t, std::char_traits<char16_t>,
    KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char16_t>>;
using u32string = std::basic_string<char32_t, std::char_traits<char32_t>,
    KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char32_t>>;
using wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>,
    KOTEK_USE_MEMORY_ALLOCATOR_CLASS<wchar_t>>;
using cstring = std::basic_string<char, std::char_traits<char>,
    KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char>>;
#endif

namespace helper
{
	inline const char* ObtainCharTypeName_FromString(void) noexcept
	{
		auto id_char8_t = typeid(char8_t).hash_code();
		auto id_char16_t = typeid(char16_t).hash_code();
		auto id_char32_t = typeid(char32_t).hash_code();
		auto id_wchar_t = typeid(wchar_t).hash_code();

        auto id_current_type = typeid(string::value_type).hash_code();

		if (id_current_type == id_char8_t)
		{
			return "char8_t";
		}
		else if (id_current_type == id_char16_t)
		{
			return "char16_t";
		}
		else if (id_current_type == id_char32_t)
		{
			return "char32_t";
		}
		else if (id_current_type == id_wchar_t)
		{
			return "wchar_t";
		}
		else
		{
			return "char";
		}
	}
} // namespace helper

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
