#include "../include/kotek_resource_manager_loader.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkResourceLoaderManager::ktkResourceLoaderManager(void) {}

ktkResourceLoaderManager::~ktkResourceLoaderManager(void) {}

void ktkResourceLoaderManager::Initialize(
	ktkIFileSystem* p_manager_filesystem, ktkMainManager* p_main_manager)
{
	this->m_p_manager_filesystem = p_manager_filesystem;

	this->Set_Loader(eResourceLoadingType::kText,
		new ktkResourceLoaderFile_Text(p_main_manager));

	for (unsigned char i = 0;
		 i < KOTEK_DEF_RESOURCE_LOADER_MANAGER_SIZE_FILE_POOL; ++i)
	{
		this->m_readers[i].second = true;
	}
}

void ktkResourceLoaderManager::Shutdown(void)
{
	for (auto& [type, p_loader] : this->m_loaders)
	{
		delete p_loader;
	}

	this->m_loaders.clear();

#ifdef KOTEK_DEBUG
	for (auto& [id, pair] : this->m_readers)
	{
		auto is_free = pair.second.load();

		KOTEK_ASSERT(is_free,
			"file is not free, but we do shutdown that means that file is "
			"opened and awaits for writing or currently writes something rn!");
	}
#endif

	this->m_readers.clear();
}

void ktkResourceLoaderManager::Set_Loader(
	eResourceLoadingType resource_type, ktkIResourceLoader* p_loader)
{
	KOTEK_ASSERT(p_loader, "you can't pass an invalid pointer here");

	KOTEK_ASSERT(p_loader->Get_Type() != eResourceLoadingType::kUnknown,
		"you must override Get_Type method because it uses default "
		"return type. It is not acceptable because developer must "
		"strictly specify what its instance contains and for what it "
		"was created");

	if (this->m_loaders.find(resource_type) != this->m_loaders.end())
	{
		KOTEK_MESSAGE_WARNING("[Core] replacing resource loader for type: [{}]",
			helper::Translate_ResourceLoadingType(resource_type));
	}

	this->m_loaders[resource_type] = p_loader;
}

ktkIResourceLoader* ktkResourceLoaderManager::Get_Loader(
	eResourceLoadingType resource_type) const noexcept
{
	KOTEK_ASSERT(resource_type != eResourceLoadingType::kUnknown,
		"can't search for a such enum!!!");

	ktkIResourceLoader* p_result{};

	if (this->m_loaders.find(resource_type) != this->m_loaders.end())
	{
		p_result = this->m_loaders.at(resource_type);

		KOTEK_ASSERT(p_result->Get_Type() == resource_type,
			"you must specify correct type of what you loading: [{}], "
			"because your loader has [{}]",
			helper::Translate_ResourceLoadingType(resource_type),
			helper::Translate_ResourceLoadingType(p_result->Get_Type()));

		if (p_result->Get_Type() != resource_type)
			p_result = nullptr;
	}

	if (p_result == nullptr)
	{
		KOTEK_MESSAGE_WARNING(
			"couldn't obtain loader for resource loading type: [{}]",
			helper::Translate_ResourceLoadingType(resource_type));
	}

	return p_result;
}

bool ktkResourceLoaderManager::Load(const ktk_filesystem_path& path,
	kun_core ktkResourceHandle object_from_construct) noexcept
{
	KOTEK_ASSERT(path.has_extension(),
		"you must provide an extension for your file: [{}]", path);

	bool result{};

	auto resource_type = this->DetectResourceTypeByFileFormat(path);

	auto* p_loader = this->Get_Loader(resource_type);

	KOTEK_ASSERT(p_loader, "failed to find loader for format file: [{}]",
		path.extension());

	if (p_loader)
		result = p_loader->Load(path, object_from_construct);

	return result;
}

bool ktkResourceLoaderManager::Open(const ktk_filesystem_path& path,
	eResourceReadingType resource_type, eResourceReadingPolicy policy,
	kun_ktk uint32_t id) noexcept
{
	KOTEK_ASSERT(path.empty() == false, "you must pass a not empty path!");
	KOTEK_ASSERT(
		resource_type != eResourceReadingType::kUnknown, "must be defined!");
	KOTEK_ASSERT(
		policy != eResourceReadingPolicy::kEndOfEnum, "must be defined!");
	KOTEK_ASSERT(id != kun_ktk uint32_t(-1), "must be valid!");
	KOTEK_ASSERT(this->m_p_manager_filesystem,
		"you must initialize file system before calling this method!");
	KOTEK_ASSERT(this->m_readers.find(id) != this->m_readers.end(),
		"failed to find file by its id: [{}]", id);

	bool result{};

	switch (resource_type)
	{
	case eResourceReadingType::kText:
	{
		KOTEK_ASSERT(path.has_extension() == true, "must have extension");
		KOTEK_ASSERT(
			path.extension().string().find("json") != std::string::npos ||
				path.extension().string().find("txt") != std::string::npos ||
				path.extension().string().find("ini"),
			"must have a such extension name");

		auto* file = &this->m_readers.at(id).first;

		auto is_already_opened = this->m_readers.at(id).second.load();

		file->open(path.c_str());
		result = file->good();

		KOTEK_ASSERT(result, "failed to open file: [{}]; error: {}", path,
			strerror(errno));

		this->m_readers.at(id).second = false;

		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "you forgot to register new type!");
		break;
	}
	}

	return result;
}

void ktkResourceLoaderManager::Seekg(kun_ktk uint32_t resource_id,
	kun_ktk size_t bytes, eFileSeekDirectionType type)
{
	KOTEK_ASSERT(this->m_readers.find(resource_id) != this->m_readers.end(),
		"can't find a such file: {}", resource_id);

	if (this->m_readers.find(resource_id) != this->m_readers.end())
	{
		auto& file = this->m_readers.at(resource_id).first;

		KOTEK_ASSERT(this->m_readers.at(resource_id).second == false,
			"file must be in state for writing!");

		std::ios_base::seekdir direction{};

		switch (type)
		{
		case Core::eFileSeekDirectionType::kSeekdDirectionCurrent:
		{
			direction = std::ios::cur;
			break;
		}
		case Core::eFileSeekDirectionType::kSeekDirectionBegin:
		{
			direction = std::ios::beg;
			break;
		}
		case Core::eFileSeekDirectionType::kSeekDirectionEnd:
		{
			direction = std::ios::end;
			break;
		}
		}

#ifdef KOTEK_DEBUG
		bool eof_state = file.eof();
#endif

		file.seekg(bytes, direction);

#ifdef KOTEK_DEBUG
		KOTEK_ASSERT(file.good(),
			"[std::ifstream] failed to seekg = [errno:{}:{}], did you reach "
			"eof and forgot to .clear call? [eof={}]",
			strerror(errno), errno, eof_state);
#endif
	}
}

kun_ktk size_t ktkResourceLoaderManager::Tellg(kun_ktk uint32_t resource_id)
{
	kun_ktk size_t result{};

	KOTEK_ASSERT(this->m_readers.find(resource_id) != this->m_readers.end(),
		"can't find a such file: {}", resource_id);

	if (this->m_readers.find(resource_id) != this->m_readers.end())
	{
		auto& file = this->m_readers.at(resource_id).first;

#ifdef KOTEK_DEBUG
		bool eof_state = file.eof();
#endif

		result = file.tellg();

#ifdef KOTEK_DEBUG
		KOTEK_ASSERT(file.good(),
			"[std::ifstream] failed to tellg = [errno:{}:{}], did you reach "
			"eof and forgot to .clear call? [eof={}]",
			strerror(errno), errno, eof_state);
#endif
	}

	return result;
}

void ktkResourceLoaderManager::Read(
	kun_ktk uint32_t resource_id, char* p_buffer, kun_ktk size_t size)
{
	KOTEK_ASSERT(resource_id != kun_ktk uint32_t(-1), "must be valid number!");
	KOTEK_ASSERT(p_buffer, "must be valid!");

	if (this->m_readers.find(resource_id) != this->m_readers.end())
	{
		auto& file = this->m_readers.at(resource_id).first;
		file.read(p_buffer, size);
	}
}

void ktkResourceLoaderManager::Clear(
	kun_ktk uint32_t resource_id, eFileIOState state)
{
	KOTEK_ASSERT(resource_id != kun_ktk uint32_t(-1), "must be valid number!");
	KOTEK_ASSERT(
		this->m_readers.find(resource_id) != this->m_readers.end(), "must be found");

	if (this->m_readers.find(resource_id) != this->m_readers.end())
	{
		auto& file = this->m_readers.at(resource_id).first;

		std::ifstream::iostate converted_state = std::ifstream::failbit;
		switch (state)
		{
		case eFileIOState::kStateEOF:
		{
			converted_state = std::ifstream::eofbit;
			break;
		}
		case eFileIOState::kStateFail:
		{
			converted_state = std::ifstream::failbit;
			break;
		}
		case eFileIOState::kStateBad:
		{
			converted_state = std::ifstream::badbit;
			break;
		}
		case eFileIOState::kStateGood:
		{
			converted_state = std::ifstream::goodbit;
			break;
		}
		default:
		{
			KOTEK_ASSERT(
				false, "unregistered state please report to developers!");
		}
		}

		file.clear(converted_state);
	}

}

bool ktkResourceLoaderManager::EndOfFile(kun_ktk uint32_t resource_id)
{
	KOTEK_ASSERT(
		resource_id != kun_ktk uint32_t(-1), "must be a valid number!");
	KOTEK_ASSERT(this->m_readers.find(resource_id) != this->m_readers.end(),
		"must be valid!");

	if (this->m_readers.find(resource_id) != this->m_readers.end())
	{
		return this->m_readers.at(resource_id).first.eof();
	}

	return false;
}

bool ktkResourceLoaderManager::Is_Open(kun_ktk uint32_t resource_id) noexcept
{
	KOTEK_ASSERT(resource_id != kun_ktk uint32_t(-1), "must be valid!");

	bool result{};
	if (this->m_readers.find(resource_id) != this->m_readers.end())
	{
		result = this->m_readers.at(resource_id).first.is_open();
	}

	return result;
}

bool ktkResourceLoaderManager::Close(kun_ktk uint32_t id) noexcept
{
	KOTEK_ASSERT(id != kun_ktk uint32_t(-1), "must be valid number!");
	KOTEK_ASSERT(this->m_readers.empty() == false, "early calling!");

	bool result{};

	if (this->m_readers.empty() == false)
	{
		if (this->m_readers.find(id) != this->m_readers.end())
		{
			KOTEK_ASSERT(this->m_readers.at(id).second == false,
				"you try to close the file that was closed or not even "
				"opened!");

			this->m_readers.at(id).first.close();
			// we set this file that it is 'freed' for writing
			this->m_readers.at(id).second = true;
			KOTEK_MESSAGE("closed file: {}", id);
			result = true;
		}
	}

	return result;
}

kun_ktk streamsize_t ktkResourceLoaderManager::Gcount(
	kun_ktk uint32_t id) noexcept
{
	KOTEK_ASSERT(id != kun_ktk uint32_t(-1), "must be valid number!");
	KOTEK_ASSERT(this->m_readers.empty() == false, "early calling!");

	if (this->m_readers.empty() == false)
	{
		if (this->m_readers.find(id) != this->m_readers.end())
		{
			return this->m_readers.at(id).first.gcount();
		}
	}

	return 0;
}

kun_ktk uint32_t ktkResourceLoaderManager::GenerateFileID(void) noexcept
{
	KOTEK_ASSERT(this->m_readers.empty() == false,
		"you must initialize your file pool!");

	// this means that if result equals to
	// KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL it means value is invalid
	// because we initialize from [0,
	// KOTEK_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL - 1]
	kun_ktk uint32_t result{KOTEK_DEF_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL};

#ifdef KOTEK_DEBUG
	bool is_any_avaiable = false;
#endif

	for (const auto& [id, pair] : this->m_readers)
	{
		bool is_available = pair.second;

		if (is_available)
		{
			result = id;

#ifdef KOTEK_DEBUG
			is_any_avaiable = true;
#endif
			break;
		}
	}

	this->m_readers.at(result).second = false;

#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(is_any_avaiable,
		"failed to obtain any avaiable file for writing. It means that engine "
		"doesn't have any freed file, allocate more! Current file pool size "
		"is: [{}]",
		KOTEK_DEF_RESOURCE_SAVER_MANAGER_SIZE_FILE_POOL);
#endif

	return result;
}

eResourceLoadingType ktkResourceLoaderManager::DetectResourceTypeByFileFormat(
	const ktk_filesystem_path& path) noexcept
{
	KOTEK_ASSERT(this->m_loaders.empty() == false,
		"you must provide some loaders. Otherwise loaders are empty thus "
		"loader manager is invalid!");

	eResourceLoadingType result{eResourceLoadingType::kUnknown};

	for (const auto& [resource_type, p_loader] : this->m_loaders)
	{
		bool status = p_loader->DetectTypeByFullPath(path);

		if (status == false)
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("Determing format type of file and it is not: {}",
				helper::Translate_ResourceLoadingType(p_loader->Get_Type()));
#endif
		}
		else
		{
#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE(
				"Obtained type by loader: {}", p_loader->Get_UserDescription());
#endif

			result = p_loader->Get_Type();
			break;
		}
	}

	KOTEK_ASSERT(result != eResourceLoadingType::kUnknown,
		"you didn't provide any detector for a format file: {}",
		reinterpret_cast<const char*>(path.extension().u8string().c_str()));

	return result;
}

/*
kun_core ktkResourceHandle ktkResourceLoaderManager::Load_Text(
    const ktk_filesystem_path& path) noexcept
{
    return kun_core ktkResourceHandle();
}

kun_core ktkResourceHandle ktkResourceLoaderManager::Load_Texture(
    const ktk_filesystem_path& path) noexcept
{
    return kun_core ktkResourceHandle();
}

kun_core ktkResourceHandle ktkResourceLoaderManager::Load_Model(
    const ktk_filesystem_path& path) noexcept
{
    auto resource_type = this->DetectResourceTypeByFileFormat(path);

    auto* p_loader = this->Get_Loader(resource_type);

    if (p_loader)
    {
        auto result = p_loader->Load(path);
        return result;
    }

    return kun_core ktkResourceHandle();
}

kun_core ktkResourceHandle ktkResourceLoaderManager::Load_Sound(
    const ktk_filesystem_path& path) noexcept
{
    return kun_core ktkResourceHandle();
}

kun_core ktkResourceHandle ktkResourceLoaderManager::Load_Video(
    const ktk_filesystem_path& path) noexcept
{
    return kun_core ktkResourceHandle();
}

kun_core ktkResourceHandle ktkResourceLoaderManager::Load_CPlusPlusLibrary(
    const ktk_filesystem_path& path) noexcept
{
    return kun_core ktkResourceHandle();
}

bool ktkResourceLoaderManager::Load_Text(
    const ktk_filesystem_path& path, kun_core ktkResourceHandle
object_from_construct) noexcept
{
    if (this->m_p_manager_filesystem->IsValidPath(path) == false)
    {
        KOTEK_ASSERT(false, "path is not valid: {}", path.c_str());
        return false;
    }

    ktkFile* p_casted_file = std::any_cast<ktkFile*>(object_from_construct);

    KOTEK_ASSERT(p_casted_file,
        "you must have a valid instance of object_from_construct");

    // TODO: make a loader for boost json and for nlohmann as separeted
    // instances that have implementation based on interface
    // ktkIResourceLoader

    ktkJson json;

#ifdef KOTEK_DEBUG
    KOTEK_MESSAGE("reading file: {}", path.c_str());
#endif

    ktk::ifstream file(path);

    if (file.good())
    {
        ktk::istreambuf_iterator being(file);
        ktk::istreambuf_iterator end;

        ktk::string_legacy content(being, end);

        ktk::json::parser parser;

        ktk::json::error_code code;

        parser.reset();

        parser.write(content, code);

        if (code)
        {
            KOTEK_MESSAGE("can't parse file status: [{}]",
                ktk::ustring(code.message()).get_as_is());
        }
        else
        {
            ktk::json::value data = parser.release();

            KOTEK_ASSERT(data.is_object(),
                "your file must be object not a some code of json");

            json = data.as_object();
        }
    }
    else
    {
        KOTEK_MESSAGE("can't read file: {}", path.c_str());
        return false;
    }

    file.close();

    p_casted_file->Set_Json(json);
    p_casted_file->Set_FileName(path.filename().string());

    return true;
}

bool ktkResourceLoaderManager::Load_Texture(
    const ktk_filesystem_path& path, kun_core ktkResourceHandle
object_from_construct) noexcept
{
    return true;
}

bool ktkResourceLoaderManager::Load_Model(
    const ktk_filesystem_path& path, kun_core ktkResourceHandle
object_from_construct) noexcept
{
    auto resource_type = this->DetectResourceTypeByFileFormat(path);

    auto* p_loader = this->Get_Loader(resource_type);

    bool result{};

    if (p_loader)
    {
        result = p_loader->Load(path, object_from_construct);

        return result;
    }

    return result;
}

bool ktkResourceLoaderManager::Load_Sound(
    const ktk_filesystem_path& path, kun_core ktkResourceHandle
object_from_construct) noexcept
{
    return true;
}

bool ktkResourceLoaderManager::Load_Video(
    const ktk_filesystem_path& path, kun_core ktkResourceHandle
object_from_construct) noexcept
{
    return true;
}
*/

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK