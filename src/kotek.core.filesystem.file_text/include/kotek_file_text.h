#pragma once

#include <kotek.core.containers.json/include/kotek_core_containers_json.h>
#include <kotek.core.containers.io/include/kotek_core_containers_io.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkFileSystem;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

constexpr const char* kFormatResource_Text = ".json";

// TODO: think about save and load operations, because it
// manages resource manager and its loader and saver managers

template <kun_ktk uint32_t _EmbeddedSize, bool _Realloc>
class ktkResourceText
{
public:
	ktkResourceText(void) {}

	ktkResourceText(const ktkResourceText& instance) :
		m_data{instance.m_data},
		m_file_name{instance.m_file_name} ktkResourceText(
			const ktk_cstring<
				KOTEK_DEF_RESOURCE_TEXT_FILENAME_LENGTH>&
				file_name
		) : m_file_name{file_name}
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

	template <typename ReturnType = ktkJson>
	ReturnType
	Get(const ktk_cstring<
		KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>& key_name
	) const noexcept
	{
		return this->m_json.Get<ReturnType>(key_name);
	}

	const ktk::json::object& Get_Json(void) const noexcept
	{
		return this->m_data.json.Get_Object();
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
			this->m_json.Get_Object();

		return json.find(field_name.c_str()) != json.end();
	}

	template <typename DataType>
	void Write(
		const ktk_cstring<
			KOTEK_DEF_RESOURCE_TEXT_KEY_FIELD_NAME_LENGTH>&
			field_name,
		DataType data
	) noexcept
	{
		this->m_json.Write<DataType>(field_name, data);
	}

	const char* Get_FileName(void) const noexcept
	{
		return this->m_file_name.c_str();
	}

	constexpr const char* Get_FileExtensionName(void
	) const noexcept
	{
		return kFormatResource_Text;
	}

	void Set_FileName(
		const ktk_cstring<
			KOTEK_DEF_RESOURCE_TEXT_FILENAME_LENGTH>& file_name
	) noexcept
	{
		this->m_file_name = file_name;
	}

	void Set_Json(const ktkJson& data) noexcept
	{
		this->m_data.json = data;
	}

	kun_ktk cstring Get_FileAsSerializedString(void
	) const noexcept
	{
		ktk::cstring result;
		bool status = this->m_data.json.Serialize(result);

		KOTEK_ASSERT(
			status, "failed to serialize json as string!"
		);

		return std::move(result);
	}

	constexpr kun_ktk uint8_t Get_MaxFileNameLength(void
	) const noexcept
	{
		return KOTEK_DEF_RESOURCE_TEXT_FILENAME_LENGTH;
	}

	bool Load_FromMemory(
		unsigned char* p_data, kun_ktk size_t size
	) noexcept
	{
		bool status = false;

		KOTEK_ASSERT(p_data, "passed invalid data");
		KOTEK_ASSERT(size > 0, "must be not zero!");

		if constexpr (!_Realloc)
		{
			KOTEK_ASSERT(
				size <= _EmbeddedSize,
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
			if constexpr (_EmbeddedSize > 0)
			{
				ktk::json::monotonic_resource mr(
					this->m_data.mem, _EmbeddedSize
				);

				p_storage =
					new (sp_mem) ktk::json::storage_ptr(&mr);
			}
			else
			{
				ktk::json::monotonic_resource mr;
				p_storage =
					new (sp_mem) ktk::json::storage_ptr(&mr);
			}
		}
		else
		{
			static_assert(
				_EmbeddedSize > 0,
				"it doesn't make any sense! can't be and fix "
				"your template arguments"
			);

			if constexpr (_EmbeddedSize)
			{
				ktk::json::static_resource static_resource(
					this->m_data.mem
				);
				p_storage = new (sp_mem)
					ktk::json::storage_ptr(&static_resource);
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

			this->m_json = js.as_object();
		}

		status = true;
		return status;
	}

	constexpr bool Is_ReallocSupported(void) const noexcept
	{
		return _Realloc;
	}

	constexpr kun_ktk uint32_t Get_MaxSize(void) const noexcept
	{
		return _EmbeddedSize;
	}

private:
	struct mem_layout_no_embedded_t
	{
		ktkJson json;
	};

	struct mem_layout_embedded_t
	{
		unsigned char mem[_EmbeddedSize];
		ktkJson json;
	};

	using mem_layout_t = std::conditional_t<
		_EmbeddedSize == 0,
		mem_layout_no_embedded_t,
		mem_layout_embedded_t>;

	mem_layout_t m_data;

	/// @brief without extension!!
	ktk_cstring<KOTEK_DEF_RESOURCE_TEXT_FILENAME_LENGTH>
		m_file_name;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
