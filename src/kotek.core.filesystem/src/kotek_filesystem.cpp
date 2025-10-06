#include "../include/kotek_filesystem.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkFileSystem::ktkFileSystem(void) {}

ktkFileSystem::~ktkFileSystem(void) {}

/*
ktkFileHandleType ktkFileSystem::Begin_Stream(
	const ktk_filesystem_path& path_to_file,
	size_t
		stream_step / *= KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE* /
)
{
	return ktkFileHandleType();
}
*/

/*
void ktkFileSystem::Stream(
	const ktkFileHandleType file_handle,
	kun_ktk uint8_t*& p_buffer,
	kun_ktk size_t buffer_size
)
{
}

void ktkFileSystem::End_Stream(
	const ktkFileHandleType file_handle
)
{
}*/

/*
bool ktkFileSystem::Is_AnyAvailableFiles(void) const noexcept
{
	return this->m_current_in_use_files.load() <
		this->m_files.size();
}*/

/*
ktkFileHandleType ktkFileSystem::Get_AvailableFile(void) const
{
	ktkFileHandleType result = kFileSystemInvalidFileHandleType;

	if (!this->Is_AnyAvailableFiles())
	{
		// trying linearly search but honestly we could optimize
		// it at some point (maybe)
		for (const ktkFileHandleImpl& file : this->m_files)
		{
			if (!file.is_in_use.load())
			{
				result =
					reinterpret_cast<ktkFileHandleType>(&file);
			}
		}
	}

	return result;
}*/

void ktkFileSystem::Validate_Folder(
	const ktk_filesystem_path& path
)
{
	bool status = this->Is_ValidPath(path);

	if (status == false)
	{
		status = this->Create_Directory(path);
		KOTEK_ASSERT(
			status, "failed to create directory: {}", path
		);
	}
}

void ktkFileSystem::Initialize_FrameworkConfig(
	ktkIFrameworkConfig* p_config
)
{
	if (p_config)
	{

	}
}

/*
bool ktkFileSystem::Read_File(
	const ktk_filesystem_path& path_to_file,
	char*& p_buffer,
	kun_ktk size_t& length_of_buffer
)
{
	KOTEK_ASSERT(p_buffer, "must be valid!");
	KOTEK_ASSERT(length_of_buffer > 0, "must be non zero!");
	KOTEK_ASSERT(
		path_to_file.empty() == false,
		"must be a non empty string"
	);

	bool result{};

	if (this->IsValidPath(path_to_file) == false)
	{
		KOTEK_MESSAGE_WARNING(
			"can't load file by following path: [{}]",
			reinterpret_cast<const char*>(
				path_to_file.u8string().c_str()
			)
		);
		return result;
	}

	kun_ktk ifstream file(path_to_file.c_str());

	if (file.good())
	{
		//	return_static_string_buffer.assign(
		//	kun_ktk istreambuf_iterator(file), kun_ktk
		// istreambuf_iterator());

		file.seekg(0, kun_ktk ios::end);

#ifdef KOTEK_DEBUG
		if (file.fail())
		{
			KOTEK_MESSAGE_WARNING(
				"failed .seekg(0, kun_ktk ios::end); for "
				"path: [{}] = reason {}",
				path_to_file,
				strerror(errno)
			);
		}
		else if (file.bad())
		{
			KOTEK_MESSAGE_ERROR(
				"fatal failed .seekg(0, kun_ktk ios::end); for "
				"path: [{}] = reason {}",
				path_to_file,
				strerror(errno)
			);
		}
#endif

		auto size_of_text = file.tellg();
#ifdef KOTEK_DEBUG
		if (file.fail())
		{
			KOTEK_MESSAGE_WARNING(
				"failed .tellg for path: [{}] = reason {}",
				path_to_file,
				strerror(errno)
			);
		}
		else if (file.bad())
		{
			KOTEK_MESSAGE_ERROR(
				"fatal failed .tellg for path: [{}] = reason "
				"{}",
				path_to_file,
				strerror(errno)
			);
		}
#endif

		file.seekg(0, kun_ktk ios::beg);

#ifdef KOTEK_DEBUG
		if (file.fail())
		{
			KOTEK_MESSAGE_WARNING(
				"failed .seekg(0, kun_ktk ios::beg); for "
				"path: [{}] = reason {}",
				path_to_file,
				strerror(errno)
			);
		}
		else if (file.bad())
		{
			KOTEK_MESSAGE_ERROR(
				"fatal fail .seekg(0, kun_ktk ios::beg); for "
				"path: [{}] = reason {}",
				path_to_file,
				strerror(errno)
			);
		}
#endif

		if (size_of_text <= length_of_buffer)
		{
			file.read(
				reinterpret_cast<char*>(p_buffer), size_of_text
			);

#ifdef KOTEK_DEBUG
			if (file.fail())
			{
				KOTEK_MESSAGE_WARNING(
					"failed "
					".read(this->m_reserved_buffer.begin(), "
					"size_of_text); for path: [{}] = reason {}",
					path_to_file,
					strerror(errno)
				);
			}
			else if (file.bad())
			{
				KOTEK_MESSAGE_ERROR(
					"fatal fail "
					".read(this->m_reserved_buffer.begin(), "
					"size_of_text); path: [{}] = reason {}",
					path_to_file,
					strerror(errno)
				);
			}
#endif

			if (!file.eof())
			{
				KOTEK_MESSAGE_ERROR(
					"fatal fail because we read whole file but "
					"state is not EOF! path: [{}]",
					path_to_file
				);
			}

			length_of_buffer = size_of_text;
			if (file || file.eof())
			{
				result = true;
			}
			else
			{
				KOTEK_MESSAGE_WARNING(
					"failed to read content of file {}",
					path_to_file
				);
				return result;
			}
		}
		else
		{
			KOTEK_ASSERT(
				size_of_text <=
					this->m_reserved_buffer.max_size(),
				"overflow the system can't handle a such huge "
				"file!"
			);
			this->m_reserved_buffer.clear();

			this->m_reserved_buffer.resize(size_of_text);
			file.read(
				this->m_reserved_buffer.begin(), size_of_text
			);
			length_of_buffer = size_of_text;
			p_buffer = this->m_reserved_buffer.begin();

#ifdef KOTEK_DEBUG
			if (file.fail())
			{
				KOTEK_MESSAGE_WARNING(
					"failed "
					".read(this->m_reserved_buffer.begin(), "
					"size_of_text); for path: [{}] = reason {}",
					path_to_file,
					strerror(errno)
				);
			}
			else if (file.bad())
			{
				KOTEK_MESSAGE_ERROR(
					"fatal fail "
					".read(this->m_reserved_buffer.begin(), "
					"size_of_text); path: [{}] = reason {}",
					path_to_file,
					strerror(errno)
				);
			}
#endif

			if (!file.eof())
			{
				KOTEK_MESSAGE_ERROR(
					"fatal fail because we read whole file but "
					"state is not EOF! path: [{}]",
					path_to_file
				);
			}

			if (file || file.eof())
			{
				result = true;
			}
			else
			{
				KOTEK_MESSAGE_WARNING(
					"failed to read content of file {}!",
					path_to_file
				);
				return result;
			}
		}
	}
	else
	{
		KOTEK_MESSAGE(
			"something is wrong while reading file: [{}]",
			reinterpret_cast<const char*>(
				path_to_file.u8string().c_str()
			)
		);
		return result;
	}

	return result;
}*/

void ktkFileSystem::Initialize(ktkIFrameworkConfig* p_config)
{
	KOTEK_ASSERT(
		p_config,
		"you must pass framework config for passing data from "
	    "sys_info.json"
	);

#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	KOTEK_ASSERT(
		kun_ktk kun_filesystem current_path().u8string().size(
		) <= KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH,
		"overflow current_path().size() > "
		"KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH({})",
		KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH
	);

#elif defined(KOTEK_USE_STD_LIBRARY_DYNAMIC_CONTAINERS) || \
	defined(KOTEK_USE_STD_LIBRARY_HYBRID_CONTAINERS)
#else
	#error unknown configuration, kotek supports only static, dynamic or hybrid containers and their implementations
#endif

	/*
	    KOTEK_MESSAGE("root path: [{}]",
	        this->m_storage_paths.at(eFolderIndex::kFolderIndex_Root).c_str());

	    bool is_valid_path =
	this->IsValidPath(this->m_storage_paths
	            .at(eFolderIndex::kFolderIndex_Root)
	#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
	            .c_str()
	#endif
	    );
	    KOTEK_ASSERT(is_valid_path, "your path must be valid!");

	    this->ValidateFolders();*/

	this->m_root_path =
		kun_ktk kun_filesystem current_path().u8string().c_str(
		);

	this->Validate_Folders();

	this->Initialize_FrameworkConfig(p_config);

	KOTEK_MESSAGE("filesystem is initialized!");
}

void ktkFileSystem::Shutdown(void) {}

/*
ktk_filesystem_path
ktkFileSystem::GetFolderByEnum(eFolderIndex id) const noexcept
{
	KOTEK_ASSERT(
		this->m_storage_paths.empty() == false,
		"can't be empty you must initialize filesystem!"
	);

	if (this->m_storage_paths.find(id) ==
	    this->m_storage_paths.end())
	{
		KOTEK_MESSAGE(
			"can't find path by id[{}]",
			static_cast<kun_ktk enum_base_t>(id)
		);
	}

	return this->m_storage_paths
		.at(id)
#ifdef KOTEK_USE_STD_LIBRARY_STATIC_CONTAINERS
		.c_str()
#endif
		;
}*/

bool ktkFileSystem::Is_ValidPath(const ktk_filesystem_path& path
) const noexcept
{
	if (path.empty())
	{
		KOTEK_MESSAGE_WARNING("you have passed an empty path");
		return false;
	}

	return kun_ktk filesystem::exists(path);
}

bool ktkFileSystem::Create_Directory(
	const ktk_filesystem_path& path
) const noexcept
{
	if (path.empty())
	{
		KOTEK_MESSAGE("path is empty");
		return false;
	}

	if (this->Is_ValidPath(path) == true)
	{
		KOTEK_MESSAGE("path is existed can't create folder");
		return false;
	}

	return kun_ktk filesystem::create_directory(path);
}
/*

bool ktkFileSystem::Read_File(
	const ktk_filesystem_path& path_to_file,
	kun_ktk ustring& result
) const noexcept
{
	bool status{};
	if (this->IsValidPath(path_to_file) == false)
	{
		KOTEK_MESSAGE_WARNING(
			"can't load file by following path: [{}]",
			reinterpret_cast<const char*>(
				path_to_file.u8string().c_str()
			)
		);
		return status;
	}

	kun_ktk ifstream file(path_to_file.c_str());

	if (file.good())
	{
		result.assign(
			kun_ktk istreambuf_iterator(file),
			kun_ktk istreambuf_iterator()
		);

		status = true;
	}
	else
	{
		KOTEK_MESSAGE(
			"something is wrong while reading file: [{}]",
			reinterpret_cast<const char*>(
				path_to_file.u8string().c_str()
			)
		);
		return status;
	}

	return status;
}

bool ktkFileSystem::Read_File(
	kun_ktk uint8_t*& p_buffer,
	size_t& length_of_buffer,
	const kun_ktk kun_filesystem
		static_path<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>&
			absolute_path_to_file
) noexcept
{
	KOTEK_ASSERT(p_buffer, "must be valid!");
	KOTEK_ASSERT(length_of_buffer > 0, "must be non zero!");
	KOTEK_ASSERT(
		absolute_path_to_file.empty() == false,
		"must be a non empty string"
	);

	bool result{};

	if (this->IsValidPath(absolute_path_to_file) == false)
	{
		KOTEK_MESSAGE_WARNING(
			"can't load file by following path: [{}]",
			reinterpret_cast<const char*>(
				absolute_path_to_file.u8string().c_str()
			)
		);
		return result;
	}

	kun_ktk ifstream file(absolute_path_to_file.c_str());

	if (file.good())
	{
		//	return_static_string_buffer.assign(
		//	kun_ktk istreambuf_iterator(file), kun_ktk
		// istreambuf_iterator());

		file.seekg(0, kun_ktk ios::end);
		auto size_of_text = file.tellg();
		file.seekg(0, kun_ktk ios::beg);

		if (size_of_text <= length_of_buffer)
		{
			file.read(
				reinterpret_cast<char*>(p_buffer), size_of_text
			);
			length_of_buffer = size_of_text;
			if (file)
			{
				result = true;
			}
			else
			{
				KOTEK_MESSAGE_WARNING(
					"failed to read content of file {}",
					absolute_path_to_file
				);
				return result;
			}
		}
		else
		{
			KOTEK_ASSERT(
				size_of_text <=
					this->m_reserved_buffer.max_size(),
				"overflow the system can't handle a such huge "
				"file!"
			);
			this->m_reserved_buffer.clear();

			this->m_reserved_buffer.resize(size_of_text);
			file.read(
				this->m_reserved_buffer.begin(), size_of_text
			);
			length_of_buffer = size_of_text;
			p_buffer = reinterpret_cast<kun_ktk uint8_t*>(
				this->m_reserved_buffer.begin()
			);
			if (file)
			{
				result = true;
			}
			else
			{
				KOTEK_MESSAGE_WARNING(
					"failed to read content of file {}!",
					absolute_path_to_file
				);
				return result;
			}
		}
	}
	else
	{
		KOTEK_MESSAGE(
			"something is wrong while reading file: [{}]",
			reinterpret_cast<const char*>(
				absolute_path_to_file.u8string().c_str()
			)
		);
		return result;
	}

	return result;
}*/

void ktkFileSystem::Create_Directory(
	const ktk_filesystem_path& path,
	Core::eFolderVisibilityType type
)
{
	KOTEK_ASSERT(
		path.empty() == false, "you can't pass an empty path"
	);

	bool status = this->Create_Directory(path);

	KOTEK_ASSERT(
		status, "failed to create directory: {}", path
	);
}

// TODO: parallel with task_group thing!
void ktkFileSystem::Validate_Folders(void) noexcept
{
	ktk_filesystem_path path_game =
		this->m_root_path /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);

	this->Validate_Folder(path_game);

	this->Validate_Folder(
		path_game /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Configs
			)
	);

	this->Validate_Folder(
		path_game /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Models
			)
	);

	this->Validate_Folder(
		path_game /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Textures
			)
	);

	ktk_filesystem_path path_shaders =
		path_game /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);

	this->Validate_Folder(path_shaders);

	this->Validate_Folder(
		path_game /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_AI
			)
	);

	this->Validate_Folder(
		path_game /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Levels
			)
	);

	this->Validate_Folder(
		path_shaders /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders_GLSL
			)
	);

	this->Validate_Folder(
		path_shaders /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders_HLSL
			)
	);

	this->Validate_Folder(
		path_shaders /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders_SPV
			)
	);

	this->Validate_Folder(
		path_shaders /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::
					kFolderIndex_DataGame_Shaders_WEBGPU
			)
	);

	ktk_filesystem_path user_path =
		this->m_root_path /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);

	this->Validate_Folder(user_path);

	this->Validate_Folder(
		user_path /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_ShaderCache
			)
	);

	ktk_filesystem_path sdk_path =
		user_path /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_SDK
			);

	this->Validate_Folder(sdk_path);

	this->Validate_Folder(
		sdk_path /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_SDK_Settings
			)
	);

	this->Validate_Folder(
		sdk_path /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_SDK_Scenes
			)
	);

#ifdef KOTEK_DEBUG
	this->Validate_Folder(
		user_path /
		kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_Tests
			)
	);
#endif
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
