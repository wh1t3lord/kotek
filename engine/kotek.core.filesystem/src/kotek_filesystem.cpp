#include "../include/kotek_filesystem.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkFileSystem::ktkFileSystem(void) {}

ktkFileSystem::~ktkFileSystem(void) {}

void ktkFileSystem::Initialize(void)
{
	this->m_storage_paths[eFolderIndex::kFolderIndex_Root] =
		ktk::filesystem::current_path();

	KOTEK_MESSAGE("root path: {}",
			this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root));

	KOTEK_ASSERT(this->IsValidPath(
					 this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root)),
		"your path must be valid!");

	this->ValidateFolders();

	KOTEK_MESSAGE("filesystem is initialized!");
}

void ktkFileSystem::Shutdown(void) {}

const ktk::filesystem::path& ktkFileSystem::GetFolderByEnum(
	eFolderIndex id) const noexcept
{
	KOTEK_ASSERT(this->m_storage_paths.empty() == false,
		"can't be empty you must initialize filesystem!");

	if (this->m_storage_paths.find(id) == this->m_storage_paths.end())
	{
		KOTEK_MESSAGE(
			"can't find path by id[{}]", static_cast<ktk::enum_base_t>(id));
	}

	return this->m_storage_paths.at(id);
}

bool ktkFileSystem::IsValidPath(
	const ktk::filesystem::path& path) const noexcept
{
	if (path.empty())
	{
		KOTEK_MESSAGE_WARNING("you have passed an empty path");
		return false;
	}

	return ktk::filesystem::exists(path);
}

bool ktkFileSystem::CreateDirectory(
	const ktk::filesystem::path& path) const noexcept
{
	if (path.empty())
	{
		KOTEK_MESSAGE("path is empty");
		return false;
	}

	if (this->IsValidPath(path) == true)
	{
		KOTEK_MESSAGE("path is existed can't create folder");
		return false;
	}

	return ktk::filesystem::create_directory(path);
}

ktk::string ktkFileSystem::ReadFile(
	const ktk::filesystem::path& path_to_file) const noexcept
{
	ktk::string result;

	if (this->IsValidPath(path_to_file) == false)
	{
		KOTEK_MESSAGE_WARNING("can't load file by following path: [{}]",
			reinterpret_cast<const char*>(path_to_file.u8string().c_str()));
		return result;
	}

	ktk::ifstream file(path_to_file.c_str());

	if (file.good())
	{
		result.assign(
			ktk::istreambuf_iterator(file), ktk::istreambuf_iterator());
	}
	else
	{
		KOTEK_MESSAGE("something is wrong while reading file: [{}]",
			reinterpret_cast<const char*>(path_to_file.u8string().c_str()));
		return result;
	}

	return result;
}

bool ktkFileSystem::AddGamedataFolderToStorage(
	const ktk::filesystem::path& path, eFolderIndex id,
	const ktk::cstring& folder_name) noexcept
{
	if (this->m_storage_paths.find(id) != this->m_storage_paths.end())
	{
		KOTEK_MESSAGE("this path {} is existed in storage, can't add",
			static_cast<ktk::enum_base_t>(id));
		return false;
	}

	ktk::filesystem::path result(path);
	result /= folder_name.c_str();

	this->m_storage_paths[id] = result;

	return this->IsValidPath(result);
}
void ktkFileSystem::ValidateFolders(void) noexcept
{
	this->m_storage_paths[eFolderIndex::kFolderIndex_Gamedata] =
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root);

	this->m_storage_paths[eFolderIndex::kFolderIndex_Gamedata] /=
		KOTEK_TEXT("gamedata");

	bool status = this->IsValidPath(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Gamedata));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Gamedata)),
			"can't create directory");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Gamedata),
		eFolderIndex::kFolderIndex_Configs, KOTEK_TEXT("configs"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Configs)),
			"can't create directory");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Gamedata),
		eFolderIndex::kFolderIndex_Models, KOTEK_TEXT("models"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Models)),
			"can't create directory");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Gamedata),
		eFolderIndex::kFolderIndex_Textures, KOTEK_TEXT("textures"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Textures)),
			"can't create directory");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Gamedata),
		eFolderIndex::kFolderIndex_Shaders, KOTEK_TEXT("shaders"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Shaders)),
			"can't create directory for shaders root folder");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Gamedata),
		eFolderIndex::kFolderIndex_AI, KOTEK_TEXT("ai"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_AI)),
			"can't create directory for ai");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Gamedata),
		eFolderIndex::kFolderIndex_Levels, KOTEK_TEXT("levels"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Levels)),
			"can't create directory for levels");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Shaders),
		eFolderIndex::kFolderIndex_Shaders_GLSL, KOTEK_TEXT("glsl"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Shaders_GLSL)),
			"can't create directory for glsl shaders");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Shaders),
		eFolderIndex::kFolderIndex_Shaders_HLSL, KOTEK_TEXT("hlsl"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Shaders_HLSL)),
			"can't create directory for hlsl shaders");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Shaders),
		eFolderIndex::kFolderindex_Shaders_SPV, KOTEK_TEXT("spv"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderindex_Shaders_SPV)),
			"can't create directory folder for SPIR-V shaders");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Shaders),
		eFolderIndex::kFolderIndex_Shaders_WEBGPU, KOTEK_TEXT("webgpu"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_Shaders_WEBGPU)),
			"can't create directory folder for WEBGPU shaders");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root),
		eFolderIndex::kFolderIndex_UserData, KOTEK_TEXT("user_data"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_UserData)),
			"can't create directory for user_data folder");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_UserData),
		eFolderIndex::kFolderIndex_UserData_ShaderCache,
		KOTEK_TEXT("shader_cache"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_UserData_ShaderCache)),
			"can't create directory for shader_cache folder");
	}

#ifdef KOTEK_DEBUG
	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_UserData),
		eFolderIndex::kFolderIndex_UserTests, KOTEK_TEXT("tests"));

	if (status == false)
	{
		KOTEK_ASSERT(this->CreateDirectory(this->m_storage_paths.at(
						 eFolderIndex::kFolderIndex_UserTests)),
			"can't create directory");
	}
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
