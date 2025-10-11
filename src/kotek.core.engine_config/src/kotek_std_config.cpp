#include "../include/kotek_std_config.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkEngineConfig::ktkEngineConfig(void) :
	m_fs_priority_list{}, m_fs_features_flag{}, m_argc{-1},
	m_argv{}, m_is_running{true},
	m_engine_feature_flags{eEngineFeature::kEngine_Feature_None
    },
	m_engine_feature_render_flags{
		eEngineFeatureRender::kEngine_Feature_Render_None
	},
	m_engine_feature_sdk_flags{
		eEngineFeatureSDK::kEngine_Feature_SDK_None
	},
	m_engine_feature_renderer_flags{
		eEngineFeatureRenderer::kEngine_Feature_Renderer_None
	},
	m_engine_feature_renderer_vendor_flags{
		eEngineFeatureRendererVendor::kNone
	},
	m_engine_feature_window_flags{
		eEngineFeatureWindow::kEngine_Feature_Window_None
	},
	m_video_memory_for_initialize{}
{
}

ktkEngineConfig::~ktkEngineConfig(void) {}

void ktkEngineConfig::Initialize() {}

void ktkEngineConfig::Shutdown(void) {}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeature id
) const noexcept
{
	return (this->m_engine_feature_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureRender id
) const noexcept
{
	return (this->m_engine_feature_render_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureRenderer id
) const noexcept
{
	return (this->m_engine_feature_renderer_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureSDK id
) const noexcept
{
	return (this->m_engine_feature_sdk_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureWindow id
) const noexcept
{
	return (this->m_engine_feature_window_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(
	eEngineFeatureRendererVendor id
) const noexcept
{
	return (this->m_engine_feature_renderer_vendor_flags & id
	       ) == id;
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineFeature id, bool status
) noexcept
{
	if (status)
	{
		this->m_engine_feature_flags |= id;
	}
	else
	{
		this->m_engine_feature_flags &= ~id;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineFeatureRender id, bool status
) noexcept
{
	if (status)
	{
		this->m_engine_feature_render_flags |= id;
	}
	else
	{
		this->m_engine_feature_render_flags &= ~id;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineFeatureRenderer id, bool status
) noexcept
{
	if (status)
	{
		if (eEngineFeatureRenderer::
		        kEngine_Feature_Renderer_None == id)
		{
			this->m_engine_feature_renderer_flags = id;
		}
		else
		{
			this->m_engine_feature_renderer_flags |= id;

			if (id ==
			    eEngineFeatureRenderer::
			        kEngine_Feature_Renderer_OpenGL_Latest)
			{
				this->SetFeatureStatus(
					eEngineSupportedRenderer::kOpenGL_Latest,
					true
				);
			}
			else if (id ==
			         eEngineFeatureRenderer::
			             kEngine_Feature_Renderer_Vulkan_Latest)
			{
				this->SetFeatureStatus(
					eEngineSupportedRenderer::kVulkan_Latest,
					true
				);
			}
			else if (id ==
			         eEngineFeatureRenderer::
			             kEngine_Feature_Renderer_DirectX_Latest)
			{
				this->SetFeatureStatus(
					eEngineSupportedRenderer::kDirectX_Latest,
					true
				);
			}
			else if (id ==
			         eEngineFeatureRenderer::
			             kEngine_Feature_Renderer_OpenGLES_Latest)
			{
				this->SetFeatureStatus(
					eEngineSupportedRenderer::kOpenGLES_Latest,
					true
				);
			}
		}
	}
	else
	{
		this->m_engine_feature_renderer_flags &= ~id;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineFeatureSDK id, bool status
) noexcept
{
	if (status)
	{
		this->m_engine_feature_sdk_flags |= id;
	}
	else
	{
		this->m_engine_feature_sdk_flags &= ~id;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineFeatureWindow id, bool status
) noexcept
{
	if (status)
	{
		this->m_engine_feature_window_flags |= id;
	}
	else
	{
		this->m_engine_feature_window_flags &= ~id;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineSupportedRenderer version, bool status
) noexcept
{
	if (status)
		this->m_version_renderer =
			static_cast<kun_ktk enum_base_t>(version);
	else
		this->m_version_renderer =
			static_cast<kun_ktk enum_base_t>(
				eEngineSupportedRenderer::kUnknown
			);
}

void ktkEngineConfig::SetFeatureStatus(
	const ktk_vector<
		eEngineSupportedRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT>&
		fallback_versions
) noexcept
{
	this->m_fallback_renderers_versions = fallback_versions;
}

void ktkEngineConfig::SetFeatureStatus(
	const ktk_vector<
		eEngineFeatureRenderer,
		KOTEK_DEF_FALLBACK_RENDERERS_COUNT>& gapis
) noexcept
{
	this->m_fallback_renderers = gapis;
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineFeatureRendererVendor vendor, bool status
) noexcept
{
	if (status)
	{
		this->m_engine_feature_renderer_vendor_flags |= vendor;
	}
	else
	{
		this->m_engine_feature_renderer_vendor_flags &= ~vendor;
	}
}

eEngineFeature ktkEngineConfig::GetEngineFeature(void
) const noexcept
{
	return this->m_engine_feature_flags;
}

eEngineFeatureRender
ktkEngineConfig::GetEngineFeatureRender(void) const noexcept
{
	return this->m_engine_feature_render_flags;
}

eEngineFeatureRenderer
ktkEngineConfig::GetEngineFeatureRenderer(void) const noexcept
{
	return this->m_engine_feature_renderer_flags;
}

eEngineFeatureSDK ktkEngineConfig::GetEngineFeatureSDK(void
) const noexcept
{
	return this->m_engine_feature_sdk_flags;
}

eEngineFeatureWindow
ktkEngineConfig::GetEngineFeatureWindow(void) const noexcept
{
	return this->m_engine_feature_window_flags;
}

eEngineSupportedRenderer
ktkEngineConfig::GetRendererVersionEnum(void) const noexcept
{
	return static_cast<eEngineSupportedRenderer>(
		this->m_version_renderer
	);
}

kun_ktk enum_base_t ktkEngineConfig::GetRendererVersion(void
) const noexcept
{
	return this->m_version_renderer;
}

const ktk_vector<
	eEngineFeatureRenderer,
	KOTEK_DEF_FALLBACK_RENDERERS_COUNT>&
ktkEngineConfig::GetFallbackRendereres(void) const noexcept
{
	return this->m_fallback_renderers;
}

const ktk_vector<
	eEngineSupportedRenderer,
	KOTEK_DEF_FALLBACK_RENDERERS_VERSIONS_COUNT>&
ktkEngineConfig::GetFallbackRendererVersions(void
) const noexcept
{
	return this->m_fallback_renderers_versions;
}

kun_ktk cstring ktkEngineConfig::GetRenderName(void
) const noexcept
{
	return helper::Translate_EngineSupportedRenderer(
		this->GetRendererVersionEnum()
	);
}

/*
eEngineFeature ktkEngineConfig::GetRenderFeature(void) const
noexcept
{
    eEngineFeature result =
eEngineFeature::kEngine_Feature_Unknown;

    int validation_count = 0;

    if (this->IsFeatureEnabled(
            eEngineFeature::kEngine_Feature_Renderer_OpenGL3_3))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_OpenGL3_3;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_OpenGL4_6))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_OpenGL4_6;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_Vulkan))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_Vulkan;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_DirectX_12))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_DirectX_12;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_DirectX_11))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_DirectX_11;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_DirectX_10))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_DirectX_10;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_DirectX_9))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_DirectX_9;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_DirectX_8))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_DirectX_8;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_DirectX_7))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_DirectX_7;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Feature_Renderer_Software))
    {
        ++validation_count;
        result =
eEngineFeature::kEngine_Feature_Renderer_Software;
    }

    KOTEK_ASSERT(
        validation_count > 0, "you must have some initialized
renderer!");

    KOTEK_ASSERT(validation_count == 1,
        "You can't have more than one initialized renderer.");

    return result;
}
*/

bool ktkEngineConfig::IsCurrentRenderLegacy(void) const noexcept
{
	return !this->IsCurrentRenderModern();
}

bool ktkEngineConfig::IsCurrentRenderModern(void) const noexcept
{
	auto render_type = this->GetEngineFeatureRenderer();

	bool status{};

	switch (this->m_engine_feature_renderer_flags)
	{
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_OpenGL_Latest:
	{
		KOTEK_ASSERT(
			this->GetRendererVersionEnum() ==
				eEngineSupportedRenderer::kOpenGL_Latest,
			"something is wrong! Your specified renderer is "
			"OpenGL latest and "
			"your version must be kOpenGL_Latest, but it is "
			"not true!"
		);

		status = true;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_OpenGL_SpecifiedByUser:
	{
		if (this->GetRendererVersionEnum() ==
		    eEngineSupportedRenderer::kOpenGL_Latest)
			status = true;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_DirectX_Latest:
	{
		KOTEK_ASSERT(
			this->GetRendererVersionEnum() ==
				eEngineSupportedRenderer::kDirectX_Latest,
			"something is wrong! your specified renderer is "
			"DirectX latest and "
			"your version must be kDirectX_Latest, but it is "
			"not true!"
		);

		status = true;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_DirectX_SpecifiedByUser:
	{
		if (this->GetRendererVersionEnum() ==
		    eEngineSupportedRenderer::kDirectX_Latest)
			status = true;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_Vulkan_Latest:
	{
		KOTEK_ASSERT(
			this->GetRendererVersionEnum() ==
				eEngineSupportedRenderer::kVulkan_Latest,
			"something is wrong! you specified renderer as "
			"Vulkan Latest and "
			"your version must be kVulkan_Latest but it is not "
			"that!"
		);

		status = true;
	}
	case eEngineFeatureRenderer::
		kEngine_Feature_Renderer_Vulkan_SpecifiedByUser:
	{
		if (this->GetRendererVersionEnum() ==
		    eEngineSupportedRenderer::kVulkan_Latest)
			status = true;
	}
	}

	return status;
}

int ktkEngineConfig::GetARGC(void) const noexcept
{
	return this->m_argc;
}

void ktkEngineConfig::SetARGC(int count_of_arguments) noexcept
{
	this->m_argc = count_of_arguments;
}

char** ktkEngineConfig::GetARGV(void) const noexcept
{
	return this->m_argv;
}

void ktkEngineConfig::SetARGV(char** p_char) noexcept
{
	this->m_argv = p_char;
	this->Parse_CommandLine();
}

bool ktkEngineConfig::IsContainsConsoleCommandLineArgument(
	const kun_ktk cstring& your_argument
) const noexcept
{
	/* TODO: delete this because it was for vector
	return
	std::find_if(this->m_parsed_command_line_arguments.begin(),
	           this->m_parsed_command_line_arguments.end(),
	           [your_argument](const kun_ktk cstring& argument)
	-> bool
	           {
	               kun_ktk cstring_view wrapped_argument =
	your_argument.c_str(); return argument == wrapped_argument;
	           }) !=
	this->m_parsed_command_line_arguments.end();*/

	return this->m_parsed_command_line_arguments.find(
			   your_argument
		   ) != this->m_parsed_command_line_arguments.end();
}

bool ktkEngineConfig::IsUserSpecifiedValidRenderer(void
) const noexcept
{
	kun_ktk size_t validation{0};
	for (const auto& argument :
	     this->m_parsed_command_line_arguments)
	{
		if (argument.starts_with(KOTEK_TEXTU("--render_")))
		{
			++validation;
		}
	}

	KOTEK_ASSERT(
		validation <= 1,
		"something is wrong and your command line contains "
		"more than one "
		"--render_renderername_verison or "
		"--render_renderernameversion_subversion"
	);

	return validation <= 1;
}

bool ktkEngineConfig::
	IsUserSpecifiedRendererOpenGLInCommandLine(void
    ) const noexcept
{
	KOTEK_ASSERT(
		this->IsUserSpecifiedValidRenderer(), "bad user! bad!"
	);

	bool result{};

	for (const auto& argument :
	     this->m_parsed_command_line_arguments)
	{
		if (argument.starts_with(KOTEK_TEXTU("--render_gl")))
		{
			result = true;
			break;
		}
	}

	return result;
}

bool ktkEngineConfig::
	IsUserSpecifiedRendererDirectXInCommandLine(void
    ) const noexcept
{
	KOTEK_ASSERT(
		this->IsUserSpecifiedValidRenderer(), "bad user! bad!"
	);

	bool result{};

	for (const auto& argument :
	     this->m_parsed_command_line_arguments)
	{
		if (argument.starts_with(KOTEK_TEXTU("--render_dx")))
		{
			result = true;
			break;
		}
	}

	return result;
}

bool ktkEngineConfig::
	IsUserSpecifiedRendererVulkanInCommandLine(void
    ) const noexcept
{
	KOTEK_ASSERT(
		this->IsUserSpecifiedValidRenderer(), "bad user! bad!"
	);

	bool result{};

	for (const auto& argument :
	     this->m_parsed_command_line_arguments)
	{
		if (argument.starts_with(KOTEK_TEXTU("--render_vk")))
		{
			result = true;
			break;
		}
	}

	return result;
}

eEngineSupportedRenderer
ktkEngineConfig::GetRendererVersionFromCommandLine(void
) const noexcept
{
	KOTEK_ASSERT(
		this->IsUserSpecifiedValidRenderer(),
		"you must specify only one renderer or only one "
		"version for that "
		"renderer"
	);

	eEngineSupportedRenderer result{
		eEngineSupportedRenderer::kUnknown
	};

	kun_ktk size_t validation{};

	if (this->m_parsed_command_line_arguments.find(
			kConsoleCommandArg_Render_Vulkan1_0
		) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kVulkan_1_0;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_Vulkan1_1
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kVulkan_1_1;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_Vulkan1_2
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kVulkan_1_2;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_Vulkan1_3
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kVulkan_1_3;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_Vulkan_Latest
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kVulkan_Latest;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGL3_3
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGL_3_3;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGL4_6
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGL_4_6;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGL_Latest
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGL_Latest;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX12
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kDirectX_12;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX11
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kDirectX_11;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX10
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kDirectX_10;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX9
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kDirectX_9;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX8
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kDirectX_8;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX7
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kDirectX_7;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX_Latest
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kDirectX_Latest;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGLES1_0
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGLES_1;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGLES2_0
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGLES_2;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGLES3_0
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGLES_3_0;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGLES3_1
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGLES_3_1;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGLES3_2
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGLES_3_2;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGLES_Latest
			 ) != this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedRenderer::kOpenGLES_Latest;
	}

	KOTEK_ASSERT(
		validation <= 1,
		"something is terribly wrong and you have more than "
		"one renderer or "
		"renderer versions"
	);

	return result;
}

bool ktkEngineConfig::IsApplicationWorking(void) const noexcept
{
	return this->m_is_running;
}

void ktkEngineConfig::SetApplicationWorking(bool status
) noexcept
{
	this->m_is_running = status;
}

void ktkEngineConfig::Set_UserLibrary(
	const ktk_filesystem_path& path_to_library
) noexcept
{
	this->m_user_dll =
		kun_ktk dll::shared_library(path_to_library.c_str());
}

void* ktkEngineConfig::Get_UserLibrary(void) noexcept
{
	return &this->m_user_dll;
}

// TODO: finish this
kun_ktk size_t ktkEngineConfig::Get_VideoMemoryTotal(void
) const noexcept
{
	return 0;
}

kun_ktk size_t ktkEngineConfig::Get_VideoMemoryForInitialize(
	void
) const noexcept
{
	return this->m_video_memory_for_initialize;
}

void ktkEngineConfig::Set_VideoMemoryForInitialize(
	kun_ktk size_t value
) noexcept
{
	this->m_video_memory_for_initialize = value;
}

void ktkEngineConfig::Parse_CommandLine(void) noexcept
{
	KOTEK_ASSERT(
		this->m_argc != -1,
		"you must set argc before calling set argv method!"
	);

#ifdef KOTEK_USE_LIBRARY_TYPE_EMB
	KOTEK_ASSERT(
		this->m_argc <= KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT,
		"overflow! reduce or set bigger size of this constant "
		"KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT in cmake "
		"(because it is "
		"dynamically generated constant and will be "
		"overwritten after any "
		"changes of cmake scripts)"
	);
#endif

	this->m_parsed_command_line_arguments = ktk_unordered_set<
		kun_ktk cstring,
		KOTEK_DEF_COMMAND_LINE_ARGUMENTS_COUNT>(
		this->m_argv, this->m_argv + this->m_argc
	);
}

eEngineFeatureRendererVendor
ktkEngineConfig::GetEngineFeatureRendererVendor(void
) const noexcept
{
	return this->m_engine_feature_renderer_vendor_flags;
}

const kun_ktk uint8_t* ktkEngineConfig::Get_FS_PriorityList(void
) const noexcept
{
	return m_fs_priority_list;
}

kun_ktk uint8_t ktkEngineConfig::Get_FS_PriorityListSize(void
) const noexcept
{
	kun_ktk uint8_t result = 0;

	for (kun_ktk uint8_t i = 0;
	     i < static_cast<kun_ktk uint8_t>(
				 eFileSystemPriorityType::kEndOfEnum
			 );
	     ++i)
	{
		if (this->m_fs_priority_list[i] ==
		    static_cast<kun_ktk uint8_t>(
				eFileSystemPriorityType::kAuto
			))
		{
			break;
		}

		++result;
	}

	return result;
}

kun_ktk uint16_t ktkEngineConfig::Get_FS_FeaturesFlag(void
) const noexcept
{
	return this->m_fs_features_flag;
}

const char* ktkEngineConfig::Get_UserLibrary_CallbackName(
	eUserEngineLibraryCallbacks callback_id
) const noexcept
{
	return this
		->m_user_engine_library_callbacks
			[static_cast<kun_ktk uint8_t>(callback_id)]
		.c_str();
}

const char* ktkEngineConfig::Get_UserLibrary_Name(void
) const noexcept
{
	return this->m_user_dll_name.c_str();
}

void ktkEngineConfig::Set_FS_PriorityList(
	const kun_ktk uint8_t (&arr)[static_cast<
		kun_ktk uint8_t>(eFileSystemPriorityType::kEndOfEnum)]
)
{
	std::memcpy(
		this->m_fs_priority_list,
		arr,
		sizeof(arr) / sizeof(arr[0])
	);
}

void ktkEngineConfig::Set_FS_FeaturesFlag(kun_ktk uint16_t
                                              features)
{
	this->m_fs_features_flag = features;
}

void ktkEngineConfig::Set_UserLibrary_CallbackName(
	eUserEngineLibraryCallbacks callback_id,
	const ktk_cstring<
		KOTEK_DEF_USER_ENGINE_LIBRARY_CALLBACK_NAME_LENGTH>&
		name
)
{
	this->m_user_engine_library_callbacks
		[static_cast<kun_ktk uint8_t>(callback_id)] = name;
}

void ktkEngineConfig::Set_UserLibrary_Name(
	const ktk_cstring<
		KOTEK_DEF_USER_ENGINE_LIBRARY_NAME_LENGTH>& name
)
{
	this->m_user_dll_name = name;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
