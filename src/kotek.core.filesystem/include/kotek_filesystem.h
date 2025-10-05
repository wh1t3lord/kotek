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

constexpr const char* kUserCallbackName_Initialize =
	"InitializeModule_Game";
constexpr const char* kUserCallbackName_Shutdown =
	"ShutdownModule_Game";
constexpr const char* kUserCallbackName_Update =
	"UpdateModule_Game";
constexpr const char* kUserCallbackName_Initialize_Render =
	"InitializeModule_Render";

class ktkFileSystem : public ktkIFileSystem
{
private:
	struct file_id_t
	{
		kun_ktk uint32_t thread_id = decltype(thread_id)(-1);
		kun_ktk uint32_t file_id[std::countr_zero(
			static_cast<kun_ktk uint32_t>(
				eFileSystemType::kEndOfEnum
			)
		)]{kun_ktk uint32_t(-1), kun_ktk uint32_t(-1)};
	};

public:
	ktkFileSystem(void);
	~ktkFileSystem(void);

	void Initialize(
		eFileSystemPriorityType priority_by_filesystem,
		eFileSystemFeatureType features,
		kun_ktk uint32_t stream_buffer_length,
		kun_ktk uint16_t simultaneously_opened_files_count
	) override;

	void Shutdown(void) override;

	/*
	 * For Win32 returns without slash
	 */
	ktk_filesystem_path GetFolderByEnum(eFolderIndex id
	) const noexcept override;

	bool IsValidPath(const ktk_filesystem_path& path
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
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemFeatureType features =
			eFileSystemFeatureType::kNone,
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

	kun_ktk size_t Get_RemaningStreamsCount(
		ktkFileHandleType file_handle
	) const noexcept override;

	kun_ktk size_t Get_TotalStreamsCount(
		ktkFileHandleType file_handle
	) const noexcept override;

	bool End_Stream(ktkFileHandleType file_handle
	) noexcept override;

	/* STREAMING */

private:
	bool AddGamedataFolderToStorage(
		const ktk_filesystem_path& path,
		eFolderIndex id,
		const kun_ktk cstring& folder_name
	) noexcept;

	void ValidateFolders(void) noexcept;

	void CreateConfigFiles(void) noexcept;

	bool CreateDirectoryImpl(const ktk_filesystem_path& path
	) const noexcept;

	bool Is_AnyAvailableFiles(void) const noexcept;

	ktkFileHandleType Get_AvailableFile(void) const;

private:
	//	ktk_vector<int, KOTEK_DEF_FILESYSTEM_MAX_OPENED_FILES>
	// m_file_tracker; 	kun_ktk kun_mt atomic<size_t>
	// m_current_in_use_files;

	kun_ktk kun_mt atomic<kun_ktk uint16_t>
		m_current_opened_files;

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
	ktkFileSystem_Native m_fs_native;
#endif

#ifdef KOTEK_USE_FILESYSTEM_TYPE_ZLIB
	ktkFileSystem_Zlib m_fs_zlib;
#endif

#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	ktkFileSystem_VFM m_fs_vfm;
#endif

	ktk_unordered_map<
		ktk_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>,
		file_id_t,
		KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT>
		m_paths_storage;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
