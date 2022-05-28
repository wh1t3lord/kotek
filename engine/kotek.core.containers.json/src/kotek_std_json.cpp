#include "../include/kotek_std_json.h"

namespace Kotek
{
	namespace Core
	{
		ktkJson::ktkJson(void) {}
		ktkJson::ktkJson(const ktk::json::object& text) : m_json(text) {}
		ktkJson::ktkJson(const ktkJson& instance) : m_json(instance.m_json) {}

		ktkJson& ktkJson::operator=(const ktkJson& instance)
		{
			this->m_json = instance.m_json;
			return *this;
		}

		ktkJson::~ktkJson(void) {}

		ktk::string ktkJson::GetString(
			const ktk::string& key_name) const noexcept
		{
			ktk::string result;

			if (key_name.empty())
			{
				KOTEK_MESSAGE("passed an empty key");
				return (result);
			}

			if (this->m_json.empty())
			{
				KOTEK_MESSAGE("you didn't load file or your file is empty");
				return (result);
			}

			ktk::string_legacy key_name_legacy = key_name.get_as_legacy();

			if (this->m_json.find(key_name_legacy) == this->m_json.end())
			{
				KOTEK_MESSAGE(
					"your json doesn't contain key: {}", key_name.get_as_is());
				return (result);
			}

			const bool is_array = this->m_json.at(key_name_legacy).is_array();

			if (is_array)
			{
				ktk::json::array buffer =
					this->m_json.at(key_name_legacy).as_array();

				for (const auto& value : buffer)
				{
					if (value == 0)
						break;

					ktk::tchar symbol =
						static_cast<ktk::tchar>(value.as_int64());

					result += symbol;
				}
			}
			else
			{
				const bool is_string =
					this->m_json.at(key_name_legacy).is_string();

				if (is_string)
				{
					ktk::string_legacy data(
						this->m_json.at(key_name_legacy).as_string().begin(),
						this->m_json.at(key_name_legacy).as_string().end());
					result = ktk::string(data.begin(), data.end());
				}
				else
				{
					KOTEK_MESSAGE("your unicode string must be array of "
								  "integers with char "
								  "null-symbol at the end");
				}
			}

			return result;
		}

		const ktk::json::object& ktkJson::GetObject(void) const noexcept
		{
			return this->m_json;
		}

		ktkJson& ktkJson::operator=(const ktk::json::object& instance)
		{
			this->m_json = instance;
			return *this;
		}

	} // namespace Core
} // namespace Kotek