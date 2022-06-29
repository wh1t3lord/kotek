#pragma once

#include "kotek_std_alias_json.h"
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

namespace Kotek
{
	namespace Core
	{
		class ktkJson
		{
		public:
			ktkJson(void);
#ifdef KOTEK_USE_BOOST_LIBRARY
			ktkJson(const ktk::json::object& text);
#endif
			ktkJson(const ktkJson& instance);

			ktkJson& operator=(const ktkJson& instance);
			ktkJson& operator=(const ktk::json::object& instance);

			~ktkJson(void);

			template <typename BasedType>
			ktk::vector<BasedType> GetVector(
				const ktk::string& key_name) const noexcept
			{
				static_assert(std::is_arithmetic<BasedType>::value);

				ktk::vector<BasedType> result;

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

				ktk::string_legacy key_name_legacy =
					ktk::string_legacy(key_name.begin(), key_name.end());

				if (this->m_json.find(key_name_legacy) == this->m_json.end())
				{
					KOTEK_MESSAGE(
						"! your file doesn't contain key: {}", key_name);
					return (result);
				}

				const bool is_array =
					this->m_json.at(key_name_legacy).is_array();

				if (is_array)
				{
					ktk::json::array buffer =
						this->m_json.at(key_name_legacy).as_array();

					for (const auto& value : buffer)
					{
						bool is_uint64 = value.is_uint64();
						bool is_int64 = value.is_int64();
						bool is_bool = value.is_bool();
						bool is_double = value.is_double();

						if (is_double)
						{
							buffer.push_back(
								static_cast<BasedType>(value.as_double()));
						}
						else if (is_uint64)
						{
							buffer.push_back(
								static_cast<BasedType>(value.as_uint64()));
						}
						else if (is_int64)
						{
							buffer.push_back(
								static_cast<BasedType>(value.as_int64()));
						}
						else if (is_bool)
						{
							buffer.push_back(
								static_cast<BasedType>(value.as_bool()));
						}
					}
				}
				else
				{
					KOTEK_MESSAGE("this only for isl::vector type");
				}

				return result;
			}

			ktk::string GetString(const ktk::string& key_name) const noexcept;

			/// <summary>
			/// If you want to obtain string you must use GetString method
			/// instead
			/// </summary>
			/// <typeparam name="ReturnType">templated parameter</typeparam>
			/// <param name="key_name">json key</param>
			/// <returns>Your specified ReturnType</returns>
			template <typename ReturnType>
			ReturnType Get(const ktk::string& key_name) const noexcept
			{
				ktk::any result = ReturnType{};

				if (key_name.empty())
				{
					KOTEK_MESSAGE("passed an empty key");
					return std::any_cast<ReturnType>(result);
				}

				if (this->m_json.empty())
				{
					KOTEK_MESSAGE("you didn't load file or your file is empty");
					return std::any_cast<ReturnType>(result);
				}

				ktk::string_legacy key_name_legacy = key_name.get_as_legacy();

				if (this->m_json.find(key_name_legacy) == this->m_json.end())
				{
					KOTEK_MESSAGE("your file doesn't contain key: {}",
						key_name.get_as_is());
					return std::any_cast<ReturnType>(result);
				}

				if (this->m_json.at(key_name_legacy).is_object())
				{
					result =
						ktkJson(this->m_json.at(key_name_legacy).as_object());
					return std::any_cast<ReturnType>(result);
				}

				const bool is_number = std::is_arithmetic<ReturnType>::value;
				const bool is_signed = !std::is_unsigned<ReturnType>::value;
				const bool is_floating =
					std::is_floating_point<ReturnType>::value;
				const bool is_array =
					this->m_json.at(key_name_legacy).is_array();
				const bool is_logical =
					this->m_json.at(key_name_legacy).is_bool();

				if (is_number)
				{
					if (is_signed && is_floating == false)
					{
						result = static_cast<ReturnType>(
							this->m_json.at(key_name_legacy).as_int64());
					}
					else if (is_signed == false && is_floating == false)
					{
						if (is_logical)
						{
							result = this->m_json.at(key_name_legacy).as_bool();
						}
						else
						{
							result = static_cast<ReturnType>(
								this->m_json.at(key_name_legacy).as_uint64());
						}
					}
					else if (is_floating)
					{
						result = static_cast<ReturnType>(
							this->m_json.at(key_name_legacy).as_double());
					}
					else
					{
						KOTEK_ASSERT(false, "unreachable section");
					}
				}
				else if (is_array)
				{
					result = this->m_json.at(key_name_legacy).as_array();
				}

				return std::any_cast<ReturnType>(result);
			}

			const ktk::json::object& GetObject(void) const noexcept;

			template <typename DataType>
			void Write(const ktk::string& field_name, DataType data) noexcept
			{
				this->m_json[field_name.get_as_legacy().c_str()] = data;
			}

			ktk::string Serialize(void) const noexcept
			{
				if (this->m_json.empty())
					return "";

				return ktk::json::serialize(this->m_json);
			}

		private:
			ktk::json::object m_json;
		};
	} // namespace Core
} // namespace Kotek