#include "../include/kotek_filesystem.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkFileSystem::ktkFileSystem(void) {}

ktkFileSystem::~ktkFileSystem(void) {}

void ktkFileSystem::Initialize(void)
{
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	KOTEK_ASSERT(ktk::filesystem::current_path().u8string().size() <=
			KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH,
		"overflow current_path().size() > "
		"KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH({})",
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH);

	ktk::memory::memcpy(
		this->m_storage_paths[eFolderIndex::kFolderIndex_Root].data(),
		reinterpret_cast<char*>(
			ktk::filesystem::current_path().u8string().data()),
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH);
#else
	this->m_storage_paths[eFolderIndex::kFolderIndex_Root] =
		ktk::filesystem::current_path();
#endif

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	KOTEK_MESSAGE("root path: [{}]",
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root).c_str());
#else
	KOTEK_MESSAGE("root path: [{}]",
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root));
#endif

	bool is_valid_path =
		this->IsValidPath(this->m_storage_paths
							  .at(eFolderIndex::kFolderIndex_Root)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
							  .c_str()
#endif
		);
	KOTEK_ASSERT(is_valid_path, "your path must be valid!");

	this->ValidateFolders();

	KOTEK_MESSAGE("filesystem is initialized!");
}

void ktkFileSystem::Shutdown(void) {}

ktk_filesystem_path ktkFileSystem::GetFolderByEnum(
	eFolderIndex id) const noexcept
{
	KOTEK_ASSERT(this->m_storage_paths.empty() == false,
		"can't be empty you must initialize filesystem!");

	if (this->m_storage_paths.find(id) == this->m_storage_paths.end())
	{
		KOTEK_MESSAGE(
			"can't find path by id[{}]", static_cast<ktk::enum_base_t>(id));
	}

	return this->m_storage_paths
		.at(id)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
		.c_str()
#endif
		;
}

bool ktkFileSystem::IsValidPath(
	const ktk_filesystem_path& path) const noexcept
{
	if (path.empty())
	{
		KOTEK_MESSAGE_WARNING("you have passed an empty path");
		return false;
	}

	return ktk::filesystem::exists(path);
}

bool ktkFileSystem::CreateDirectoryImpl(
	const ktk_filesystem_path& path) const noexcept
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

ktk::ustring ktkFileSystem::ReadFile(
	const ktk_filesystem_path& path_to_file) const noexcept
{
	ktk::ustring result;

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

void ktkFileSystem::Create_Directory(
	const ktk_filesystem_path& path, Core::eFolderVisibilityType type)
{
	KOTEK_ASSERT(path.empty() == false, "you can't pass an empty path");

	bool status = this->CreateDirectoryImpl(path);

	KOTEK_ASSERT(status, "failed to create directory: {}", path);
}

bool ktkFileSystem::AddGamedataFolderToStorage(
	const ktk_filesystem_path& path, eFolderIndex id,
	const ktk::cstring& folder_name) noexcept
{
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	KOTEK_ASSERT(path.u8string().size() <= KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH,
		"overflow path is > KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH({})",
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH);
#endif

	if (this->m_storage_paths.find(id) != this->m_storage_paths.end())
	{
		KOTEK_MESSAGE("this path {} is existed in storage, can't add",
			static_cast<ktk::enum_base_t>(id));
		return false;
	}

	ktk_filesystem_path result(path);
	result /= folder_name.c_str();

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	KOTEK_ASSERT(result.u8string().size() <= KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH,
		"path overflow, filesystem::path::size() > "
		"KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH({})!",
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH);

	ktk::memory::memcpy(this->m_storage_paths[id].data(),
		reinterpret_cast<char*>(result.u8string().data()),
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH);
#else
	this->m_storage_paths[id] = result;
#endif

	return this->IsValidPath(result);
}

// TODO: parallel with task_group thing!
void ktkFileSystem::ValidateFolders(void) noexcept
{
	this->m_storage_paths[eFolderIndex::kFolderIndex_Gamedata] =
		this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root);

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	ktk_filesystem_path temp =
		this->m_storage_paths[eFolderIndex::kFolderIndex_Gamedata].c_str();
	temp /= KOTEK_TEXTU("game_data");

	KOTEK_ASSERT(temp.u8string().size() <= KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH,
		"overflow kFolderIndex_Gamedata path is > "
		"KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH({})",
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH);

	ktk::memory::memcpy(
		this->m_storage_paths[eFolderIndex::kFolderIndex_Gamedata].data(),
		reinterpret_cast<char*>(temp.u8string().data()),
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH);

#else
	this->m_storage_paths[eFolderIndex::kFolderIndex_Gamedata] /=
		KOTEK_TEXTU("game_data");
#endif

	bool status = this->IsValidPath(this->m_storage_paths
										.at(eFolderIndex::kFolderIndex_Gamedata)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
										.c_str()
#endif
	);

	if (status == false)
	{
		auto status_dir =
			this->CreateDirectoryImpl(this->m_storage_paths
									  .at(eFolderIndex::kFolderIndex_Gamedata)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
									  .c_str()
#endif
			);
		KOTEK_ASSERT(status_dir, "can't create directory");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Gamedata)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_Configs, KOTEK_TEXTU("configs"));

	if (status == false)
	{
		auto status_dir =
			this->CreateDirectoryImpl(this->m_storage_paths
									  .at(eFolderIndex::kFolderIndex_Configs)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
									  .c_str()
#endif
			);
		KOTEK_ASSERT(status_dir, "can't create directory");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Gamedata)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_Models, KOTEK_TEXTU("models"));

	if (status == false)
	{
		auto status_dir =
			this->CreateDirectoryImpl(this->m_storage_paths
									  .at(eFolderIndex::kFolderIndex_Models)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
									  .c_str()
#endif
			);
		KOTEK_ASSERT(status_dir, "can't create directory");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Gamedata)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_Textures, KOTEK_TEXTU("textures"));

	if (status == false)
	{
		auto status_dir =
			this->CreateDirectoryImpl(this->m_storage_paths
									  .at(eFolderIndex::kFolderIndex_Textures)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
									  .c_str()
#endif
			);
		KOTEK_ASSERT(status_dir, "can't create directory");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Gamedata)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_Shaders, KOTEK_TEXTU("shaders"));

	if (status == false)
	{
		auto status_dir =
			this->CreateDirectoryImpl(this->m_storage_paths
									  .at(eFolderIndex::kFolderIndex_Shaders)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
									  .c_str()
#endif
			);

		KOTEK_ASSERT(
			status_dir, "can't create directory for shaders root folder");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Gamedata)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_AI, KOTEK_TEXTU("ai"));

	if (status == false)
	{
		auto status_dir =
			this->CreateDirectoryImpl(this->m_storage_paths
									  .at(eFolderIndex::kFolderIndex_AI)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
									  .c_str()
#endif
			);
		KOTEK_ASSERT(status_dir, "can't create directory for ai");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Gamedata)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_Levels, KOTEK_TEXTU("levels"));

	if (status == false)
	{
		auto status_dir =
			this->CreateDirectoryImpl(this->m_storage_paths
									  .at(eFolderIndex::kFolderIndex_Levels)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
									  .c_str()
#endif
			);
		KOTEK_ASSERT(status_dir, "can't create directory for levels");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Shaders)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_Shaders_GLSL, KOTEK_TEXTU("glsl"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderIndex_Shaders_GLSL)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
#endif
		);
		KOTEK_ASSERT(status_dir, "can't create directory for glsl shaders");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Shaders)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_Shaders_HLSL, KOTEK_TEXTU("hlsl"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderIndex_Shaders_HLSL)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
#endif
		);
		KOTEK_ASSERT(status_dir, "can't create directory for hlsl shaders");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Shaders)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderindex_Shaders_SPV, KOTEK_TEXTU("spv"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderindex_Shaders_SPV)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
#endif
		);
		KOTEK_ASSERT(
			status_dir, "can't create directory folder for SPIR-V shaders");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Shaders)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_Shaders_WEBGPU, KOTEK_TEXTU("webgpu"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderIndex_Shaders_WEBGPU)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
#endif
		);
		KOTEK_ASSERT(
			status_dir, "can't create directory folder for WEBGPU shaders");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_Root)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_UserData, KOTEK_TEXTU("user_data"));

	if (status == false)
	{
		auto status_dir =
			this->CreateDirectoryImpl(this->m_storage_paths
									  .at(eFolderIndex::kFolderIndex_UserData)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
									  .c_str()
#endif
			);
		KOTEK_ASSERT(status_dir, "can't create directory for user_data folder");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_UserData)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_UserData_ShaderCache,
		KOTEK_TEXTU("shader_cache"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderIndex_UserData_ShaderCache)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
#endif
		);
		KOTEK_ASSERT(
			status_dir, "can't create directory for shader_cache folder!");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_UserData)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_UserData_SDK, KOTEK_TEXTU("sdk"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderIndex_UserData_SDK)

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
#endif
		);

		KOTEK_ASSERT(status_dir, "can't create directory for sdk folder!");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_UserData_SDK)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_UserData_SDK_Settings,
		KOTEK_TEXTU("settings"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderIndex_UserData_SDK_Settings)

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
#endif
		);

		KOTEK_ASSERT(
			status_dir, "can't create directory for sdk/settings folder!");
	}

	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_UserData_SDK)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
#endif
			,
		eFolderIndex::kFolderIndex_UserData_SDK_Scenes, KOTEK_TEXTU("scenes"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderIndex_UserData_SDK_Scenes)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
#endif
		);

		KOTEK_ASSERT(
			status_dir, "can't create direcotry for sdk/scenes folder!");
	}

#ifdef KOTEK_DEBUG
	status = this->AddGamedataFolderToStorage(
		this->m_storage_paths
			.at(eFolderIndex::kFolderIndex_UserData)
	#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
			.c_str()
	#endif
			,
		eFolderIndex::kFolderIndex_UserData_Tests, KOTEK_TEXTU("tests"));

	if (status == false)
	{
		auto status_dir = this->CreateDirectoryImpl(
			this->m_storage_paths
				.at(eFolderIndex::kFolderIndex_UserData_Tests)
	#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
				.c_str()
	#endif
		);
		KOTEK_ASSERT(status_dir, "can't create directory");
	}
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
