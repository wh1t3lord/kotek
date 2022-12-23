#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.types.string/include/kotek_core_types_string.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

class string;

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace cast
{
#ifdef KOTEK_PLATFORM_LINUX
	wstring to_wchar_string(const string_unicode& source) noexcept;
	string_unicode to_string(const wstring& source) noexcept;
#elif defined(KOTEK_PLATFORM_WINDOWS)
	string_windows to_wchar_string(const string_unicode& source) noexcept;
	string_unicode to_string(const string_windows& source) noexcept;
#endif

	string_legacy to_legacy_string(const string_unicode& source) noexcept;

	string_unicode to_string(const string_legacy& source) noexcept;

	u8string to_utf8(const string_unicode& source) noexcept;

	// @ Converts from 1,0,yes,no,true,false into appropriate bool type
	// Register independent
	bool to_bool(const string& your_logical_string_written_in_text) noexcept;
} // namespace cast

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
