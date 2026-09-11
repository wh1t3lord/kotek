#include "../include/kotek_filesystem.h"
#include <kotek.core.constants/include/kotek_core_constants.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkFileSystem::ktkFileSystem(void) : m_p_config{} {}

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
