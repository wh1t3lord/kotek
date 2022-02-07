#pragma once

#include "kotek_std_alias_string.h"
#include "kotek_std_preprocessors.h"
#include <boost/lexical_cast.hpp>

namespace Kotek
{
	namespace ktk
	{
		class string;
	}
} // namespace Kotek

namespace Kotek
{
	namespace ktk
	{
		template <typename T, typename S>
		T lexical_cast(const S& args)
		{
			return boost::lexical_cast<T, S>(args);
		}

		namespace cast
		{
#ifdef KOTEK_PLATFORM_LINUX
			wstring to_wchar_string(const string_unicode& source) noexcept;
			string_unicode to_string(const wstring& source) noexcept;
#elif defined(KOTEK_PLATFORM_WINDOWS)
			string_windows to_wchar_string(
				const string_unicode& source) noexcept;
			string_unicode to_string(const string_windows& source) noexcept;
#endif

			string_legacy to_legacy_string(
				const string_unicode& source) noexcept;

			string_unicode to_string(const string_legacy& source) noexcept;

			// @ Converts from 1,0,yes,no,true,false into appropriate bool type
			// Register independent 
			bool to_bool(
				const string& your_logical_string_written_in_text) noexcept;
		} // namespace cast

	} // namespace ktk
} // namespace Kotek
