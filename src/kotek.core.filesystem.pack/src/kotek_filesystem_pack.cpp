#include "../include/kotek_filesystem_pack.h"

#include <algorithm>
#include <stdio.h>
#include <string.h>

#include <zstd.h>
#include <zlib.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace
{
	// little-endian field decoders — the format is LE by spec and must not
	// depend on the host's struct layout/endianness
	kun_ktk uint32_t kpack_decode_u32(const kun_ktk uint8_t* p) noexcept
	{
		return static_cast<kun_ktk uint32_t>(p[0]) |
			(static_cast<kun_ktk uint32_t>(p[1]) << 8) |
			(static_cast<kun_ktk uint32_t>(p[2]) << 16) |
			(static_cast<kun_ktk uint32_t>(p[3]) << 24);
	}

	kun_ktk uint64_t kpack_decode_u64(const kun_ktk uint8_t* p) noexcept
	{
		return static_cast<kun_ktk uint64_t>(kpack_decode_u32(p)) |
			(static_cast<kun_ktk uint64_t>(kpack_decode_u32(p + 4)) << 32);
	}

	constexpr kun_ktk size_t k_kpack_header_size = 20;
	constexpr kun_ktk size_t k_kpack_entry_record_size = 45;
} // namespace

ktkFileSystem_Pack::ktkFileSystem_Pack() :
#ifdef KOTEK_DEBUG
	m_shutdown_was_called{},
	m_initialize_was_called{},
#endif
	m_root_path{},
	m_mounts{}
{
}

ktkFileSystem_Pack::~ktkFileSystem_Pack()
{
#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(
		this->m_shutdown_was_called,
		"you forgot to call shutdown for this manager"
	);
#endif
}

void ktkFileSystem_Pack::Initialize(const ktk_filesystem_path& root_path)
{
	this->m_root_path = root_path;

#ifdef KOTEK_DEBUG
	this->m_initialize_was_called = true;
#endif
}

void ktkFileSystem_Pack::Shutdown(void)
{
	this->UnmountAll();

#ifdef KOTEK_DEBUG
	this->m_shutdown_was_called = true;
#endif
}

bool ktkFileSystem_Pack::Mount(const ktk_filesystem_path& pack_file_path)
{
#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(
		this->m_initialize_was_called,
		"call Initialize(root_path) before mounting"
	);
#endif

	if (this->m_mounts.size() >=
	    KOTEK_DEF_FILESYSTEM_PACK_MAX_MOUNTED_PACKS)
	{
		KOTEK_MESSAGE_ERROR(
			"can't mount pack {}: the mounted-pack cap ({}) is reached — "
			"the pack is skipped",
			pack_file_path, KOTEK_DEF_FILESYSTEM_PACK_MAX_MOUNTED_PACKS
		);
		return false;
	}

	FILE* p_file = fopen(pack_file_path.c_str(), "rb");

	if (p_file == nullptr)
	{
		// a pack that can't even be opened is a loud error (a pack is
		// shipped/mounted deliberately — unlike a loose-file miss)
		KOTEK_MESSAGE_ERROR(
			"failed to open pack file: {}", pack_file_path
		);
		return false;
	}

	_fseeki64(p_file, 0, SEEK_END);
	const kun_ktk int64_t file_size_signed = _ftelli64(p_file);
	_fseeki64(p_file, 0, SEEK_SET);

	if (file_size_signed <
	    static_cast<kun_ktk int64_t>(k_kpack_header_size))
	{
		KOTEK_MESSAGE_ERROR(
			"pack file {} is truncated (size {} < the {}-byte header) — "
			"the pack is skipped",
			pack_file_path, file_size_signed, k_kpack_header_size
		);
		fclose(p_file);
		return false;
	}

	// the mount tables are big (bounded by the PACK defines), so the mount
	// state lives on the heap — ktkFileSystem (which can sit on a test's
	// stack) only carries the pointer
	mount_state_t* p_mount = new mount_state_t();

	p_mount->p_file = p_file;
	p_mount->path = pack_file_path;

	const bool status = this->Mount_ReadAndValidate(
		*p_mount, static_cast<kun_ktk uint64_t>(file_size_signed)
	);

	if (status == false)
	{
		fclose(p_file);
		delete p_mount;
		return false;
	}

	this->m_mounts.push_back(p_mount);

	KOTEK_MESSAGE(
		"mounted pack {} ({} entries, {} blocks)",
		pack_file_path, p_mount->entries.size(),
		p_mount->block_sizes.size()
	);

	return true;
}

void ktkFileSystem_Pack::UnmountAll(void) noexcept
{
	for (kun_ktk size_t i = 0; i < this->m_mounts.size(); ++i)
	{
		mount_state_t* p_mount = this->m_mounts[i];

		if (p_mount->p_file)
			fclose(p_mount->p_file);

		delete p_mount;
	}

	this->m_mounts.clear();
}

kun_ktk uint32_t ktkFileSystem_Pack::Get_MountedPackCount(void
) const noexcept
{
	return static_cast<kun_ktk uint32_t>(this->m_mounts.size());
}

kun_ktk uint64_t ktkFileSystem_Pack::Hash_PathName(
	const ktk_filesystem_path& path_name) const noexcept
{
	const char* p_text = path_name.c_str();

	// an absolute incoming path is relativized against the filesystem root
	// (fold-rule compare, so case and separator style don't matter)
	if (this->m_root_path.empty() == false)
	{
		const char* p_root = this->m_root_path.c_str();
		const kun_ktk size_t root_length = strlen(p_root);

		bool is_prefixed = true;

		for (kun_ktk size_t i = 0; i < root_length; ++i)
		{
			if (p_text[i] == '\0' ||
			    kpack_fold_ascii(p_text[i]) != kpack_fold_ascii(p_root[i]))
			{
				is_prefixed = false;
				break;
			}
		}

		if (is_prefixed &&
		    (p_text[root_length] == '/' || p_text[root_length] == '\\'))
		{
			p_text += root_length + 1;
		}
	}

	// tolerate leading "./" pairs
	while (p_text[0] == '.' && (p_text[1] == '/' || p_text[1] == '\\'))
		p_text += 2;

	// a ktk_filesystem_path can never exceed the cap, so truncation here
	// is only a theoretical bound
	kun_ktk size_t name_length = 0;
	while (p_text[name_length] != '\0' &&
	       name_length < KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH)
		++name_length;

	// the fold rule itself lives inside kpack_hash_name
	return kpack_hash_name(p_text, name_length);
}

const ktkFileSystem_Pack::mount_state_t* ktkFileSystem_Pack::Find_Entry(
	kun_ktk uint64_t name_hash, const pack_entry_t*& p_out_entry
) const noexcept
{
	p_out_entry = nullptr;

	for (kun_ktk size_t i = 0; i < this->m_mounts.size(); ++i)
	{
		const mount_state_t* p_mount = this->m_mounts[i];

		// hand-rolled lower_bound over the hash-sorted entry table
		kun_ktk size_t left = 0;
		kun_ktk size_t right = p_mount->entries.size();

		while (left < right)
		{
			const kun_ktk size_t middle = (left + right) / 2;

			if (p_mount->entries[middle].name_hash < name_hash)
				left = middle + 1;
			else
				right = middle;
		}

		if (left < p_mount->entries.size() &&
		    p_mount->entries[left].name_hash == name_hash)
		{
			p_out_entry = &p_mount->entries[left];
			return p_mount;
		}
	}

	return nullptr;
}

eKpackReadResult ktkFileSystem_Pack::Read_Block(
	const mount_state_t& mount,
	const pack_entry_t& entry,
	kun_ktk uint32_t block_index,
	kun_ktk uint8_t* p_buffer,
	kun_ktk size_t& length_of_buffer
) noexcept
{
	const kun_ktk uint64_t expected_raw64 =
		entry.raw_size -
		static_cast<kun_ktk uint64_t>(block_index) *
			KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;

	const kun_ktk size_t expected_raw = static_cast<kun_ktk size_t>(
		expected_raw64 < KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
			? expected_raw64
			: KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
	);

	if (length_of_buffer < expected_raw)
	{
		length_of_buffer = expected_raw;
		return eKpackReadResult::kTooSmall;
	}

	const kun_ktk uint32_t packed_block_size =
		mount.block_sizes[entry.block_table_begin + block_index];

	kun_ktk uint64_t block_offset = entry.data_offset;

	for (kun_ktk uint32_t i = 0; i < block_index; ++i)
		block_offset += mount.block_sizes[entry.block_table_begin + i];

	if (_fseeki64(
			mount.p_file, static_cast<kun_ktk int64_t>(block_offset),
			SEEK_SET
		) != 0)
	{
		KOTEK_MESSAGE_ERROR(
			"pack {}: failed to seek to block {} of an entry "
			"(offset {})",
			mount.path, block_index, block_offset
		);
		return eKpackReadResult::kCorrupt;
	}

	if (entry.compression == eKpackCompression::kStored)
	{
		// a stored block is the raw bytes themselves — read straight
		// into the caller's buffer, no scratch
		const size_t was_read =
			fread(p_buffer, 1, expected_raw, mount.p_file);

		if (was_read != expected_raw)
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: short read on a stored block ({} of {})",
				mount.path, was_read, expected_raw
			);
			return eKpackReadResult::kCorrupt;
		}

		length_of_buffer = expected_raw;
		return eKpackReadResult::kSuccess;
	}

	// one fixed scratch per in-flight block read — the consumer never
	// holds more than one block over its own buffer (the streaming
	// posture)
	kun_ktk uint8_t packed_scratch
		[KOTEK_DEF_FILESYSTEM_PACK_MAX_PACKED_BLOCK_SIZE];

	const size_t was_read =
		fread(packed_scratch, 1, packed_block_size, mount.p_file);

	if (was_read != packed_block_size)
	{
		KOTEK_MESSAGE_ERROR(
			"pack {}: short read on a packed block ({} of {})",
			mount.path, was_read, packed_block_size
		);
		return eKpackReadResult::kCorrupt;
	}

	switch (entry.compression)
	{
	case eKpackCompression::kZstd:
	{
		const size_t decoded = ZSTD_decompress(
			p_buffer, expected_raw, packed_scratch, packed_block_size
		);

		if (ZSTD_isError(decoded) || decoded != expected_raw)
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: zstd block decompression failed ({})",
				mount.path,
				ZSTD_isError(decoded) ? ZSTD_getErrorName(decoded)
				                      : "size mismatch"
			);
			return eKpackReadResult::kCorrupt;
		}

		break;
	}
	case eKpackCompression::kZlib:
	{
		uLongf decoded_length = static_cast<uLongf>(expected_raw);

		const int zlib_status = uncompress(
			p_buffer, &decoded_length, packed_scratch,
			static_cast<uLong>(packed_block_size)
		);

		if (zlib_status != Z_OK ||
		    decoded_length != static_cast<uLongf>(expected_raw))
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: zlib block decompression failed "
				"(status {})",
				mount.path, zlib_status
			);
			return eKpackReadResult::kCorrupt;
		}

		break;
	}
	default:
	{
		// unreachable — the compression enum is validated at mount
		KOTEK_ASSERT(false, "corrupt mount state");
		return eKpackReadResult::kCorrupt;
	}
	}

	length_of_buffer = expected_raw;
	return eKpackReadResult::kSuccess;
}

eKpackReadResult ktkFileSystem_Pack::Read_File(
	const ktk_filesystem_path& path_name,
	kun_ktk uint8_t* p_buffer,
	kun_ktk size_t& length_of_buffer
) noexcept
{
	KOTEK_ASSERT(
		path_name.empty() == false, "you can't pass an empty path"
	);
	KOTEK_ASSERT(p_buffer, "you can't pass a null buffer");

	const kun_ktk size_t capacity = length_of_buffer;

	const pack_entry_t* p_entry = nullptr;
	const mount_state_t* p_mount =
		this->Find_Entry(this->Hash_PathName(path_name), p_entry);

	if (p_mount == nullptr)
	{
		// not mine — the dispatcher falls through SILENTLY (the
		// override-chain rule). The miss residue is size 0, mirroring the
		// native miss exactly; the dispatcher re-hands the caller's
		// capacity to the next backend, so this can't poison the chain
		length_of_buffer = 0;
		return eKpackReadResult::kNotFound;
	}

	if (p_entry->raw_size == 0)
	{
		// a 0-byte entry is an explicit successful empty read, mirroring
		// the native empty-file path (terminator included)
		if (capacity > 0)
			p_buffer[0] = '\0';

		length_of_buffer = 0;
		return eKpackReadResult::kSuccess;
	}

	if (capacity < p_entry->raw_size)
	{
		// the B0 too-small contract: fail + the REQUIRED size
		length_of_buffer =
			static_cast<kun_ktk size_t>(p_entry->raw_size);
		return eKpackReadResult::kTooSmall;
	}

	// block-by-block into the caller's buffer — the whole file is never
	// materialized anywhere else
	for (kun_ktk uint32_t i = 0; i < p_entry->block_count; ++i)
	{
		kun_ktk size_t block_out = capacity;

		const eKpackReadResult block_status = this->Read_Block(
			*p_mount, *p_entry, i,
			p_buffer +
				static_cast<kun_ktk size_t>(i) *
					KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE,
			block_out
		);

		if (block_status != eKpackReadResult::kSuccess)
			return block_status;
	}

	// mirror the native read: a room-permitting terminator at [size]
	if (capacity > p_entry->raw_size)
		p_buffer[p_entry->raw_size] = '\0';

	length_of_buffer = static_cast<kun_ktk size_t>(p_entry->raw_size);
	return eKpackReadResult::kSuccess;
}

eKpackReadResult ktkFileSystem_Pack::Get_FileSize(
	const ktk_filesystem_path& path_name, kun_ktk size_t& result
) noexcept
{
	KOTEK_ASSERT(
		path_name.empty() == false, "you can't pass an empty path"
	);

	result = 0;

	const pack_entry_t* p_entry = nullptr;
	const mount_state_t* p_mount =
		this->Find_Entry(this->Hash_PathName(path_name), p_entry);

	if (p_mount == nullptr)
		return eKpackReadResult::kNotFound;

	result = static_cast<kun_ktk size_t>(p_entry->raw_size);
	return eKpackReadResult::kSuccess;
}

eKpackReadResult ktkFileSystem_Pack::Read_File_Block(
	const ktk_filesystem_path& path_name,
	kun_ktk uint32_t block_index,
	kun_ktk uint8_t* p_buffer,
	kun_ktk size_t& length_of_buffer
) noexcept
{
	KOTEK_ASSERT(
		path_name.empty() == false, "you can't pass an empty path"
	);
	KOTEK_ASSERT(p_buffer, "you can't pass a null buffer");

	const pack_entry_t* p_entry = nullptr;
	const mount_state_t* p_mount =
		this->Find_Entry(this->Hash_PathName(path_name), p_entry);

	if (p_mount == nullptr)
	{
		// same contract as Read_File: silent, size-0 miss residue
		length_of_buffer = 0;
		return eKpackReadResult::kNotFound;
	}

	if (block_index >= p_entry->block_count)
	{
		KOTEK_MESSAGE_ERROR(
			"pack {}: block index {} is past the entry's block count "
			"({})",
			p_mount->path, block_index, p_entry->block_count
		);
		return eKpackReadResult::kCorrupt;
	}

	return this->Read_Block(
		*p_mount, *p_entry, block_index, p_buffer, length_of_buffer
	);
}

bool ktkFileSystem_Pack::Mount_ReadAndValidate(
	mount_state_t& mount, kun_ktk uint64_t file_size
) noexcept
{
	kun_ktk uint8_t header[k_kpack_header_size];

	if (fread(header, 1, sizeof(header), mount.p_file) != sizeof(header))
	{
		KOTEK_MESSAGE_ERROR(
			"pack {}: failed to read the header — the pack is skipped",
			mount.path
		);
		return false;
	}

	if (memcmp(header, kKpackMagic, sizeof(kKpackMagic)) != 0)
	{
		KOTEK_MESSAGE_ERROR(
			"pack {}: bad magic (not a {} pack / version mismatch) — "
			"the pack is skipped",
			mount.path, kKpackMagic
		);
		return false;
	}

	const kun_ktk uint32_t declared_entry_count =
		kpack_decode_u32(header + 8);
	const kun_ktk uint32_t flags = kpack_decode_u32(header + 12);

	if (flags != 0)
	{
		KOTEK_MESSAGE_ERROR(
			"pack {}: reserved header flags must be 0 (got {}) — the "
			"pack is skipped",
			mount.path, flags
		);
		return false;
	}

	kun_ktk uint32_t entry_count = declared_entry_count;

	if (entry_count > KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES)
	{
		// clamp, don't reject: the first cap entries stay readable, and
		// the excess is reported loudly
		KOTEK_MESSAGE_ERROR(
			"pack {}: entry count {} exceeds the reader cap ({}) — "
			"only the first {} entries are readable",
			mount.path, entry_count,
			KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES,
			KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES
		);
		entry_count = KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES;
	}

	// an empty pack is legal: it mounts and answers nothing
	if (entry_count == 0)
		return true;

	const kun_ktk uint64_t table_bytes =
		static_cast<kun_ktk uint64_t>(entry_count) *
		k_kpack_entry_record_size;

	if (k_kpack_header_size + table_bytes > file_size)
	{
		KOTEK_MESSAGE_ERROR(
			"pack {}: truncated entry table (need {} bytes, file is "
			"{}) — the pack is skipped",
			mount.path, k_kpack_header_size + table_bytes, file_size
		);
		return false;
	}

	kun_ktk uint8_t* p_table = new kun_ktk uint8_t[table_bytes];

	if (fread(p_table, 1, table_bytes, mount.p_file) != table_bytes)
	{
		KOTEK_MESSAGE_ERROR(
			"pack {}: failed to read the entry table — the pack is "
			"skipped",
			mount.path
		);
		delete[] p_table;
		return false;
	}

	mount.entries.resize(entry_count);

	// pass 1: decode + validate the records, accumulate the block budget
	kun_ktk uint64_t total_blocks = 0;

	for (kun_ktk uint32_t i = 0; i < entry_count; ++i)
	{
		const kun_ktk uint8_t* p_record =
			p_table + i * k_kpack_entry_record_size;

		pack_entry_t decoded;
		decoded.name_hash = kpack_decode_u64(p_record);
		decoded.data_offset = kpack_decode_u64(p_record + 8);
		decoded.raw_size = kpack_decode_u64(p_record + 16);
		decoded.packed_size = kpack_decode_u64(p_record + 24);
		decoded.compression =
			static_cast<eKpackCompression>(p_record[32]);
		decoded.block_count = kpack_decode_u32(p_record + 33);
		// assigned in pass 2 against the running block base
		decoded.block_table_begin = 0;

		const kun_ktk uint64_t block_table_offset =
			kpack_decode_u64(p_record + 37);

		const char* p_why = nullptr;

		if (decoded.compression == eKpackCompression::kEndOfEnum ||
		    static_cast<kun_ktk uint8_t>(decoded.compression) >
		        static_cast<kun_ktk uint8_t>(
					eKpackCompression::kZlib
		        ))
		{
			p_why = "unknown compression id";
		}
		else if (
			decoded.block_count >
		    KOTEK_DEF_FILESYSTEM_PACK_MAX_BLOCKS_PER_ENTRY)
		{
			p_why = "block count exceeds the per-entry cap";
		}
		else if (
			kpack_block_count_for_size(decoded.raw_size) !=
		    decoded.block_count)
		{
			p_why = "block count is not ceil(raw_size / 64 KB)";
		}
		else if (
			decoded.data_offset %
			    KOTEK_DEF_FILESYSTEM_PACK_DATA_ALIGNMENT !=
		    0)
		{
			p_why = "data offset is not 4 KB-aligned";
		}
		else if (
			decoded.data_offset + decoded.packed_size > file_size)
		{
			p_why = "the data span runs past the end of file";
		}
		else if (
			block_table_offset +
			    static_cast<kun_ktk uint64_t>(decoded.block_count) *
			        sizeof(kun_ktk uint32_t) >
			file_size)
		{
			p_why = "the block table runs past the end of file";
		}

		if (p_why)
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: entry {} is invalid ({}) — the pack is "
				"skipped",
				mount.path, i, p_why
			);
			delete[] p_table;
			return false;
		}

		total_blocks += decoded.block_count;

		if (total_blocks > KOTEK_DEF_FILESYSTEM_PACK_MAX_BLOCKS_TOTAL)
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: total block count exceeds the reader cap "
				"({}) — the pack is skipped",
				mount.path, KOTEK_DEF_FILESYSTEM_PACK_MAX_BLOCKS_TOTAL
			);
			delete[] p_table;
			return false;
		}

		mount.entries[i] = decoded;
	}

	// pass 2: read + validate the block tables
	mount.block_sizes.resize(static_cast<kun_ktk size_t>(total_blocks));

	kun_ktk uint32_t block_base = 0;

	for (kun_ktk uint32_t i = 0; i < entry_count; ++i)
	{
		const kun_ktk uint8_t* p_record =
			p_table + i * k_kpack_entry_record_size;

		pack_entry_t& entry = mount.entries[i];

		const kun_ktk uint64_t block_table_offset =
			kpack_decode_u64(p_record + 37);

		entry.block_table_begin = block_base;
		block_base += entry.block_count;

		if (entry.block_count == 0)
		{
			if (entry.packed_size != 0)
			{
				KOTEK_MESSAGE_ERROR(
					"pack {}: entry {} has 0 blocks but a non-zero "
					"packed size — the pack is skipped",
					mount.path, i
				);
				delete[] p_table;
				return false;
			}
			continue;
		}

		if (_fseeki64(
				mount.p_file,
				static_cast<kun_ktk int64_t>(block_table_offset),
				SEEK_SET
			) != 0)
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: failed to seek to entry {}'s block table — "
				"the pack is skipped",
				mount.path, i
			);
			delete[] p_table;
			return false;
		}

		// a per-entry table is capped by the per-entry block cap
		kun_ktk uint8_t block_scratch
			[KOTEK_DEF_FILESYSTEM_PACK_MAX_BLOCKS_PER_ENTRY *
		     sizeof(kun_ktk uint32_t)];

		const kun_ktk size_t table_size =
			static_cast<kun_ktk size_t>(entry.block_count) *
			sizeof(kun_ktk uint32_t);

		if (fread(block_scratch, 1, table_size, mount.p_file) !=
		    table_size)
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: failed to read entry {}'s block table — "
				"the pack is skipped",
				mount.path, i
			);
			delete[] p_table;
			return false;
		}

		kun_ktk uint64_t packed_sum = 0;

		for (kun_ktk uint32_t b = 0; b < entry.block_count; ++b)
		{
			const kun_ktk uint32_t packed_block_size =
				kpack_decode_u32(
					block_scratch + b * sizeof(kun_ktk uint32_t)
				);

			mount.block_sizes[entry.block_table_begin + b] =
				packed_block_size;

			packed_sum += packed_block_size;

			const char* p_block_why = nullptr;

			if (packed_block_size == 0 ||
			    packed_block_size >
			        KOTEK_DEF_FILESYSTEM_PACK_MAX_PACKED_BLOCK_SIZE)
			{
				p_block_why = "packed block size is out of bounds";
			}
			else if (
				entry.compression == eKpackCompression::kStored)
			{
				// a stored span is the raw bytes contiguously — each
				// block size is exactly its raw piece
				const kun_ktk uint64_t raw_piece =
					entry.raw_size -
					static_cast<kun_ktk uint64_t>(b) *
						KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;
				const kun_ktk uint64_t expected_piece =
					raw_piece < KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
					? raw_piece
					: KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;

				if (packed_block_size != expected_piece)
					p_block_why =
						"a stored block size is not its raw piece";
			}

			if (p_block_why)
			{
				KOTEK_MESSAGE_ERROR(
					"pack {}: entry {} block {} is invalid ({}) — "
					"the pack is skipped",
					mount.path, i, b, p_block_why
				);
				delete[] p_table;
				return false;
			}
		}

		if (packed_sum != entry.packed_size)
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: entry {}'s block table sums to {} but the "
				"packed size is {} — the pack is skipped",
				mount.path, i, packed_sum, entry.packed_size
			);
			delete[] p_table;
			return false;
		}
	}

	delete[] p_table;

	// hash-sort the entries (bounded one-time mount cost) so reads
	// binary-search
	std::sort(
		mount.entries.begin(), mount.entries.end(),
		[](const pack_entry_t& left, const pack_entry_t& right)
		{
			return left.name_hash < right.name_hash;
		}
	);

	// a duplicated name hash means a corrupt or hostile pack (the writer
	// rejects duplicates) — reject loudly
	for (kun_ktk size_t i = 1; i < mount.entries.size(); ++i)
	{
		if (mount.entries[i - 1].name_hash ==
		    mount.entries[i].name_hash)
		{
			KOTEK_MESSAGE_ERROR(
				"pack {}: duplicate name hash in the entry table — "
				"the pack is skipped",
				mount.path
			);
			return false;
		}
	}

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
