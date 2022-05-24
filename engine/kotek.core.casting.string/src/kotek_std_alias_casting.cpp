#include "../include/kotek_std_alias_casting.h"
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <boost/algorithm/string.hpp>

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

			bool to_bool(
				const string& your_logical_string_written_in_text) noexcept
			{
				const auto& casted =
					your_logical_string_written_in_text.get_as_legacy();

				if (boost::iequals(casted, "no") ||
					boost::iequals(casted, "false") || casted == "0")
					return false;

				return true;
			}

		} // namespace cast
	}     // namespace ktk
} // namespace Kotek