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

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK