#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.types.char/include/kotek_core_types_char.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
	#include <fstream>
#else
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY
using ofstream = std::basic_ofstream<tchar, std::char_traits<tchar>>;
using cofstream = std::basic_ofstream<char, std::char_traits<char>>;

using ifstream = std::basic_ifstream<tchar, std::char_traits<tchar>>;
using cifstream = std::basic_ifstream<char, std::char_traits<char>>;

using fstream = std::basic_fstream<tchar, std::char_traits<tchar>>;
using cfstream = std::basic_fstream<char, std::char_traits<char>>;

using istreambuf_iterator =
	std::istreambuf_iterator<tchar, std::char_traits<tchar>>;
using cistreambuf_iterator =
	std::istreambuf_iterator<char, std::char_traits<char>>;

using ostreambuf_iterator =
	std::ostreambuf_iterator<tchar, std::char_traits<tchar>>;
using costreambuf_iterator =
	std::ostreambuf_iterator<char, std::char_traits<char>>;
#else
#endif

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
