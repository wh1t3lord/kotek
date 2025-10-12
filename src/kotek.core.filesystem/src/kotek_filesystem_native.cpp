#include "../include/kotek_filesystem_native.h"
#include "../include/kotek_virtualfilemapper.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
ktkFileSystem_Native::ktkFileSystem_Native() :
	#ifdef KOTEK_DEBUG
	m_shutdown_was_called{},
	#endif

	m_default_stream_buffer_size{}
	#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	,
	m_p_vfm{}
	#endif
{
}

ktkFileSystem_Native::~ktkFileSystem_Native(void)
{
	#ifdef KOTEK_DEBUG
	KOTEK_ASSERT(
		this->m_shutdown_was_called,
		"you forgot to call shutdown for this manager"
	);
	#endif
}

bool ktkFileSystem_Native::Read_File(
	const ktk_filesystem_path& path,
	kun_ktk uint8_t*& p_buffer,
	kun_ktk size_t& length_of_buffer,
	eFileSystemFeatureType features
)
{
	bool status = false;

	KOTEK_ASSERT(
		path.empty() == false, "you can't pass empty path!"
	);

	if (path.empty())
	{
		KOTEK_MESSAGE_WARNING("you pass empty path!");
		return status;
	}

	bool is_vfm_cache_enabled =
		(features & eFileSystemFeatureType::kVFMCacheEnabled) ==
		eFileSystemFeatureType::kVFMCacheEnabled;

	bool is_vfm_read_enabled =
		(features & eFileSystemFeatureType::kVFMRead) ==
		eFileSystemFeatureType::kVFMRead;
	bool is_vfm_write_enabled =
		(features & eFileSystemFeatureType::kVFMWrite) ==
		eFileSystemFeatureType::kVFMWrite;

	bool is_vfm_enabled =
		is_vfm_read_enabled || is_vfm_write_enabled;

	KOTEK_ASSERT(
		is_vfm_cache_enabled ? is_vfm_enabled : true,
		"logic is broken, vfm must be enabled by passing "
		"kVFMRead or kVFMWrite (or both) otherwise you didn't "
		"enable vfm but enabled vfm cache it doesn't work like "
		"this!"
	);

	if (is_vfm_enabled)
	{
		if (is_vfm_cache_enabled)
		{
			// todo: implement this
			KOTEK_ASSERT(false, "implement this");
		}

		// todo: think about read and write operations... like
		// what if i enable write but not read or something ????
		// what are other variants of vfm usage?
	}
	else
	{
		// use traditional fopen/fwrite

		FILE* p_file = fopen(path.c_str(), "rb");

		KOTEK_ASSERT(
			p_file, "failed to fopen={}", GetLastError()
		);

		if (p_file)
		{
			auto status_fseek = fseek(p_file, 0, SEEK_END);
			KOTEK_ASSERT(status_fseek == 0, "fseek failed");

			auto file_size = ftell(p_file);
			status_fseek = fseek(p_file, 0, SEEK_SET);
			KOTEK_ASSERT(status_fseek == 0, "fseek failed");

			if (file_size <= length_of_buffer)
			{
				fread(p_buffer, file_size, 1, p_file);
				p_buffer[file_size] = '\0';
				KOTEK_ASSERT(
					ferror(p_file) == 0, "fread failed!"
				);
				length_of_buffer = file_size;

				status = true;
			}
			else
			{
				KOTEK_ASSERT(
					file_size <=
						sizeof(this->m_reserved_cache) /
							sizeof(this->m_reserved_cache[0]),
					"overflow, resize your cache or use "
					"another dynamic/streaming methods for "
					"loading this data"
				);

				if (file_size <=
				    sizeof(this->m_reserved_cache) /
				        sizeof(this->m_reserved_cache[0]))
				{
					fread(
						this->m_reserved_cache,
						file_size,
						1,
						p_file
					);

					KOTEK_ASSERT(
						ferror(p_file) == 0, "fread failed!"
					);

					this->m_reserved_cache[file_size] = '\0';
					length_of_buffer = file_size;
					p_buffer = this->m_reserved_cache;
				}
				else
				{
					p_buffer[0] = '\0';
				}
			}
		}

		fclose(p_file);
	}

	return status;
}

bool ktkFileSystem_Native::Write_File(
	const ktk_filesystem_path& path_to_file,
	const char* p_buffer,
	kun_ktk size_t length_of_buffer,
	eFileSystemFeatureType features
)
{
	bool status = false;

	KOTEK_ASSERT(
		path_to_file.empty() == false,
		"you can't pass empty path!"
	);

	if (path_to_file.empty())
	{
		KOTEK_MESSAGE_WARNING("you pass empty path!");
		return status;
	}

	FILE* p_file = fopen(path_to_file.c_str(), "w");

	KOTEK_ASSERT(p_file, "failed to fopen={}", GetLastError());

	if (p_file)
	{
		auto _status_written =
			fwrite(p_buffer, length_of_buffer, 1, p_file);

		if (_status_written == 1)
		{
			status = true;

	#ifdef KOTEK_DEBUG
			KOTEK_ASSERT(
				kun_ktk kun_filesystem exists(path_to_file),
				"file wasn't created! Check your previliges or "
				"are you able to write to file on disk?"
			);
	#endif
		}
	}

	fclose(p_file);

	return status;
}

#endif

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK