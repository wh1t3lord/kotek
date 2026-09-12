#include "../include/kotek_filesystem.h"
#include <kotek.core.constants/include/kotek_core_constants.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkFileSystem::ktkFileSystem(void) : m_p_config{}
{
	this->m_fstream_pool.resize(
		KOTEK_DEF_FILESYSTEM_FSTREAM_POOL_SIZE
	);
}

ktkFileSystem::~ktkFileSystem(void) {}

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
							else if (name.size() >= 1 &&
							         tolower(name[0]) == 'p')
							{
								return eFileSystemPriorityType::
									kPack;
							}

							return eFileSystemPriorityType::
								kAuto;
						};

						// B2a: zero-initialized — the list contract is
						// dense + kAuto-terminated (the pre-fix
						// uninitialized tail could be counted as real
						// entries by the old Set_FS_PriorityList)
						kun_ktk uint8_t priority_list
							[static_cast<kun_ktk uint8_t>(
								eFileSystemPriorityType::
									kEndOfEnum
							)] = {};

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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return false;
			}
		}

		kun_ktk uint8_t repeat_fs_iter = 0;

		// B2a: every backend in the override chain is handed the CALLER's
		// capacity — a middle backend's failure residue (a miss writes
		// size 0, a too-small writes the required size) must not poison
		// the next backend's attempt
		const kun_ktk size_t caller_buffer_capacity = length_of_buffer;

		for (kun_ktk uint8_t i = 0; i < list_size; ++i)
		{
			if (status)
				break;

			length_of_buffer = caller_buffer_capacity;

			eFileSystemPriorityType fs_type =
				static_cast<eFileSystemPriorityType>(
					p_fs_list[i]
				);

			switch (fs_type)
			{
			case eFileSystemPriorityType::kAuto:
			{
				// a corrupt priority list is a logic error, but
				// library code never exits the process — fail the call
				KOTEK_ASSERT(false, "can't be!");
				return false;
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked for the packs
					eKpackReadResult pack_result =
						this->m_fs_pack.Read_File(
							path_to_file, p_buffer, length_of_buffer
						);

					if (pack_result == eKpackReadResult::kSuccess)
						status = true;

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
						eKpackReadResult pack_result =
							this->m_fs_pack.Read_File(
								path_to_file, p_buffer,
								length_of_buffer
							);

						if (pack_result == eKpackReadResult::kSuccess)
						{
							status = true;
						}
						else if (
							pack_result != eKpackReadResult::kNotFound)
						{
							// found but failed (too-small / corrupt):
							// the override chain falls through on
							// ABSENCE only — stop here so the failure
							// (the required size / the loud error) is
							// the answer
							return status;
						}
						// kNotFound: silent fallthrough to the next
						// backend
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
				return false;
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

					// same capacity hand-off rule as the main loop
					length_of_buffer = caller_buffer_capacity;

					eFileSystemPriorityType fs_type =
						repeat_fs[i];

					switch (fs_type)
					{
					case eFileSystemPriorityType::kAuto:
					{
						KOTEK_ASSERT(false, "can't be!");
						return false;
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
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
						eKpackReadResult pack_result =
							this->m_fs_pack.Read_File(
								path_to_file, p_buffer,
								length_of_buffer
							);

						if (pack_result == eKpackReadResult::kSuccess)
						{
							status = true;
						}
						else if (
							pack_result != eKpackReadResult::kNotFound)
						{
							// same absence-only fallthrough rule as the
							// main loop
							return status;
						}
#endif

						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return false;
					}
					}
				}

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
	const ktk_filesystem_path& path_to_file,
	const kun_ktk uint8_t* p_buffer,
	kun_ktk size_t length_of_buffer,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto*/,
	eFileSystemFeatureType
		featurs /*= eFileSystemFeatureType::kNone */
) noexcept
{
	return this->Write_File(
		path_to_file,
		reinterpret_cast<const char*>(p_buffer),
		length_of_buffer,
		priority,
		featurs
	);
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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return false;
			}
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
				// a corrupt priority list is a logic error, but
				// library code never exits the process — fail the call
				KOTEK_ASSERT(false, "can't be!");
				return false;
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
					// todo: implement the zlib backend (phase B2) —
					// degrade gracefully instead of aborting
					KOTEK_MESSAGE_WARNING(
						"zlib filesystem is not implemented, skipping"
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked the packs for an
					// operation they don't have in B2a (writes, the
					// handle API — packs are read-only and handle-less
					// until B3)
					KOTEK_MESSAGE_WARNING(
						"the pack filesystem does not support this "
						"operation, skipping"
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
					// chain case: SILENT skip — an override-chain
					// backend not answering an operation is the normal
					// flow, not an event
				}
#endif

				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "something is broken, can't be!"
				);
				return false;
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
						return false;
					}
					case eFileSystemPriorityType::kNative:
					{
						// todo: the repeat-fs retry is unreachable
						// today (was_overloaded_fs_order is mutually
						// exclusive with this loop's guard) — kept
						// for the phase-B2 priority-list rework
						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
						// packs don't offer this operation in B2a —
						// silent skip, the chain continues
						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return false;
					}
					}
				}

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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return false;
			}
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
				// a corrupt priority list is a logic error, but
				// library code never exits the process — fail the call
				KOTEK_ASSERT(false, "can't be!");
				return false;
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
					// todo: implement the zlib backend (phase B2) —
					// degrade gracefully instead of aborting
					KOTEK_MESSAGE_WARNING(
						"zlib filesystem is not implemented, skipping"
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked the packs for an
					// operation they don't have in B2a (writes, the
					// handle API — packs are read-only and handle-less
					// until B3)
					KOTEK_MESSAGE_WARNING(
						"the pack filesystem does not support this "
						"operation, skipping"
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
					// chain case: SILENT skip — an override-chain
					// backend not answering an operation is the normal
					// flow, not an event
				}
#endif

				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "something is broken, can't be!"
				);
				return false;
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
						return false;
					}
					case eFileSystemPriorityType::kNative:
					{
						// todo: the repeat-fs retry is unreachable
						// today (was_overloaded_fs_order is mutually
						// exclusive with this loop's guard) — kept
						// for the phase-B2 priority-list rework
						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
						// packs don't offer this operation in B2a —
						// silent skip, the chain continues
						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return false;
					}
					}
				}

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

ktkFileSystem::fstream_state_t* ktkFileSystem::Get_Stream(
	ktkFileHandleType file_handle
) noexcept
{
	if (this->m_fstream_pool.empty())
		return nullptr;

	const kun_ktk uintptr_t handle_value = file_handle;
	const kun_ktk uintptr_t begin_value =
		reinterpret_cast<kun_ktk uintptr_t>(
			this->m_fstream_pool.data()
		);
	const kun_ktk uintptr_t end_value =
		begin_value +
		this->m_fstream_pool.size() * sizeof(fstream_state_t);

	// foreign/garbage handles are never dereferenced: the handle must
	// point INSIDE the pool (the handle-as-pointer-into-pool ABI) and at
	// a live slot
	if (handle_value < begin_value || handle_value >= end_value)
		return nullptr;

	if ((handle_value - begin_value) % sizeof(fstream_state_t) != 0)
		return nullptr;

	fstream_state_t* p_state =
		reinterpret_cast<fstream_state_t*>(handle_value);

	if (p_state->is_free)
		return nullptr;

	return p_state;
}

const ktkFileSystem::fstream_state_t* ktkFileSystem::Get_Stream(
	ktkFileHandleType file_handle
) const noexcept
{
	return const_cast<ktkFileSystem*>(this)->Get_Stream(file_handle);
}

void ktkFileSystem::Release_Stream(fstream_state_t& state) noexcept
{
	if (state.p_file)
	{
		fclose(state.p_file);
		state.p_file = nullptr;
	}

#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	if (state.is_vfm)
	{
		// keeps the B1 map/unmap balance counters exact — a stream's
		// Begin map always pairs with its End unmap
		this->m_vfm.UnMapFile(state.vfm_mapping_id);
	}
#endif

	state.is_vfm = false;
	state.vfm_mapping_id = decltype(state.vfm_mapping_id)(-1);
	state.is_failed = false;
	state.check_thread = false;
	state.owner_thread_id = std::thread::id{};
	state.stream_type = eFileSystemStreamingType::kAuto;
	state.backend = eFileSystemPriorityType::kAuto;
	state.step_size = 0;
	state.total_size = 0;
	state.position = 0;
	state.next_block = 0;
	state.path.clear();
	state.is_free = true;
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
	KOTEK_ASSERT(
		path_to_file.empty() == false, "you can't pass empty path"
	);

	KOTEK_ASSERT(
		this->m_p_config,
		"you must initialize config before using filesystem!"
	);

	if (path_to_file.empty())
	{
		KOTEK_MESSAGE_WARNING("you passed empty path to file!");
		return kInvalidFileHandleType;
	}

	if (streaming_type == eFileSystemStreamingType::kAuto)
	{
		streaming_type = eFileSystemStreamingType::kReadOnly;
	}

	if (streaming_type == eFileSystemStreamingType::kReadAndWrite)
	{
		// documented out of scope for this phase
		KOTEK_MESSAGE_WARNING(
			"Begin_Stream: kReadAndWrite streams are not supported "
			"this phase: {}",
			path_to_file
		);
		return kInvalidFileHandleType;
	}

	if (streaming_type != eFileSystemStreamingType::kReadOnly &&
	    streaming_type != eFileSystemStreamingType::kWriteOnly)
	{
		KOTEK_MESSAGE_WARNING(
			"Begin_Stream: unknown streaming type {} for: {}",
			static_cast<std::underlying_type_t<
				eFileSystemStreamingType>>(streaming_type),
			path_to_file
		);
		return kInvalidFileHandleType;
	}

	// pool exhaustion is a budget violation (the cap is a named
	// define): loud error + invalid handle, never an assert
	fstream_state_t* p_free_state = nullptr;

	for (kun_ktk size_t i = 0; i < this->m_fstream_pool.size(); ++i)
	{
		if (this->m_fstream_pool[i].is_free)
		{
			p_free_state = &this->m_fstream_pool[i];
			break;
		}
	}

	if (p_free_state == nullptr)
	{
		KOTEK_MESSAGE_ERROR(
			"Begin_Stream: the stream pool ({}) is exhausted — "
			"End_Stream some streams or raise "
			"KOTEK_DEF_FILESYSTEM_FSTREAM_POOL_SIZE (file: {})",
			KOTEK_DEF_FILESYSTEM_FSTREAM_POOL_SIZE, path_to_file
		);
		return kInvalidFileHandleType;
	}

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
	if (streaming_type == eFileSystemStreamingType::kWriteOnly)
	{
		// append-only writes to a FRESH native file this phase (packs
		// are read-only — pack writes stay tool-side per B2b)
		const ktk_filesystem_path absolute_path =
			this->m_root_path / path_to_file;

		FILE* p_file = fopen(absolute_path.c_str(), "wb");

		if (p_file == nullptr)
		{
			// a missing directory / unwritable target is user data
			KOTEK_MESSAGE_WARNING(
				"Begin_Stream: failed to open file for write "
				"streaming: {} (GetLastError={})",
				absolute_path, GetLastError()
			);
			return kInvalidFileHandleType;
		}

		p_free_state->is_free = false;
		p_free_state->stream_type = streaming_type;
		p_free_state->backend = eFileSystemPriorityType::kNative;
		p_free_state->p_file = p_file;
		p_free_state->path = path_to_file;
		p_free_state->step_size =
			override_stream_reading_length != 0
			? override_stream_reading_length
			: KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE;
		p_free_state->check_thread =
			force_be_called_from_one_thread_only;

		if (force_be_called_from_one_thread_only)
			p_free_state->owner_thread_id =
				std::this_thread::get_id();

		return reinterpret_cast<ktkFileHandleType>(p_free_state);
	}
#else
	if (streaming_type == eFileSystemStreamingType::kWriteOnly)
	{
		KOTEK_MESSAGE_WARNING(
			"Begin_Stream: write streams need the native backend"
		);
		return kInvalidFileHandleType;
	}
#endif

	// read stream: resolve the backend ONCE through the override chain
	// (a stream can not migrate backends mid-flight)

	if (features == eFileSystemFeatureType::kNone)
	{
		features = static_cast<eFileSystemFeatureType>(
			this->m_p_config->Get_FS_FeaturesFlag()
		);
	}

	const bool is_priority_list_enabled =
		(features &
	     eFileSystemFeatureType::kEnablePriorityWhenFailedToOpenFile) ==
		eFileSystemFeatureType::kEnablePriorityWhenFailedToOpenFile;

	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();

	KOTEK_ASSERT(p_fs_list, "must be initialized");

	// the attempt order mirrors the Read_File dispatch semantics:
	// feature off -> the explicit backend (or the list's first); feature
	// on + kAuto -> the whole configured list; feature on + explicit ->
	// the explicit one first, then the rest of the list
	eFileSystemPriorityType
		attempts[static_cast<kun_ktk uint8_t>(
			eFileSystemPriorityType::kEndOfEnum
		)];
	kun_ktk uint8_t attempt_count = 0;

	if (is_priority_list_enabled == false)
	{
		attempts[0] = priority != eFileSystemPriorityType::kAuto
			? priority
			: static_cast<eFileSystemPriorityType>(p_fs_list[0]);
		attempt_count = 1;
	}
	else if (priority == eFileSystemPriorityType::kAuto)
	{
		attempt_count = this->m_p_config->Get_FS_PriorityListSize();

		constexpr kun_ktk uint8_t attempts_capacity =
			sizeof(attempts) / sizeof(attempts[0]);

		// a corrupt/over-long list is a logic error: clamp loud, never
		// walk past the array
		KOTEK_ASSERT(
			attempt_count <= attempts_capacity,
			"the configured FS priority list ({}) is bigger than the "
			"backend count ({})",
			attempt_count, attempts_capacity
		);

		if (attempt_count > attempts_capacity)
			attempt_count = attempts_capacity;

		for (kun_ktk uint8_t i = 0; i < attempt_count; ++i)
			attempts[i] =
				static_cast<eFileSystemPriorityType>(p_fs_list[i]);
	}
	else
	{
		attempts[0] = priority;
		attempt_count = 1;

		const kun_ktk uint8_t list_size =
			this->m_p_config->Get_FS_PriorityListSize();

		for (kun_ktk uint8_t i = 0; i < list_size; ++i)
		{
			const eFileSystemPriorityType entry =
				static_cast<eFileSystemPriorityType>(p_fs_list[i]);

			if (entry != priority &&
			    attempt_count < sizeof(attempts) / sizeof(attempts[0]))
			{
				attempts[attempt_count] = entry;
				++attempt_count;
			}
		}
	}

	eFileSystemPriorityType resolved_backend =
		eFileSystemPriorityType::kAuto;
	kun_ktk uint64_t resolved_size = 0;

	for (kun_ktk uint8_t i = 0; i < attempt_count; ++i)
	{
		switch (attempts[i])
		{
		case eFileSystemPriorityType::kNative:
		{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
			// a SILENT existence probe (Get_FileSize would log its own
			// warning on a miss — the single all-failed warning below
			// is the one warning a missing file gets)
			if (kun_ktk kun_filesystem exists(
					this->m_root_path / path_to_file
				))
			{
				resolved_backend = eFileSystemPriorityType::kNative;
			}
#endif
			break;
		}
		case eFileSystemPriorityType::kPack:
		{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
			kun_ktk size_t pack_size = 0;

			// kNotFound is the silent fallthrough (the override-chain
			// rule) — a pack entry answers with its raw size
			if (this->m_fs_pack.Get_FileSize(
					path_to_file, pack_size
				) == eKpackReadResult::kSuccess)
			{
				resolved_backend = eFileSystemPriorityType::kPack;
				resolved_size = pack_size;
			}
#endif
			break;
		}
		case eFileSystemPriorityType::kZlib:
		{
			// same graceful skip as the single-shot dispatch
			KOTEK_MESSAGE_WARNING(
				"zlib filesystem is not implemented, skipping"
			);
			break;
		}
		default:
		{
			// a corrupt priority list is a logic error, but library
			// code never exits the process — fail the call
			KOTEK_ASSERT(false, "can't be!");
			return kInvalidFileHandleType;
		}
		}

		if (resolved_backend != eFileSystemPriorityType::kAuto)
			break;
	}

	if (resolved_backend == eFileSystemPriorityType::kAuto)
	{
		// a missing file is user data, not a programmer error: invalid
		// handle + ONE warning, never an assert
		KOTEK_MESSAGE_WARNING(
			"can't begin stream on file: {} because all file systems "
			"couldn't obtain it",
			path_to_file
		);
		return kInvalidFileHandleType;
	}

	p_free_state->is_free = false;
	p_free_state->stream_type = streaming_type;
	p_free_state->backend = resolved_backend;
	p_free_state->path = path_to_file;
	p_free_state->total_size = resolved_size;
	p_free_state->step_size =
		resolved_backend == eFileSystemPriorityType::kPack
		? KOTEK_DEF_FILESYSTEM_PACK_BLOCK_SIZE
		: (override_stream_reading_length != 0
		       ? override_stream_reading_length
		       : KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE);
	p_free_state->check_thread =
		force_be_called_from_one_thread_only;

	if (force_be_called_from_one_thread_only)
		p_free_state->owner_thread_id = std::this_thread::get_id();

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
	if (resolved_backend == eFileSystemPriorityType::kNative)
	{
		const ktk_filesystem_path absolute_path =
			this->m_root_path / path_to_file;

		bool is_opened = false;

#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
		const bool is_vfm_read_enabled =
			(features & eFileSystemFeatureType::kVFMRead) ==
			eFileSystemFeatureType::kVFMRead;

		if (is_vfm_read_enabled)
		{
			kun_ktk uint32_t mapping_id =
				static_cast<kun_ktk uint32_t>(-1);
			kun_ktk size_t mapped_size = 0;

			const eVFMMapFileResult map_result =
				this->m_vfm.MapFileForRead(
					absolute_path, mapping_id, mapped_size
				);

			switch (map_result)
			{
			case eVFMMapFileResult::kSuccess:
			{
				// the stream holds the mapping for its lifetime:
				// chunked copies out of it per Read_Stream, unmap at
				// End_Stream (Begin's map balances End's unmap)
				p_free_state->is_vfm = true;
				p_free_state->vfm_mapping_id = mapping_id;
				p_free_state->total_size = mapped_size;
				is_opened = true;
				break;
			}
			case eVFMMapFileResult::kEmptyFile:
			{
				// a 0-byte file is a legal empty stream (0 steps)
				p_free_state->total_size = 0;
				is_opened = true;
				break;
			}
			case eVFMMapFileResult::kMissingFile:
			{
				// the file vanished between the probe and the map —
				// the VFM layer already emitted the single warning
				this->Release_Stream(*p_free_state);
				return kInvalidFileHandleType;
			}
			case eVFMMapFileResult::kMappingFailed:
			default:
			{
				// an existing file that failed to map degrades to the
				// CRT stream below (the VFM layer already warned)
				break;
			}
			}
		}
#endif

		if (is_opened == false)
		{
			FILE* p_file = fopen(absolute_path.c_str(), "rb");

			if (p_file)
			{
				auto status_fseek = fseek(p_file, 0, SEEK_END);
				KOTEK_ASSERT(status_fseek == 0, "fseek failed");

				const long file_size = ftell(p_file);

				status_fseek = fseek(p_file, 0, SEEK_SET);
				KOTEK_ASSERT(status_fseek == 0, "fseek failed");

				if (status_fseek == 0 && file_size >= 0)
				{
					p_free_state->p_file = p_file;
					p_free_state->total_size =
						static_cast<kun_ktk uint64_t>(file_size);
					is_opened = true;
				}
				else
				{
					fclose(p_file);
				}
			}

			if (is_opened == false)
			{
				// the probe said the file exists but the open failed
				// (permissions, a race) — user data, one warning
				KOTEK_MESSAGE_WARNING(
					"Begin_Stream: failed to open file for read "
					"streaming: {} (GetLastError={})",
					absolute_path, GetLastError()
				);
				this->Release_Stream(*p_free_state);
				return kInvalidFileHandleType;
			}
		}
	}
#endif

	return reinterpret_cast<ktkFileHandleType>(p_free_state);
}

bool ktkFileSystem::Write_Stream(
	ktkFileHandleType file_handle, kun_ktk ustring& input
) noexcept
{
	return this->Write_Stream(
		file_handle,
		reinterpret_cast<const unsigned char*>(input.data()),
		input.size()
	);
}

bool ktkFileSystem::Write_Stream(
	ktkFileHandleType file_handle,
	const unsigned char* p_buffer,
	kun_ktk size_t override_write_streaming_length /*= 0 */
) noexcept
{
	KOTEK_ASSERT(p_buffer, "you passed a null buffer");

	fstream_state_t* p_state = this->Get_Stream(file_handle);

	KOTEK_ASSERT(
		p_state,
		"you passed an invalid stream handle to Write_Stream"
	);

	if (p_state == nullptr || p_buffer == nullptr)
		return false;

	if (p_state->check_thread)
	{
		KOTEK_ASSERT(
			p_state->owner_thread_id == std::this_thread::get_id(),
			"this stream must be driven from its creating thread only"
		);
	}

	if (p_state->stream_type != eFileSystemStreamingType::kWriteOnly)
	{
		KOTEK_MESSAGE_WARNING(
			"Write_Stream on a non-write stream: {}",
			p_state->path
		);
		return false;
	}

	// a poisoned stream stays failed until End_Stream (the loud error
	// already fired at the point of failure)
	if (p_state->is_failed)
		return false;

	const kun_ktk size_t write_count =
		override_write_streaming_length != 0
		? override_write_streaming_length
		: p_state->step_size;

	if (write_count == 0)
		return true;

	// append-only sequential write — the forward cursor never seeks
	const size_t was_written =
		fwrite(p_buffer, 1, write_count, p_state->p_file);

	if (was_written != write_count)
	{
		p_state->is_failed = true;

		KOTEK_MESSAGE_ERROR(
			"Write_Stream: short write on {} ({} of {} bytes, "
			"GetLastError={}) — the stream is poisoned until "
			"End_Stream",
			p_state->path, was_written, write_count, GetLastError()
		);
		return false;
	}

	p_state->position += write_count;
	p_state->total_size = p_state->position;

	return true;
}

bool ktkFileSystem::Read_Stream(
	ktkFileHandleType file_handle,
	unsigned char* p_buffer,
	kun_ktk size_t& length_of_streaming_buffer
) noexcept
{
	KOTEK_ASSERT(p_buffer, "you passed a null buffer");

	fstream_state_t* p_state = this->Get_Stream(file_handle);

	KOTEK_ASSERT(
		p_state, "you passed an invalid stream handle to Read_Stream"
	);

	if (p_state == nullptr || p_buffer == nullptr)
	{
		length_of_streaming_buffer = 0;
		return false;
	}

	if (p_state->check_thread)
	{
		KOTEK_ASSERT(
			p_state->owner_thread_id == std::this_thread::get_id(),
			"this stream must be driven from its creating thread only"
		);
	}

	if (p_state->stream_type != eFileSystemStreamingType::kReadOnly)
	{
		KOTEK_MESSAGE_WARNING(
			"Read_Stream on a non-read stream: {}", p_state->path
		);
		length_of_streaming_buffer = 0;
		return false;
	}

	// a poisoned stream stays failed until End_Stream — loudly ONCE at
	// the point of failure, silently false afterwards
	if (p_state->is_failed)
	{
		length_of_streaming_buffer = 0;
		return false;
	}

	// a drained stream is not an error: true + 0 bytes
	if (p_state->position >= p_state->total_size)
	{
		length_of_streaming_buffer = 0;
		return true;
	}

	const kun_ktk uint64_t remaining =
		p_state->total_size - p_state->position;

	kun_ktk size_t chunk = p_state->step_size;

	if (remaining < chunk)
		chunk = static_cast<kun_ktk size_t>(remaining);

	if (length_of_streaming_buffer < chunk)
	{
		// a step is ATOMIC (a pack step is one whole compression
		// block) — the caller's buffer must fit the stream's step; this
		// is a caller error, the cursor does not advance
		KOTEK_MESSAGE_WARNING(
			"Read_Stream: the buffer ({} bytes) is too small for the "
			"stream's step ({} bytes) on {} — size it by "
			"Get_StreamingBufferLength",
			length_of_streaming_buffer, chunk, p_state->path
		);
		length_of_streaming_buffer = 0;
		return false;
	}

	switch (p_state->backend)
	{
	case eFileSystemPriorityType::kNative:
	{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
		if (p_state->is_vfm)
		{
			// the mapped stream's step is a chunked copy out of the
			// live mapping (B1's copy is the reference)
			const kun_ktk uint8_t* p_mapped =
				static_cast<const kun_ktk uint8_t*>(
					this->m_vfm.Get_MappedData(
						p_state->vfm_mapping_id
					)
				);

			if (p_mapped == nullptr)
			{
				p_state->is_failed = true;

				KOTEK_MESSAGE_ERROR(
					"Read_Stream: the mapping of {} is gone — the "
					"stream is poisoned until End_Stream",
					p_state->path
				);
				length_of_streaming_buffer = 0;
				return false;
			}

			std::memcpy(
				p_buffer,
				p_mapped + p_state->position,
				chunk
			);

			p_state->position += chunk;
			length_of_streaming_buffer = chunk;
			return true;
		}
#endif

		// the CRT step: one sequential fread at the forward cursor —
		// no seeks, the disk head stays in the sweep
		const size_t was_read =
			fread(p_buffer, 1, chunk, p_state->p_file);

		if (was_read != chunk)
		{
			p_state->is_failed = true;

			KOTEK_MESSAGE_ERROR(
				"Read_Stream: short read on {} ({} of {} bytes) — "
				"the stream is poisoned until End_Stream",
				p_state->path, was_read, chunk
			);
			length_of_streaming_buffer = 0;
			return false;
		}

		p_state->position += chunk;
		length_of_streaming_buffer = chunk;
		return true;
#else
		length_of_streaming_buffer = 0;
		return false;
#endif
	}
	case eFileSystemPriorityType::kPack:
	{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
		kun_ktk size_t block_out = length_of_streaming_buffer;

		// the stream step IS the entry's 64 KB compression block —
		// sequential block indices only (forward-only, one outstanding
		// read); the entry's blocks are contiguous on disk
		const eKpackReadResult block_status =
			this->m_fs_pack.Read_File_Block(
				p_state->path, p_state->next_block, p_buffer, block_out
			);

		if (block_status != eKpackReadResult::kSuccess)
		{
			// the pack layer already reported the detail loudly — a
			// corrupt block fails the stream ONCE and poisons it until
			// End_Stream
			p_state->is_failed = true;

			KOTEK_MESSAGE_ERROR(
				"Read_Stream: block {} of {} failed — the stream is "
				"poisoned until End_Stream",
				p_state->next_block, p_state->path
			);
			length_of_streaming_buffer = 0;
			return false;
		}

		++p_state->next_block;
		p_state->position += block_out;
		length_of_streaming_buffer = block_out;
		return true;
#else
		length_of_streaming_buffer = 0;
		return false;
#endif
	}
	default:
	{
		KOTEK_ASSERT(false, "corrupt stream state");
		length_of_streaming_buffer = 0;
		return false;
	}
	}
}

kun_ktk uint32_t
ktkFileSystem::Get_DefaultStreamingBufferLength(void
) const noexcept
{
	return KOTEK_DEF_FILESYSTEM_STREAM_STEP_SIZE;
}

kun_ktk uint32_t ktkFileSystem::Get_StreamingBufferLength(
	ktkFileHandleType file_handle
) const noexcept
{
	const fstream_state_t* p_state = this->Get_Stream(file_handle);

	if (p_state == nullptr)
		return 0;

	return p_state->step_size;
}

kun_ktk size_t ktkFileSystem::Get_RemainingStreamsCount(
	ktkFileHandleType file_handle
) const noexcept
{
	const fstream_state_t* p_state = this->Get_Stream(file_handle);

	if (p_state == nullptr ||
	    p_state->stream_type != eFileSystemStreamingType::kReadOnly ||
	    p_state->step_size == 0)
		return 0;

	if (p_state->position >= p_state->total_size)
		return 0;

	const kun_ktk uint64_t remaining =
		p_state->total_size - p_state->position;

	return static_cast<kun_ktk size_t>(
		(remaining + p_state->step_size - 1) / p_state->step_size
	);
}

kun_ktk size_t ktkFileSystem::Get_TotalStreamsCount(
	ktkFileHandleType file_handle
) const noexcept
{
	const fstream_state_t* p_state = this->Get_Stream(file_handle);

	if (p_state == nullptr ||
	    p_state->stream_type != eFileSystemStreamingType::kReadOnly ||
	    p_state->step_size == 0)
		return 0;

	return static_cast<kun_ktk size_t>(
		(p_state->total_size + p_state->step_size - 1) /
		p_state->step_size
	);
}

bool ktkFileSystem::End_Stream(ktkFileHandleType file_handle
) noexcept
{
	fstream_state_t* p_state = this->Get_Stream(file_handle);

	// always safe: ending an invalid/already-ended stream is a quiet
	// no-op (idempotent cleanup), never an assert
	if (p_state == nullptr)
		return false;

	this->Release_Stream(*p_state);

	return true;
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
		path = this->m_root_path.c_str();
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

				// B2a: native-only default (the zlib archive backend was
				// never implemented; packs join at runtime when
				// data_game/packs exists)
				fs_priority_list.emplace_back(
					kSysInfoFieldName_CoreNamespace_FileSystemPriorityList_Native
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
		kun_ktk uint16_t fs_features =
			static_cast<kun_ktk uint16_t>(
				eFileSystemFeatureType::kVFMRead
			);
		// 2026-07-23: do NOT enable kVFMCacheEnabled by default — the cache
		// is not implemented and asserts in kotek_filesystem_native.cpp
		fs_features |= static_cast<kun_ktk uint16_t>(
			eFileSystemFeatureType::
				kEnablePriorityWhenFailedToOpenFile
		);

		this->m_p_config->Set_FS_FeaturesFlag(fs_features);

		// B2a: the built-in default (only used when sys_info.json is
		// absent) is native-only — the zlib archive backend was never
		// implemented, and with the fixed Set_FS_PriorityList sentinel a
		// listed kZlib would now ACTUALLY be consulted (skip-warnings on
		// every miss); packs join the effective list at runtime when
		// data_game/packs exists (Mount_Packs_From_Conventional_Folder).
		// Zero-initialized: the list contract is dense + kAuto-terminated.
		kun_ktk uint8_t
			fs_priority_list[static_cast<kun_ktk uint8_t>(
				eFileSystemPriorityType::kEndOfEnum
			)] = {};
		fs_priority_list[0] = static_cast<kun_ktk uint8_t>(
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

	if (path_to_file.empty())
	{
		KOTEK_MESSAGE_WARNING(
			"you passed empty path to file can't processed"
		);
		return result;
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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return result;
			}
		}

		kun_ktk uint8_t repeat_fs_iter = 0;

		for (kun_ktk uint8_t i = 0; i < list_size; ++i)
		{
			if (result != kInvalidFileHandleType)
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
				return result;
			}
			case eFileSystemPriorityType::kNative:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
				if (priority == fs_type)
				{
					result = this->m_fs_native.Open_File(
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
						result = this->m_fs_native.Open_File(
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
					// todo: implement the zlib backend (phase B2) —
					// degrade gracefully instead of aborting
					KOTEK_MESSAGE_WARNING(
						"zlib filesystem is not implemented, skipping"
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked the packs for an
					// operation they don't have in B2a (writes, the
					// handle API — packs are read-only and handle-less
					// until B3)
					KOTEK_MESSAGE_WARNING(
						"the pack filesystem does not support this "
						"operation, skipping"
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
					// chain case: SILENT skip — an override-chain
					// backend not answering an operation is the normal
					// flow, not an event
				}
#endif

				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "something is broken, can't be!"
				);
				return result;
			}
			}
		}

		if (result == kInvalidFileHandleType &&
		    is_priority_list_enabled)
		{
			if (priority != eFileSystemPriorityType::kAuto)
			{
				for (kun_ktk uint8_t i = 0; i < repeat_fs_iter;
				     ++i)
				{
					if (result != kInvalidFileHandleType)
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
						return result;
					}
					case eFileSystemPriorityType::kNative:
					{
						result = this->m_fs_native.Open_File(
							path_to_file, type, features
						);

						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
						// packs don't offer this operation in B2a —
						// silent skip, the chain continues
						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return result;
					}
					}
				}

				if (result == kInvalidFileHandleType)
				{
					KOTEK_MESSAGE_WARNING(
						"can't open file: {} because all file "
						"systems couldn't obtain it",
						path_to_file
					);
				}
			}
			else
			{
				KOTEK_MESSAGE_WARNING(
					"can't open file: {} because all file "
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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return false;
			}
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
				// a corrupt priority list is a logic error, but
				// library code never exits the process — fail the call
				KOTEK_ASSERT(false, "can't be!");
				return false;
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
					// todo: implement the zlib backend (phase B2) —
					// degrade gracefully instead of aborting
					KOTEK_MESSAGE_WARNING(
						"zlib filesystem is not implemented, skipping"
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked the packs for an
					// operation they don't have in B2a (writes, the
					// handle API — packs are read-only and handle-less
					// until B3)
					KOTEK_MESSAGE_WARNING(
						"the pack filesystem does not support this "
						"operation, skipping"
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
					// chain case: SILENT skip — an override-chain
					// backend not answering an operation is the normal
					// flow, not an event
				}
#endif

				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "something is broken, can't be!"
				);
				return false;
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
						return false;
					}
					case eFileSystemPriorityType::kNative:
					{
						// todo: the repeat-fs retry is unreachable
						// today (was_overloaded_fs_order is mutually
						// exclusive with this loop's guard) — kept
						// for the phase-B2 priority-list rework
						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
						// packs don't offer this operation in B2a —
						// silent skip, the chain continues
						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return false;
					}
					}
				}

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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return false;
			}
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
				// a corrupt priority list is a logic error, but
				// library code never exits the process — fail the call
				KOTEK_ASSERT(false, "can't be!");
				return false;
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
					// todo: implement the zlib backend (phase B2) —
					// degrade gracefully instead of aborting
					KOTEK_MESSAGE_WARNING(
						"zlib filesystem is not implemented, skipping"
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked the packs for an
					// operation they don't have in B2a (writes, the
					// handle API — packs are read-only and handle-less
					// until B3)
					KOTEK_MESSAGE_WARNING(
						"the pack filesystem does not support this "
						"operation, skipping"
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
					// chain case: SILENT skip — an override-chain
					// backend not answering an operation is the normal
					// flow, not an event
				}
#endif

				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "something is broken, can't be!"
				);
				return false;
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
						return false;
					}
					case eFileSystemPriorityType::kNative:
					{
						// todo: the repeat-fs retry is unreachable
						// today (was_overloaded_fs_order is mutually
						// exclusive with this loop's guard) — kept
						// for the phase-B2 priority-list rework
						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
						// packs don't offer this operation in B2a —
						// silent skip, the chain continues
						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return false;
					}
					}
				}

				if (!status)
				{
					KOTEK_MESSAGE_WARNING("can't get file size"
					);
				}
			}
			else
			{
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
	const ktk_filesystem_path& path_to_file,
	kun_ktk size_t& result,
	eFileSystemPriorityType
		priority /*= eFileSystemPriorityType::kAuto */
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
	result = 0;

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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return status;
			}
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
				return status;
			}
			case eFileSystemPriorityType::kNative:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
				if (priority == fs_type)
				{
					status = this->m_fs_native.Get_FileSize(
						this->m_root_path / path_to_file, result
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
							this->m_root_path / path_to_file,
							result
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
					// todo: implement the zlib backend (phase B2) —
					// degrade gracefully instead of aborting
					KOTEK_MESSAGE_WARNING(
						"zlib filesystem is not implemented, skipping"
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked for the packs
					kun_ktk size_t pack_size = 0;

					eKpackReadResult pack_result =
						this->m_fs_pack.Get_FileSize(
							path_to_file, pack_size
						);

					if (pack_result == eKpackReadResult::kSuccess)
					{
						result = pack_size;
						status = true;
					}

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
						kun_ktk size_t pack_size = 0;

						eKpackReadResult pack_result =
							this->m_fs_pack.Get_FileSize(
								path_to_file, pack_size
							);

						if (pack_result == eKpackReadResult::kSuccess)
						{
							result = pack_size;
							status = true;
						}
						// kNotFound: silent fallthrough
					}
				}
#endif

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
						return status;
					}
					case eFileSystemPriorityType::kNative:
					{
						status = this->m_fs_native.Get_FileSize(
							this->m_root_path / path_to_file,
							result
						);

						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
						kun_ktk size_t pack_size = 0;

						eKpackReadResult pack_result =
							this->m_fs_pack.Get_FileSize(
								path_to_file, pack_size
							);

						if (pack_result == eKpackReadResult::kSuccess)
						{
							result = pack_size;
							status = true;
						}
						// kNotFound: silent fallthrough
#endif

						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return status;
					}
					}
				}

				if (!status)
				{
					KOTEK_MESSAGE_WARNING(
						"can't get file size: {} because all file "
						"systems couldn't obtain it",
						path_to_file
					);
				}
			}
			else
			{
				KOTEK_MESSAGE_WARNING(
					"can't get file size: {} because all file "
					"systems couldn't obtain it",
					path_to_file
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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return false;
			}
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
				// a corrupt priority list is a logic error, but
				// library code never exits the process — fail the call
				KOTEK_ASSERT(false, "can't be!");
				return false;
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
					// todo: implement the zlib backend (phase B2) —
					// degrade gracefully instead of aborting
					KOTEK_MESSAGE_WARNING(
						"zlib filesystem is not implemented, skipping"
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked the packs for an
					// operation they don't have in B2a (writes, the
					// handle API — packs are read-only and handle-less
					// until B3)
					KOTEK_MESSAGE_WARNING(
						"the pack filesystem does not support this "
						"operation, skipping"
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
					// chain case: SILENT skip — an override-chain
					// backend not answering an operation is the normal
					// flow, not an event
				}
#endif

				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "something is broken, can't be!"
				);
				return false;
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
						return false;
					}
					case eFileSystemPriorityType::kNative:
					{
						// todo: the repeat-fs retry is unreachable
						// today (was_overloaded_fs_order is mutually
						// exclusive with this loop's guard) — kept
						// for the phase-B2 priority-list rework
						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
						// packs don't offer this operation in B2a —
						// silent skip, the chain continues
						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return false;
					}
					}
				}

				if (!status)
				{
					KOTEK_MESSAGE_WARNING("can't get file seek"
					);
				}
			}
			else
			{
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
			// the repeat storage must fit the whole priority list (the
			// pre-B0 check was inverted and asserted the opposite); a
			// violation is a logic error, but library code never exits
			// the process — fail the call
			const bool is_repeat_storage_big_enough =
				list_size <=
				(sizeof(repeat_fs) / sizeof(repeat_fs[0]));

			KOTEK_ASSERT(
				is_repeat_storage_big_enough,
				"something is wrong your list is much bigger "
				"than system can handle, see "
				"eFileSystemPriorityType::kEndOfEnum={}",
				static_cast<kun_ktk uint8_t>(
					eFileSystemPriorityType::kEndOfEnum
				)
			);

			if (is_repeat_storage_big_enough == false)
			{
				return false;
			}
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
				// a corrupt priority list is a logic error, but
				// library code never exits the process — fail the call
				KOTEK_ASSERT(false, "can't be!");
				return false;
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
					// todo: implement the zlib backend (phase B2) —
					// degrade gracefully instead of aborting
					KOTEK_MESSAGE_WARNING(
						"zlib filesystem is not implemented, skipping"
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
						// todo: implement the zlib backend (phase
						// B2) — a missing file must degrade to a
						// warning, not an abort
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
					}
				}
#endif

				break;
			}
			case eFileSystemPriorityType::kPack:
			{
#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
				if (priority == fs_type)
				{
					// the caller explicitly asked the packs for an
					// operation they don't have in B2a (writes, the
					// handle API — packs are read-only and handle-less
					// until B3)
					KOTEK_MESSAGE_WARNING(
						"the pack filesystem does not support this "
						"operation, skipping"
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
					// chain case: SILENT skip — an override-chain
					// backend not answering an operation is the normal
					// flow, not an event
				}
#endif

				break;
			}
			default:
			{
				KOTEK_ASSERT(
					false, "something is broken, can't be!"
				);
				return false;
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
						return false;
					}
					case eFileSystemPriorityType::kNative:
					{
						// todo: the repeat-fs retry is unreachable
						// today (was_overloaded_fs_order is mutually
						// exclusive with this loop's guard) — kept
						// for the phase-B2 priority-list rework
						break;
					}
					case eFileSystemPriorityType::kZlib:
					{
						// todo: implement the zlib backend (phase
						// B2)
						KOTEK_MESSAGE_WARNING(
							"zlib filesystem is not implemented, "
							"skipping"
						);
						break;
					}
					case eFileSystemPriorityType::kPack:
					{
						// packs don't offer this operation in B2a —
						// silent skip, the chain continues
						break;
					}
					default:
					{
						KOTEK_ASSERT(
							false,
							"something is broken can't be!"
						);
						return false;
					}
					}
				}

				if (!status)
				{
					KOTEK_MESSAGE_WARNING("can't get file tell"
					);
				}
			}
			else
			{
				KOTEK_MESSAGE_WARNING(
					"can't read file: because all file "
					"systems couldn't obtain it"
				);
			}
		}
	}

	return status;
}

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

	this->m_root_path =
		kun_ktk kun_filesystem current_path().u8string().c_str(
		);

#if defined(KOTEK_USE_FILESYSTEM_TYPE_NATIVE) && \
	defined(KOTEK_USE_FILESYSTEM_FEATURE_VFM)
	// B1: the native single-shot read consults the VFM layer when the
	// runtime feature flags (kVFMRead / kVFMCacheEnabled) ask for
	// mapped IO — wire it before any config-driven read happens
	this->m_vfm.Initialize();
	this->m_fs_native.Initialize(&this->m_vfm);
#endif

	this->Validate_Folders();

	this->Initialize_FrameworkConfig();

#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
	// B2a: wire the pack backend's root (absolute read paths are
	// relativized against it), then mount the conventional folder
	// (data_game/packs/*.kpack, newest-first) — the ONE directory walk
	// of the filesystem; a missing/empty folder is a silent no-op
	this->m_fs_pack.Initialize(this->m_root_path);
	this->Mount_Packs_From_Conventional_Folder();
#endif

	KOTEK_MESSAGE("filesystem is initialized!");
}

void ktkFileSystem::Shutdown(void)
{
	// B3: no state leaks past Shutdown — a still-live stream is a caller
	// leak, reported loudly and cleaned up anyway (native handles close,
	// held VFM mappings unmap so the balance counters stay exact)
	for (kun_ktk size_t i = 0; i < this->m_fstream_pool.size(); ++i)
	{
		fstream_state_t& state = this->m_fstream_pool[i];

		if (state.is_free == false)
		{
			KOTEK_MESSAGE_ERROR(
				"Shutdown: a stream on {} was never End_Stream'ed — "
				"closing it (fix the caller)",
				state.path
			);

			this->Release_Stream(state);
		}
	}

#ifdef KOTEK_USE_FILESYSTEM_TYPE_NATIVE
	this->m_fs_native.Shutdown();
#endif

#ifdef KOTEK_USE_FILESYSTEM_TYPE_ZLIB
	this->m_fs_zlib.Shutdown();
#endif

#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
	this->m_fs_pack.Shutdown();
#endif

#ifdef KOTEK_USE_FILESYSTEM_FEATURE_VFM
	this->m_vfm.Shutdown();
#endif
}

#ifdef KOTEK_USE_FILESYSTEM_TYPE_PACK
bool ktkFileSystem::Mount_Pack(const ktk_filesystem_path& pack_file_path)
{
	const bool status = this->m_fs_pack.Mount(pack_file_path);

	if (status)
		this->Ensure_Pack_In_PriorityList();

	return status;
}

void ktkFileSystem::Ensure_Pack_In_PriorityList()
{
	const kun_ktk uint8_t* p_fs_list =
		this->m_p_config->Get_FS_PriorityList();
	const kun_ktk uint8_t list_size =
		this->m_p_config->Get_FS_PriorityListSize();

	for (kun_ktk uint8_t i = 0; i < list_size; ++i)
	{
		if (p_fs_list[i] ==
		    static_cast<kun_ktk uint8_t>(eFileSystemPriorityType::kPack))
		{
			// the user configured the pack's place explicitly — their
			// order wins (["Native","Pack"] = loose files override)
			return;
		}
	}

	// B2a mount-order choice (documented in the K25 row): when packs are
	// present and the config says nothing, kPack is PREPENDED — packs
	// override the native dirs ("always native-last"): a not-found-in-
	// pack miss is a silent fallthrough while a native miss warns, so
	// this order serves packed content without per-read miss noise; the
	// classic mod/patch story rides the packs' newest-first mount order
	kun_ktk uint8_t updated_list[static_cast<kun_ktk uint8_t>(
		eFileSystemPriorityType::kEndOfEnum
	)] = {};

	updated_list[0] =
		static_cast<kun_ktk uint8_t>(eFileSystemPriorityType::kPack);

	const kun_ktk uint8_t tail_room = static_cast<kun_ktk uint8_t>(
		eFileSystemPriorityType::kEndOfEnum
	) - 1;

	kun_ktk uint8_t written = 1;

	for (kun_ktk uint8_t i = 0; i < list_size && written <= tail_room;
	     ++i)
	{
		updated_list[written] = p_fs_list[i];
		++written;
	}

	if (list_size > tail_room)
	{
		const unsigned dropped =
			static_cast<unsigned>(list_size - tail_room);

		KOTEK_MESSAGE_WARNING(
			"the FS priority list is full; kPack is prepended and "
			"the last {} configured entr{} {} dropped",
			dropped, dropped == 1 ? "y" : "ies",
			dropped == 1 ? "is" : "are"
		);
	}

	this->m_p_config->Set_FS_PriorityList(updated_list);

	KOTEK_MESSAGE(
		"packs mounted: the effective FS priority order is pack-first "
		"(native dirs are the fallback)"
	);
}

void ktkFileSystem::Mount_Packs_From_Conventional_Folder()
{
	ktk_filesystem_path packs_folder =
		this->m_root_path /
		kun_ktk kun_filesystem get_frameworks_folder_name_by_enum(
			eFolderIndex::kFolderIndex_DataGame
		);
	packs_folder /= kKpackPacksFolderName;

	if (this->Is_Exists(packs_folder) == false)
	{
		// mount-when-folder-exists: no folder, no packs, no noise
		return;
	}

	// the ONE allowed directory walk: collect the .kpack candidates with
	// their write times, sort newest-first, mount in that order (the
	// mount order IS the override order)
	struct pack_candidate_t
	{
		ktk_filesystem_path path;
		kun_ktk int64_t write_time;
	};

	pack_candidate_t candidates
		[KOTEK_DEF_FILESYSTEM_PACK_ENUMERATION_MAX_CANDIDATES];
	kun_ktk size_t candidate_count = 0;

	{
		std::error_code ec;

		for (kun_ktk kun_filesystem directory_iterator it(
				 packs_folder, ec
			 );
		     ec.value() == 0 &&
		     it != kun_ktk kun_filesystem directory_iterator();
		     it.increment(ec))
		{
			const auto& entry = *it;

			if (entry.is_regular_file() == false)
				continue;

			const ktk_filesystem_path& entry_path = entry.path();

			const kun_ktk size_t path_length =
				strlen(entry_path.c_str());
			const kun_ktk size_t extension_length =
				strlen(kKpackFileExtension);

			if (path_length <= extension_length)
				continue;

			bool is_kpack = true;

			for (kun_ktk size_t c = 0; c < extension_length; ++c)
			{
				if (kpack_fold_ascii(
						entry_path.c_str()
							[path_length - extension_length + c]
					) != kpack_fold_ascii(kKpackFileExtension[c]))
				{
					is_kpack = false;
					break;
				}
			}

			if (is_kpack == false)
				continue;

			if (candidate_count >=
			    KOTEK_DEF_FILESYSTEM_PACK_ENUMERATION_MAX_CANDIDATES)
			{
				KOTEK_MESSAGE_WARNING(
					"more than {} packs in {}; the rest are ignored",
					KOTEK_DEF_FILESYSTEM_PACK_ENUMERATION_MAX_CANDIDATES,
					packs_folder
				);
				break;
			}

			candidates[candidate_count].path = entry_path;
			candidates[candidate_count].write_time =
				static_cast<kun_ktk int64_t>(
					entry.last_write_time().time_since_epoch().count()
				);
			++candidate_count;
		}

		if (ec.value() != 0 &&
		    candidate_count == 0)
		{
			// the folder exists but can't be enumerated (the empty-
			// folder ERROR_FILE_NOT_FOUND shape also lands here — that
			// one is a legit no-op, not an error)
			if (ec.value() != 2 /*ERROR_FILE_NOT_FOUND*/)
			{
				KOTEK_MESSAGE_WARNING(
					"failed to enumerate the packs folder {} "
					"(error {})",
					packs_folder, ec.value()
				);
			}
			return;
		}
	}

	// insertion sort, newest first (ties broken by the path for
	// determinism)
	for (kun_ktk size_t i = 1; i < candidate_count; ++i)
	{
		const pack_candidate_t value = candidates[i];

		kun_ktk size_t hole = i;

		while (hole > 0)
		{
			const pack_candidate_t& prev = candidates[hole - 1];

			const bool is_older = prev.write_time < value.write_time;
			const bool is_same_time_earlier_name =
				prev.write_time == value.write_time &&
				strcmp(prev.path.c_str(), value.path.c_str()) > 0;

			if (is_older == false && is_same_time_earlier_name == false)
				break;

			candidates[hole] = prev;
			--hole;
		}

		candidates[hole] = value;
	}

	for (kun_ktk size_t i = 0; i < candidate_count; ++i)
	{
		this->Mount_Pack(candidates[i].path);
	}
}
#endif


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
