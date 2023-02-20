#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>

#ifdef KOTEK_USE_BOOST_LIBRARY

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK

inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
	Kotek::ktk::json::value& write_to, const Kotek::ktk::cstring& str)
{
	Kotek::ktk::json::object result;

	Kotek::ktk::json::array raw_string(str.begin(), str.end());

	result["type"] = "char";

	result["raw_string"] = raw_string;

	write_to = result;
}

inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
	Kotek::ktk::json::value& write_to, const Kotek::ktk::string& data)
{
	Kotek::ktk::cstring type =
		Kotek::ktk::helper::ObtainCharTypeName_FromString();

	if (type != "char")
	{
		Kotek::ktk::json::object str;

		Kotek::ktk::json::array raw_string(data.cbegin(), data.cend());
		str["type"] = Kotek::ktk::helper::ObtainCharTypeName_FromString();
		str["raw_string"] = raw_string;
		write_to = str;
	}
	else
	{
		Kotek::ktk::json::string str;

		str = reinterpret_cast<const char*>(data.c_str());

		write_to = str;
	}
}

inline Kotek::ktk::string tag_invoke(
	const Kotek::ktk::json::value_to_tag<Kotek::ktk::string>&,
	const Kotek::ktk::json::value& read_from)
{
	if (read_from.is_object())
	{
		const Kotek::ktk::json::object& str = read_from.as_object();

		Kotek::ktk::string result;
		const auto& char_name = str.at("type").as_string();

		if (char_name == "char8_t")
		{
			Kotek::ktk::u8string buffer;

			const auto& raw_number_string_buffer =
				str.at("raw_string").as_array();

			for (const auto number : raw_number_string_buffer)
			{
				buffer += number.as_int64();
			}

			result = Kotek::ktk::string(buffer.begin(), buffer.end());
		}
		else if (char_name == "char16_t")
		{
			Kotek::ktk::u16string buffer;

			const auto& raw_number_string_buffer =
				str.at("raw_string").as_array();

			for (const auto number : raw_number_string_buffer)
			{
				buffer += number.as_int64();
			}

			result = Kotek::ktk::string(buffer.begin(), buffer.end());
		}
		else if (char_name == "char32_t")
		{
			Kotek::ktk::u32string buffer;

			const auto& raw_number_string_buffer =
				str.at("raw_string").as_array();

			for (const auto number : raw_number_string_buffer)
			{
				buffer += number.as_int64();
			}

			result = Kotek::ktk::string(buffer.begin(), buffer.end());
		}
		else if (char_name == "wchar_t")
		{
			Kotek::ktk::wstring buffer;

			const auto& raw_number_string_buffer =
				str.at("raw_string").as_array();

			for (const auto number : raw_number_string_buffer)
			{
				buffer += number.as_int64();
			}

			result = Kotek::ktk::string(buffer.begin(), buffer.end());
		}
		else
		{
			KOTEK_ASSERT(false,
				"can't find an appropriate casting for your type. Engine "
				"supports only UTF-8 and char strings");
		}

		return result;
	}
	else
	{
		const auto& char_string = read_from.as_string();
		return Kotek::ktk::string(char_string.begin(), char_string.end());
	}
}

	#ifdef KOTEK_USE_MEMORY_ALLOCATOR_CPU_MIMALLOC
inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
	Kotek::ktk::json::value& write_to, const Kotek::ktk::u8string& str)
{
	Kotek::ktk::json::object result;

	Kotek::ktk::json::array raw_string(str.begin(), str.end());

	result["type"] = "char8_t";
	result["raw_string"] = raw_string;

	write_to = result;
}

inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
	Kotek::ktk::json::value& write_to, const Kotek::ktk::u16string& str)
{
	Kotek::ktk::json::object result;

	Kotek::ktk::json::array raw_string(str.begin(), str.end());

	result["type"] = "char16_t";
	result["raw_string"] = raw_string;

	write_to = result;
}

inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
	Kotek::ktk::json::value& write_to, const Kotek::ktk::u32string& str)
{
	Kotek::ktk::json::object result;

	Kotek::ktk::json::array raw_string(str.begin(), str.end());

	result["type"] = "char32_t";
	result["raw_string"] = raw_string;

	write_to = result;
}

inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
	Kotek::ktk::json::value& write_to, const Kotek::ktk::wstring& str)
{
	Kotek::ktk::json::object result;

	Kotek::ktk::json::array raw_string(str.begin(), str.end());

	result["type"] = "wchar_t";
	result["raw_string"] = raw_string;

	write_to = result;
}
	#endif

KOTEK_END_NAMESPACE_KTK

KOTEK_END_NAMESPACE_KOTEK

namespace std
{
	inline Kotek::ktk::string tag_invoke(
		const Kotek::ktk::json::value_to_tag<Kotek::ktk::string>& tag,
		const Kotek::ktk::json::value& read_from)
	{
		return Kotek::ktk::tag_invoke(tag, read_from);
	}

	inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
		Kotek::ktk::json::value& write_to, const std::u8string& str)
	{
		Kotek::ktk::json::object result;

		Kotek::ktk::json::array raw_string(str.begin(), str.end());

		result["type"] = "char8_t";
		result["raw_string"] = raw_string;

		write_to = result;
	}

	inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
		Kotek::ktk::json::value& write_to, const std::u16string& str)
	{
		Kotek::ktk::json::object result;

		Kotek::ktk::json::array raw_string(str.begin(), str.end());

		result["type"] = "char16_t";
		result["raw_string"] = raw_string;

		write_to = result;
	}

	inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
		Kotek::ktk::json::value& write_to, const std::u32string& str)
	{
		Kotek::ktk::json::object result;

		Kotek::ktk::json::array raw_string(str.begin(), str.end());

		result["type"] = "char32_t";
		result["raw_string"] = raw_string;

		write_to = result;
	}

	inline void tag_invoke(const Kotek::ktk::json::value_from_tag&,
		Kotek::ktk::json::value& write_to, const std::wstring& str)
	{
		Kotek::ktk::json::object result;

		Kotek::ktk::json::array raw_string(str.begin(), str.end());

		result["type"] = "wchar_t";
		result["raw_string"] = raw_string;

		write_to = result;
	}
} // namespace std

#endif
