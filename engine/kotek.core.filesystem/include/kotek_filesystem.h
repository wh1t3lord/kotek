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

#ifdef KOTEK_USE_PLATFORM_WINDOWS
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 260
#elif defined(KOTEK_USE_PLATFORM_LINUX)
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 1024
#elif defined(KOTEK_USE_PLATFORM_MAC)
	#define KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH 1024
#else
	#error undefined platform
#endif

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
	ktk::filesystem::path GetFolderByEnum(
		eFolderIndex id) const noexcept override;

	bool IsValidPath(const ktk::filesystem::path& path) const noexcept override;

	bool CreateDirectory(const ktk::filesystem::path& path) const noexcept;

	// TODO: think about multithreading and probably it is better to move to
	// resource manager loader/saver
	/*!
	 * \brief readFile reads to ktk::ustring all content of file
	 * \param path_to_file your valid path to file, you should use file
	 * system to navigate file by calling getFolderByEnum
	 *
	 * If you need to use or pass string_legacy (aka
	 * std::basic_string<char>) you should cast to
	 * ktk::cast::to_string_legacy otherwise it stands for unicode files
	 *
	 * \return ktk::ustring
	 */
	ktk::ustring ReadFile(
		const ktk::filesystem::path& path_to_file) const noexcept override;

private:
	bool AddGamedataFolderToStorage(const ktk::filesystem::path& path,
		eFolderIndex id, const ktk::cstring& folder_name) noexcept;

	void ValidateFolders(void) noexcept;

	void CreateConfigFiles(void) noexcept;

private:
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	ktk::static_unordered_map<eFolderIndex,
		ktk::static_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>,
		static_cast<size_t>(
			static_cast<ktk::enum_base_t>(eFolderIndex::kEndOfEnum) - 1)>
		m_storage_paths;
#else
	ktk::unordered_map<eFolderIndex, ktk::filesystem::path> m_storage_paths;
#endif
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
