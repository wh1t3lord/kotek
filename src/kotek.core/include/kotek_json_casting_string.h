#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>

#ifdef KOTEK_USE_NOT_CUSTOM_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const ustring& data
)
{
	#ifndef KOTEK_USE_STRING_CONFIGURATION_OPTIMIZED
	cstring type = helper::ObtainCharTypeName_FromString();

	if (type != "char")
	{
		json::object str;

		json::array raw_string(data.cbegin(), data.cend());
		str["type"] = helper::ObtainCharTypeName_FromString();
		str["raw_string"] = raw_string;
		write_to = str;
	}
	else
	#endif
	{
		json::string str;

		str = data.c_str();

		write_to = str;
	}
}

inline ustring tag_invoke(
	const json::value_to_tag<ustring>&,
	const json::value& read_from
)
{
	if (read_from.is_object())
	{
		const json::object& str = read_from.as_object();

		ustring result;
		const auto& char_name = str.at("type").as_string();

		if (char_name == "char8_t")
		{
			u8string buffer;

			const auto& raw_number_string_buffer =
				str.at("raw_string").as_array();

			for (const auto number : raw_number_string_buffer)
			{
				buffer += number.as_int64();
			}

			result = ustring(buffer.begin(), buffer.end());
		}
		else if (char_name == "char16_t")
		{
			u16string buffer;

			const auto& raw_number_string_buffer =
				str.at("raw_string").as_array();

			for (const auto number : raw_number_string_buffer)
			{
				buffer += number.as_int64();
			}

			result = ustring(buffer.begin(), buffer.end());
		}
		else if (char_name == "char32_t")
		{
			u32string buffer;

			const auto& raw_number_string_buffer =
				str.at("raw_string").as_array();

			for (const auto number : raw_number_string_buffer)
			{
				buffer += number.as_int64();
			}

			result = ustring(buffer.begin(), buffer.end());
		}
		else if (char_name == "wchar_t")
		{
			wstring buffer;

			const auto& raw_number_string_buffer =
				str.at("raw_string").as_array();

			for (const auto number : raw_number_string_buffer)
			{
				buffer += number.as_int64();
			}

			result = ustring(buffer.begin(), buffer.end());
		}
		else
		{
			KOTEK_ASSERT(
				false,
				"can't find an appropriate casting for your "
			    "type. Engine "
				"supports only UTF-8 and char strings"
			);
		}

		return result;
	}
	else
	{
		const auto& char_string = read_from.as_string();
		return ustring(char_string.begin(), char_string.end());
	}
}

	#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const u8string& str
)
{
	json::object result;

	json::array raw_string(str.begin(), str.end());

	result["type"] = "char8_t";
	result["raw_string"] = raw_string;

	write_to = result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const u16string& str
)
{
	json::object result;

	json::array raw_string(str.begin(), str.end());

	result["type"] = "char16_t";
	result["raw_string"] = raw_string;

	write_to = result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const u32string& str
)
{
	json::object result;

	json::array raw_string(str.begin(), str.end());

	result["type"] = "char32_t";
	result["raw_string"] = raw_string;

	write_to = result;
}

inline void tag_invoke(
	const json::value_from_tag&,
	json::value& write_to,
	const wstring& str
)
{
	json::object result;

	json::array raw_string(str.begin(), str.end());

	result["type"] = "wchar_t";
	result["raw_string"] = raw_string;

	write_to = result;
}
	#endif

KOTEK_END_NAMESPACE_KTK

KOTEK_END_NAMESPACE_KOTEK

namespace std
{
	inline KUN_KOTEK KUN_KTK ustring tag_invoke(
		const KUN_KOTEK KUN_KTK json::value_to_tag<KUN_KOTEK KUN_KTK ustring>& tag,
		const KUN_KOTEK KUN_KTK json::value& read_from
	)
	{
		return tag_invoke(tag, read_from);
	}

	inline void tag_invoke(
		const KUN_KOTEK KUN_KTK json::value_from_tag&,
		KUN_KOTEK KUN_KTK json::value& write_to,
		const std::u8string& str
	)
	{
		KUN_KOTEK KUN_KTK json::object result;

		KUN_KOTEK KUN_KTK json::array raw_string(str.begin(), str.end());

		result["type"] = "char8_t";
		result["raw_string"] = raw_string;

		write_to = result;
	}

	inline void tag_invoke(
		const KUN_KOTEK KUN_KTK json::value_from_tag&,
		KUN_KOTEK KUN_KTK json::value& write_to,
		const std::u16string& str
	)
	{
		KUN_KOTEK KUN_KTK json::object result;

		KUN_KOTEK KUN_KTK json::array raw_string(str.begin(), str.end());

		result["type"] = "char16_t";
		result["raw_string"] = raw_string;

		write_to = result;
	}

	inline void tag_invoke(
		const KUN_KOTEK KUN_KTK json::value_from_tag&,
		KUN_KOTEK KUN_KTK json::value& write_to,
		const std::u32string& str
	)
	{
		KUN_KOTEK KUN_KTK json::object result;

		KUN_KOTEK KUN_KTK json::array raw_string(str.begin(), str.end());

		result["type"] = "char32_t";
		result["raw_string"] = raw_string;

		write_to = result;
	}

	inline void tag_invoke(
		const KUN_KOTEK KUN_KTK json::value_from_tag&,
		KUN_KOTEK KUN_KTK json::value& write_to,
		const std::wstring& str
	)
	{
		KUN_KOTEK KUN_KTK json::object result;

		KUN_KOTEK KUN_KTK json::array raw_string(str.begin(), str.end());

		result["type"] = "wchar_t";
		result["raw_string"] = raw_string;

		write_to = result;
	}
} // namespace std

#endif
