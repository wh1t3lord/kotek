#pragma once

#include "kotek_std_preprocessors.h"

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_USE_UNICODE

	/// Attention don't break the rules, if we want to use UNICODE that means
	/// tchar uses strict opposite type against char So if you choose unicode
	/// means you will get ALWAYS different type to char that doesn't equal to
	/// char at all!!! Don't try to set tchar = char that means nothing for all
	/// system and doesn't make any sense
	#ifdef KOTEK_PLATFORM_WINDOWS
		using uchar = wchar_t;
	#else
		using uchar = char32_t;
	#endif

		using tchar = uchar;

#else
		using tchar = char;
#endif

	} // namespace ktk
} // namespace Kotek