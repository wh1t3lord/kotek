#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

constexpr const char* kConfigFileNameSystemInfo = "sys_info.json";
constexpr const char* kSysInfoFieldName_InitializeCallback =
	"UserCallbackForGameLibrary_Initialize";
constexpr const char* kSysInfoFieldName_ShutdownCallback =
	"UserCallbackForGameLibrary_Shutdown";
constexpr const char* kSysInfoFieldName_UpdateCallback =
	"UserCallbackForGameLibrary_Update";
constexpr const char* kSysInfoFieldName_UserLibraryName = "UserGameLibraryName";

constexpr const char* kSysInfoFieldName_UpdateCallbackContainsLoop =
	"UserCallbackForGameLibrary_Update_Contains_Loop";
constexpr const char* kSysInfoFieldName_InitializeCallback_Render =
	"UserCallbackForGameLibrary_Initialize_Render";

constexpr const char* kUserCallbackName_Initialize = "InitializeModule_Game";
constexpr const char* kUserCallbackName_Shutdown = "ShutdownModule_Game";
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
	ktk_filesystem_path GetFolderByEnum(
		eFolderIndex id) const noexcept override;

	bool IsValidPath(const ktk_filesystem_path& path) const noexcept override;

	/*!
	 * \brief readFile reads to kun_ktk ustring all content of file
	 * \param path_to_file your valid path to file, you should use file
	 * system to navigate file by calling getFolderByEnum
	 *
	 * If you need to use or pass string_legacy (aka
	 * std::basic_string<char>) you should cast to
	 * ktk::cast::to_string_legacy otherwise it stands for unicode files
	 *
	 * \return ktk::ustring
	 */
	kun_ktk ustring Read_File(
		const ktk_filesystem_path& path_to_file) const noexcept override;

	// static implementation
	bool Read_File(char*& p_buffer, size_t& length_of_buffer,
		const kun_ktk kun_filesystem
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
				absolute_path_to_file) noexcept override;

	void Create_Directory(const ktk_filesystem_path& path,
		eFolderVisibilityType type) override;

private:
	bool AddGamedataFolderToStorage(const ktk_filesystem_path& path,
		eFolderIndex id, const kun_ktk cstring& folder_name) noexcept;

	void ValidateFolders(void) noexcept;

	void CreateConfigFiles(void) noexcept;

	bool CreateDirectoryImpl(const ktk_filesystem_path& path) const noexcept;

private:
	ktk_unordered_map<eFolderIndex,
		kun_ktk static_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>,
		static_cast<size_t>(
			static_cast<kun_ktk enum_base_t>(eFolderIndex::kEndOfEnum) - 1)>
		m_storage_paths;
	// for static string buffer implementation of Read_File
	kun_ktk static_cstring<2048> m_reserved_buffer;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
