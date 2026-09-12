#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>

#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
	#include <kotek.core.filesystem.pack/include/kotek_filesystem_pack.h>
#endif

#include "kotek_filesystem_native.h"
#include "kotek_filesystem_zlib.h"
#include "kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

constexpr const char* kConfigFileNameSystemInfo =
	"sys_info.json";

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
	kSysInfoFieldName_UserNamespace_EngineNamespace_Name =
		"Name";
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
	kSysInfoFieldName_CoreNamespace_FileSystemPriorityList_Native =
		"Native";
constexpr const char*
	kSysInfoFieldName_CoreNamespace_FileSystemPriorityList_ZLIB =
		"ZLIB";
/// @brief \~english the .kpack backend's sys_info.json priority-list
/// name (B2a) — an explicit ["Pack","Native"] list puts packs FIRST
constexpr const char*
	kSysInfoFieldName_CoreNamespace_FileSystemPriorityList_Pack =
		"Pack";
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

	/// @brief \~english B3 stream slot of the dispatcher-level bounded
	/// pool (KOTEK_DEF_FILESYSTEM_FSTREAM_POOL_SIZE): one slot = one live
	/// stream, the handle is a pointer into the pool (the documented
	/// handle-as-pointer-into-pool ABI — plan §Risks, kept as-is). A
	/// stream is FORWARD-ONLY: a byte cursor plus ONE outstanding
	/// sequential step, no seeks. The contract lives on
	/// ktkIFileSystem::Begin_Stream.
	struct fstream_state_t
	{
		bool is_free = true;
		/// @brief \~english sticky failure: a data error fails the
		/// stream loudly ONCE and every later Read/Write_Stream returns
		/// false until End_Stream
		bool is_failed = false;
		/// @brief \~english native read streams ride a live mapping when
		/// the kVFMRead feature is in effect (held for the stream's
		/// lifetime, released at End_Stream — map/Begin balances
		/// unmap/End)
		bool is_vfm = false;
		/// @brief \~english Begin_Stream's
		/// force_be_called_from_one_thread_only: pin every later call on
		/// the handle to owner_thread_id (debug discipline)
		bool check_thread = false;
		eFileSystemStreamingType stream_type =
			eFileSystemStreamingType::kAuto;
		eFileSystemPriorityType backend =
			eFileSystemPriorityType::kAuto;
		/// @brief \~english bytes per Read_Stream step — the backend's
		/// block size: KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE (or the
		/// Begin override) on native/mapped,
		/// KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE on pack entries (the
		/// compression block is the atomic step there)
		kun_ktk uint32_t step_size = 0;
		/// @brief \~english read streams: the file/entry size; write
		/// streams: bytes written so far
		kun_ktk uint64_t total_size = 0;
		/// @brief \~english the forward cursor (bytes consumed/written)
		kun_ktk uint64_t position = 0;
		/// @brief \~english the pack cursor: the next compression block
		/// index (blocks of an entry are contiguous on disk — the steps
		/// are one sequential sweep, the HDD discipline)
		kun_ktk uint32_t next_block = 0;
		kun_ktk uint32_t vfm_mapping_id =
			decltype(vfm_mapping_id)(-1);
		FILE* p_file = nullptr;
		std::thread::id owner_thread_id{};
		/// @brief \~english pack streams re-resolve the entry per step
		/// (a hash + binary search per 64 KB block — nothing against the
		/// block's decompress cost) so no mount pointers are held across
		/// calls; kept on every backend for the failure/diagnostic lines
		ktk_filesystem_path path{};
	};

public:
	ktkFileSystem(void);
	~ktkFileSystem(void);

	void Initialize(ktkIFrameworkConfig* p_config) override;

	void Shutdown(void) override;

	bool Is_Exists(
		const ktk_filesystem_path& path,
		bool is_relative_path = false
	) const noexcept override;

	void Create_Directory(
		const ktk_filesystem_path& path,
		eFolderVisibilityType type
	) override;

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

	bool Get_FileSize(
		const ktk_filesystem_path& path_to_file,
		kun_ktk size_t& result,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto
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

	void Make_Path(
		ktk_filesystem_path& path, eFolderIndex index, bool is_relative=false
	) const noexcept override;
	void Make_Path(
		ktk_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& path,
		eFolderIndex index,
		bool is_relative=false
	) const noexcept override;

	ktkFileHandleType Open_File(
		const ktk_filesystem_path& path,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto,
		eFileSystemStreamingType type =
			eFileSystemStreamingType::kReadOnly
	) override;

	 bool Write_File(
		ktkFileHandleType handle,
		const kun_ktk uint8_t* p_buffer,
		kun_ktk size_t length_of_buffer,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto
	) override;

	 bool Write_File(
		ktkFileHandleType handle,
		const char* p_buffer,
		kun_ktk size_t length_of_buffer,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto
	) override;

	bool Get_FileSize(
		 ktkFileHandleType handle,
		 kun_ktk size_t& result,
		 eFileSystemPriorityType priority =
			 eFileSystemPriorityType::kAuto
	 ) override;
	
	bool Seek(
		ktkFileHandleType handle,
		kun_ktk size_t offset,
		eFileSystemSeekType seek_type,
		eFileSystemPriorityType priority = eFileSystemPriorityType::kAuto
	) override;

	bool Tell(
		ktkFileHandleType handle,
		kun_ktk size_t& result,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto
	) override;

	bool Close_File(
		ktkFileHandleType handle,
		eFileSystemPriorityType priority =
			eFileSystemPriorityType::kAuto
	) override;

#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	/// @brief \~english B1 diagnostic seam: the VFM layer (with its
	/// test-pinned map/unmap/cache counters) — concrete-class only,
	/// deliberately not on ktkIFileSystem
	ktkFileSystem_VFM* Get_VFM(void) noexcept
	{
		return &this->m_vfm;
	}
#endif

#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
	/// @brief \~english B2a: mounts one .kpack file into the read path and
	/// makes the priority list real for it — when the configured list
	/// lacks kPack, kPack is PREPENDED (packs override the native dirs —
	/// the "always native-last" choice, documented in the K25 row; an
	/// explicit ["Native","Pack"] list in sys_info.json restores
	/// loose-file-wins). A corrupt pack = loud error + false, other
	/// mounts stay. Test seam AND the conventional-folder mounter share
	/// this entry point.
	bool Mount_Pack(const ktk_filesystem_path& pack_file_path);

	/// @brief \~english B2a diagnostic seam (the Get_VFM precedent —
	/// concrete class, deliberately not on ktkIFileSystem): block-level
	/// reads for B3 ride ktkFileSystem_Pack::Read_File_Block
	ktkFileSystem_Pack* Get_Pack(void) noexcept
	{
		return &this->m_fs_pack;
	}
#endif

private:
	void Validate_Folders(void) noexcept;

	void Validate_Folder(const ktk_filesystem_path& path);

	void Create_ConfigFiles(void) noexcept;

	bool Create_Directory(const ktk_filesystem_path& path
	) const noexcept;

	void Initialize_FrameworkConfig();

	void Create_DefaultFrameworkConfig();
	void Fill_FrameworkConfigDefaults();

	/// @brief \~english B3: validates a stream handle — null, a pointer
	/// outside the pool (foreign/garbage handles never get dereferenced)
	/// or a freed slot all return nullptr
	fstream_state_t* Get_Stream(
		ktkFileHandleType file_handle
	) noexcept;

	const fstream_state_t* Get_Stream(
		ktkFileHandleType file_handle
	) const noexcept;

	/// @brief \~english B3: releases one live slot's OS state (native
	/// fclose, VFM unmap) and returns it to the pool — the shared core
	/// of End_Stream and Shutdown's leaked-stream sweep
	void Release_Stream(fstream_state_t& state) noexcept;

#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
	/// @brief \~english B2a: the ONE allowed directory walk — enumerates
	/// data_game/packs/*.kpack once at Initialize, mounts newest-first.
	/// A missing/empty folder is a silent no-op; a corrupt pack is a loud
	/// skip.
	void Mount_Packs_From_Conventional_Folder();

	/// @brief \~english prepends kPack to the configured priority list
	/// when it is absent (idempotent)
	void Ensure_Pack_In_PriorityList();
#endif

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

#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
	ktkFileSystem_Pack m_fs_pack;
#endif

#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	ktkFileSystem_VFM m_vfm;
#endif

	ktk_unordered_map<
		ktk_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>,
		file_desc_t,
		KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT>
		m_paths_storage;

	/// @brief \~english B3: the bounded stream pool (see
	/// fstream_state_t), resized to the cap in the ctor — handles are
	/// pointers into it and stay valid until End_Stream (a static
	/// vector never reallocates)
	ktk_vector<
		fstream_state_t,
		KOTEK_DEF_FILESYSTEM_FSTREAM_POOL_SIZE>
		m_fstream_pool;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
