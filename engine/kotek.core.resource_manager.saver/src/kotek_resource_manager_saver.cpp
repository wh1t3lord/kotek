#include "../include/kotek_resource_manager_saver.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkResourceSaverManager::ktkResourceSaverManager(void) :
	ktkIResourceSaverManager()
{
}

ktkResourceSaverManager::~ktkResourceSaverManager(void) {}

void ktkResourceSaverManager::Initialize(
	ktkIFileSystem* p_filesystem, ktkMainManager* p_main_manager)
{
	this->m_p_manager_filesystem = p_filesystem;

	this->Set_Saver(eResourceLoadingType::kText,
		new ktkResourceSaverFile_Text(p_main_manager));
}

void ktkResourceSaverManager::Shutdown(void) {}

void ktkResourceSaverManager::Set_Saver(
	eResourceLoadingType resource_type, ktkIResourceSaver* p_saver)
{
	KOTEK_ASSERT(p_saver, "you can't pass an invalid pointer here");

	KOTEK_ASSERT(p_saver->Get_Type() != eResourceLoadingType::kUnknown,
		"you must override Get_Type method because it uses default return "
		"type. It is not acceptable because developer must strictly specify "
		"what its instance contains and for what it was created");

	if (this->m_savers.find(resource_type) != this->m_savers.end())
	{
		KOTEK_MESSAGE_WARNING("replacing resource loader for type: [{}]",
			helper::Translate_ResourceLoadingType(resource_type));
	}

	this->m_savers[resource_type] = p_saver;
}

ktkIResourceSaver* ktkResourceSaverManager::Get_Saver(
	eResourceLoadingType resource_type) const noexcept
{
	KOTEK_ASSERT(resource_type != eResourceLoadingType::kUnknown,
		"you must pass a valid enum");

	ktkIResourceSaver* p_result{};

	if (this->m_savers.find(resource_type) != this->m_savers.end())
	{
		p_result = this->m_savers.at(resource_type);

		KOTEK_ASSERT(p_result->Get_Type() == resource_type,
			"you must specify correct type of what you saving: [{}], because "
			"your saver has [{}]",
			helper::Translate_ResourceLoadingType(resource_type),
			helper::Translate_ResourceLoadingType(p_result->Get_Type()));

		if (p_result->Get_Type() != resource_type)
			p_result = nullptr;
	}

	if (p_result == nullptr)
	{
		KOTEK_MESSAGE_WARNING(
			"couldn't obtain loader for resource saving type: [{}]",
			helper::Translate_ResourceLoadingType(resource_type));
	}

	return p_result;
}

bool ktkResourceSaverManager::Save(
	const ktk::filesystem::path& path, ktk::any data) noexcept
{
	KOTEK_ASSERT(path.has_extension(),
		"you must provide an extension for your file: [{}]", path);

	bool result{};

	auto resource_type = this->DetectResourceTypeByFileFormat(path);

	auto* p_saver = this->Get_Saver(resource_type);

	KOTEK_ASSERT(p_saver, "failed to find saver for format file: [{}]",
		path.extension());

	if (p_saver)
		result = p_saver->Save(path, data);

	return result;
}

bool ktkResourceSaverManager::Open(const ktk::filesystem::path& path,
	eResourceWritingType resource_type, eResourceWritingPolicy policy,
	eResourceWritingMode mode, ktk::uint32_t id) noexcept
{
	KOTEK_ASSERT(path.empty() == false, "you must pass a not empty path!");
	KOTEK_ASSERT(
		resource_type != eResourceWritingType::kUnknown, "must be defined!");
	KOTEK_ASSERT(
		policy != eResourceWritingPolicy::kEndOfEnum, "must be defined!");
	KOTEK_ASSERT(mode != eResourceWritingMode::kEndOfEnum, "must be defined!");
	KOTEK_ASSERT(id != ktk::uint32_t(-1), "must be valid!");
	KOTEK_ASSERT(this->m_p_manager_filesystem,
		"you must initialize file system before calling this method!");
	KOTEK_ASSERT(this->m_writers.size() < this->m_writers.max_size(),
		"overflow system can't allocate more!");

	bool result{};

	switch (resource_type)
	{
	case eResourceWritingType::kText:
	{
		KOTEK_ASSERT(path.has_extension() == true, "must have extension");
		KOTEK_ASSERT(
			path.extension().string().find("json") != std::string::npos,
			"must have a such name");

		result = this->CreateWriter(path, id);
		break;
	}
	}

	return result;
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, const char* p_string) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id);

		file << p_string;
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, const char* p_string, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id);
		file.write(p_string, size);
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, const unsigned char* p_raw_memory) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id);
		file << p_raw_memory;
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const unsigned char* p_raw_memory, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such file!");

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id);
		file.write((char*)&p_raw_memory[0], size);
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, ktk::int32_t value) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id);
		file << value;
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, ktk::float_t value) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id);
		file << value;
	}
}

void ktkResourceSaverManager::Write(
	ktk::uint32_t resource_id, ktk::double_t value) noexcept
{
	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		auto& file = this->m_writers.at(resource_id);
		file << value;
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::int32_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::cofstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id);
	}

	if (p_file)
	{
		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::uint32_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::cofstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id);
	}

	if (p_file)
	{
		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::float_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::cofstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id);
	}

	if (p_file)
	{
		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::double_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::cofstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id);
	}

	if (p_file)
	{
		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::int8_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::cofstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id);
	}

	if (p_file)
	{
		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::uint8_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::cofstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id);
	}

	if (p_file)
	{
		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::int16_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::cofstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id);
	}

	if (p_file)
	{
		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

void ktkResourceSaverManager::Write(ktk::uint32_t resource_id,
	const ktk::uint16_t* p_arr, ktk::size_t size) noexcept
{
	KOTEK_ASSERT(p_arr, "must be valid pointer!");
	KOTEK_ASSERT(size != ktk::size_t(-1), "must have a valid size");
	KOTEK_ASSERT(size != 0, "can't be zero! Just doesn't make any sense!");

	KOTEK_ASSERT(this->m_writers.find(resource_id) != this->m_writers.end(),
		"can't find a such thing!");

	ktk::cofstream* p_file{};
	if (this->m_writers.find(resource_id) != this->m_writers.end())
	{
		p_file = &this->m_writers.at(resource_id);
	}

	if (p_file)
	{
		for (auto i = 0; i < size; ++i)
		{
			(*p_file) << p_arr[i];
		}
	}
}

bool ktkResourceSaverManager::Close(ktk::uint32_t id) noexcept
{
	KOTEK_ASSERT(id != ktk::uint32_t(-1), "must be valid number!");
	KOTEK_ASSERT(this->m_writers.empty() == false, "early calling!");

	bool result{};

	if (this->m_writers.empty() == false)
	{
		if (this->m_writers.find(id) != this->m_writers.end())
		{
			this->m_writers.erase(id);
			result = true;
		}
	}

	return result;
}

eResourceLoadingType ktkResourceSaverManager::DetectResourceTypeByFileFormat(
	const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(this->m_savers.empty() == false,
		"you must provide some loaders. Otherwise loaders are empty thus "
		"loader manager is invalid!");

	eResourceLoadingType result{eResourceLoadingType::kUnknown};

	for (const auto& [resource_type, p_saver] : this->m_savers)
	{
		bool status = p_saver->DetectTypeByFullPath(path);

		if (status == false)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("Determing format type of file and it is not: {}",
				helper::Translate_ResourceLoadingType(p_saver->Get_Type()));
#endif
		}
		else
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE(
				"Obtained type by loader: {}", p_saver->Get_UserDescription());
#endif

			result = p_saver->Get_Type();
			break;
		}
	}

	KOTEK_ASSERT(result != eResourceLoadingType::kUnknown,
		"you didn't provide any detector for a format file: {}",
		reinterpret_cast<const char*>(path.extension().u8string().c_str()));

	return result;
}

bool ktkResourceSaverManager::CreateWriter(
	const ktk::filesystem::path& path, ktk::uint32_t id) noexcept
{
	KOTEK_ASSERT(path.empty() == false, "must be not empty!");
	KOTEK_ASSERT(id != ktk::uint32_t(-1), "msut be valid!");
	KOTEK_ASSERT(this->m_p_manager_filesystem, "must be valid!");
	KOTEK_ASSERT(
		this->m_p_manager_filesystem->IsValidPath(path), "invalid path!");

	bool result{};

	if (this->m_writers.find(id) == this->m_writers.end())
	{
		this->m_writers[id] = ktk::cofstream(path);
		result = true;
	}

	KOTEK_ASSERT(this->m_writers.at(id).good(),
		"something went wrong when we tried to open file!");

	return result;
}

/*
bool ktkResourceSaverManager::Save_Text(
    const ktk::filesystem::path& path, ktk::any data) noexcept
{
    KOTEK_ASSERT(this->m_p_manager_filesystem,
        "you must initialize your file system here");

    if (this->m_p_manager_filesystem->IsValidPath(path) == false)
    {
        KOTEK_ASSERT(false, "path is not valid: {}", path.c_str());
        return false;
    }

    ktkFileText* p_casted_file = std::any_cast<ktkFileText*>(data);

    KOTEK_ASSERT(
        p_casted_file, "you must have a valid instance of ktkFileText");

    KOTEK_ASSERT(p_casted_file->Get_FileName().empty() == false,
        "you can't have an empty filename in your ktkFileText instance");

    auto path_compiled = path;

    path_compiled /= p_casted_file->Get_FileName().get_as_is();

    ktk::ofstream output_file(path_compiled);

    output_file << p_casted_file->Get_FileAsSerializedString().get_as_is();

    output_file.close();

#ifdef KOTEK_DEBUG
    KOTEK_MESSAGE("file was successfully created: {}", path_compiled.c_str());
#endif

    return true;
}

bool ktkResourceSaverManager::Save_Text_Formatted(
    const ktk::filesystem::path& path, ktk::any data) noexcept
{

}

void ktkResourceSaverManager::FormatTextFile_Json(ktk::ofstream& file,
    const ktk::json::value& json, std::string* indent) noexcept
{

}
*/

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK