#pragma once

#include <kotek.core.types.char/include/kotek_core_types_char.h>
#include <fstream>

namespace Kotek
{
	namespace ktk
	{
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
	} // namespace ktk
} // namespace Kotek
