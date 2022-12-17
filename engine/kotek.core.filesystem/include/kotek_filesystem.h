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
constexpr const char* kSysInfoFieldName_UserLibraryName =
	"UserGameLibraryName";

constexpr const char* kSysInfoFieldName_UpdateCallbackContainsLoop =
	"UserCallbackForGameLibrary_Update_Contains_Loop";
constexpr const char* kSysInfoFieldName_InitializeCallback_Render =
	"UserCallbackForGameLibrary_Initialize_Render";

// TODO: implement fallback renderer execution and deffered initializing if user
// specified UserConfig

/// @brief by our standard we have a fallback situation where for some reason
/// the specified renderer for loading is not loaded or initialized successful,
/// it means when you specified for loading OpenGL and OpenGL is not initialized
/// good it will try to initialize your specified fallback renderer (even if it
/// is OpenGL it will just try again to execute initialization of OpenGL)
/// UserConfig value means that information will be taken from your config and
/// you will have deffered calling of render module (our render module, don't
/// mistake with your implementation module, see documentation TODO: implement
/// section in doc)
constexpr const char* kSysInfoFieldName_FallbackRenderer = "FallbackRenderer";

constexpr const char* kSysInfoFieldName_FallbackRenderer_Vulkan = "Vulkan";
constexpr const char* kSysInfoFieldName_FallbackRenderer_OpenGL = "OpenGL";
constexpr const char* kSysInfoFieldName_FallbackRenderer_DirectX = "DirectX";
constexpr const char* kSysInfoFieldName_FallbackRenderer_ANGLE = "ANGLE";
constexpr const char* kSysInfoFieldName_FallbackRenderer_Software = "Software";
constexpr const char* kSysInfoFieldName_FallbackRenderer_UserConfig =
	"UserConfig";

/// @brief if it is empty or field doesn't present in config we take latest
/// version of specified renderer
constexpr const char* kSysInfoFieldName_FallbackRenderer_Version =
	"FallbackRenderer_Version";

constexpr const char* kSysInfoFieldName_RendererForLoading =
	"RendererForLoading";

constexpr const char* kSysInfoFieldName_RendererForLoading_Vulkan = "Vulkan";
constexpr const char* kSysInfoFieldName_RendererForLoading_OpenGL = "OpenGL";
constexpr const char* kSysInfoFieldName_RendererForLoading_DirectX = "DirectX";
constexpr const char* kSysInfoFieldName_RendererForLoading_ANGLE = "ANGLE";
constexpr const char* kSysInfoFieldName_RendererForLoading_Software = "Software";
constexpr const char* kSysInfoFieldName_RendererForLoading_UserConfig =
	"UserConfig";

constexpr const char* kSysInfoFieldName_RendererForLoading_Version =
	"RendererForLoading_Version";

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
	const ktk::filesystem::path& GetFolderByEnum(
		eFolderIndex id) const noexcept override;

	bool IsValidPath(const ktk::filesystem::path& path) const noexcept override;

	bool CreateDirectory(const ktk::filesystem::path& path) const noexcept;

	// TODO: think about multithreading and probably it is better to move to
	// resource manager loader/saver
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
		const ktk::filesystem::path& path_to_file) const noexcept override;

private:
	bool AddGamedataFolderToStorage(const ktk::filesystem::path& path,
		eFolderIndex id, const ktk::string& folder_name) noexcept;

	void ValidateFolders(void) noexcept;

	void CreateConfigFiles(void) noexcept;

private:
	ktk::unordered_map<eFolderIndex, ktk::filesystem::path> m_storage_paths;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
