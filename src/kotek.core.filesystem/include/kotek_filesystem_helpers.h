#pragma once

#include <kotek.core.api/include/kotek_api.h>
#include <kotek.core.filesystem.file_text/include/kotek_core_filesystem_file_text.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// @brief \~english "API simplicity" free-function helpers over
/// ktkIFileSystem (the filesystem plan's "write less code" item, landed
/// after B0/B3 made the underlying contracts graceful). Every helper
/// composes the EXISTING ktkIFileSystem surface — backend-free, no new
/// virtuals, no friend access — so mounted packs, VFM-mapped reads and
/// the priority chain all apply unchanged, and the helpers stay
/// interface-pure for the PLUGIN linkage mode (header-only on purpose:
/// a .cpp inside the module would be a direct-call edge plugin
/// consumers cannot link).
///
/// Contracts are the underlying calls' B0/B3 contracts: user data (a
/// missing, unreadable, malformed or oversized file) is false + at most
/// one warning from the failing call, NEVER an assert. Caller errors
/// (a null filesystem, a null buffer/name) are programmer errors and
/// keep their KOTEK_ASSERT.
///
/// Silence rule: a helper reports one warning through the failing
/// underlying call. Call sites where absence is the NORMAL case (a
/// first-boot config, a scene without metadata, a not-yet-built shader
/// blob) keep their Is_Exists pre-check so even that one line is
/// suppressed — that is the documented B0 idiom, not a workaround.

/// @brief \~english read_json's one-shot/streaming fork is
/// KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE (a file at or under one stream
/// step takes the single-shot read, a bigger file goes through B3's
/// Begin/Read/End_Stream); this define is the hard bound on the json
/// TEXT the helpers accumulate/serialize, and the stack scratch both
/// helpers are built on. Sized from the ecosystem's real json texts:
/// game_config/sys_info <= 4 KB, scene metadata <= 2 KB (the 192 KB
/// locale files keep their own zircon-side loader) — 64 KB covers every
/// current consumer with an order of magnitude of headroom. A bigger
/// file is false + one warning (retriable: raise the bound or the
/// resource's parser buffer), never an assert.
#define KOTEK_DEF_FILESYSTEM_HELPERS_JSON_SCRATCH_SIZE 65536

/// @brief \~english single-shot read with the interface's in/out pair
/// split into an explicit capacity + an out-size. The B0 contract passes
/// through untouched: on success out_size is the real read size (a '\0'
/// terminator is written when the buffer has room); a missing or
/// unreadable file is false + out_size 0 + one warning; a too-small
/// buffer is false + the REQUIRED size in out_size — the caller's
/// pointer is never redirected to internal scratch.
inline bool read_file(
	ktkIFileSystem* p_filesystem,
	const ktk_filesystem_path& path_to_file,
	kun_ktk uint8_t* p_buffer,
	kun_ktk size_t buffer_capacity,
	kun_ktk size_t& out_size,
	eFileSystemPriorityType priority = eFileSystemPriorityType::kAuto,
	eFileSystemFeatureType features = eFileSystemFeatureType::kNone
) noexcept
{
	KOTEK_ASSERT(
		p_filesystem, "you must pass a valid filesystem instance!"
	);
	KOTEK_ASSERT(p_buffer, "you must pass a valid buffer!");

	if (!p_filesystem || !p_buffer)
	{
		out_size = 0;
		return false;
	}

	kun_ktk uint8_t* p_out = p_buffer;
	out_size = buffer_capacity;

	return p_filesystem->Read_File(
		path_to_file, p_out, out_size, priority, features
	);
}

/// @brief \~english reads a json text file into a ktkResourceText: the
/// size probe (Get_FileSize), the read and Create_FromMemory in one
/// call. Files at or under KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE take
/// the single-shot read; bigger files are read through B3's streaming
/// API (forward-only, bounded steps) into the same scratch, so the
/// bytes — and the resulting DOM — are identical on both paths.
/// missing = false + one warning (from the size probe); empty,
/// over-KOTEK_DEF_FILESYSTEM_HELPERS_JSON_SCRATCH_SIZE, over the
/// resource's own _ParserBufferSize (checked BEFORE Create_FromMemory,
/// whose assert never fires on user data) or malformed = false + one
/// warning, the resource left untouched. Note Create_FromMemory's own
/// contract stands past these checks: a syntactically valid json that
/// is not an object trips the resource class's is_object assert
/// (pre-existing ktkResourceText behavior, not user-data graceful).
template <
	kun_ktk uint32_t _ParserBufferSize,
	kun_ktk uint32_t _JsonMemorySize,
	bool _Realloc>
bool read_json(
	ktkIFileSystem* p_filesystem,
	const ktk_filesystem_path& path_to_file,
	ktkResourceText<_ParserBufferSize, _JsonMemorySize, _Realloc>&
		out_resource
) noexcept
{
	KOTEK_ASSERT(
		p_filesystem, "you must pass a valid filesystem instance!"
	);

	if (!p_filesystem)
		return false;

	kun_ktk size_t json_size = 0;

	// a missing file is false + the probe's one B0 warning — the
	// helper adds no noise of its own on the absent path
	if (p_filesystem->Get_FileSize(path_to_file, json_size) == false)
		return false;

	if (json_size == 0)
	{
		KOTEK_MESSAGE_WARNING(
			"read_json: '{}' is an empty file — nothing to parse",
			path_to_file
		);
		return false;
	}

	if (json_size > KOTEK_DEF_FILESYSTEM_HELPERS_JSON_SCRATCH_SIZE)
	{
		KOTEK_MESSAGE_WARNING(
			"read_json: '{}' is bigger than the helpers' json text "
			"bound ({} > {} bytes) — raise "
			"KOTEK_DEF_FILESYSTEM_HELPERS_JSON_SCRATCH_SIZE or use a "
			"dedicated loader",
			path_to_file, json_size,
			KOTEK_DEF_FILESYSTEM_HELPERS_JSON_SCRATCH_SIZE
		);
		return false;
	}

	if constexpr (!_Realloc)
	{
		// Create_FromMemory asserts size <= _ParserBufferSize on the
		// static-resource leg — an oversized FILE is user data, so the
		// check lives here where it degrades gracefully
		if (json_size > _ParserBufferSize)
		{
			KOTEK_MESSAGE_WARNING(
				"read_json: '{}' ({} bytes) does not fit the target "
				"resource's parser buffer ({} bytes) — raise its "
				"_ParserBufferSize",
				path_to_file, json_size, _ParserBufferSize
			);
			return false;
		}
	}

	unsigned char scratch[KOTEK_DEF_FILESYSTEM_HELPERS_JSON_SCRATCH_SIZE];

	kun_ktk size_t text_size = 0;

	if (json_size <= KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE)
	{
		unsigned char* p_scratch = scratch;
		text_size = sizeof(scratch);

		// one B0 warning on failure; a grow past the scratch since the
		// probe reports false + the required size, never an overrun
		if (p_filesystem->Read_File(path_to_file, p_scratch, text_size) ==
			false)
		{
			return false;
		}
	}
	else
	{
		// the B3 streaming path — the documented loop shape (the same
		// one the zircon resource manager's worker drives): a
		// forward-only cursor, bounded steps, End_Stream always safe
		ktkFileHandleType stream =
			p_filesystem->Begin_Stream(path_to_file);

		if (stream == kInvalidFileHandleType)
		{
			// Begin_Stream already logged its one warning
			return false;
		}

		bool is_stream_ok = true;

		while (p_filesystem->Get_RemainingStreamsCount(stream) > 0)
		{
			kun_ktk size_t chunk = sizeof(scratch) - text_size;

			if (p_filesystem->Read_Stream(
					stream, scratch + text_size, chunk
				) == false)
			{
				is_stream_ok = false;
				break;
			}

			text_size += chunk;
		}

		p_filesystem->End_Stream(stream);

		if (is_stream_ok == false || text_size == 0)
			return false;
	}

	if (out_resource.Create_FromMemory(scratch, text_size) == false)
	{
		KOTEK_MESSAGE_WARNING(
			"read_json: '{}' is not valid json — nothing loaded",
			path_to_file
		);
		return false;
	}

	return true;
}

/// @brief \~english serializes a ktkResourceText and writes it in one
/// Write_File call. The raw scratch array is forced by
/// ktkResourceText::Serialize_ToString's signature (char (&)[N], Size&)
/// — the same exemption the zircon call sites carry. A serialization
/// failure (the DOM's text form exceeds
/// KOTEK_DEF_FILESYSTEM_HELPERS_JSON_SCRATCH_SIZE — a caller-side
/// capacity error, the resource class's own assert pins it in debug) or
/// a failed write is false + one warning.
template <
	kun_ktk uint32_t _ParserBufferSize,
	kun_ktk uint32_t _JsonMemorySize,
	bool _Realloc>
bool write_json(
	ktkIFileSystem* p_filesystem,
	const ktk_filesystem_path& path_to_file,
	const ktkResourceText<_ParserBufferSize, _JsonMemorySize, _Realloc>&
		resource
) noexcept
{
	KOTEK_ASSERT(
		p_filesystem, "you must pass a valid filesystem instance!"
	);

	if (!p_filesystem)
		return false;

	char text[KOTEK_DEF_FILESYSTEM_HELPERS_JSON_SCRATCH_SIZE];
	kun_ktk size_t text_real_length = 0;

	if (resource.Serialize_ToString(text, text_real_length) == false)
	{
		KOTEK_MESSAGE_WARNING(
			"write_json: the resource failed to serialize — nothing "
			"written to '{}'",
			path_to_file
		);
		return false;
	}

	if (p_filesystem->Write_File(
			path_to_file, text, text_real_length
		) == false)
	{
		KOTEK_MESSAGE_WARNING(
			"write_json: failed to write '{}'", path_to_file
		);
		return false;
	}

	return true;
}

/// @brief \~english the path-shaped Get_FileSize, for call-site
/// symmetry with the rest of the helpers. The B0 contract passes
/// through: a present file is true + its size; a missing file is false
/// + out_size 0 + one warning from the underlying call.
inline bool file_size(
	ktkIFileSystem* p_filesystem,
	const ktk_filesystem_path& path_to_file,
	kun_ktk size_t& out_size,
	eFileSystemPriorityType priority = eFileSystemPriorityType::kAuto
) noexcept
{
	KOTEK_ASSERT(
		p_filesystem, "you must pass a valid filesystem instance!"
	);

	if (!p_filesystem)
	{
		out_size = 0;
		return false;
	}

	return p_filesystem->Get_FileSize(path_to_file, out_size, priority);
}

/// @brief \~english the Make_Path + '/=' two-step in one call: out_path
/// becomes <folder of index>/p_file_name (is_relative forwards to
/// Make_Path). False only on a caller error (null filesystem/name).
inline bool path_for(
	ktkIFileSystem* p_filesystem,
	eFolderIndex index,
	const char* p_file_name,
	ktk_filesystem_path& out_path,
	bool is_relative = false
) noexcept
{
	KOTEK_ASSERT(
		p_filesystem, "you must pass a valid filesystem instance!"
	);
	KOTEK_ASSERT(p_file_name, "you must pass a valid file name!");

	if (!p_filesystem || !p_file_name)
		return false;

	p_filesystem->Make_Path(out_path, index, is_relative);
	out_path /= p_file_name;

	return true;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
