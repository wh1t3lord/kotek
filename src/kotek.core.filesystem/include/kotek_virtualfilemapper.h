#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.containers.unordered_map/include/kotek_core_containers_unordered_map.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>
#include <kotek.core.containers.filesystem/include/kotek_core_containers_filesystem.h>
#include <kotek.core.containers.multithreading.atomic/include/kotek_core_containers_multithreading_atomic.h>
#include <kotek.core.containers.queue/include/kotek_core_containers_queue.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// @brief \~english result of ktkFileSystem_VFM::MapFileForRead (B1) —
/// the caller (the native single-shot read) branches on it:
/// kMissingFile and kEmptyFile are FINAL answers (the CRT fallback must
/// NOT engage — the missing case already emitted its single warning
/// here, the empty case is a successful 0-byte read), kMappingFailed
/// asks the caller to degrade to the CRT read (an existing file that
/// failed to map is user data, never a hard error)
enum class eVFMMapFileResult : kun_ktk uint8_t
{
	kSuccess,
	kEmptyFile,
	kMissingFile,
	kMappingFailed
};

/// THREADING (B1): this class is NOT thread-safe by design — the
/// filesystem is a single-threaded component today (the zircon
/// resource worker exists but its real IO is phase B3's scope; the id
/// pool and the counters get their synchronization story there, not
/// here).
///
/// POSTURE (owner directive 2026-09-05): NO user-space mapping cache —
/// the OS page cache already IS the file-content cache, and an
/// engine-side name→mapping cache just duplicates it with worse
/// bookkeeping. A mapped read is map → copy out → unmap; big reads
/// stream through the mapping in
/// KOTEK_DEF_FILESYSTEM_VFM_STREAM_CHUNK_SIZE chunks and repeated
/// access rides the OS page cache or B3's streaming API.
class ktkFileSystem_VFM
{
	using id_type = kun_ktk uint32_t;

	struct vfm_handle_t
	{
#ifdef KOTEK_USE_PLATFORM_WINDOWS
		/// @brief file mapping handle obtained as result of CreateFileMapping
		HANDLE p_fmh = HANDLE(0);
		void* p_data = nullptr;
		size_t file_size = 0;
#else
	#error unknown platform
#endif
	};

public:
	ktkFileSystem_VFM(void);
	~ktkFileSystem_VFM(void);

	void Initialize();
	/// @brief \~english unmaps EVERYTHING still live — with the B1
	/// map→copy→unmap contract nothing should outlive its read, so any
	/// remainder here is a leaked UnMapFile somewhere (the balance
	/// counters make it visible)
	void Shutdown();

	id_type MapFile(FILE* p_file);

	/// @brief \~english unmaps a LIVE slot and marks it free — no
	/// erase: positions of the other live ids must stay stable (the
	/// pre-B1 erase shifted them under any other holder of an id). A
	/// double unmap is a caller logic slip (assert), not user data.
	void UnMapFile(id_type file_id);

	/// @brief \~english B1: maps an existing file for reading by its
	/// ABSOLUTE path (the dispatcher's m_root_path / name form) and
	/// hands the mapping id to the caller, which MUST UnMapFile it
	/// after the copy (the map→copy→unmap contract). The CRT file
	/// handle is never retained — the view survives fclose. A 0-byte
	/// file reports kEmptyFile WITHOUT mapping (CreateFileMapping
	/// rejects size 0 on Win32); a missing file reports kMissingFile
	/// with the single warning already emitted here.
	eVFMMapFileResult MapFileForRead(
		const ktk_filesystem_path& absolute_path,
		id_type& out_mapping_id,
		kun_ktk size_t& out_file_size
	);

	const void* Get_MappedData(id_type file_id) const;

	kun_ktk size_t Get_MappedSize(id_type file_id) const;

	/* B1 test-pinned diagnostics (the house pattern): outstanding
	 * mappings at any moment = Get_StatMapCount() -
	 * Get_StatUnmapCount(); every read balances and Shutdown must see
	 * zero outstanding */
	kun_ktk uint32_t Get_StatMapCount(void) const noexcept;
	kun_ktk uint32_t Get_StatUnmapCount(void) const noexcept;

private:
	ktk_queue<id_type, KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT> m_free_ids;
	ktk_vector<vfm_handle_t, KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT>
		m_mappings;

	// B1 diagnostics — plain members, no atomics: single-threaded by
	// design this phase (see the class note)
	kun_ktk uint32_t m_stat_map_count = 0;
	kun_ktk uint32_t m_stat_unmap_count = 0;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
