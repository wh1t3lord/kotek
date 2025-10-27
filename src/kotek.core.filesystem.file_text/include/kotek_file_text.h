#pragma once

#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.io/include/kotek_core_containers_io.h>
#include <kotek.core.api/include/kotek_api_no_std.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkFileSystem;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

constexpr const char* kFormatResource_Text = ".json";

class ktkResourceViewText;

// TODO: think about save and load operations, because it
// manages resource manager and its loader and saver managers

template <
	kun_ktk uint32_t _ParserBufferSize,
	kun_ktk uint32_t _JsonMemorySize,
	bool _Realloc>
class ktkResourceText
{
private:
	friend class ktkResourceViewText;

public:
	ktkResourceText(
		const ktk_cstring<
			KOTEK_DEF_RESOURCE_TEXT_FILENAME_LENGTH>& filename
	) : m_data{}
	{
	}

	ktkResourceText(void) : m_data{} {}

	ktkResourceText(const ktkResourceText& instance) :
		m_data{instance}
	{
	}

	template <
		kun_ktk size_t _PBS2,
		kun_ktk size_t _JMS2,
		bool _Realloc2,
		typename = std::enable_if_t<
			((_ParserBufferSize >= _PBS2 &&
	          _JsonMemorySize >= _JMS2) ||
	         _Realloc == true)>>
	ktkResourceText(
		const ktkResourceText<_PBS2, _JMS2, _Realloc2>& instance
	) : m_data{instance}
	{
	}

	ktkResourceText& operator=(const ktkResourceText& instance)
	{
		this->m_data.json = instance.m_data.json;
		return *this;
	}
	~ktkResourceText(void) {}

	/* TODO: implement separated loader and saver classes
	bool Load(
	    Core::ktkMainManager& main_manager, const ktk::ustring&
	path);

	/// <summary>
	/// creates file from ktk::ofstream class
	/// </summary>
	/// <param name="path">your full path where file to create
	in your
	/// OS</param> <param
	name="serialized_json_into_string">this is
	/// your valid json which serialize by boost library and
	serialize
	/// function of that library</param> <returns></returns>
	bool Save(Core::ktkMainManager& main_manager,
	    const ktk::ustring& full_path_to_folder,
	    const ktk::ustring& full_path_to_file, bool is_format =
	true);

	// file_name without format!!
	bool Save(
	    Core::ktkMainManager& main_manager, const ktk::ustring&
	path);

	bool Save(Core::ktkFileSystem* p_file_system,
	    const ktk::ustring& full_path_to_folder,
	    const ktk::ustring& full_path_to_file, bool is_format =
	true);

	bool Save(
	    Core::ktkFileSystem* p_file_system, const ktk::ustring&
	path);
	*/

	template <
		typename ReturnType =
			ktkJson<_JsonMemorySize, _Realloc>>
	ReturnType
	Get(const ktk_cstring<
		KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>& key_name
	) const noexcept
	{
		return this->m_data.json.Get<ReturnType>(key_name);
	}

	const ktk::json::object& Get_Object(void) const noexcept
	{
		return this->m_data.json.Get_Object();
	}

	const ktkJson<_JsonMemorySize, _Realloc>& Get_JSON(void) const noexcept
	{
		return this->m_data.json;
	}

	bool
	Is_KeyExist(const ktk_cstring<
				KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>&
	                field_name) const noexcept
	{
		if (field_name.empty())
		{
			KOTEK_MESSAGE_WARNING("field is empty");
			return false;
		}

		const ktk::json::object& json =
			this->m_data.json.Get_Object();

		return json.find(field_name.c_str()) != json.end();
	}

	template <typename DataType>
	void Write(
		const ktk_cstring<
			KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>&
			field_name,
		const DataType& data
	) noexcept
	{
		this->m_data.json.Write<DataType>(field_name, data);
	}

	constexpr const char* Get_FileExtensionName(void
	) const noexcept
	{
		return kFormatResource_Text;
	}

	void Set_JSON(const ktkJson<_JsonMemorySize, _Realloc>& data
	) noexcept
	{
		this->m_data.json = data;
	}

	template <
		kun_ktk size_t _JMS2,
		bool _Realloc2,
		typename = std::enable_if_t<
			((_JsonMemorySize >= _JMS2) || _Realloc == true)>>
	void Set_JSON(const ktkJson<_JMS2, _Realloc2>& data
	) noexcept
	{
		this->m_data.json = data;
	}

	bool Serialize_ToString(kun_ktk cstring& result
	) const noexcept
	{
		bool status = this->m_data.json.Serialize(result);

		KOTEK_ASSERT(
			status, "failed to serialize json as string!"
		);

		return status;
	}

	template <kun_ktk size_t _StringLength, typename _SizeType>
	bool Serialize_ToString(
		char (&buffer_out)[_StringLength], _SizeType& real_size
	) const noexcept
	{
		const auto& obj = this->m_data.json.Get_Object();

		kun_ktk json::serializer sr;
		sr.reset(&obj);
		const auto& str_view = sr.read(buffer_out);

		KOTEK_ASSERT(
			str_view.size() <= _StringLength,
			"something is wrong, did it just json bug and not "
			"on our side? Otherwise it means that real size is "
			"bigger than what you've read, if asset below is "
			"valid then you can ignore this assert"
		);

		real_size = static_cast<_SizeType>(str_view.size());
		buffer_out[str_view.size()] = '\0';

		bool status = sr.done();

		KOTEK_ASSERT(
			status, "failed to serialize json as string!"
		);
		return status;
	}

	constexpr kun_ktk uint8_t Get_MaxFileNameLength(void
	) const noexcept
	{
		return KOTEK_DEF_RESOURCE_TEXT_FILENAME_LENGTH;
	}

	bool Create_FromMemory(
		unsigned char* p_data, kun_ktk size_t size
	) noexcept
	{
		bool status = false;

		KOTEK_ASSERT(p_data, "passed invalid data");
		KOTEK_ASSERT(size > 0, "must be not zero!");

		if constexpr (!_Realloc)
		{
			KOTEK_ASSERT(
				size <= _ParserBufferSize,
				"can't construct json because out of memory!"
			);
		}

		if (!p_data)
			return status;

		if (size == 0)
			return status;

		ktk::json::parse_options options;
		options.allow_comments = true;
		options.allow_invalid_utf8 = true;
		options.allow_trailing_commas = false;

		unsigned char sp_mem[sizeof(ktk::json::storage_ptr)];

		ktk::json::storage_ptr* p_storage = nullptr;

		if constexpr (_Realloc)
		{
			if constexpr (_ParserBufferSize > 0)
			{
				p_storage = new (sp_mem
				) ktk::json::storage_ptr(&this->m_data.resource
				);
			}
			else
			{
				p_storage = new (sp_mem
				) ktk::json::storage_ptr(&this->m_data.resource
				);
			}
		}
		else
		{
			static_assert(
				_ParserBufferSize > 0,
				"it doesn't make any sense! can't be and fix "
				"your template arguments"
			);

			if constexpr (_ParserBufferSize)
			{
				p_storage = new (sp_mem
				) ktk::json::storage_ptr(&this->m_data.resource
				);
			}
		}

		ktk::json::parser parser(*p_storage, options);

		ktk::json::error_code code;

		parser.reset();

		parser.write(
			reinterpret_cast<char*>(p_data), size, code
		);

		if (code)
		{
			KOTEK_MESSAGE(
				"can't parse file status[{}]", code.message()
			);
		}
		else
		{
			ktk::json::value js = parser.release();

			KOTEK_ASSERT(
				js.is_object(),
				"your file must be object not a some code of "
				"json"
			);

			this->m_data.json = js.as_object();
			status = true;
		}

		p_storage->~storage_ptr();

		return status;
	}

	constexpr bool Is_ReallocationSupported(void) const noexcept
	{
		return _Realloc;
	}

	constexpr kun_ktk uint32_t
	Get_MaxSerializeTextBufferSize(void) const noexcept
	{
		return _ParserBufferSize;
	}
	
private:
	ktkJson<_JsonMemorySize, _Realloc>& Get_JSON() noexcept
	{
		return this->m_data.json;
	}

private:
	struct mem_layout_no_embedded_t
	{
		mem_layout_no_embedded_t() {}
		mem_layout_no_embedded_t(const ktkResourceText& instance
		) : json{instance.m_data.json}
		{
		}

		template <
			kun_ktk size_t _PBS2,
			kun_ktk size_t _JMS2,
			bool _Realloc2,
			typename = std::enable_if_t<
				((_ParserBufferSize >= _PBS2 &&
		          _JsonMemorySize >= _JMS2) ||
		         _Realloc == true)>>
		mem_layout_no_embedded_t(
			const ktkResourceText<_PBS2, _JMS2, _Realloc2>&
				instance
		) : json{instance.Get_JSON()}
		{
		}

		ktkJson<_JsonMemorySize, _Realloc> json;
	};

	struct mem_layout_embedded_t
	{
		mem_layout_embedded_t() : mem(), resource{mem}, json{}
		{
		}
		mem_layout_embedded_t(const ktkResourceText& instance) :
			mem(), resource{mem}, json{instance.m_data.json}
		{
		}

		template <
			kun_ktk size_t _PBS2,
			kun_ktk size_t _JMS2,
			bool _Realloc2,
			typename = std::enable_if_t<
				((_ParserBufferSize >= _PBS2 &&
		          _JsonMemorySize >= _JMS2) ||
		         _Realloc == true)>>
		mem_layout_embedded_t(
			const ktkResourceText<_PBS2, _JMS2, _Realloc2>&
				instance
		) : mem(), resource{mem}, json{instance.Get_JSON()}
		{
		}

		unsigned char mem[_ParserBufferSize];
		using resource_t = std::conditional_t<
			_Realloc == true,
			ktk::json::monotonic_resource,
			ktk::json::static_resource>;
		resource_t resource;

		ktkJson<_JsonMemorySize, _Realloc> json;
	};

	using mem_layout_t = std::conditional_t<
		_ParserBufferSize == 0,
		mem_layout_no_embedded_t,
		mem_layout_embedded_t>;

	mem_layout_t m_data;
};

class ktkResourceViewText
{
public:
	template <
		kun_ktk uint32_t _ParserBufferSize,
		kun_ktk uint32_t _JsonMemorySize,
		bool _Realloc>
	ktkResourceViewText(ktkResourceText<
						_ParserBufferSize,
						_JsonMemorySize,
						_Realloc>& inst) :
		m_view{inst.Get_JSON()}
	{
	}

	~ktkResourceViewText() {}

	template<typename ReturnType>
	ReturnType
	Get(const ktk_cstring<
		KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>& key_name
	) const noexcept
	{
		return m_view.Get<ReturnType>(key_name);
	}

	const ktk::json::object& Get_JSON(void) const noexcept
	{
		return m_view.Get_Object();
	}

	bool
	Is_KeyExist(const ktk_cstring<
				KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>&
	                field_name) const noexcept
	{
		if (field_name.empty())
		{
			KOTEK_MESSAGE_WARNING("field is empty");
			return false;
		}

		const ktk::json::object& json = m_view.Get_Object();

		return json.find(field_name.c_str()) != json.end();
	}

	template <typename DataType>
	void Write(
		const ktk_cstring<
			KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>&
			field_name,
		const DataType& data
	) noexcept
	{
		m_view.Write<DataType>(field_name, data);
	}

	constexpr const char* Get_FileExtensionName(void
	) const noexcept
	{
		return kFormatResource_Text;
	}

	bool Serialize_ToString(kun_ktk cstring& result
	) const noexcept
	{
		bool status = m_view.Serialize(result);

		KOTEK_ASSERT(
			status, "failed to serialize json as string!"
		);

		return status;
	}

private:
	ktkJsonView m_view;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
