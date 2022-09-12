#include "../include/kotek_filesystem.h"

namespace Kotek
{
	namespace Core
	{
		ktkFileSystem::ktkFileSystem(void) {}

		ktkFileSystem::~ktkFileSystem(void) {}

		void ktkFileSystem::Initialize(void)
		{
			this->m_storage_paths[eFolderIndex::kFolderIndex_Root] =
				ktk::filesystem::current_path();

			KOTEK_MESSAGE("root path: {}",
				this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root)
					.c_str());

			KOTEK_ASSERT(this->IsValidPath(this->m_storage_paths.at(
							 eFolderIndex::kFolderIndex_Root)),
				"your path must be valid!");

			this->ValidateFolders();
			this->CreateConfigFiles();

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
				KOTEK_MESSAGE("can't find path by id[{}]",
					static_cast<ktk::enum_base_t>(id));
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
					path_to_file.c_str());
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
					path_to_file.c_str());
				return result;
			}

			return result;
		}

		bool ktkFileSystem::AddGamedataFolderToStorage(
			const ktk::filesystem::path& path, eFolderIndex id,
			const ktk::string& folder_name) noexcept
		{
			if (this->m_storage_paths.find(id) != this->m_storage_paths.end())
			{
				KOTEK_MESSAGE("this path {} is existed in storage, can't add",
					static_cast<ktk::enum_base_t>(id));
				return false;
			}

			ktk::filesystem::path result(path);
			result /= folder_name.get_as_is();

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
				eFolderIndex::kFolderIndex_Shaders_WEBGPU,
				KOTEK_TEXT("webgpu"));

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
				KOTEK_ASSERT(
					this->CreateDirectory(this->m_storage_paths.at(
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

		void ktkFileSystem::CreateConfigFiles(void) noexcept
		{
			auto path_to_system_json =
				this->GetFolderByEnum(eFolderIndex::kFolderIndex_Root);

			path_to_system_json / kConfigFileNameSystemInfo;

			if (this->IsValidPath(path_to_system_json) == false)
			{
				ktkFile sys_info("sys_info");

				sys_info.Write(kSysInfoFieldName_InitializeCallback,
					kUserCallbackName_Initialize);
				sys_info.Write(kSysInfoFieldName_ShutdownCallback,
					kUserCallbackName_Shutdown);
				sys_info.Write(
					kSysInfoFieldName_UpdateCallback, kUserCallbackName_Update);
				sys_info.Write(kSysInfoFieldName_InitializeCallback_Render,
					kUserCallbackName_Initialize_Render);

				sys_info.Write(
					kSysInfoFieldName_UserLibraryNameWindows, "game.dll");
				sys_info.Write(
					kSysInfoFieldName_UserLibraryNameLinux, "game.so");
				sys_info.Write(
					kSysInfoFieldName_UserLibraryNameMacOS, "game.so");

				// TODO: implement saver!!!
				//				sys_info.Save(this,
				//				this->GetFolderByEnum(eFolderIndex::kFolderIndex_Root));
			}
		}
	} // namespace Core
} // namespace Kotek
