#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>

#ifdef KOTEK_USE_BOOST_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

inline void tag_invoke(const ktk::json::value_from_tag&,
	ktk::json::value& write_to, const ktk::string& data)
{
	Kotek::ktk::json::object str;

	str["type"] = "char8_t";
	str["raw_string"] = {casted};

	write_to = str;
}

inline ktk::string tag_invoke(const ktk::json::value_to_tag<ktk::string>&,
	const ktk::json::value& read_from)
{
	const ktk::json::object& str = read_from.as_object();

	ktk::tstring result;

	const auto& char_name = str.at("type").as_string();

	if (char_name == "char8_t")
	{
		ktk::u8string buffer;

		const auto& raw_number_string_buffer = str.at("raw_string").as_array();

		for (const auto number : raw_number_string_buffer)
		{
			buffer += number.as_int64();
		}

		result = ktk::tstring(buffer.begin(), buffer.end());
	}
	else if (char_name == "char16_t")
	{
		ktk::u16string buffer;

		const auto& raw_number_string_buffer = str.at("raw_string").as_array();

		for (const auto number : raw_number_string_buffer)
		{
			buffer += number.as_int64();
		}

		result = ktk::tstring(buffer.begin(), buffer.end());
	}
	else if (char_name == "char32_t")
	{
		ktk::u32string buffer;

		const auto& raw_number_string_buffer = str.at("raw_string").as_array();

		for (const auto number : raw_number_string_buffer)
		{
			buffer += number.as_int64();
		}

		result = ktk::tstring(buffer.begin(), buffer.end());
	}
	else if (char_name == "wchar_t")
	{
		ktk::wstring buffer;

		const auto& raw_number_string_buffer = str.at("raw_string").as_array();

		for (const auto number : raw_number_string_buffer)
		{
			buffer += number.as_int64();
		}

		result = ktk::tstring(buffer.begin(), buffer.end());
	}
	else
	{
		KOTEK_ASSERT(false, "can't find an appropriate casting for your type");
	}

	return result;
}

KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

namespace std
{

}

inline void tag_invoke(
	const KOTEK_USE_NAMESPACE_KOTEK ktk::json::value_from_tag&,
	KOTEK_USE_NAMESPACE_KOTEK ktk::json::value& write_to, const char8_t* p_string)
{
	Kotek::ktk::u8string casted = p_string;

	Kotek::ktk::json::object str;

	str["type"] = "char8_t";
	str["raw_string"] = {casted};

	write_to = str;
}

inline void tag_invoke(
	const KOTEK_USE_NAMESPACE_KOTEK ktk::json::value_from_tag&,
	KOTEK_USE_NAMESPACE_KOTEK ktk::json::value& write_to,
	const char16_t* p_string)
{
	Kotek::ktk::u16string casted = p_string;

	Kotek::ktk::json::object str;

	str["type"] = "char16_t";
	str["raw_string"] = {casted};

	write_to = str;
}

inline void tag_invoke(
	const KOTEK_USE_NAMESPACE_KOTEK ktk::json::value_from_tag&,
	KOTEK_USE_NAMESPACE_KOTEK ktk::json::value& write_to,
	const char32_t* p_string)
{
	Kotek::ktk::u32string casted = p_string;

	Kotek::ktk::json::object str;

	str["type"] = "char32_t";
	str["raw_string"] = {casted};

	write_to = str;
}

inline void tag_invoke(
	const KOTEK_USE_NAMESPACE_KOTEK ktk::json::value_from_tag&,
	KOTEK_USE_NAMESPACE_KOTEK ktk::json::value& write_to,
	const wchar_t* p_string)
{
	Kotek::ktk::wstring casted = p_string;

	Kotek::ktk::json::object str;

	str["type"] = "wchar_t";
	str["raw_string"] = {casted};

	write_to = str;
}

#endif