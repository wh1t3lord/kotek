#pragma once

#include "kotek_std_alias_json.h"
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkJson
{
public:
	ktkJson(void);
	ktkJson(const ktk::json::object& text);
	ktkJson(const ktkJson& instance);

	ktkJson& operator=(const ktkJson& instance);
	ktkJson& operator=(const ktk::json::object& instance);

	~ktkJson(void);

	/// <summary>
	/// If you want to obtain string you must use GetString
	/// method instead
	/// </summary>
	/// <typeparam name="ReturnType">templated
	/// parameter</typeparam> <param name="key_name">json
	/// key</param> <returns>Your specified ReturnType</returns>
	template <typename ReturnType>
	ReturnType
	Get(const ktk_cstring<
		KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>& key_name
	) const noexcept
	{
		ReturnType result{};

#ifdef KOTEK_USE_BOOST_LIBRARY
		if (key_name.empty())
		{
			KOTEK_MESSAGE_WARNING("passed an empty key");
			return result;
		}

		if (this->m_json.empty())
		{
			KOTEK_MESSAGE_WARNING(
				"you didn't load file or your file is empty"
			);
			return result;
		}

		if (this->m_json.find(key_name.c_str()) ==
		    this->m_json.end())
		{
			KOTEK_MESSAGE_WARNING(
				"your file doesn't contain key: {}", key_name
			);

			return result;
		}

		const auto& json_value = this->m_json.at(key_name);

		result = ktk::json::value_to<ReturnType>(json_value);
#endif

		return result;
	}

	const ktk::json::object& Get_Object(void) const noexcept;

	// TODO: standartize this thing for any type what the kotek
	// has, containers, math structures, graphs and etc

	template <typename DataType>
	void Write(
		const ktk_cstring<
			KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>&
			field_name,
		DataType data
	) noexcept
	{
		this->m_json[field_name.c_str()] =
			ktk::json::value_from(data);
	}

	ktk::json::value& operator[](ktk::json::string_view key
	) noexcept
	{
		return this->m_json[key];
	}

	bool Serialize(kun_ktk cstring& result) const noexcept
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		bool status = false;

		if (this->m_json.empty())
			return status;

		result = ktk::json::serialize(this->m_json);

		status = true;
	
		return status;
#else
		bool status = false;
		#error implement this!
		return status;
#endif
	}

private:
	ktk::json::object m_json;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
