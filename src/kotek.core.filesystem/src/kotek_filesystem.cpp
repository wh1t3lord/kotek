#include "../include/kotek_filesystem.h"
#include <kotek.core.constants/include/kotek_core_constants.h>


KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkFileSystem::ktkFileSystem(void) : m_p_config{} {}

ktkFileSystem::~ktkFileSystem(void) {}

/*
ktkFileHandleType ktkFileSystem::Begin_Stream(
    const ktk_filesystem_path& path_to_file,
    size_t
        stream_step / *= KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE*
/
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

void ktkFileSystem::Initialize_FrameworkConfig()
{
	KOTEK_ASSERT(this->m_p_config, "must be initialized");

	if (this->m_p_config)
	{
		kun_ktk uint8_t buffer[1024];
		kun_ktk size_t buffer_size =
			sizeof(buffer) / sizeof(buffer[0]);

		kun_ktk uint8_t* p_temp = buffer;

		bool status = this->Read_File(
			kConfigFileNameSystemInfo,
			p_temp,
			buffer_size,
			eFileSystemPriorityType::kNative
		);

		KOTEK_ASSERT(status, "failed to read file!");

		using sys_info_t = ktkResourceText<1024, 4096, false>;

		if (status)
		{
			sys_info_t cfg;
			cfg.Create_FromMemory(p_temp, buffer_size);

			cfg.Get(kSysInfoFieldName_UserNamespace);
		}
		else
		{
			sys_info_t cfg;

			{
				// User
				{
					sys_info_t user_content;
					{
						sys_info_t engine_content;
						{
							engine_content.Write(
								kSysInfoFieldName_UserNamespace_EngineNamespace_Name,
								KOTEK_USE_GAME_OUTPUT_LIBRARY_NAME
							);
							{
								sys_info_t callbacks_content;
								{
									callbacks_content.Write(
										kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Init,
										kUserCallbackName_Initialize
									);
									callbacks_content.Write(
										kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Shutdown,
										kUserCallbackName_Shutdown
									);
									callbacks_content.Write(
										kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Update,
										kUserCallbackName_Update
									);
									callbacks_content.Write(
										kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Init_Render,
										kUserCallbackName_Initialize_Render
									);
								}

								engine_content.Write(
									kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks,
									callbacks_content.Get_JSON()
								);
							}
						}

						user_content.Write(
							kSysInfoFieldName_UserNamespace_EngineNamespace,
							engine_content.Get_JSON()
						);
					}

					cfg.Write(
						kSysInfoFieldName_UserNamespace,
						user_content.Get_JSON()
					);
				}

				// core
				{
					sys_info_t core_content;
					{
						unsigned char pl_mem[256];
						ktk::json::static_resource pl{pl_mem};

						ktk::json::array fs_priority_list(&pl);

						fs_priority_list.emplace_back(
							kSysInfoFieldName_CoreNamespace_FileSystemPriorityList_Native
						);

						fs_priority_list.emplace_back(
							kSysInfoFieldName_CoreNamespace_FileSystemPriorityList_ZLIB
						);

						core_content.Write(
							kSysInfoFieldName_CoreNamespace_FileSystemPriorityList,
							fs_priority_list
						);
					}

					{
						// todo: provide own wrapper with
						// template argument that will define
						// dynamic or static initialization of
						// json related fundamental types
						unsigned char f_mem[256];
						ktk::json::static_resource feat{f_mem};

						ktk::json::array fs_features(&feat);

						fs_features.emplace_back(
							kSysInfoFieldName_CoreNamespace_FileSystemFeatures_VFMRead
						);
						fs_features.emplace_back(
							kSysInfoFieldName_CoreNamespace_FileSystemFeatures_PriorityList
						);
						fs_features.emplace_back(
							kSysInfoFieldName_CoreNamespace_FileSystemFeatures_VFMCache
						);

						core_content.Write(
							kSysInfoFieldName_CoreNamespace_FileSystemFeatures,
							fs_features
						);
					}

					cfg.Write(
						kSysInfoFieldName_CoreNamespace,
						core_content.Get_JSON()
					);
				}
			}

			char cfg_as_string[1024];
			bool status =
				cfg.Serialize_ToString(cfg_as_string);

			KOTEK_ASSERT(
				status, "failed to make json as string"
			);

			if (status)
			{
				status = this->Write_File(
					kConfigFileNameSystemInfo,
					cfg_as_string,
					sizeof(cfg_as_string) /
						sizeof(cfg_as_string[0]),
					eFileSystemPriorityType::kNative
				);

				KOTEK_ASSERT(
					status, "failed to write json on disk!"
				);
			}
		}
	}
}

bool ktkFileSystem::Read_File(
	const ktk_filesystem_path& path_to_file,
	char*& p_buffer,
	kun_ktk size_t& length_of_buffer,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto*/,
	eFileSystemFeatureType
		features /*= eFileSystemFeatureType::kNone */
)
{
	KOTEK_ASSERT(false, "implement");
	return false;
}

bool ktkFileSystem::Read_File(
	const ktk_filesystem_path& path_to_file,
	kun_ktk uint8_t*& p_buffer,
	kun_ktk size_t& length_of_buffer,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto*/,
	eFileSystemFeatureType
		features /*= eFileSystemFeatureType::kNone */
) noexcept
{
	KOTEK_ASSERT(
		path_to_file.empty() == false,
		"you can't pass empty path"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	bool status = false;

	if (path_to_file.empty())
	{
		KOTEK_MESSAGE_WARNING(
			"you passed empty path to file can't processeed!"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

	KOTEK_ASSERT(p_fs_list, "must be initialized");
	KOTEK_ASSERT(
		p_fs_list[0] !=
			static_cast<kun_ktk uint8_t>(
				eFileSystemPriorityType::kAuto
			),
		"can't be, it means that your config is not "
		"initialized or data was corrupted because of let's "
		"say memory leaks or something"
	);

	if (features == eFileSystemFeatureType::kNone)
	{
		features = static_cast<eFileSystemFeatureType>(
			this->m_p_config->Get_FS_FeaturesFlag()
		);
	}

	bool is_priority_list_enabled =
		(features &
	     eFileSystemFeatureType::
	         kEnablePriorityWhenFailedToOpenFile) ==
		eFileSystemFeatureType::
			kEnablePriorityWhenFailedToOpenFile;

	kun_ktk uint8_t specified_fs =
		static_cast<kun_ktk uint8_t>(priority);
	bool was_overloaded_fs_order = false;
	if (is_priority_list_enabled == false)
	{
		if (priority != eFileSystemPriorityType::kAuto)
		{
			p_fs_list = &specified_fs;
			was_overloaded_fs_order = true;
		}
	}

	if (p_fs_list)
	{
		kun_ktk uint8_t list_size = is_priority_list_enabled
			? this->m_p_config->Get_FS_PriorityListSize()
			: 1;
		KOTEK_ASSERT(
			list_size > 0,
			"you must specify at least 1 file system"
		);

		bool was_used_specified_fs = false;

		eFileSystemPriorityType
			repeat_fs[static_cast<kun_ktk uint8_t>(
				eFileSystemPriorityType::kEndOfEnum
			)];

		if (is_priority_list_enabled &&
		    priority != eFileSystemPriorityType::kAuto)
		{
			KOTEK_ASSERT(
				(sizeof(repeat_fs) / sizeof(repeat_fs[0])) <=
					list_size,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);
			std::exit(-1);
		}

		kun_ktk uint8_t repeat_fs_iter = 0;

		for (kun_ktk uint8_t i = 0; i < list_size; ++i)
		{
			if (status)
				break;

			eFileSystemPriorityType fs_type =
				static_cast<eFileSystemPriorityType>(
					p_fs_list[i]
				);

			switch (fs_type)
			{
			case eFileSystemPriorityType::kAuto:
			{
				KOTEK_ASSERT(false, "can't be!");

				// todo: make own exit function for break the
				// application
				std::exit(-1);

				break;
			}
			case eFileSystemPriorityType::kNative:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
				if (priority == fs_type)
				{
					// todo: implement please
					was_used_specified_fs = true;
				}
				else
				{
					if (was_overloaded_fs_order)
					{
						if (was_used_specified_fs == false)
						{
							repeat_fs[repeat_fs_iter] = fs_type;
							++repeat_fs_iter;
							continue;
						}
					}
					else
					{
						status = this->m_fs_native.Read_File(
							this->m_root_path / path_to_file,
							p_buffer,
							length_of_buffer,
							features
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kZlib:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_ZLIB
				if (priority == fs_type)
				{
					// todo: implement please

					was_used_specified_fs = true;
				}
				else
				{
					if (was_overloaded_fs_order)
					{
						if (was_used_specified_fs == false)
						{
							repeat_fs[repeat_fs_iter] = fs_type;
							++repeat_fs_iter;
							continue;
						}
					}
					else
					{
						// todo: implement please
						KOTEK_ASSERT(false, "implement this");
					}
				}
#endif

				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "something is broken, can't be!"
				);
				std::exit(-1);
				break;
			}
			}
		}

		if (!status && is_priority_list_enabled)
		{
			if (priority != eFileSystemPriorityType::kAuto)
			{
				for (kun_ktk uint8_t i = 0; i < repeat_fs_iter;
				     ++i)
				{
					if (status)
					{
						break;
					}

					eFileSystemPriorityType fs_type =
						repeat_fs[i];

					switch (fs_type)
					{
					case eFileSystemPriorityType::kAuto:
					{
						KOTEK_ASSERT(false, "can't be!");
						std::exit(-1);
						break;
					}
					case eFileSystemPriorityType::kNative:
					{
						status = this->m_fs_native.Read_File(
							this->m_root_path / path_to_file,
							p_buffer,
							length_of_buffer,
							features
						);

						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						KOTEK_ASSERT(false, "not implemented");
						// todo: implement this please
						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						std::exit(-1);

						break;
					}
					}
				}

				KOTEK_ASSERT(
					status,
					"failed to obtain file {} using all file "
					"systems!",
					path_to_file
				);

				if (!status)
				{
					KOTEK_MESSAGE_WARNING(
						"can't read file: {} because all file "
						"systems couldn't obtain it",
						path_to_file
					);
				}
			}
			else
			{
				KOTEK_ASSERT(false, "failed to obtain file!");
				KOTEK_MESSAGE_WARNING(
					"can't read file: {} because all file "
					"systems couldn't obtain it",
					path_to_file
				);
			}
		}
	}

	return status;
}

bool ktkFileSystem::Read_File(
	const ktk_filesystem_path& path_to_file,
	kun_ktk ustring& output_result,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto*/,
	eFileSystemFeatureType
		feature /*= eFileSystemFeatureType::kNone */
) const noexcept
{
	KOTEK_ASSERT(false, "implement");
	return false;
}

bool ktkFileSystem::Write_File(
	const ktk_filesystem_path& path_to_file,
	kun_ktk ustring& input,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto*/,
	eFileSystemFeatureType
		feature /*= eFileSystemFeatureType::kNone */
) noexcept
{
	KOTEK_ASSERT(false, "implement");

	return false;
}

bool ktkFileSystem::Write_File(
	const ktk_filesystem_path& path_to_file,
	const kun_ktk uint8_t* p_buffer,
	kun_ktk size_t length_of_buffer,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto*/,
	eFileSystemFeatureType
		featurs /*= eFileSystemFeatureType::kNone */
) noexcept
{
	return false;
}

bool ktkFileSystem::Write_File(
	const ktk_filesystem_path& path_to_file,
	const char* p_buffer,
	kun_ktk size_t length_of_buffer,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto*/,
	eFileSystemFeatureType
		features /*= eFileSystemFeatureType::kNone */
) noexcept
{
	return false;
}

ktkFileHandleType ktkFileSystem::Begin_Stream(
	const ktk_filesystem_path& path_to_file,
	kun_ktk uint32_t override_stream_reading_length /*= 0*/,
	bool force_be_called_from_one_thread_only /*= false*/,
	eFileSystemStreamingType
		streaming_type /*= eFileSystemStreamingType::kAuto*/,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto*/,
	eFileSystemFeatureType
		features /*= eFileSystemFeatureType::kNone */
) noexcept
{
	KOTEK_ASSERT(false, "implement");
	return kInvalidFileHandleType;
}

bool ktkFileSystem::Write_Stream(
	ktkFileHandleType file_handle, kun_ktk ustring& input
) noexcept
{
	KOTEK_ASSERT(false, "implement");
	return false;
}

bool ktkFileSystem::Write_Stream(
	ktkFileHandleType file_handle,
	const unsigned char* p_buffer,
	kun_ktk size_t override_write_streaming_length /*= 0 */
) noexcept
{
	KOTEK_ASSERT(false, "implement");
	return false;
}

bool ktkFileSystem::Read_Stream(
	ktkFileHandleType file_handle,
	unsigned char* p_buffer,
	kun_ktk size_t& length_of_streaming_buffer
) noexcept
{
	KOTEK_ASSERT(false, "implement");
	return false;
}

kun_ktk uint32_t
ktkFileSystem::Get_DefaultStreamingBufferLength(void
) const noexcept
{
	KOTEK_ASSERT(false, "implement");
	return 0;
}

kun_ktk uint32_t ktkFileSystem::Get_StreamingBufferLength(
	ktkFileHandleType file_handle
) const noexcept
{
	KOTEK_ASSERT(false, "implement");
	return 0;
}

kun_ktk size_t ktkFileSystem::Get_RemainingStreamsCount(
	ktkFileHandleType file_handle
) const noexcept
{
	KOTEK_ASSERT(false, "implement");
	return 0;
}

kun_ktk size_t ktkFileSystem::Get_TotalStreamsCount(
	ktkFileHandleType file_handle
) const noexcept
{
	KOTEK_ASSERT(false, "implement");
	return 0;
}

bool ktkFileSystem::End_Stream(ktkFileHandleType file_handle
) noexcept
{
	KOTEK_ASSERT(false, "implement");
	return 0;
}

void ktkFileSystem::Make_Path(
	ktk_filesystem_path& path, eFolderIndex index
) const noexcept
{
	path = this->m_root_path;

	switch (index)
	{
	case eFolderIndex::kFolderIndex_Root:
	{
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Configs:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Scripts:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Textures:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders_GLSL:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders_HLSL:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders_WEBGPU:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders_SPV:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Models:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Sounds:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Levels:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_AI:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_Tests:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_ShaderCache:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_SDK:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_SDK_Settings:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_SDK
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_SDK_Scenes:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_SDK
			);
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser:
	{
		path /= kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "unsupported folder index");
		break;
	}
	}
}

void ktkFileSystem::Make_Path(
	ktk_cstring<KOTEK_DEF_MAXIMUM_OS_PATH_LENGTH>& path,
	eFolderIndex index
) const noexcept
{
	path = this->m_root_path;
	path += "/";

	switch (index)
	{
	case eFolderIndex::kFolderIndex_Root:
	{
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Configs:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Scripts:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Textures:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders_GLSL:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders_HLSL:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders_WEBGPU:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Shaders_SPV:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame_Shaders
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Models:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Sounds:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_Levels:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataGame_AI:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataGame
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_Tests:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_ShaderCache:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_SDK:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_SDK_Settings:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_SDK
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser_SDK_Scenes:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(
				eFolderIndex::kFolderIndex_DataUser_SDK
			);
		path += kPathSeparator;
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	case eFolderIndex::kFolderIndex_DataUser:
	{
		path += kun_ktk kun_filesystem
			get_frameworks_folder_name_by_enum(index);
		break;
	}
	default:
	{
		KOTEK_ASSERT(false, "unsupported folder index");
		break;
	}
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

	this->m_p_config = p_config;

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

	this->Initialize_FrameworkConfig();

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

bool ktkFileSystem::Is_ValidPath(
	const ktk_filesystem_path& path, bool is_relative_path
) const noexcept
{
	KOTEK_ASSERT(
		this->m_root_path.empty() == false,
		"must be initialized, otherwise early calling"
	);

	ktk_filesystem_path temp = path;

	if (is_relative_path)
	{
		temp = this->m_root_path;
		temp /= path;
	}

	if (temp.empty())
	{
		KOTEK_MESSAGE_WARNING("you have passed an empty path");
		return false;
	}

	return kun_ktk kun_filesystem exists(temp);
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
