#include "../include/kotek_resource_manager_loader.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkResourceLoaderManager::ktkResourceLoaderManager(void) {}

ktkResourceLoaderManager::~ktkResourceLoaderManager(void) {}

void ktkResourceLoaderManager::Initialize(ktkIFileSystem* p_manager_filesystem)
{
	this->m_p_manager_filesystem = p_manager_filesystem;
}

void ktkResourceLoaderManager::Shutdown(void) {}

void ktkResourceLoaderManager::Set_Loader(
	eResourceLoadingType resource_type, ktkIResourceLoader* p_loader)
{
	KOTEK_ASSERT(p_loader, "you can't pass an invalid pointer here");

	KOTEK_ASSERT(p_loader->Get_Type() == eResourceLoadingType::kUnknown,
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

ktk::any ktkResourceLoaderManager::Load(
	const ktk::filesystem::path& path) noexcept
{
	KOTEK_ASSERT(path.has_extension(),
		"you must provide an extension for your file: [{}]", path);

	auto resource_type = this->DetectResourceTypeByFileFormat(path);

	auto* p_loader = this->Get_Loader(resource_type);

	KOTEK_ASSERT(p_loader, "failed to find loader for format file: [{}]",
		path.extension());

	if (p_loader)
	{
		return p_loader->Load(path);
	}

	return ktk::any();
}

bool ktkResourceLoaderManager::Load(
	const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
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

eResourceLoadingType ktkResourceLoaderManager::DetectResourceTypeByFileFormat(
	const ktk::filesystem::path& path) noexcept
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
		path.extension().c_str());

	return result;
}

/*
ktk::any ktkResourceLoaderManager::Load_Text(
    const ktk::filesystem::path& path) noexcept
{
    return ktk::any();
}

ktk::any ktkResourceLoaderManager::Load_Texture(
    const ktk::filesystem::path& path) noexcept
{
    return ktk::any();
}

ktk::any ktkResourceLoaderManager::Load_Model(
    const ktk::filesystem::path& path) noexcept
{
    auto resource_type = this->DetectResourceTypeByFileFormat(path);

    auto* p_loader = this->Get_Loader(resource_type);

    if (p_loader)
    {
        auto result = p_loader->Load(path);
        return result;
    }

    return ktk::any();
}

ktk::any ktkResourceLoaderManager::Load_Sound(
    const ktk::filesystem::path& path) noexcept
{
    return ktk::any();
}

ktk::any ktkResourceLoaderManager::Load_Video(
    const ktk::filesystem::path& path) noexcept
{
    return ktk::any();
}

ktk::any ktkResourceLoaderManager::Load_CPlusPlusLibrary(
    const ktk::filesystem::path& path) noexcept
{
    return ktk::any();
}

bool ktkResourceLoaderManager::Load_Text(
    const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
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
                ktk::string(code.message()).get_as_is());
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
    const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
{
    return true;
}

bool ktkResourceLoaderManager::Load_Model(
    const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
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
    const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
{
    return true;
}

bool ktkResourceLoaderManager::Load_Video(
    const ktk::filesystem::path& path, ktk::any object_from_construct) noexcept
{
    return true;
}
*/

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK