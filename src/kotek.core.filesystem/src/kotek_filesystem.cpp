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
	bool status = this->Is_Exists(path);

	if (status == false)
	{
		status = this->Create_Directory(path);
		KOTEK_ASSERT(
			status, "failed to create directory: {}", path
		);
	}
}
using sys_info_t = ktkResourceText<1024, 4096, false>;
using sys_info_small_t = ktkResourceText<1024, 2048, false>;

void ktkFileSystem::Initialize_FrameworkConfig()
{
	KOTEK_ASSERT(this->m_p_config, "must be initialized");

	if (this->m_p_config)
	{
		kun_ktk uint8_t buffer[1024];
		kun_ktk size_t buffer_size =
			sizeof(buffer) / sizeof(buffer[0]);

		kun_ktk uint8_t* p_temp = buffer;

		bool status = this->Is_Exists(
			this->m_root_path / kConfigFileNameSystemInfo
		);

		if (status)
		{
			status = this->Read_File(
				kConfigFileNameSystemInfo,
				p_temp,
				buffer_size,
				eFileSystemPriorityType::kNative
			);

			KOTEK_ASSERT(status, "failed to read file!");

			sys_info_t cfg;
			status = cfg.Create_FromMemory(p_temp, buffer_size);

			KOTEK_ASSERT(
				status, "failed to make json from string"
			);

			KOTEK_ASSERT(
				cfg.Is_KeyExist(kSysInfoFieldName_UserNamespace
			    ),
				"there's no field as: {}",
				kSysInfoFieldName_UserNamespace
			);

			if (cfg.Is_KeyExist(kSysInfoFieldName_UserNamespace
			    ))
			{
				const auto& user =
					cfg.Get(kSysInfoFieldName_UserNamespace);

				KOTEK_ASSERT(
					user.Is_KeyExist(
						kSysInfoFieldName_UserNamespace_EngineNamespace
					),
					"there's no field as: {}",
					kSysInfoFieldName_UserNamespace_EngineNamespace
				);

				if (user.Is_KeyExist(
						kSysInfoFieldName_UserNamespace_EngineNamespace
					))
				{
					const auto& engine = user.Get(
						kSysInfoFieldName_UserNamespace_EngineNamespace
					);

					if (engine.Is_KeyExist(
							kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks
						))
					{
						if (engine.Is_KeyExist(
								kSysInfoFieldName_UserNamespace_EngineNamespace_Name
							))
						{
							this->m_p_config->Set_UserLibrary_Name(
								engine.Get<ktk_cstring<
									KOTEK_DEF_USER_ENGINE_LIBRARY_NAME_LENGTH>>(
									kSysInfoFieldName_UserNamespace_EngineNamespace_Name
								)
							);
						}
						else
						{
							KOTEK_MESSAGE_WARNING(
								"can't obtain field: {}",
								kSysInfoFieldName_UserNamespace_EngineNamespace_Name
							);
						}

						const auto& callbacks = engine.Get(
							kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks
						);

						auto p_read_and_set_callback =
							[this](
								const decltype(callbacks
						        )& section,
								const char* p_field_name,
								eUserEngineLibraryCallbacks
									callback_id
							) -> void
						{
							if (section.Is_KeyExist(p_field_name
							    ))
							{
								const ktk_cstring<
									KOTEK_DEF_USER_ENGINE_LIBRARY_CALLBACK_NAME_LENGTH>&
									callback_name =
										section.Get<ktk_cstring<
											KOTEK_DEF_USER_ENGINE_LIBRARY_CALLBACK_NAME_LENGTH>>(
											p_field_name
										);

								this->m_p_config
									->Set_UserLibrary_CallbackName(
										callback_id,
										callback_name
									);
							}
							else
							{
								KOTEK_MESSAGE_WARNING(
									"can't obtain field: {}",
									p_field_name
								);
							}
						};

						p_read_and_set_callback(
							callbacks,
							kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Init,
							eUserEngineLibraryCallbacks::
								kGame_Init
						);

						p_read_and_set_callback(
							callbacks,
							kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Shutdown,
							eUserEngineLibraryCallbacks::
								kGame_Shutdown
						);

						p_read_and_set_callback(
							callbacks,
							kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Update,
							eUserEngineLibraryCallbacks::
								kGame_Update
						);

						p_read_and_set_callback(
							callbacks,
							kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Init_Render,
							eUserEngineLibraryCallbacks::
								kRender_Init
						);
					}
					else
					{
						KOTEK_MESSAGE_WARNING(
							"can't obtain field: {}",
							kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks
						);
					}
				}
			}
			else
			{
				KOTEK_MESSAGE_ERROR(
					"can't obtain field: {}",
					kSysInfoFieldName_UserNamespace
				);
			}

			if (cfg.Is_KeyExist(kSysInfoFieldName_CoreNamespace
			    ))
			{
				const auto& core =
					cfg.Get(kSysInfoFieldName_CoreNamespace);

				if (core.Is_KeyExist(
						kSysInfoFieldName_CoreNamespace_FileSystemPriorityList
					))
				{
					const kun_ktk json::array& arr = core.Get<
						kun_ktk json::array>(
						kSysInfoFieldName_CoreNamespace_FileSystemPriorityList
					);

					if (arr.empty())
					{
						KOTEK_MESSAGE_WARNING(
							"priority list is empty!"
						);
					}
					else
					{
						auto p_get_priority_type =
							[](const kun_ktk json::string& name
						    ) -> eFileSystemPriorityType
						{
							if (name.empty())
								return eFileSystemPriorityType::
									kAuto;

							if (name.size() >= 1 &&
							    tolower(name[0]) == 'n')
							{
								return eFileSystemPriorityType::
									kNative;
							}
							else if (name.size() >= 1 &&
							         tolower(name[0]) == 'z')
							{
								return eFileSystemPriorityType::
									kZlib;
							}

							return eFileSystemPriorityType::
								kAuto;
						};

						kun_ktk uint8_t priority_list
							[static_cast<kun_ktk uint8_t>(
								eFileSystemPriorityType::
									kEndOfEnum
							)];

						for (int i = 0; i < arr.size(); ++i)
						{
							if (i >=
							    static_cast<kun_ktk uint8_t>(
									eFileSystemPriorityType::
										kEndOfEnum
								))
							{
								KOTEK_MESSAGE_WARNING(
									"your field=[{}] has too "
									"many "
									"fields that system won't "
									"handle!",
									kSysInfoFieldName_CoreNamespace_FileSystemPriorityList
								);

								break;
							}

							const auto& value =
								arr[i].as_string();

							eFileSystemPriorityType casted =
								p_get_priority_type(value);

							KOTEK_ASSERT(
								casted !=
									eFileSystemPriorityType::
										kAuto,
								"failed to cast to "
								"eFileSystemPriorityType={}",
								value.c_str()
							);

							priority_list[i] =
								static_cast<kun_ktk uint8_t>(
									casted
								);
						}

						this->m_p_config->Set_FS_PriorityList(
							priority_list
						);
					}
				}
				else
				{
					KOTEK_MESSAGE_WARNING(
						"can't obtain field: {}",
						kSysInfoFieldName_CoreNamespace_FileSystemPriorityList
					);
				}

				if (core.Is_KeyExist(
						kSysInfoFieldName_CoreNamespace_FileSystemFeatures
					))
				{
					const kun_ktk json::array& features =
						core.Get<kun_ktk json::array>(
							kSysInfoFieldName_CoreNamespace_FileSystemFeatures
						);

					if (features.empty() == false)
					{
						kun_ktk uint16_t features_result = 0;

						auto p_cast_feature =
							[](const kun_ktk json::string& name
						    ) -> kun_ktk uint16_t
						{
							if (name.empty())
								return 0;

							if (name.size() >= 5 &&
							    tolower(name[0]) == 'v' &&
							    tolower(name[1]) == 'f' &&
							    tolower(name[2]) == 'm' &&
							    tolower(name[3]) == '_')
							{
								if (tolower(name[4]) == 'r')
								{
									return static_cast<
										kun_ktk uint16_t>(
										eFileSystemFeatureType::
											kVFMRead
									);
								}
								else if (tolower(name[4]) ==
								         'w')
								{
									return static_cast<
										kun_ktk uint16_t>(
										eFileSystemFeatureType::
											kVFMWrite
									);
								}
								else if (tolower(name[4]) ==
								         'c')
								{
									return static_cast<
										kun_ktk uint16_t>(
										eFileSystemFeatureType::
											kVFMCacheEnabled
									);
								}
							}
							else if (name.size() >= 5 &&
							         tolower(name[0]) == 'p' &&
							         tolower(name[1]) == 'r' &&
							         tolower(name[2]) == 'i' &&
							         tolower(name[3]) == 'o' &&
							         tolower(name[4]) == 'r')
							{
								return static_cast<
									kun_ktk uint16_t>(
									eFileSystemFeatureType::
										kEnablePriorityWhenFailedToOpenFile
								);
							}

							return 0;
						};

						for (int i = 0; i < features.size();
						     ++i)
						{
							if (i >=
							    _kEndOfEnum_eFileSystemFeatureType)
							{
								KOTEK_MESSAGE_WARNING(
									"your field={} has too "
									"many fields that system "
									"won't handle",
									kSysInfoFieldName_CoreNamespace_FileSystemFeatures
								);
								break;
							}

							const auto& value =
								features[i].as_string();

							kun_ktk uint16_t casted =
								p_cast_feature(value);

							features_result |= casted;
						}

						this->m_p_config->Set_FS_FeaturesFlag(
							features_result
						);
					}
				}
				else
				{
					KOTEK_MESSAGE_WARNING(
						"can't obtain field: {}",
						kSysInfoFieldName_CoreNamespace_FileSystemFeatures
					);
				}
			}
			else
			{
				KOTEK_MESSAGE_ERROR(
					"can't obtain field: {}",
					kSysInfoFieldName_CoreNamespace
				);
			}
		}
		else
		{
			this->Create_DefaultFrameworkConfig();
			this->Fill_FrameworkConfigDefaults();
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

	if (length_of_buffer == 0)
	{
		KOTEK_MESSAGE_WARNING(
			"you try to write no information to file: {} "
			"(buffer_size==0)",
			path_to_file
		);
		status = true;
		return status;
	}

	if (path_to_file.empty())
	{
		KOTEK_MESSAGE_WARNING(
			"you passed empty path to file can't processeed!"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

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
		else
		{
			KOTEK_ASSERT(p_fs_list, "must be initialized");
			KOTEK_ASSERT(
				p_fs_list[0] !=
					static_cast<kun_ktk uint8_t>(
						eFileSystemPriorityType::kAuto
					),
				"can't be, it means that your config is not "
				"initialized or data was corrupted because of "
				"let's "
				"say memory leaks or something"
			);
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
					status = this->m_fs_native.Read_File(
						this->m_root_path / path_to_file,
						p_buffer,
						length_of_buffer,
						features
					);

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
						KOTEK_ASSERT(false, "todo: implement");
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
	KOTEK_ASSERT(
		path_to_file.empty() == false,
		"you can't pass an empty path"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	bool status = false;

	if (path_to_file.empty())
	{
		KOTEK_MESSAGE_WARNING(
			"you passed empty path to file can't processed"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

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
		else
		{
			KOTEK_ASSERT(p_fs_list, "must be initialized");
			KOTEK_ASSERT(
				p_fs_list[0] !=
					static_cast<kun_ktk uint8_t>(
						eFileSystemPriorityType::kAuto
					),
				"can't be, it means that your config is not "
				"initialized or data was corrupted because of "
				"let's "
				"say memory leaks or something"
			);
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
					status = this->m_fs_native.Write_File(
						this->m_root_path / path_to_file,
						p_buffer,
						length_of_buffer,
						features
					);

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
						status = this->m_fs_native.Write_File(
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
					KOTEK_ASSERT(false, "todo: implement");

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
						KOTEK_ASSERT(false, "todo: implement");
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
						KOTEK_ASSERT(false, "todo: implement");
						/*status = this->m_fs_native.Read_File(
						    this->m_root_path / path_to_file,
						    p_buffer,
						    length_of_buffer,
						    features
						);*/

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

bool ktkFileSystem::Write_File(
	ktkFileHandleType handle,
	const kun_ktk uint8_t* p_buffer,
	kun_ktk size_t length_of_buffer,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto */
)
{
	KOTEK_ASSERT(
		handle != kInvalidFileHandleType, "invalid handle"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	bool status = false;

	if (handle == kInvalidFileHandleType)
	{
		KOTEK_MESSAGE_WARNING(
			"you passed invalid handle to file can't processed"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

	eFileSystemFeatureType features =
		static_cast<eFileSystemFeatureType>(
			this->m_p_config->Get_FS_FeaturesFlag()
		);

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
		else
		{
			KOTEK_ASSERT(p_fs_list, "must be initialized");
			KOTEK_ASSERT(
				p_fs_list[0] !=
					static_cast<kun_ktk uint8_t>(
						eFileSystemPriorityType::kAuto
					),
				"can't be, it means that your config is not "
				"initialized or data was corrupted because of "
				"let's "
				"say memory leaks or something"
			);
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
					status = this->m_fs_native.Write_File(
						handle, p_buffer, length_of_buffer
					);

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
						status = this->m_fs_native.Write_File(
							handle, p_buffer, length_of_buffer
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
					KOTEK_ASSERT(false, "todo: implement");

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
						KOTEK_ASSERT(false, "todo: implement");
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
						KOTEK_ASSERT(false, "todo: implement");
						/*status = this->m_fs_native.Read_File(
						    this->m_root_path / path_to_file,
						    p_buffer,
						    length_of_buffer,
						    features
						);*/

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
					"failed to obtain file using all file "
					"systems!"
				);

				if (!status)
				{
					KOTEK_MESSAGE_WARNING(
						"can't read file: because all file "
						"systems couldn't obtain it"
					);
				}
			}
			else
			{
				KOTEK_ASSERT(false, "failed to obtain file!");
				KOTEK_MESSAGE_WARNING(
					"can't read file: because all file "
					"systems couldn't obtain it"
				);
			}
		}
	}

	return status;
}

bool ktkFileSystem::Write_File(
	ktkFileHandleType handle,
	const char* p_buffer,
	kun_ktk size_t length_of_buffer,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto */
)
{
	return this->Write_File(
		handle,
		reinterpret_cast<const kun_ktk uint8_t*>(p_buffer),
		length_of_buffer,
		priority
	);
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
	ktk_filesystem_path& path,
	eFolderIndex index,
	bool is_relative
) const noexcept
{
	if (is_relative == false)
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
	eFolderIndex index,
	bool is_relative
) const noexcept
{
	if (is_relative == false)
	{
		path = this->m_root_path;
		path += "/";
	}

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

void ktkFileSystem::Create_DefaultFrameworkConfig()
{
	sys_info_t cfg;

	{
		// User
		{
			sys_info_small_t user_content;
			{
				sys_info_small_t engine_content;
				{
					engine_content.Write(
						kSysInfoFieldName_UserNamespace_EngineNamespace_Name,
						KOTEK_USE_GAME_OUTPUT_LIBRARY_NAME
					);
					{
						sys_info_small_t callbacks_content;
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
							callbacks_content.Get_Object()
						);
					}
				}

				user_content.Write(
					kSysInfoFieldName_UserNamespace_EngineNamespace,
					engine_content.Get_Object()
				);
			}

			cfg.Write(
				kSysInfoFieldName_UserNamespace,
				user_content.Get_Object()
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
				core_content.Get_Object()
			);
		}
	}

	char cfg_as_string[1024];
	kun_ktk uint16_t cfg_as_string_real_length = 0;
	bool status = cfg.Serialize_ToString(
		cfg_as_string, cfg_as_string_real_length
	);

	KOTEK_ASSERT(status, "failed to make json as string");

	if (status)
	{
		status = this->Write_File(
			kConfigFileNameSystemInfo,
			cfg_as_string,
			static_cast<kun_ktk size_t>(
				cfg_as_string_real_length
			),
			eFileSystemPriorityType::kNative
		);

		KOTEK_ASSERT(status, "failed to write json on disk!");
	}
}

void ktkFileSystem::Fill_FrameworkConfigDefaults()
{
	KOTEK_ASSERT(this->m_p_config, "must be initialized");

	if (this->m_p_config)
	{
		//	this->m_p_config->Set_FS_FeaturesFlag()

		kun_ktk uint16_t fs_features =
			static_cast<kun_ktk uint16_t>(
				eFileSystemFeatureType::kVFMRead
			);
		fs_features |= static_cast<kun_ktk uint16_t>(
			eFileSystemFeatureType::kVFMCacheEnabled
		);
		fs_features |= static_cast<kun_ktk uint16_t>(
			eFileSystemFeatureType::
				kEnablePriorityWhenFailedToOpenFile
		);

		this->m_p_config->Set_FS_FeaturesFlag(fs_features);

		kun_ktk uint8_t
			fs_priority_list[static_cast<kun_ktk uint8_t>(
				eFileSystemPriorityType::kEndOfEnum
			)];
		fs_priority_list[0] = static_cast<kun_ktk uint8_t>(
			eFileSystemPriorityType::kZlib
		);
		fs_priority_list[1] = static_cast<kun_ktk uint8_t>(
			eFileSystemPriorityType::kNative
		);
		this->m_p_config->Set_FS_PriorityList(fs_priority_list);

		this->m_p_config->Set_UserLibrary_Name(
			KOTEK_USE_GAME_OUTPUT_LIBRARY_NAME
		);

		this->m_p_config->Set_UserLibrary_CallbackName(
			eUserEngineLibraryCallbacks::kGame_Init,
			kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Init
		);
		this->m_p_config->Set_UserLibrary_CallbackName(
			eUserEngineLibraryCallbacks::kGame_Shutdown,
			kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Shutdown
		);
		this->m_p_config->Set_UserLibrary_CallbackName(
			eUserEngineLibraryCallbacks::kGame_Update,
			kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Update
		);
		this->m_p_config->Set_UserLibrary_CallbackName(
			eUserEngineLibraryCallbacks::kRender_Init,
			kSysInfoFieldName_UserNamespace_EngineNamespace_Callbacks_Init_Render
		);
	}
}

ktkFileHandleType ktkFileSystem::Open_File(
	const ktk_filesystem_path& path_to_file,
	eFileSystemPriorityType priority,
	eFileSystemStreamingType
		type /*= eFileSystemStreamingType::kReadOnly */
)
{
	ktkFileHandleType result = kInvalidFileHandleType;

	KOTEK_ASSERT(
		path_to_file.empty() == false,
		"you can't pass an empty path"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	bool status = false;

	if (path_to_file.empty())
	{
		KOTEK_MESSAGE_WARNING(
			"you passed empty path to file can't processed"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

	eFileSystemFeatureType features =
		static_cast<eFileSystemFeatureType>(
			this->m_p_config->Get_FS_FeaturesFlag()
		);

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
		else
		{
			KOTEK_ASSERT(p_fs_list, "must be initialized");
			KOTEK_ASSERT(
				p_fs_list[0] !=
					static_cast<kun_ktk uint8_t>(
						eFileSystemPriorityType::kAuto
					),
				"can't be, it means that your config is not "
				"initialized or data was corrupted because of "
				"let's "
				"say memory leaks or something"
			);
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
					status = this->m_fs_native.Open_File(
						path_to_file, type, features
					);

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
						status = this->m_fs_native.Open_File(
							path_to_file, type, features
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
					KOTEK_ASSERT(false, "todo: implement");

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
						KOTEK_ASSERT(false, "todo: implement");
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
						KOTEK_ASSERT(false, "todo: implement");
						/*status = this->m_fs_native.Read_File(
						    this->m_root_path / path_to_file,
						    p_buffer,
						    length_of_buffer,
						    features
						);*/

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
					result != kInvalidFileHandleType,
					"failed to obtain file {} using all file "
					"systems!",
					path_to_file
				);

				if (result == kInvalidFileHandleType)
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

	return result;
}

bool ktkFileSystem::Close_File(
	ktkFileHandleType handle, eFileSystemPriorityType priority
)
{
	KOTEK_ASSERT(
		handle != kInvalidFileHandleType, "invalid handle"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	bool status = false;

	if (handle == kInvalidFileHandleType)
	{
		KOTEK_MESSAGE_WARNING(
			"you passed invalid handle to file can't processed"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

	eFileSystemFeatureType features =
		static_cast<eFileSystemFeatureType>(
			this->m_p_config->Get_FS_FeaturesFlag()
		);

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
		else
		{
			KOTEK_ASSERT(p_fs_list, "must be initialized");
			KOTEK_ASSERT(
				p_fs_list[0] !=
					static_cast<kun_ktk uint8_t>(
						eFileSystemPriorityType::kAuto
					),
				"can't be, it means that your config is not "
				"initialized or data was corrupted because of "
				"let's "
				"say memory leaks or something"
			);
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
					status =
						this->m_fs_native.Close_File(handle);

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
						status =
							this->m_fs_native.Close_File(handle
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
					KOTEK_ASSERT(false, "todo: implement");

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
						KOTEK_ASSERT(false, "todo: implement");
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
						KOTEK_ASSERT(false, "todo: implement");
						/*status = this->m_fs_native.Read_File(
						    this->m_root_path / path_to_file,
						    p_buffer,
						    length_of_buffer,
						    features
						);*/

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
					"failed to obtain file using all file "
					"systems!"
				);

				if (!status)
				{
					KOTEK_MESSAGE_WARNING(
						"can't read file: because all file "
						"systems couldn't obtain it"
					);
				}
			}
			else
			{
				KOTEK_ASSERT(false, "failed to obtain file!");
				KOTEK_MESSAGE_WARNING(
					"can't read file: because all file "
					"systems couldn't obtain it"
				);
			}
		}
	}

	return status;
}

bool ktkFileSystem::Get_FileSize(
	ktkFileHandleType handle,
	kun_ktk size_t& result,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto */
)
{
	KOTEK_ASSERT(
		handle != kInvalidFileHandleType, "invalid handle"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	bool status = false;

	if (handle == kInvalidFileHandleType)
	{
		KOTEK_MESSAGE_WARNING(
			"you passed invalid handle to file can't processed"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

	eFileSystemFeatureType features =
		static_cast<eFileSystemFeatureType>(
			this->m_p_config->Get_FS_FeaturesFlag()
		);

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
		else
		{
			KOTEK_ASSERT(p_fs_list, "must be initialized");
			KOTEK_ASSERT(
				p_fs_list[0] !=
					static_cast<kun_ktk uint8_t>(
						eFileSystemPriorityType::kAuto
					),
				"can't be, it means that your config is not "
				"initialized or data was corrupted because of "
				"let's "
				"say memory leaks or something"
			);
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
					status = this->m_fs_native.Get_FileSize(
						handle, result
					);

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
						status = this->m_fs_native.Get_FileSize(
							handle, result
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
					KOTEK_ASSERT(false, "todo: implement");

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
						KOTEK_ASSERT(false, "todo: implement");
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
						KOTEK_ASSERT(false, "todo: implement");
						/*status = this->m_fs_native.Read_File(
						    this->m_root_path / path_to_file,
						    p_buffer,
						    length_of_buffer,
						    features
						);*/

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
					status, "failed to obtain file size "
				);

				if (!status)
				{
					KOTEK_MESSAGE_WARNING("can't get file size"
					);
				}
			}
			else
			{
				KOTEK_ASSERT(false, "failed to obtain file!");
				KOTEK_MESSAGE_WARNING(
					"can't read file: because all file "
					"systems couldn't obtain it"
				);
			}
		}
	}

	return status;
}

bool ktkFileSystem::Seek(
	ktkFileHandleType handle,
	kun_ktk size_t offset,
	eFileSystemSeekType seek_type,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto */
)
{
	KOTEK_ASSERT(
		handle != kInvalidFileHandleType, "invalid handle"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	bool status = false;

	if (handle == kInvalidFileHandleType)
	{
		KOTEK_MESSAGE_WARNING(
			"you passed invalid handle to file can't processed"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

	eFileSystemFeatureType features =
		static_cast<eFileSystemFeatureType>(
			this->m_p_config->Get_FS_FeaturesFlag()
		);

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
		else
		{
			KOTEK_ASSERT(p_fs_list, "must be initialized");
			KOTEK_ASSERT(
				p_fs_list[0] !=
					static_cast<kun_ktk uint8_t>(
						eFileSystemPriorityType::kAuto
					),
				"can't be, it means that your config is not "
				"initialized or data was corrupted because of "
				"let's "
				"say memory leaks or something"
			);
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
					status = this->m_fs_native.Seek(
						handle, offset, seek_type
					);

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
						status = this->m_fs_native.Seek(
							handle, offset, seek_type
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
					KOTEK_ASSERT(false, "todo: implement");

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
						KOTEK_ASSERT(false, "todo: implement");
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
						KOTEK_ASSERT(false, "todo: implement");
						/*status = this->m_fs_native.Read_File(
						    this->m_root_path / path_to_file,
						    p_buffer,
						    length_of_buffer,
						    features
						);*/

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
					status, "failed to obtain file seek "
				);

				if (!status)
				{
					KOTEK_MESSAGE_WARNING("can't get file seek"
					);
				}
			}
			else
			{
				KOTEK_ASSERT(false, "failed to obtain file!");
				KOTEK_MESSAGE_WARNING(
					"can't read file: because all file "
					"systems couldn't obtain it"
				);
			}
		}
	}

	return status;
}

bool ktkFileSystem::Tell(
	ktkFileHandleType handle,
	kun_ktk size_t& result,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto */
)
{
	KOTEK_ASSERT(
		handle != kInvalidFileHandleType, "invalid handle"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	bool status = false;

	if (handle == kInvalidFileHandleType)
	{
		KOTEK_MESSAGE_WARNING(
			"you passed invalid handle to file can't processed"
		);
		return status;
	}

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

	eFileSystemFeatureType features =
		static_cast<eFileSystemFeatureType>(
			this->m_p_config->Get_FS_FeaturesFlag()
		);

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
		else
		{
			KOTEK_ASSERT(p_fs_list, "must be initialized");
			KOTEK_ASSERT(
				p_fs_list[0] !=
					static_cast<kun_ktk uint8_t>(
						eFileSystemPriorityType::kAuto
					),
				"can't be, it means that your config is not "
				"initialized or data was corrupted because of "
				"let's "
				"say memory leaks or something"
			);
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
					status =
						this->m_fs_native.Tell(handle, result);

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
						status = this->m_fs_native.Tell(
							handle, result
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
					KOTEK_ASSERT(false, "todo: implement");

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
						KOTEK_ASSERT(false, "todo: implement");
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
						KOTEK_ASSERT(false, "todo: implement");
						/*status = this->m_fs_native.Read_File(
						    this->m_root_path / path_to_file,
						    p_buffer,
						    length_of_buffer,
						    features
						);*/

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
					status, "failed to obtain file tell "
				);

				if (!status)
				{
					KOTEK_MESSAGE_WARNING("can't get file tell"
					);
				}
			}
			else
			{
				KOTEK_ASSERT(false, "failed to obtain file!");
				KOTEK_MESSAGE_WARNING(
					"can't read file: because all file "
					"systems couldn't obtain it"
				);
			}
		}
	}

	return status;
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

void ktkFileSystem::Shutdown(void)
{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
	this->m_fs_native.Shutdown();
#endif

#ifdef KOTEK_USE_FILESYSTEM_TYPE_ZLIB
	this->m_fs_zlib.Shutdown();
#endif

#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	this->m_vfm.Shutdown();
#endif
}

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

bool ktkFileSystem::Is_Exists(
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

	if (this->Is_Exists(path) == true)
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
