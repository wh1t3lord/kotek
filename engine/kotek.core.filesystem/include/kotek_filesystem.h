#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem.path/include/kotek_core_containers_filesystem_path.h>

namespace Kotek
{
	namespace Core
	{
		constexpr const char* kConfigFileNameSystemInfo = "sys_info.json";
		constexpr const char* kSysInfoFieldName_InitializeCallback =
			"UserCallbackForGameLibrary_Initialize";
		constexpr const char* kSysInfoFieldName_ShutdownCallback =
			"UserCallbackForGameLibrary_Shutdown";
		constexpr const char* kSysInfoFieldName_UpdateCallback =
			"UserCallbackForGameLibrary_Update";
		constexpr const char* kSysInfoFieldName_UserLibraryNameWindows =
			"UserGameLibraryName_Win32";
		constexpr const char* kSysInfoFieldName_UserLibraryNameLinux =
			"UserGameLibraryName_Linux";
		constexpr const char* kSysInfoFieldName_UserLibraryNameMacOS = "UserGameLibraryName_MacOS";

		constexpr const char* kSysInfoFieldName_UpdateCallbackContainsLoop =
			"UserCallbackForGameLibrary_Update_Contains_Loop";
		constexpr const char* kSysInfoFieldName_InitializeCallback_Render =
			"UserCallbackForGameLibrary_Initialize_Render";

		constexpr const char* kUserCallbackName_Initialize =
			"InitializeModule_Game";
		constexpr const char* kUserCallbackName_Shutdown =
			"ShutdownModule_Game";
		constexpr const char* kUserCallbackName_Update = "UpdateModule_Game";
		constexpr const char* kUserCallbackName_Initialize_Render =
			"InitializeModule_Render";

		class ktkFileSystem : public ktkIFileSystem
		{
		public:
			ktkFileSystem(void);
			~ktkFileSystem(void);

			void Initialize(void) override;
			void Shutdown(void) override;

			/*
			* For Win32 returns without slash
			*/
			const ktk::string& GetFolderByEnum(
				folder_index_t id) const noexcept override;

			bool IsValidPath(const ktk::string& path) const noexcept override;

			bool CreateDirectory(const ktk::string& path) const noexcept;

			// TODO: think about multithreading and probably it is better to move to resource manager loader/saver
			/*!
			 * \brief readFile reads to ktk::string all content of file
			 * \param path_to_file your valid path to file, you should use file
			 * system to navigate file by calling getFolderByEnum
			 *
			 * If you need to use or pass string_legacy (aka
			 * std::basic_string<char>) you should cast to
			 * ktk::cast::to_string_legacy otherwise it stands for unicode files
			 *
			 * \return ktk::string
			 */
			ktk::string ReadFile(
				const ktk::string& path_to_file) const noexcept override;

		private:
			bool AddGamedataFolderToStorage(const ktk::string& path,
				folder_index_t id, const ktk::string& folder_name) noexcept;

			void ValidateFolders(void) noexcept;

			void CreateConfigFiles(void) noexcept;

		private:
			ktk::unordered_map<folder_index_t, ktk::string> m_storage_paths;
		};
	} // namespace Core
} // namespace Kotek
