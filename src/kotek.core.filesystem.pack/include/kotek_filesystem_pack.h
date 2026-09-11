#pragma once

#include <kotek.core.api/include/kotek_api_no_std.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.containers.filesystem.path/include/kotek_core_containers_filesystem_path.h>
#include <kotek.core.containers.vector/include/kotek_core_containers_vector.h>

#include "kotek_kpack_format.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// @brief \~english the .kpack READER backend (B2a) — an override-chain
/// member of ktkFileSystem's dispatch (eFileSystemPriorityType::kPack).
///
/// Mount-time: header + entry table + block tables are read ONCE and
/// validated (bounded by the KOTEK_DEF_FILESYSTEM_PACK_* defines — see
/// kotek_kpack_format.h for the layout); a pack file stays open (one CRT
/// handle per mount) and answers reads by name-hash with PER-BLOCK
/// decompression — only the blocks a request spans are touched.
///
/// Lookups: mounts are scanned newest-first (the mount order IS the
/// override order — a newer pack shadows an older one), entries inside a
/// mount are hash-sorted and binary-searched.
///
/// THREADING: NOT thread-safe by design this phase (the filesystem is
/// single-threaded today; B3's worker-thread IO is what will need a
/// locking story).
///
/// OWNERSHIP: mount states are heap-allocated by THIS module (Mount) and
/// freed by THIS module (UnmountAll/Shutdown) — the module-boundary rule
/// (never free across a module line). ktkFileSystem embeds this class by
/// value and never touches the mount states directly.
class ktkFileSystem_Pack
{
	/// @brief \~english one in-memory entry: the on-disk record with the
	/// block-table file offset resolved to a base index into the mount's
	/// block_sizes array
	struct pack_entry_t
	{
		kun_ktk uint64_t name_hash;
		kun_ktk uint64_t data_offset;
		kun_ktk uint64_t raw_size;
		kun_ktk uint64_t packed_size;
		kun_ktk uint32_t block_table_begin;
		kun_ktk uint32_t block_count;
		eKpackCompression compression;
	};

	struct mount_state_t
	{
		mount_state_t(void) :
			p_file{},
			path{},
			entries{},
			block_sizes{}
		{
		}

		FILE* p_file;
		ktk_filesystem_path path;
		// hash-sorted at mount (binary search on read)
		ktk_vector<pack_entry_t, KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES>
			entries;
		ktk_vector<
			kun_ktk uint32_t,
			KOTEK_DEF_FILESYSTEM_PACK_MAX_BLOCKS_TOTAL>
			block_sizes;
	};

public:
	ktkFileSystem_Pack();
	~ktkFileSystem_Pack();

	/// @brief \~english wires the filesystem root in — incoming absolute
	/// read paths are relativized against it before hashing (relative
	/// paths pass through). Must be called before Mount/Read.
	void Initialize(const ktk_filesystem_path& root_path);

	/// @brief \~english unmounts everything (Shutdown is UnmountAll + the
	/// debug discipline check)
	void Shutdown(void);

	/// @brief \~english mounts one pack. Returns true when the pack is
	/// usable (a 0-entry pack is a legal empty mount). Returns false on a
	/// corrupt/oversized pack — the error is reported loudly HERE and the
	/// pack is skipped (user data is not a programmer error; other mounts
	/// are unaffected). An entry count above
	/// KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES is clamped with a loud error —
	/// the first cap entries stay readable.
	///
	/// MOUNT ORDER IS PRIORITY ORDER: the caller mounts the NEWEST pack
	/// first; on a name collision across packs the earlier mount wins.
	bool Mount(const ktk_filesystem_path& pack_file_path);

	void UnmountAll(void) noexcept;

	/// @brief \~english full-file read, block-by-block into the caller's
	/// buffer (decompresses every block the file spans; the B3 streaming
	/// API rides Read_File_Block directly). path_name may be root-relative
	/// or absolute (relativized against the root given to Initialize).
	/// Contract: kSuccess = bytes delivered (+ a room-permitting 0
	/// terminator at [size], mirroring the native read); kNotFound =
	/// SILENT fallthrough with the size-0 miss residue (mirroring the
	/// native miss; the dispatcher re-hands the caller's capacity to the
	/// next backend, so the residue can't poison the override chain);
	/// kTooSmall = the size out-param carries the REQUIRED size;
	/// kCorrupt = already reported loudly.
	eKpackReadResult Read_File(
		const ktk_filesystem_path& path_name,
		kun_ktk uint8_t* p_buffer,
		kun_ktk size_t& length_of_buffer
	) noexcept;

	/// @brief \~english the raw (uncompressed) size of a packed entry.
	/// kNotFound is the silent fallthrough, same as Read_File.
	eKpackReadResult Get_FileSize(
		const ktk_filesystem_path& path_name,
		kun_ktk size_t& result
	) noexcept;

	/// @brief \~english reads ONE decompressed block of an entry — the
	/// unit B3's streaming rides: a stream cursor is (entry, next block
	/// index) and every stream step is one Read_File_Block. The caller's
	/// buffer must fit the block's raw size (64 KB, short for the last
	/// block); the size out-param is in=capacity, out=bytes written
	/// (kTooSmall reports the REQUIRED size). A block_index at/past
	/// block_count is a caller error: false-as-kCorrupt with a loud error.
	/// kNotFound is silent with the size-0 miss residue, same as
	/// Read_File.
	eKpackReadResult Read_File_Block(
		const ktk_filesystem_path& path_name,
		kun_ktk uint32_t block_index,
		kun_ktk uint8_t* p_buffer,
		kun_ktk size_t& length_of_buffer
	) noexcept;

	/// @brief \~english diagnostics (test-pinned): mounts currently live
	kun_ktk uint32_t Get_MountedPackCount(void) const noexcept;

private:
	/// @brief \~english folds + relativizes the incoming path into the
	/// canonical root-relative form and hashes it
	kun_ktk uint64_t Hash_PathName(
		const ktk_filesystem_path& path_name) const noexcept;

	/// @brief \~english newest-first scan over the mounts, binary search
	/// inside each (first hit wins = the newest pack shadows older ones)
	const mount_state_t* Find_Entry(
		kun_ktk uint64_t name_hash, const pack_entry_t*& p_out_entry
	) const noexcept;

	eKpackReadResult Read_Block(
		const mount_state_t& mount,
		const pack_entry_t& entry,
		kun_ktk uint32_t block_index,
		kun_ktk uint8_t* p_buffer,
		kun_ktk size_t& length_of_buffer
	) noexcept;

	bool Mount_ReadAndValidate(
		mount_state_t& mount, kun_ktk uint64_t file_size
	) noexcept;

private:
	ktk_filesystem_path m_root_path;

#ifdef KOTEK_DEBUG
	bool m_shutdown_was_called;
	bool m_initialize_was_called;
#endif

	/// newest-first: index 0 wins on a name collision across packs
	ktk_vector<
		mount_state_t*,
		KOTEK_DEF_FILESYSTEM_PACK_MAX_MOUNTED_PACKS>
		m_mounts;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
