#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.types.char/include/kotek_core_types_char.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <fstream>
#else
#endif

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
		using ofstream = std::basic_ofstream<tchar, std::char_traits<tchar>>;
		using ofstream_legacy =
			std::basic_ofstream<char, std::char_traits<char>>;

		using ifstream = std::basic_ifstream<tchar, std::char_traits<tchar>>;
		using ifstream_legacy =
			std::basic_ifstream<char, std::char_traits<char>>;

		using istreambuf_iterator =
			std::istreambuf_iterator<tchar, std::char_traits<tchar>>;
		using istreambuf_iterator_legacy =
			std::istreambuf_iterator<char, std::char_traits<char>>;

		using ostreambuf_iterator =
			std::ostreambuf_iterator<tchar, std::char_traits<tchar>>;
		using ostreambuf_iterator_legacy =
			std::ostreambuf_iterator<char, std::char_traits<char>>;
#else
#endif
	} // namespace ktk
} // namespace Kotek
