#pragma once

#include "kotek_std.h"

namespace Kotek
{
	namespace Core
	{
		// TODO: add helper namespace for translating this enum
		enum class folder_index_t : int
		{
			kFolderIndex_Root,
			kFolderIndex_Gamedata,
			kFolderIndex_Configs,
			kFolderIndex_Scripts,
			kFolderIndex_Textures,
			kFolderIndex_Shaders,
			kFolderIndex_Models,
			kFolderIndex_Sound,
			kFolderIndex_UserTests,
			kFolderIndex_UserData
		};

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
				folder_index_t id) const noexcept;

			bool IsValidPath(const ktk::string& path) const noexcept;

			bool CreateDirectory(const ktk::string& path) const noexcept;

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
				const ktk::string& path_to_file) const noexcept;

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
