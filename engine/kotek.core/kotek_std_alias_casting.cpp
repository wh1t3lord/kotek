#include "kotek_std_alias_casting.h"

namespace Kotek
{
	namespace ktk
	{
		namespace cast
		{
#ifdef KOTEK_PLATFORM_WINDOWS
			string_windows to_wchar_string(
				const string_unicode& source) noexcept
			{
				string_windows result(source.begin(), source.end());

				return result;
			}

			string_unicode to_string(const string_windows& source) noexcept
			{
				string_unicode result(source.begin(), source.end());

				return result;
			}
#elif KOTEK_PLATFORM_LINUX
			wstring to_wchar_string(const string_unicode& source) noexcept
			{
				wstring result(source.begin(), source.end());

				return result;
			}

			string_unicode to_string(const wstring& source) noexcept
			{
				string_unicode result(source.begin(), source.end());

				return result;
			}
#endif

			string_legacy to_legacy_string(
				const string_unicode& source) noexcept
			{
				string_legacy result(source.begin(), source.end());

				return result;
			}

			string_unicode to_string(const string_legacy& source) noexcept
			{
				string_unicode result(source.begin(), source.end());

				return result;
			}

		} // namespace cast
	}     // namespace ktk
} // namespace Kotek