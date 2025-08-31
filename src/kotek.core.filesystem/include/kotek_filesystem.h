#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

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
private:
	struct ktkFileHandleImpl
	{
		kun_ktk size_t lookup_id;
		kun_ktk size_t stream_total_steps;
		kun_ktk size_t stream_current_step;
		kun_ktk size_t stream_step_size;
		kun_ktk kun_mt atomic<bool> is_in_use;
		kun_ktk cfstream file;
	};

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

	bool Read_File(const ktk_filesystem_path& path_to_file,
		kun_ktk ustring& output_result) const noexcept override;

	template <kun_ktk size_t BytesCount>
	bool Read_File(const ktk_filesystem_path& path_to_file,
		ktk_vector<kun_ktk uint8_t, BytesCount>& output_result) const noexcept;

	// todo: change order of arguments and make same as ustring version
	bool Read_File(kun_ktk uint8_t*& p_buffer, size_t& length_of_buffer,
		const kun_ktk kun_filesystem
			static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
				path_to_file) noexcept override;


	bool Read_File(const ktk_filesystem_path& path_to_file, char*& p_buffer,
		kun_ktk size_t& length_of_buffer) override;

	ktkFileSystemFileHandleType Begin_Stream(
		const ktk_filesystem_path& path_to_file,
		size_t stream_step = KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE);

	template <kun_ktk size_t BytesCount = KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE>
	void Stream(const ktkFileSystemFileHandleType file_handle,
		ktk_vector<kun_ktk uint8_t, BytesCount>& vector);

	void Stream(const ktkFileSystemFileHandleType file_handle,
		kun_ktk uint8_t*& p_buffer, kun_ktk size_t buffer_size);

	void End_Stream(const ktkFileSystemFileHandleType file_handle);

	void Create_Directory(
		const ktk_filesystem_path& path, eFolderVisibilityType type) override;

private:
	bool AddGamedataFolderToStorage(const ktk_filesystem_path& path,
		eFolderIndex id, const kun_ktk cstring& folder_name) noexcept;

	void ValidateFolders(void) noexcept;

	void CreateConfigFiles(void) noexcept;

	bool CreateDirectoryImpl(const ktk_filesystem_path& path) const noexcept;

	bool Is_AnyAvailableFiles(void) const noexcept;

	ktkFileSystemFileHandleType Get_AvailableFile(void) const;

private:
	ktk_unordered_map<eFolderIndex,
		kun_ktk static_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>,
		static_cast<size_t>(
			static_cast<kun_ktk enum_base_t>(eFolderIndex::kEndOfEnum) - 1)>
		m_storage_paths;

	kun_ktk kun_mt atomic<size_t> m_current_in_use_files;
	ktk_vector<ktkFileHandleImpl, KOTEK_DEF_FILESYSTEM_FSTREAM_POOL_SIZE>
		m_files;

	// for static string buffer implementation of Read_File
	kun_ktk static_cstring<2048> m_reserved_buffer;
};

template <kun_ktk size_t BytesCount /*= KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE*/>
void ktkFileSystem::Stream(const ktkFileSystemFileHandleType file_handle,
	ktk_vector<kun_ktk uint8_t, BytesCount>& vector)
{
	this->Stream(file_handle, vector.data(), BytesCount);
}

template <kun_ktk size_t BytesCount>
bool ktkFileSystem::Read_File(const ktk_filesystem_path& path_to_file,
	ktk_vector<kun_ktk uint8_t, BytesCount>& output_result) const noexcept
{
	kun_ktk size_t size = BytesCount;
	return this->Read_File(output_result.data(), size, path_to_file);
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
