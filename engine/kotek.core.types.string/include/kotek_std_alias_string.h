#pragma once

#include <kotek.core.defines.static.string/include/kotek_core_defines_static_string.h>
#include <kotek.core.types.char/include/kotek_core_types_char.h>
#include <kotek.core.memory.cpu/include/kotek_core_memory_cpu.h>
#include <string>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_UNICODE
using string_unicode = std::basic_string<uchar, std::char_traits<uchar>,
	KOTEK_USE_MEMORY_ALLOCATOR_CLASS<uchar>>;
#endif

using string_legacy = std::basic_string<char, std::char_traits<char>,
	KOTEK_USE_MEMORY_ALLOCATOR_CLASS<char>>;

#ifdef KOTEK_PLATFORM_WINDOWS
/// <summary>
/// Use this only for casting operation under CRD_USE_UNICODE == 0!
/// For instance: ktk::string_windows your_string(string_legacy.begin(),
/// string_legacy.end());
/// </summary>
using string_windows = std::basic_string<wchar_t, std::char_traits<wchar_t>,
	KOTEK_USE_MEMORY_ALLOCATOR_CLASS<wchar_t>>;
#elif defined(KOTEK_PLATFORM_LINUX)
using wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>,
	KOTEK_USE_MEMORY_ALLOCATOR_CLASS<wchar_t>>;
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK