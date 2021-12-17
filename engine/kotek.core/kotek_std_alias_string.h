#pragma once

#include "kotek_std_alias_char_model.h"
#include "kotek_std_memory.h"
#include <string>

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_UNICODE
		using string_unicode = std::basic_string<uchar, std::char_traits<uchar>,
			mi_stl_allocator<uchar>>;
#endif

		using string_legacy = std::basic_string<char, std::char_traits<char>,
			mi_stl_allocator<char>>;

#ifdef KOTEK_PLATFORM_WINDOWS
		/// <summary>
		/// Use this only for casting operation under CRD_USE_UNICODE == 0!
		/// For instance: ktk::string_windows your_string(string_legacy.begin(),
		/// string_legacy.end());
		/// </summary>
		using string_windows = std::basic_string<wchar_t,
			std::char_traits<wchar_t>, mi_stl_allocator<wchar_t>>;
#elif defined(KOTEK_PLATFORM_LINUX)
		using wstring = std::basic_string<wchar_t, std::char_traits<wchar_t>,
			mi_stl_allocator<wchar_t>>;
#endif
	} // namespace ktk
} // namespace Kotek
