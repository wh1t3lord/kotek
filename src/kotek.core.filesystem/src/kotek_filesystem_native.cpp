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
	this->m_files.resize(
		KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT
	);
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

bool ktkFileSystem_Native::Read_File(
	ktkFileHandleType handle,
	kun_ktk uint8_t* p_buffer,
	kun_ktk size_t length_of_buffer
)
{
	bool result = false;
	KOTEK_ASSERT(
		handle != kInvalidFileHandleType, "invalid handle"
	);

	file_handle_t* p_handle =
		reinterpret_cast<file_handle_t*>(handle);

	KOTEK_ASSERT(p_handle->is_free == false, "invalid data");
	KOTEK_ASSERT(
		p_handle->stream_type !=
			eFileSystemStreamingType::kAuto,
		"invalid data"
	);

	KOTEK_ASSERT(
		p_handle->stream_type ==
				eFileSystemStreamingType::kReadOnly ||
			p_handle->stream_type ==
				eFileSystemStreamingType::kReadAndWrite,
		"invalid streaming type, it is only support writing "
		"operation so you can't use read!"
	);

	if (!(p_handle->stream_type ==
	          eFileSystemStreamingType::kReadOnly ||
	      p_handle->stream_type ==
	          eFileSystemStreamingType::kReadAndWrite))
	{
		return result;
	}

	if (std::holds_alternative<file_handle_no_vfm_t>(
			p_handle->desc
		))
	{
		const file_handle_no_vfm_t& data =
			std::get<file_handle_no_vfm_t>(p_handle->desc);

		fread(p_buffer, length_of_buffer, 1, data.p_file);
		result = true;
	}
	else
	{
		KOTEK_ASSERT(false, "not suppose to be implemented!");
	}

	return result;
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

bool ktkFileSystem_Native::Write_File(
	ktkFileHandleType handle,
	const kun_ktk uint8_t* p_buffer,
	kun_ktk size_t length_of_buffer
)
{
	bool result = false;
	KOTEK_ASSERT(
		handle != kInvalidFileHandleType, "invalid handle"
	);

	file_handle_t* p_handle =
		reinterpret_cast<file_handle_t*>(handle);

	KOTEK_ASSERT(p_handle->is_free == false, "invalid data");
	KOTEK_ASSERT(
		p_handle->stream_type !=
			eFileSystemStreamingType::kAuto,
		"invalid data"
	);
	KOTEK_ASSERT(
		p_handle->priority == eFileSystemPriorityType::kNative,
		"wrong data! you passed different handle to wrong "
		"filesystem"
	);

	KOTEK_ASSERT(
		p_handle->stream_type ==
				eFileSystemStreamingType::kWriteOnly ||
			p_handle->stream_type ==
				eFileSystemStreamingType::kReadAndWrite,
		"invalid streaming type, it is only support reading "
		"operation so you can't use write!"
	);

	if (!(p_handle->stream_type ==
	          eFileSystemStreamingType::kWriteOnly ||
	      p_handle->stream_type ==
	          eFileSystemStreamingType::kReadAndWrite))
	{
		return result;
	}

	if (std::holds_alternative<file_handle_no_vfm_t>(
			p_handle->desc
		))
	{
		const file_handle_no_vfm_t& data =
			std::get<file_handle_no_vfm_t>(p_handle->desc);

		auto _status_fwrite =
			fwrite(p_buffer, length_of_buffer, 1, data.p_file);

		KOTEK_ASSERT(
			_status_fwrite == 1,
			"failed fwrite={}",
			GetLastError()
		);

		result = _status_fwrite == 1;
	}
	else
	{
		KOTEK_ASSERT(false, "not suppose to be implemented!");
	}

	return result;
}

bool ktkFileSystem_Native::Write_File(
	ktkFileHandleType handle,
	const char* p_buffer,
	kun_ktk size_t length_of_buffer
)
{
	return this->Write_File(
		handle,
		reinterpret_cast<const kun_ktk uint8_t*>(p_buffer),
		length_of_buffer
	);
}

ktkFileHandleType ktkFileSystem_Native::Open_File(
	const ktk_filesystem_path& path_to_file,
	eFileSystemStreamingType stream_type,
	eFileSystemFeatureType features
)
{
	ktkFileHandleType result;

	KOTEK_ASSERT(
		path_to_file.empty() == false, "you passed empty file!"
	);

	this->Get_FreeHandle(result);

	if (result == kInvalidFileHandleType)
	{
		KOTEK_MESSAGE_ERROR(
			"failed to obtain handle for file: {}", path_to_file
		);

		return result;
	}

	file_handle_t* p_handle =
		reinterpret_cast<file_handle_t*>(result);

	KOTEK_ASSERT(
		p_handle->is_free == false,
		"you must set this flag to false otherwise your logic "
		"is broken or memory corruption"
	);

	p_handle->stream_type = stream_type;

	KOTEK_ASSERT(
		kun_ktk kun_filesystem exists(path_to_file),
		"requested path is not valid and doesn't present on "
		"system! {}",
		path_to_file
	);

	if (kun_ktk kun_filesystem exists(path_to_file))
	{
		const char* p_open_type =
			this->Get_FOpenTypeByStreamingType(stream_type);

		KOTEK_ASSERT(
			p_open_type,
			"invalid streaming type: {}",
			static_cast<std::underlying_type_t<
				eFileSystemStreamingType>>(stream_type)
		);

		FILE* p_f = fopen(path_to_file.c_str(), p_open_type);

		KOTEK_ASSERT(p_f, "failed to fopen={}", GetLastError());

		file_handle_no_vfm_t desc;
		desc.p_file = p_f;
		p_handle->desc = desc;
	}
	else
	{
		p_handle->is_free = true;
		p_handle->stream_type = eFileSystemStreamingType::kAuto;
		result = kInvalidFileHandleType;
	}

	return result;
}

void ktkFileSystem_Native::Get_FreeHandle(
	ktkFileHandleType& result
)
{
	kun_ktk uint32_t j =
		KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT - 1;

	bool is_found = false;
	for (kun_ktk uint32_t i = 0;
	     i < KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT;
	     ++i, --j)
	{
		file_handle_t& left = this->m_files[i];
		file_handle_t& right = this->m_files[j];

		if (left.is_free)
		{
			left.is_free = false;

			result = reinterpret_cast<ktkFileHandleType>(&left);

			return;
		}

		if (right.is_free)
		{
			right.is_free = false;

			result =
				reinterpret_cast<ktkFileHandleType>(&right);

			return;
		}
	}

	if (is_found == false)
	{
		KOTEK_MESSAGE_ERROR(
			"there's no freed handle that can be allocated!"
		);
		result = kInvalidFileHandleType;
	}
}

const char* ktkFileSystem_Native::Get_FOpenTypeByStreamingType(
	eFileSystemStreamingType stream_type
)
{
	switch (stream_type)
	{
	case eFileSystemStreamingType::kReadOnly:
	{
		return "rb";
	}
	case eFileSystemStreamingType::kWriteOnly:
	{
		return "wb";
	}
	case eFileSystemStreamingType::kReadAndWrite:
	{
		return "r+b";
	}
	default:
	{
		return nullptr;
	}
	}
}

bool ktkFileSystem_Native::Close_File(ktkFileHandleType handle)
{
	bool result =false;
	KOTEK_ASSERT(
		handle != kInvalidFileHandleType,
		"you passed invalid file handle"
	);

	file_handle_t* p_handle =
		reinterpret_cast<file_handle_t*>(handle);

	KOTEK_ASSERT(p_handle->is_free == false, "invalid data");
	KOTEK_ASSERT(
		p_handle->stream_type !=
			eFileSystemStreamingType::kAuto,
		"invalid data"
	);

	if (std::holds_alternative<file_handle_no_vfm_t>(
			p_handle->desc
		))
	{
		file_handle_no_vfm_t& data =
			std::get<file_handle_no_vfm_t>(p_handle->desc);

		fclose(data.p_file);
		result = true;
	}
	else
	{
		KOTEK_ASSERT(false, "not supposed to be implemented");
	}

	return result;
}

bool ktkFileSystem_Native::Get_FileSize(
	ktkFileHandleType handle, kun_ktk size_t& result
)
{
	bool status = true;

	KOTEK_ASSERT(
		handle != kInvalidFileHandleType,
		"you passed invalid file handle"
	);

	file_handle_t* p_handle =
		reinterpret_cast<file_handle_t*>(handle);

	KOTEK_ASSERT(p_handle->is_free == false, "invalid data");
	KOTEK_ASSERT(
		p_handle->stream_type !=
			eFileSystemStreamingType::kAuto,
		"invalid data"
	);

	if (std::holds_alternative<file_handle_no_vfm_t>(
			p_handle->desc
		))
	{
		file_handle_no_vfm_t& data =
			std::get<file_handle_no_vfm_t>(p_handle->desc);

		auto cur = ftell(data.p_file);
		KOTEK_ASSERT(
			cur != -1L, "failed ftell={}", GetLastError()
		);
		status = cur != -1L;

		if (!status)
			return status;

		auto status_fseek = fseek(data.p_file, 0, SEEK_END);
		KOTEK_ASSERT(
			status_fseek == 0, "fseek failed={}", GetLastError()
		);
		status = status_fseek == 0;

		if (!status)
			return status;

		result = ftell(data.p_file);
		KOTEK_ASSERT(
			result != -1L, "failed ftell={}", GetLastError()
		);
		status = result != -1L;
		if (!status)
			return status;

		status_fseek = fseek(data.p_file, cur, SEEK_SET);
		KOTEK_ASSERT(
			status_fseek == 0, "fseek failed={}", GetLastError()
		);

		status = status_fseek == 0;
		if (!status)
			return status;
	}
	else
	{
		KOTEK_ASSERT(false, "not supposed to be implemented");
	}

	return status;
}

bool ktkFileSystem_Native::Seek(
	ktkFileHandleType handle,
	kun_ktk size_t offset,
	eFileSystemSeekType seek_type
)
{
	bool status = true;

	KOTEK_ASSERT(
		handle != kInvalidFileHandleType,
		"you passed invalid file handle"
	);

	file_handle_t* p_handle =
		reinterpret_cast<file_handle_t*>(handle);

	KOTEK_ASSERT(p_handle->is_free == false, "invalid data");
	KOTEK_ASSERT(
		p_handle->stream_type !=
			eFileSystemStreamingType::kAuto,
		"invalid data"
	);

	if (std::holds_alternative<file_handle_no_vfm_t>(
			p_handle->desc
		))
	{
		file_handle_no_vfm_t& data =
			std::get<file_handle_no_vfm_t>(p_handle->desc);

		int _seek_type = SEEK_SET;

		switch (seek_type)
		{
		case eFileSystemSeekType::kBegin:
		{
			break;
		}
		case eFileSystemSeekType::kCurrent:
		{
			_seek_type = SEEK_CUR;
			break;
		}
		case eFileSystemSeekType::kEnd:
		{
			_seek_type = SEEK_END;
			break;
		}
		default:
		{
			KOTEK_ASSERT(false, "undefined");
			break;
		}
		}

		auto status_fseek =
			fseek(data.p_file, offset, _seek_type);
		status = status_fseek == 0;
		KOTEK_ASSERT(status, "failed fseek={}", GetLastError());
	}
	else
	{
		KOTEK_ASSERT(false, "not supposed to be implemented");
	}

	return status;
}

bool ktkFileSystem_Native::Tell(ktkFileHandleType handle, kun_ktk size_t& result) 
{
	bool status = true;

	KOTEK_ASSERT(
		handle != kInvalidFileHandleType,
		"you passed invalid file handle"
	);

	file_handle_t* p_handle =
		reinterpret_cast<file_handle_t*>(handle);

	KOTEK_ASSERT(p_handle->is_free == false, "invalid data");
	KOTEK_ASSERT(
		p_handle->stream_type !=
			eFileSystemStreamingType::kAuto,
		"invalid data"
	);

	if (std::holds_alternative<file_handle_no_vfm_t>(
			p_handle->desc
		))
	{
		file_handle_no_vfm_t& data =
			std::get<file_handle_no_vfm_t>(p_handle->desc);

		result = ftell(data.p_file);
		status = result != -1L;
		KOTEK_ASSERT(status, "failed ftell={}", GetLastError());
	}
	else
	{
		KOTEK_ASSERT(false, "not supposed to be implemented");
	}

	return status;
}

void ktkFileSystem_Native::Shutdown() 
{
	#ifdef KOTEK_DEBUG
	this->m_shutdown_was_called = true;
	#endif
}

#endif

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK