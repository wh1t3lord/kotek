#pragma once

#include <kotek.core.api/include/kotek_api_no_std.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// @brief \~english the .kpack archive format, v1 (the magic carries the
/// version). Little-endian, written field-by-field (no struct dumps, no
/// padding bytes); big-endian hosts would need a byte-swap layer (the
/// framework is Windows-first today).
///
/// On-disk layout:
///
/// [header] 20 bytes
///   +0   8   magic char[8] = {'K','P','A','C','K','0','1','\0'}
///   +8   4   entry_count u32
///   +12  4   flags u32 (reserved, must be 0 in v1)
/// [entry table] entry_count records x 45 bytes, in writer (load) order:
///   +0   8   name_hash u64 — kpack_hash_name of the normalized
///            root-relative path (see the fold rule below)
///   +8   8   data_offset u64 — absolute file offset of the entry's first
///            packed block, aligned to
///            KOTEK_DEF_FILESYSTEM_PACK_DATA_ALIGNMENT (4 KB)
///   +16  8   raw_size u64 — uncompressed size
///   +24  8   packed_size u64 — must equal the sum of the entry's block
///            table (the reader validates this at mount)
///   +32  1   compression u8 — eKpackCompression (0=stored, 1=zstd, 2=zlib)
///   +33  4   block_count u32 — exactly ceil(raw_size / 64 KB); a 0-byte
///            entry has 0 blocks
///   +37  8   block_table_offset u64 — absolute file offset of the entry's
///            block table
/// [block tables] per entry: block_count x packed_block_size u32. Each
///   block compresses KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE (64 KB) of raw
///   data independently (the last block may be short) — that is what lets
///   the reader decompress ONLY the blocks a requested range spans (the
///   streaming posture; B3's stream steps are these blocks). Stored
///   entries keep the same table shape (block sizes are the raw 64 KB
///   pieces), their data is a single contiguous span with no per-block
///   compression.
/// [data] the packed blocks in ENTRY order (the writer lays entries out in
///   load order; the reader does not care — every offset is absolute).
///   Block i of an entry sits at data_offset + sum(block_sizes[0..i-1]).
///
/// The reader's mount-time bounds (all named defines, sized in
/// kotek.core.defines.static.cpp): entry_count is clamped to
/// KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES with a loud error (the first cap
/// entries stay readable); block_count per entry must be <=
/// KOTEK_DEF_FILESYSTEM_PACK_MAX_BLOCKS_PER_ENTRY and the pack's total
/// block count <= KOTEK_DEF_FILESYSTEM_PACK_MAX_BLOCKS_TOTAL, otherwise the
/// pack is rejected (loud, graceful — other packs still mount).

/// @brief \~english compression codec id stored in every entry record
enum class eKpackCompression : kun_ktk uint8_t
{
	kStored = 0,
	kZstd = 1,
	kZlib = 2,
	kEndOfEnum
};

/// @brief \~english tri-state of a pack read: a pack is an OVERRIDE-CHAIN
/// backend, so "the entry is not in any mounted pack" is NOT an error and
/// NOT a warning — the dispatcher falls through to the next backend
/// silently. Corrupt data behind an EXISTING entry is the loud case (a
/// KOTEK_MESSAGE_ERROR is emitted at the point of detection).
enum class eKpackReadResult : kun_ktk uint8_t
{
	/// bytes were delivered
	kSuccess,
	/// not present in any mounted pack — silent fallthrough
	kNotFound,
	/// the entry exists but the caller's buffer is too small; the size
	/// out-param carries the REQUIRED size (the B0 contract)
	kTooSmall,
	/// the entry exists but its data failed validation/decompression —
	/// already reported loudly
	kCorrupt
};

/// @brief \~english the .kpack magic WITH the format version inside
/// ("KPACK01" + NUL); a format change bumps the digits, so old readers
/// reject new packs on the magic comparison alone
inline constexpr char kKpackMagic[8] = {'K', 'P', 'A', 'C', 'K', '0', '1', '\0'};

/// @brief \~english the .kpack file extension (with dot), used by the
/// mount-time folder enumeration
constexpr const char* kKpackFileExtension = ".kpack";

/// @brief \~english the conventional pack folder under the data_game root
/// ("data_game/packs") — mounted newest-first at filesystem Initialize when
/// the folder exists (the ONE allowed directory walk)
constexpr const char* kKpackPacksFolderName = "packs";

/// @brief \~english THE name fold rule (single source for writer and
/// reader): '\\' becomes '/', ASCII 'A'..'Z' fold to 'a'..'z', every other
/// byte passes through unchanged. Entry names are root-relative paths with
/// forward slashes after folding; the reader additionally relativizes an
/// absolute incoming path against the filesystem root before hashing.
constexpr char kpack_fold_ascii(char symbol) noexcept
{
	if (symbol == '\\')
		return '/';

	if (symbol >= 'A' && symbol <= 'Z')
		return static_cast<char>(symbol - 'A' + 'a');

	return symbol;
}

/// @brief \~english fnv1a-64 over the fold-rule-normalized name bytes
inline kun_ktk uint64_t kpack_hash_name(
	const char* p_name, kun_ktk size_t name_length) noexcept
{
	constexpr kun_ktk uint64_t k_offset_basis = 14695981039346656037ull;
	constexpr kun_ktk uint64_t k_prime = 1099511628211ull;

	kun_ktk uint64_t hash = k_offset_basis;

	for (kun_ktk size_t i = 0; i < name_length; ++i)
	{
		hash ^= static_cast<kun_ktk uint8_t>(
			kpack_fold_ascii(p_name[i]));
		hash *= k_prime;
	}

	return hash;
}

/// @brief \~english ceil(raw_size / 64 KB) — the format's block_count rule
/// (a 0-byte entry has 0 blocks)
constexpr kun_ktk uint64_t kpack_block_count_for_size(
	kun_ktk uint64_t raw_size) noexcept
{
	return (raw_size + KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE - 1) /
		KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;
}

/// @brief \~english one entry for the pack writer: raw bytes + the codec.
/// The name is the root-relative path (any separator/case — the writer
/// applies the fold rule); names with a drive letter, a leading separator
/// or ".." segments are rejected (packs never address outside the root).
struct kpack_writer_entry_t
{
	const char* p_name;
	const kun_ktk uint8_t* p_data;
	kun_ktk size_t data_size;
	eKpackCompression compression;
};

/// @brief \~english writes a .kpack file from the given entries, in the
/// given order (= load order). Streams block-by-block through fixed
/// scratch buffers (never materializes the whole pack in RAM) and patches
/// the tables in place at the end, so a failed write leaves a partial file
/// that fails the reader's mount validation loudly. Returns false (with a
/// loud error) on invalid input (empty/over-long name, path escapes, a
/// duplicate name hash, a block-count overflow) or on any IO/compression
/// failure.
///
/// SHARING STORY (B2b): this is THE encoder — the zircon_kpacker host tool
/// links kotek.core.filesystem.pack and calls this function; the format
/// constants + the fold/hash rules above are the format's single source of
/// truth for both sides.
bool kpack_write_file(
	const char* p_pack_file_path,
	const kpack_writer_entry_t* p_entries,
	kun_ktk size_t entry_count
) noexcept;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
