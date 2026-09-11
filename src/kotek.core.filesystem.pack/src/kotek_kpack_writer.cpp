#include "../include/kotek_core_filesystem_pack.h"

#include <stdio.h>
#include <string.h>

#include <zstd.h>
#include <zlib.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace
{
	constexpr kun_ktk size_t k_kpack_header_size = 20;
	constexpr kun_ktk size_t k_kpack_entry_record_size = 45;

	void kpack_encode_u32(kun_ktk uint8_t* p, kun_ktk uint32_t v) noexcept
	{
		p[0] = static_cast<kun_ktk uint8_t>(v & 0xFF);
		p[1] = static_cast<kun_ktk uint8_t>((v >> 8) & 0xFF);
		p[2] = static_cast<kun_ktk uint8_t>((v >> 16) & 0xFF);
		p[3] = static_cast<kun_ktk uint8_t>((v >> 24) & 0xFF);
	}

	void kpack_encode_u64(kun_ktk uint8_t* p, kun_ktk uint64_t v) noexcept
	{
		kpack_encode_u32(p, static_cast<kun_ktk uint32_t>(v & 0xFFFFFFFFull));
		kpack_encode_u32(p + 4, static_cast<kun_ktk uint32_t>(v >> 32));
	}

	/// the pack name rules (writer-side): root-relative, non-empty, no
	/// drive letter, no leading separator, no ".." segments — a pack never
	/// addresses anything outside the filesystem root
	bool kpack_is_name_valid(const char* p_name, kun_ktk size_t length) noexcept
	{
		if (length == 0 || length > KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH)
			return false;

		if (p_name[0] == '/' || p_name[0] == '\\')
			return false;

		for (kun_ktk size_t i = 0; i < length; ++i)
		{
			const char symbol = p_name[i];

			if (symbol == ':')
				return false;

			// a ".." segment: two dots bounded by the string start /
			// separators / the string end
			if (symbol == '.' &&
			    (i == 0 || p_name[i - 1] == '/' || p_name[i - 1] == '\\') &&
			    i + 1 < length && p_name[i + 1] == '.' &&
			    (i + 2 >= length || p_name[i + 2] == '/' ||
			     p_name[i + 2] == '\\'))
			{
				return false;
			}
		}

		return true;
	}

	/// one entry's write-time bookkeeping (the on-disk record fields plus
	/// nothing else — the tables are patched in place at the end)
	struct kpack_write_entry_state_t
	{
		kun_ktk uint64_t name_hash;
		kun_ktk uint64_t data_offset;
		kun_ktk uint64_t raw_size;
		kun_ktk uint64_t packed_size;
		kun_ktk uint64_t block_table_offset;
		kun_ktk uint32_t block_count;
		eKpackCompression compression;
	};
} // namespace

bool kpack_write_file(
	const char* p_pack_file_path,
	const kpack_writer_entry_t* p_entries,
	kun_ktk size_t entry_count
) noexcept
{
	if (p_pack_file_path == nullptr || p_pack_file_path[0] == '\0')
	{
		KOTEK_MESSAGE_ERROR("kpack writer: an empty pack path");
		return false;
	}

	if (entry_count > 0 && p_entries == nullptr)
	{
		KOTEK_MESSAGE_ERROR("kpack writer: a null entry array");
		return false;
	}

	if (entry_count > 0xFFFFFFFFu)
	{
		KOTEK_MESSAGE_ERROR(
			"kpack writer: entry count {} does not fit u32", entry_count
		);
		return false;
	}

	// NOTE ON CAPS: the writer enforces structural sanity only (names,
	// duplicate hashes, u32 fits). The READER's mount caps
	// (KOTEK_DEF_FILESYSTEM_PACK_MAX_ENTRIES / _MAX_BLOCKS_TOTAL /
	// _MAX_BLOCKS_PER_ENTRY) are deliberately NOT enforced here — the
	// reader clamps/rejects loudly at mount, and tests build over-cap
	// packs through this writer to prove it.

	// validate + hash every name up front (a pack write is all-or-nothing)
	kun_ktk uint64_t* p_hashes =
		entry_count ? new kun_ktk uint64_t[entry_count] : nullptr;

	for (kun_ktk size_t i = 0; i < entry_count; ++i)
	{
		const char* p_name = p_entries[i].p_name;
		const kun_ktk size_t name_length =
			p_name ? strlen(p_name) : 0;

		if (p_name == nullptr ||
		    kpack_is_name_valid(p_name, name_length) == false)
		{
			KOTEK_MESSAGE_ERROR(
				"kpack writer: entry {} has an invalid name ('{}')",
				i, p_name ? p_name : "<null>"
			);
			delete[] p_hashes;
			return false;
		}

		if (p_entries[i].data_size > 0 && p_entries[i].p_data == nullptr)
		{
			KOTEK_MESSAGE_ERROR(
				"kpack writer: entry '{}' has data size {} but a null "
				"buffer",
				p_name, p_entries[i].data_size
			);
			delete[] p_hashes;
			return false;
		}

		if (static_cast<kun_ktk uint8_t>(p_entries[i].compression) >=
		    static_cast<kun_ktk uint8_t>(eKpackCompression::kEndOfEnum))
		{
			KOTEK_MESSAGE_ERROR(
				"kpack writer: entry '{}' has an unknown compression id",
				p_name
			);
			delete[] p_hashes;
			return false;
		}

		p_hashes[i] = kpack_hash_name(p_name, name_length);
	}

	// duplicate name hashes (a hash collision or a repeated name) make a
	// pack ambiguous — rejected here, re-rejected by the reader at mount
	for (kun_ktk size_t i = 0; i < entry_count; ++i)
	{
		for (kun_ktk size_t j = i + 1; j < entry_count; ++j)
		{
			if (p_hashes[i] == p_hashes[j])
			{
				KOTEK_MESSAGE_ERROR(
					"kpack writer: entries '{}' and '{}' share one name "
					"hash",
					p_entries[i].p_name, p_entries[j].p_name
				);
				delete[] p_hashes;
				return false;
			}
		}
	}

	// per-entry write state + the flat block-size table (patched into the
	// file at the end)
	kpack_write_entry_state_t* p_states =
		entry_count ? new kpack_write_entry_state_t[entry_count] : nullptr;

	kun_ktk uint64_t total_blocks = 0;

	for (kun_ktk size_t i = 0; i < entry_count; ++i)
	{
		kpack_write_entry_state_t& state = p_states[i];

		state.name_hash = p_hashes[i];
		state.raw_size =
			static_cast<kun_ktk uint64_t>(p_entries[i].data_size);
		state.compression = p_entries[i].compression;
		state.block_count = static_cast<kun_ktk uint32_t>(
			kpack_block_count_for_size(state.raw_size)
		);
		state.block_table_offset = 0;
		state.data_offset = 0;
		state.packed_size = 0;

		total_blocks += state.block_count;

		if (total_blocks > 0xFFFFFFFFu)
		{
			KOTEK_MESSAGE_ERROR(
				"kpack writer: the total block count does not fit u32"
			);
			delete[] p_hashes;
			delete[] p_states;
			return false;
		}
	}

	kun_ktk uint32_t* p_block_sizes = total_blocks
		? new kun_ktk uint32_t[static_cast<size_t>(total_blocks)]
		: nullptr;

	delete[] p_hashes;
	p_hashes = nullptr;

	FILE* p_file = fopen(p_pack_file_path, "wb");

	if (p_file == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"kpack writer: failed to open {} for writing",
			p_pack_file_path
		);
		delete[] p_states;
		delete[] p_block_sizes;
		return false;
	}

	bool status = false;
	kun_ktk uint32_t* p_block_size_iter = p_block_sizes;

	// the fixed per-block scratch — the writer never holds more than one
	// packed block over the caller's raw bytes
	kun_ktk uint8_t* p_packed_scratch =
		new kun_ktk uint8_t[KOTEK_DEF_FILESYSTEM_PACK_MAX_PACKED_BLOCK_SIZE];

	{
		// [header] — real entry_count, reserved flags 0
		kun_ktk uint8_t header[k_kpack_header_size] = {};
		memcpy(header, kKpackMagic, sizeof(kKpackMagic));
		kpack_encode_u32(
			header + 8, static_cast<kun_ktk uint32_t>(entry_count)
		);
		kpack_encode_u32(header + 12, 0);

		if (fwrite(header, 1, sizeof(header), p_file) != sizeof(header))
		{
			KOTEK_MESSAGE_ERROR(
				"kpack writer: failed to write the header of {}",
				p_pack_file_path
			);
			goto cleanup;
		}

		// [entry table] + [block tables] placeholders — patched below
		const kun_ktk uint64_t entry_table_bytes =
			static_cast<kun_ktk uint64_t>(entry_count) *
			k_kpack_entry_record_size;
		const kun_ktk uint64_t block_tables_bytes =
			total_blocks * sizeof(kun_ktk uint32_t);

		{
			const kun_ktk uint64_t zero_region =
				entry_table_bytes + block_tables_bytes;
			kun_ktk uint8_t zero_page[4096] = {};
			kun_ktk uint64_t written = 0;

			while (written < zero_region)
			{
				const kun_ktk uint64_t left = zero_region - written;
				const size_t chunk =
					static_cast<size_t>(left < sizeof(zero_page)
							? left
							: sizeof(zero_page));

				if (fwrite(zero_page, 1, chunk, p_file) != chunk)
				{
					KOTEK_MESSAGE_ERROR(
						"kpack writer: failed to reserve the tables of "
						"{}",
						p_pack_file_path
					);
					goto cleanup;
				}

				written += chunk;
			}
		}

		// block_table_offset for entry i: right after the entry table,
		// tables laid out in entry order
		{
			kun_ktk uint64_t block_table_cursor =
				k_kpack_header_size + entry_table_bytes;

			for (kun_ktk size_t i = 0; i < entry_count; ++i)
			{
				p_states[i].block_table_offset = block_table_cursor;
				block_table_cursor +=
					static_cast<kun_ktk uint64_t>(
						p_states[i].block_count
					) *
					sizeof(kun_ktk uint32_t);
			}
		}

		// [data] — per entry: align, then stream block-by-block
		for (kun_ktk size_t i = 0; i < entry_count; ++i)
		{
			kpack_write_entry_state_t& state = p_states[i];

			// align the entry's data span to 4 KB
			const kun_ktk int64_t position = _ftelli64(p_file);

			if (position < 0)
			{
				KOTEK_MESSAGE_ERROR(
					"kpack writer: failed to tell in {}",
					p_pack_file_path
				);
				goto cleanup;
			}

			const kun_ktk uint64_t alignment =
				KOTEK_DEF_FILESYSTEM_PACK_DATA_ALIGNMENT;
			const kun_ktk uint64_t padding =
				(alignment -
		         (static_cast<kun_ktk uint64_t>(position) % alignment)) %
				alignment;

			if (padding > 0)
			{
				kun_ktk uint8_t zero_page[4096] = {};
				if (fwrite(
						zero_page, 1, static_cast<size_t>(padding),
						p_file
					) != static_cast<size_t>(padding))
				{
					KOTEK_MESSAGE_ERROR(
						"kpack writer: failed to align entry {}'s data "
						"in {}",
						i, p_pack_file_path
					);
					goto cleanup;
				}
			}

			state.data_offset = static_cast<kun_ktk uint64_t>(position) +
				padding;

			// a 0-byte entry has no blocks and no data span
			for (kun_ktk uint32_t b = 0; b < state.block_count; ++b)
			{
				const kun_ktk uint64_t raw_left =
					state.raw_size -
					static_cast<kun_ktk uint64_t>(b) *
						KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;
				const size_t raw_block_size = static_cast<size_t>(
					raw_left < KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
						? raw_left
						: KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
				);

				const kun_ktk uint8_t* p_raw_block =
					p_entries[i].p_data +
					static_cast<kun_ktk size_t>(b) *
						KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE;

				const kun_ktk uint8_t* p_to_write = p_raw_block;
				size_t packed_block_size = raw_block_size;

				switch (state.compression)
				{
				case eKpackCompression::kStored:
				{
					// the block IS the raw span — no scratch
					break;
				}
				case eKpackCompression::kZstd:
				{
					const size_t compressed = ZSTD_compress(
						p_packed_scratch,
						KOTEK_DEF_FILESYSTEM_PACK_MAX_PACKED_BLOCK_SIZE,
						p_raw_block, raw_block_size, ZSTD_CLEVEL_DEFAULT
					);

					if (ZSTD_isError(compressed))
					{
						KOTEK_MESSAGE_ERROR(
							"kpack writer: zstd failed on entry '{}' "
							"block {} ({})",
							p_entries[i].p_name, b,
							ZSTD_getErrorName(compressed)
						);
						goto cleanup;
					}

					p_to_write = p_packed_scratch;
					packed_block_size = compressed;
					break;
				}
				case eKpackCompression::kZlib:
				{
					uLongf bound = static_cast<uLongf>(
						KOTEK_DEF_FILESYSTEM_PACK_MAX_PACKED_BLOCK_SIZE
					);

					const int zlib_status = compress2(
						p_packed_scratch, &bound, p_raw_block,
						static_cast<uLong>(raw_block_size),
						Z_DEFAULT_COMPRESSION
					);

					if (zlib_status != Z_OK)
					{
						KOTEK_MESSAGE_ERROR(
							"kpack writer: zlib failed on entry '{}' "
							"block {} (status {})",
							p_entries[i].p_name, b, zlib_status
						);
						goto cleanup;
					}

					p_to_write = p_packed_scratch;
					packed_block_size = static_cast<size_t>(bound);
					break;
				}
				default:
				{
					KOTEK_MESSAGE_ERROR(
						"kpack writer: entry '{}' has an unknown "
						"compression id",
						p_entries[i].p_name
					);
					goto cleanup;
				}
				}

				KOTEK_ASSERT(
					packed_block_size <=
						KOTEK_DEF_FILESYSTEM_PACK_MAX_PACKED_BLOCK_SIZE,
					"packed block size overflow"
				);

				if (fwrite(p_to_write, 1, packed_block_size, p_file) !=
				    packed_block_size)
				{
					KOTEK_MESSAGE_ERROR(
						"kpack writer: failed to write entry '{}' block "
						"{} of {}",
						p_entries[i].p_name, b, p_pack_file_path
					);
					goto cleanup;
				}

				*p_block_size_iter =
					static_cast<kun_ktk uint32_t>(packed_block_size);
				++p_block_size_iter;

				state.packed_size += packed_block_size;
			}
		}

		// patch the tables in place
		{
			if (_fseeki64(p_file, k_kpack_header_size, SEEK_SET) != 0)
			{
				KOTEK_MESSAGE_ERROR(
					"kpack writer: failed to seek back for the entry "
					"table of {}",
					p_pack_file_path
				);
				goto cleanup;
			}

			kun_ktk uint8_t record[k_kpack_entry_record_size];

			for (kun_ktk size_t i = 0; i < entry_count; ++i)
			{
				const kpack_write_entry_state_t& state = p_states[i];

				kpack_encode_u64(record + 0, state.name_hash);
				kpack_encode_u64(record + 8, state.data_offset);
				kpack_encode_u64(record + 16, state.raw_size);
				kpack_encode_u64(record + 24, state.packed_size);
				record[32] =
					static_cast<kun_ktk uint8_t>(state.compression);
				kpack_encode_u32(record + 33, state.block_count);
				kpack_encode_u64(record + 37, state.block_table_offset);

				if (fwrite(record, 1, sizeof(record), p_file) !=
				    sizeof(record))
				{
					KOTEK_MESSAGE_ERROR(
						"kpack writer: failed to patch the entry table "
						"of {}",
						p_pack_file_path
					);
					goto cleanup;
				}
			}

			// the block tables, entry order
			kun_ktk uint32_t* p_block_read = p_block_sizes;

			for (kun_ktk size_t i = 0; i < entry_count; ++i)
			{
				const kpack_write_entry_state_t& state = p_states[i];

				if (state.block_count == 0)
					continue;

				if (_fseeki64(
						p_file,
						static_cast<kun_ktk int64_t>(
							state.block_table_offset
						),
						SEEK_SET
					) != 0)
				{
					KOTEK_MESSAGE_ERROR(
						"kpack writer: failed to seek back for the "
						"block table of {}",
						p_pack_file_path
					);
					goto cleanup;
				}

				for (kun_ktk uint32_t b = 0; b < state.block_count; ++b)
				{
					kun_ktk uint8_t packed_size_bytes[4];
					kpack_encode_u32(packed_size_bytes, p_block_read[b]);

					if (fwrite(packed_size_bytes, 1, 4, p_file) != 4)
					{
						KOTEK_MESSAGE_ERROR(
							"kpack writer: failed to patch the block "
							"table of {}",
							p_pack_file_path
						);
						goto cleanup;
					}
				}

				p_block_read += state.block_count;
			}
		}
	}

	status = true;

cleanup:
	delete[] p_packed_scratch;
	delete[] p_states;
	delete[] p_block_sizes;

	fclose(p_file);

	if (status == false)
	{
		// a failed write leaves a partial file behind — remove it so a
		// later mount never trips over the debris (the reader would
		// reject it loudly anyway)
		remove(p_pack_file_path);
	}

	return status;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
