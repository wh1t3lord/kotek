#include "../include/kotek_std_alias_casting.h"
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <boost/algorithm/string.hpp>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <type_traits>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

namespace cast
{
#ifdef KOTEK_PLATFORM_WINDOWS
	string_windows to_wchar_string(const string_unicode& source) noexcept
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

	string_legacy to_legacy_string(const string_unicode& source) noexcept
	{
		string_legacy result(source.begin(), source.end());

		return result;
	}

	string_unicode to_string(const string_legacy& source) noexcept
	{
		string_unicode result(source.begin(), source.end());

		return result;
	}

	u8string to_utf8(const string_unicode& source) noexcept
	{
		KOTEK_ASSERT((std::is_same<string_unicode::value_type, char>::value == false),
			"You can't use this function if your uchar type is char! It "
			"doesn't make any sense!!!!!!!");

		return u8string(source.begin(), source.end());
	}

	bool to_bool(const string& your_logical_string_written_in_text) noexcept
	{
		const auto& casted =
			your_logical_string_written_in_text.get_as_legacy();

		if (boost::iequals(casted, "no") || boost::iequals(casted, "false") ||
			casted == "0")
			return false;

		return true;
	}

} // namespace cast

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK