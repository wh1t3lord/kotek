#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.defines_dependent.text/include/kotek_core_defines_dependent_text.h>
#include <kotek.core.types.char/include/kotek_core_types_char.h>

namespace Kotek
{
	namespace ktk
	{
#ifdef KOTEK_PLATFORM_WINDOWS
		constexpr tchar kPathSeparator = KOTEK_TEXT('\\');
#else
		constexpr tchar kPathSeparator = KOTEK_TEXT('/');
#endif
	} // namespace ktk
} // namespace Kotek