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

void ktkResourceSaverManager::Shutdown(void)
{
	for (auto& [type, saver] : this->m_savers)
	{
		auto* p_saver = saver;

		delete p_saver;
	}

	this->m_savers.clear();
}

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
		KOTEK_MESSAGE_WARNING(
			"you try to replace resource loader for type: [{}]",
			helper::Translate_ResourceLoadingType(resource_type));

		delete this->m_savers[resource_type];
		this->m_savers[resource_type] = nullptr;
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
	const ktk_filesystem_path& path, kun_core ktkResourceHandle data) noexcept
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

eResourceLoadingType ktkResourceSaverManager::DetectResourceTypeByFileFormat(
	const ktk_filesystem_path& path) noexcept
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

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK