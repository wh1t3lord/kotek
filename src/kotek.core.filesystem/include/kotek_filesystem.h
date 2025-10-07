#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

#include "kotek_filesystem_native.h"
#include "kotek_filesystem_zlib.h"
#include "kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

constexpr const char* kConfigFileNameSystemInfo =
	"sys_info.json";

/* todo: legacy delete
constexpr const char* kSysInfoFieldName_InitializeCallback =
    "UserCallbackForGameLibrary_Initialize";
constexpr const char* kSysInfoFieldName_ShutdownCallback =
    "UserCallbackForGameLibrary_Shutdown";
constexpr const char* kSysInfoFieldName_UpdateCallback =
    "UserCallbackForGameLibrary_Update";
constexpr const char* kSysInfoFieldName_UserLibraryName =
    "UserGameLibraryName";

constexpr const char*
    kSysInfoFieldName_UpdateCallbackContainsLoop =
        "UserCallbackForGameLibrary_Update_Contains_Loop";
constexpr const char*
    kSysInfoFieldName_InitializeCallback_Render =
        "UserCallbackForGameLibrary_Initialize_Render";
*/

constexpr const char* kSysInfoFieldName_UserNamespace = "User";
constexpr const char*
	kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks =
		"Callbacks";
constexpr const char*
	kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Init =
		"Init";
constexpr const char*
	kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Shutdown =
		"Shutdown";
constexpr const char*
	kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Update =
		"Update";
constexpr const char*
	kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Init_Render =
		"Init_Render";
constexpr const char*
	kSysInfoFieldName_UserNamespace_EngineNamespace = "Engine";

constexpr const char* kUserCallbackName_Initialize =
	"InitializeModule_Game";
constexpr const char* kUserCallbackName_Shutdown =
	"ShutdownModule_Game";
constexpr const char* kUserCallbackName_Update =
	"UpdateModule_Game";
constexpr const char* kUserCallbackName_Initialize_Render =
	"InitializeModule_Render";

/* CORE */
constexpr const char* kSysInfoFieldName_CoreNamespace = "Core";

/// @brief this defines registered file systems and their
/// priority in one field!!! this field must be defined and
/// specified in kConfigFileNameSystemInfo
constexpr const char*
	kSysInfoFieldName_CoreNamespace_FileSystemPriorityList =
		"FS_PriorityList";
constexpr const char*
	kSysInfoFieldName_CoreNamespace_FileSystemFeatures =
		"FS_Features";
constexpr const char*
	kSysInfoFieldName_CoreNamespace_FileSystemFeatures_VFMRead =
		"VFM_READ";
/// @brief if this is not specifie in
/// kSysInfoFieldName_CoreNamespace_FileSystemPriorityList then
/// the first entry that was specified in
/// kSysInfoFieldName_CoreNamespace_FileSystemPriorityList will
/// be used as main and single FS
constexpr const char*
	kSysInfoFieldName_CoreNamespace_FileSystemFeatures_PriorityList =
		"PRIORITY_LIST";
constexpr const char*
	kSysInfoFieldName_CoreNamespace_FileSystemFeatures_VFMCache =
		"VFM_CACHE";
/* CORE */

#ifndef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
	#error you can't initialize framework because kConfigFileNameSystemInfo is stored on physical disk as standard design of framework 
#endif

class ktkFileSystem : public ktkIFileSystem
{
private:
	struct file_desc_t
	{
		/// @brief must be defined as NOT AUTO it means that
		/// this field shows to us in which FS we truly
		/// determine our file based on current priority like if
		/// it was native then we search native if native failed
		/// (but feature about
		/// kEnablePriorityWhenFailedToOpenFile was
		/// specified)then we try to use any other fs based on
		/// priority order that was defined in
		/// kConfigFileNameSystemInfo
		eFileSystemPriorityType fs_type =
			eFileSystemPriorityType::kAuto;
		eFileSystemStreamingType fs_streaming =
			eFileSystemStreamingType::kAuto;
		kun_ktk uint32_t thread_id = decltype(thread_id)(-1);

		kun_ktk uint32_t file_id = decltype(file_id)(-1);
	};

	static_assert(
		sizeof(file_desc_t::thread_id) ==
			sizeof(std::thread::id),
		"must be same size otherwise you need to update "
		"this field for your std::thread::id "
		"implementation, but basically it is uint32_t"
	);

public:
	ktkFileSystem(void);
	~ktkFileSystem(void);

	void Initialize(ktkIFrameworkConfig* p_config) override;

	void Shutdown(void) override;

	bool Is_ValidPath(const ktk_filesystem_path& path
	) const noexcept override;

	void Create_Directory(
		const ktk_filesystem_path& path,
		eFolderVisibilityType type
	) override;

	bool Read_File(
		const ktk_filesystem_path& path_to_file,
		kun_ktk ustring& output_result,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemFeatureType feature =
			eFileSystemFeatureType::kNone
	) const noexcept override;

	bool Read_File(
		const ktk_filesystem_path& path_to_file,
		kun_ktk uint8_t*& p_buffer,
		kun_ktk size_t& length_of_buffer,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemFeatureType features =
			eFileSystemFeatureType::kNone
	) noexcept override;

	bool Read_File(
		const ktk_filesystem_path& path_to_file,
		char*& p_buffer,
		kun_ktk size_t& length_of_buffer,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemFeatureType features =
			eFileSystemFeatureType::kNone
	) override;

	bool Write_File(
		const ktk_filesystem_path& path_to_file,
		kun_ktk ustring& input,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemFeatureType feature =
			eFileSystemFeatureType::kNone
	) noexcept override;

	bool Write_File(
		const ktk_filesystem_path& path_to_file,
		const kun_ktk uint8_t* p_buffer,
		kun_ktk size_t length_of_buffer,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemFeatureType featurs =
			eFileSystemFeatureType::kNone
	) noexcept override;

	bool Write_File(
		const ktk_filesystem_path& path_to_file,
		const char* p_buffer,
		kun_ktk size_t length_of_buffer,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemFeatureType features =
			eFileSystemFeatureType::kNone
	) noexcept override;

	/* SINGLE SHOT READ&WRITE */

	/* STREAMING */

	ktkFileHandleType Begin_Stream(
		const ktk_filesystem_path& path_to_file,
		kun_ktk uint32_t override_stream_reading_length = 0,
		bool force_be_called_from_one_thread_only = false,
		eFileSystemStreamingType streaming_type =
			eFileSystemStreamingType::kAuto,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemFeatureType features =
			eFileSystemFeatureType::kNone
	) noexcept override;

	bool Write_Stream(
		ktkFileHandleType file_handle, kun_ktk ustring& input
	) noexcept override;

	bool Write_Stream(
		ktkFileHandleType file_handle,
		const unsigned char* p_buffer,
		kun_ktk size_t override_write_streaming_length = 0
	) noexcept override;

	bool Read_Stream(
		ktkFileHandleType file_handle,
		unsigned char* p_buffer,
		kun_ktk size_t& length_of_streaming_buffer
	) noexcept override;

	kun_ktk uint32_t Get_DefaultStreamingBufferLength(void
	) const noexcept override;

	kun_ktk uint32_t Get_StreamingBufferLength(
		ktkFileHandleType file_handle
	) const noexcept override;

	kun_ktk size_t Get_RemainingStreamsCount(
		ktkFileHandleType file_handle
	) const noexcept override;

	kun_ktk size_t Get_TotalStreamsCount(
		ktkFileHandleType file_handle
	) const noexcept override;

	bool End_Stream(ktkFileHandleType file_handle
	) noexcept override;

	/* STREAMING */

private:
	void Validate_Folders(void) noexcept;

	void Validate_Folder(const ktk_filesystem_path& path);

	void Create_ConfigFiles(void) noexcept;

	bool Create_Directory(const ktk_filesystem_path& path
	) const noexcept;

	void Initialize_FrameworkConfig();

private:
	ktkIFrameworkConfig* m_p_config;

	kun_ktk kun_mt atomic<kun_ktk uint16_t>
		m_current_opened_files;

	ktk_filesystem_path m_root_path;

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
	ktkFileSystem_Native m_fs_native;
#endif

#ifdef KOTEK_USE_FILESYSTEM_TYPE_ZLIB
	ktkFileSystem_Zlib m_fs_zlib;
#endif

#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	ktkFileSystem_VFM m_vfm;
#endif

	ktk_unordered_map<
		ktk_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>,
		file_desc_t,
		KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT>
		m_paths_storage;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
