#pragma once

#include "kotek_std_alias_json.h"
#include <kotek.core.containers.any/include/kotek_core_containers_any.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

template <kun_ktk size_t _MemorySize, bool _Realloc>
class ktkJson
{
public:
	ktkJson(void) : m_data{} {}
	ktkJson(const ktk::json::object& text) : m_data{text} {}
	ktkJson(const ktkJson& instance) : m_data{instance} {}

	template <
		kun_ktk size_t _MemorySize2,
		bool _Realloc2,
		typename = std::enable_if_t<
			(_MemorySize >= _MemorySize2 || _Realloc == true)>>
	ktkJson(const ktkJson<_MemorySize2, _Realloc2>& instance) :
		m_data{instance}
	{
	}

	ktkJson& operator=(const ktkJson& instance)
	{
		this->m_data.json = instance.m_data.json;
		return *this;
	}

	template <
		kun_ktk size_t _MS2,
		bool _Realloc2,
		typename = std::enable_if_t<(_MemorySize >= _MS2 || _Realloc == true)>>
	ktkJson& operator=(const ktkJson<_MS2, _Realloc2>& instance)
	{
		this->m_data.json = instance.Get_Object();
		return *this;
	}

	ktkJson& operator=(const ktk::json::object& instance)
	{
		this->m_data.json = instance;
		return *this;
	}

	~ktkJson(void) {}

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

		if (this->m_data.json.empty())
		{
			KOTEK_MESSAGE_WARNING(
				"you didn't load file or your file is empty"
			);
			return result;
		}

		if (this->m_data.json.find(key_name.c_str()) ==
		    this->m_data.json.end())
		{
			KOTEK_MESSAGE_WARNING(
				"your file doesn't contain key: {}", key_name
			);

			return result;
		}

		const auto& json_value = this->m_data.json.at(key_name);

		result = ktk::json::value_to<ReturnType>(json_value);
#endif

		return result;
	}

	const ktk::json::object& Get_Object(void) const noexcept
	{
		return m_data.json;
	}

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
		this->m_data.json[field_name.c_str()] =
			ktk::json::value_from(data);
	}

	ktk::json::value& operator[](ktk::json::string_view key
	) noexcept
	{
		return this->m_data.json[key];
	}

	bool Serialize(kun_ktk cstring& result) const noexcept
	{
#ifdef KOTEK_USE_BOOST_LIBRARY
		bool status = false;

		if (this->m_data.json.empty())
			return status;

		result = ktk::json::serialize(this->m_data.json);

		status = true;

		return status;
#else
		bool status = false;
	#error implement this!
		return status;
#endif
	}

	constexpr kun_ktk size_t Get_PreallocateMemorySize(void
	) const noexcept
	{
		return _MemorySize;
	}

	constexpr bool Is_ReallocationSupported(void) const noexcept
	{
		return _Realloc;
	}

private:
	struct mem_layout_no_embedded_t
	{
		mem_layout_no_embedded_t() {}

		mem_layout_no_embedded_t(const ktk::json::object& obj) :
			json{obj}
		{
		}

		mem_layout_no_embedded_t(const ktkJson& instance) :
			json{instance.m_data.json}
		{
		}

		ktk::json::object json;
	};

	struct mem_layout_embedded_t
	{
		mem_layout_embedded_t() :
			mem{}, resource{mem},
			json(ktk::json::storage_ptr(&resource))
		{
		}

		mem_layout_embedded_t(const ktk::json::object& obj) :
			mem{}, resource{mem},
			json(obj, ktk::json::storage_ptr(&resource))
		{
		}

		mem_layout_embedded_t(const ktkJson& instance) :
			mem{}, resource{mem},
			json(
				instance.m_data.json,
				ktk::json::storage_ptr(&resource)
			)
		{
		}

		template <
			kun_ktk size_t _MemorySize2,
			bool _Realloc2,
			typename = std::enable_if_t<
				(_MemorySize >= _MemorySize2 || _Realloc == true
		        )>>
		mem_layout_embedded_t(
			const ktkJson<_MemorySize2, _Realloc2>& instance
		) :
			mem{}, resource{mem},
			json{
				instance.Get_Object(),
				ktk::json::storage_ptr(&resource)
			}
		{
		}

		unsigned char mem[_MemorySize];

		using resource_t = std::conditional_t<
			_Realloc == true,
			ktk::json::monotonic_resource,
			ktk::json::static_resource>;

		resource_t resource;

		ktk::json::object json;
	};

	using mem_layout_t = std::conditional_t<
		_MemorySize == 0,
		mem_layout_no_embedded_t,
		mem_layout_embedded_t>;

	mem_layout_t m_data;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
