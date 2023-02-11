#include "../include/kotek_std_config.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkEngineConfig::ktkEngineConfig(void) :
	m_argc{-1}, m_argv{}, m_is_running{true},
	m_engine_feature_flags{eEngineFeature::kNone},
	m_engine_feature_render_flags{eEngineFeatureRender::kNone},
	m_engine_feature_sdk_flags{eEngineFeatureSDK::kNone},
	m_engine_feature_renderer_flags{eEngineFeatureRenderer::kNone},
	m_engine_feature_window_flags{eEngineFeatureWindow::kNone}
{
}

ktkEngineConfig::~ktkEngineConfig(void) {}

void ktkEngineConfig::Initialize(void) {}

void ktkEngineConfig::Shutdown(void) {}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeature id) const noexcept
{
	return (this->m_engine_feature_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureRender id) const noexcept
{
	return (this->m_engine_feature_render_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureRenderer id) const noexcept
{
	return (this->m_engine_feature_renderer_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureSDK id) const noexcept
{
	return (this->m_engine_feature_sdk_flags & id) == id;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureWindow id) const noexcept
{
	return (this->m_engine_feature_window_flags & id) == id;
}

void ktkEngineConfig::SetFeatureStatus(eEngineFeature id, bool status) noexcept
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
	eEngineFeatureRender id, bool status) noexcept
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
	eEngineFeatureRenderer id, bool status) noexcept
{
	if (status)
	{
		if (eEngineFeatureRenderer::kNone == id)
		{
			this->m_engine_feature_renderer_flags = id;
		}
		else
		{
			this->m_engine_feature_renderer_flags |= id;

			if (id ==
				eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest)
			{
				this->SetFeatureStatus(
					eEngineSupportedOpenGLVersion::kOpenGL_Latest, true);
			}
			else if (id ==
				eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest)
			{
				this->SetFeatureStatus(
					eEngineSupportedVulkanVersion::kVulkan_Latest, true);
			}
			else if (id ==
				eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest)
			{
				this->SetFeatureStatus(
					eEngineSupportedDirectXVersion::kDirectX_Latest, true);
			}
		}
	}
	else
	{
		this->m_engine_feature_renderer_flags &= ~id;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineFeatureSDK id, bool status) noexcept
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
	eEngineFeatureWindow id, bool status) noexcept
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
	eEngineSupportedOpenGLVersion version, bool status) noexcept
{
	KOTEK_ASSERT(
		this->IsFeatureEnabled(
			eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest) ||
			this->IsFeatureEnabled(eEngineFeatureRenderer::
					kEngine_Render_Renderer_OpenGL_SpecifiedByUser),
		"you can't call this method because your current renderer is not "
		"OpenGL! Your Renderer is: {}",
		helper::Translate_EngineFeatureRenderer(
			this->m_engine_feature_renderer_flags));

	if (this->m_engine_feature_renderer_flags ==
		eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest)
	{
		KOTEK_ASSERT(eEngineSupportedOpenGLVersion::kOpenGL_Latest != version,
			"you can't specify version that is not latest for OpenGL!");
	}

	if (status)
	{
		this->m_version_for_loading_opengl = version;
	}
	else
	{
		this->m_version_for_loading_opengl =
			eEngineSupportedOpenGLVersion::kUnknown;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineSupportedDirectXVersion version, bool status) noexcept
{
	KOTEK_ASSERT(
		this->IsFeatureEnabled(
			eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest) ||
			this->IsFeatureEnabled(eEngineFeatureRenderer::
					kEngine_Render_Renderer_DirectX_SpecifiedByUser),
		"you can't call this method because your current renderer is not "
		"DirectX! Your Renderer is: {}",
		helper::Translate_EngineFeatureRenderer(
			this->m_engine_feature_renderer_flags));

	if (this->m_engine_feature_renderer_flags ==
		eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest)
	{
		KOTEK_ASSERT(eEngineSupportedDirectXVersion::kDirectX_Latest != version,
			"you can't specify version that is not latest for OpenGL!");
	}

	if (status)
	{
		this->m_version_for_loading_directx = version;
	}
	else
	{
		this->m_version_for_loading_directx =
			eEngineSupportedDirectXVersion::kUnknown;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineSupportedVulkanVersion version, bool status) noexcept
{
	KOTEK_ASSERT(
		this->IsFeatureEnabled(
			eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest) ||
			this->IsFeatureEnabled(eEngineFeatureRenderer::
					kEngine_Render_Renderer_Vulkan_SpecifiedByUser),
		"you can't call this method because your current renderer is not "
		"Vulkan! Your Renderer is: {}",
		helper::Translate_EngineFeatureRenderer(
			this->m_engine_feature_renderer_flags));

	if (this->m_engine_feature_renderer_flags ==
		eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest)
	{
		KOTEK_ASSERT(eEngineSupportedVulkanVersion::kVulkan_Latest != version,
			"you can't specify version that is not latest for OpenGL!");
	}

	if (status)
	{
		this->m_version_for_loading_vulkan = version;
	}
	else
	{
		this->m_version_for_loading_vulkan =
			eEngineSupportedVulkanVersion::kUnknown;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	const ktk::vector<eEngineSupportedDirectXVersion>&
		fallback_versions) noexcept
{
	this->m_fallback_directx_versions = fallback_versions;
}

void ktkEngineConfig::SetFeatureStatus(
	const ktk::vector<eEngineSupportedOpenGLVersion>&
		fallback_versions) noexcept
{
	this->m_fallback_opengl_versions = fallback_versions;
}

void ktkEngineConfig::SetFeatureStatus(
	const ktk::vector<eEngineSupportedVulkanVersion>&
		fallback_versions) noexcept
{
	this->m_fallback_vulkan_versions = fallback_versions;
}

void ktkEngineConfig::SetFeatureStatus(
	const ktk::vector<eEngineFeatureRenderer>& gapis) noexcept
{
	this->m_fallback_renderers = gapis;
}

eEngineFeature ktkEngineConfig::GetEngineFeature(void) const noexcept
{
	return this->m_engine_feature_flags;
}

eEngineFeatureRender ktkEngineConfig::GetEngineFeatureRender(
	void) const noexcept
{
	return this->m_engine_feature_render_flags;
}

eEngineFeatureRenderer ktkEngineConfig::GetEngineFeatureRenderer(
	void) const noexcept
{
	return this->m_engine_feature_renderer_flags;
}

eEngineFeatureSDK ktkEngineConfig::GetEngineFeatureSDK(void) const noexcept
{
	return this->m_engine_feature_sdk_flags;
}

eEngineFeatureWindow ktkEngineConfig::GetEngineFeatureWindow(
	void) const noexcept
{
	return this->m_engine_feature_window_flags;
}

eEngineSupportedDirectXVersion ktkEngineConfig::GetDirectXVersionForLoading(
	void) const noexcept
{
	return this->m_version_for_loading_directx;
}

eEngineSupportedOpenGLVersion ktkEngineConfig::GetOpenGLVersionForLoading(
	void) const noexcept
{
	return this->m_version_for_loading_opengl;
}

eEngineSupportedVulkanVersion ktkEngineConfig::GetVulkanVersionForLoading(
	void) const noexcept
{
	return this->m_version_for_loading_vulkan;
}

const ktk::vector<eEngineSupportedDirectXVersion>&
ktkEngineConfig::GetFallbackDirectXVersions(void) const noexcept
{
	return this->m_fallback_directx_versions;
}

const ktk::vector<eEngineSupportedOpenGLVersion>&
ktkEngineConfig::GetFallbackOpenGLVersions(void) const noexcept
{
	return this->m_fallback_opengl_versions;
}

const ktk::vector<eEngineSupportedVulkanVersion>&
ktkEngineConfig::GetFallbackVulkanVersions(void) const noexcept
{
	return this->m_fallback_vulkan_versions;
}

const ktk::vector<eEngineFeatureRenderer>&
ktkEngineConfig::GetFallbackRendereres(void) const noexcept
{
	return this->m_fallback_renderers;
}

eEngineSupportedDirectXVersion
ktkEngineConfig::GetDirectXVersionFromCommandLine(void) const noexcept
{
	KOTEK_ASSERT(this->IsUserSpecifiedValidRenderer(),
		"you must specify only one renderer or only one version for that "
		"renderer");

	eEngineSupportedDirectXVersion result{
		eEngineSupportedDirectXVersion::kUnknown};

	ktk::size_t validation{};
	if (this->m_parsed_command_line_arguments.find(
			kConsoleCommandArg_Render_DirectX12) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedDirectXVersion::kDirectX_12;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX11) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedDirectXVersion::kDirectX_11;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX10) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedDirectXVersion::kDirectX_10;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX9) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedDirectXVersion::kDirectX_9;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX8) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedDirectXVersion::kDirectX_8;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX7) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedDirectXVersion::kDirectX_7;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_DirectX_Latest) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedDirectXVersion::kDirectX_Latest;
	}

	KOTEK_ASSERT(validation <= 1,
		"something is terribly wrong and you have more than one renderer or "
		"renderer versions");

	return result;
}

eEngineSupportedOpenGLVersion ktkEngineConfig::GetOpenGLVersionFromCommandLine(
	void) const noexcept
{
	KOTEK_ASSERT(this->IsUserSpecifiedValidRenderer(),
		"you must specify only one renderer or only one version for that "
		"renderer");

	eEngineSupportedOpenGLVersion result{
		eEngineSupportedOpenGLVersion::kUnknown};

	ktk::size_t validation{};
	if (this->m_parsed_command_line_arguments.find(
			kConsoleCommandArg_Render_OpenGL3_3) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedOpenGLVersion::kOpenGL_3_3;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGL4_6) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedOpenGLVersion::kOpenGL_4_6;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_OpenGL_Latest) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedOpenGLVersion::kOpenGL_Latest;
	}

	KOTEK_ASSERT(validation <= 1,
		"something is terribly wrong and you have more than one renderer or "
		"renderer versions");

	return result;
}

eEngineSupportedVulkanVersion ktkEngineConfig::GetVulkanVersionFromCommandLine(
	void) const noexcept
{
	KOTEK_ASSERT(this->IsUserSpecifiedValidRenderer(),
		"you must specify only one renderer or only one version for that "
		"renderer");

	eEngineSupportedVulkanVersion result{
		eEngineSupportedVulkanVersion::kUnknown};

	ktk::size_t validation{};

	if (this->m_parsed_command_line_arguments.find(
			kConsoleCommandArg_Render_Vulkan1_0) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedVulkanVersion::kVulkan_1_0;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_Vulkan1_1) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedVulkanVersion::kVulkan_1_1;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_Vulkan1_2) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedVulkanVersion::kVulkan_1_2;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_Vulkan1_3) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedVulkanVersion::kVulkan_1_3;
	}
	else if (this->m_parsed_command_line_arguments.find(
				 kConsoleCommandArg_Render_Vulkan_Latest) !=
		this->m_parsed_command_line_arguments.end())
	{
		++validation;
		result = eEngineSupportedVulkanVersion::kVulkan_Latest;
	}

	KOTEK_ASSERT(validation <= 1,
		"something is terribly wrong and you have more than one renderer or "
		"renderer versions");

	return result;
}

ktk::cstring ktkEngineConfig::GetRenderName(void) const noexcept
{
	switch (this->m_engine_feature_renderer_flags)
	{
	case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest:
	{
		return helper::Translate_EngineSupportedOpenGLVersion(
			this->GetOpenGLVersionForLoading());
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_SpecifiedByUser:
	{
		return helper::Translate_EngineSupportedOpenGLVersion(
			this->GetOpenGLVersionForLoading());
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest:
	{
		return helper::Translate_EngineSupportedDirectXVersion(
			this->GetDirectXVersionForLoading());
	}
	case eEngineFeatureRenderer::
		kEngine_Render_Renderer_DirectX_SpecifiedByUser:
	{
		return helper::Translate_EngineSupportedDirectXVersion(
			this->GetDirectXVersionForLoading());
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest:
	{
		return helper::Translate_EngineSupportedVulkanVersion(
			this->GetVulkanVersionForLoading());
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_SpecifiedByUser:
	{
		return helper::Translate_EngineSupportedVulkanVersion(
			this->GetVulkanVersionForLoading());
	}
	default:
	{
		return helper::Translate_EngineFeatureRenderer(
			this->m_engine_feature_renderer_flags);
	}
	}
}

/*
eEngineFeature ktkEngineConfig::GetRenderFeature(void) const noexcept
{
    eEngineFeature result = eEngineFeature::kEngine_Feature_Unknown;

    int validation_count = 0;

    if (this->IsFeatureEnabled(
            eEngineFeature::kEngine_Render_Renderer_OpenGL3_3))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_OpenGL3_3;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_OpenGL4_6))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_OpenGL4_6;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_Vulkan))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_Vulkan;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_DirectX_12))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_DirectX_12;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_DirectX_11))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_DirectX_11;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_DirectX_10))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_DirectX_10;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_DirectX_9))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_DirectX_9;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_DirectX_8))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_DirectX_8;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_DirectX_7))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_DirectX_7;
    }
    else if (this->IsFeatureEnabled(
                 eEngineFeature::kEngine_Render_Renderer_Software))
    {
        ++validation_count;
        result = eEngineFeature::kEngine_Render_Renderer_Software;
    }

    KOTEK_ASSERT(
        validation_count > 0, "you must have some initialized renderer!");

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
	case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest:
	{
		KOTEK_ASSERT(this->GetOpenGLVersionForLoading() ==
				eEngineSupportedOpenGLVersion::kOpenGL_Latest,
			"something is wrong! Your specified renderer is OpenGL latest and "
			"your version must be kOpenGL_Latest, but it is not true!");

		status = true;
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_SpecifiedByUser:
	{
		if (this->GetOpenGLVersionForLoading() ==
			eEngineSupportedOpenGLVersion::kOpenGL_Latest)
			status = true;
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest:
	{
		KOTEK_ASSERT(this->GetDirectXVersionForLoading() ==
				eEngineSupportedDirectXVersion::kDirectX_Latest,
			"something is wrong! your specified renderer is DirectX latest and "
			"your version must be kDirectX_Latest, but it is not true!");

		status = true;
	}
	case eEngineFeatureRenderer::
		kEngine_Render_Renderer_DirectX_SpecifiedByUser:
	{
		if (this->GetDirectXVersionForLoading() ==
			eEngineSupportedDirectXVersion::kDirectX_Latest)
            status = true;
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest:
	{
		KOTEK_ASSERT(this->GetVulkanVersionForLoading() ==
				eEngineSupportedVulkanVersion::kVulkan_Latest,
			"something is wrong! you specified renderer as Vulkan Latest and "
			"your version must be kVulkan_Latest but it is not that!");

		status = true;
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_SpecifiedByUser:
	{
		if (this->GetVulkanVersionForLoading() ==
			eEngineSupportedVulkanVersion::kVulkan_Latest)
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
    const ktk::cstring& your_argument) const noexcept
{
	return std::find_if(this->m_parsed_command_line_arguments.begin(),
			   this->m_parsed_command_line_arguments.end(),
               [your_argument](const ktk::cstring& argument) -> bool
               {
                   ktk::cstring_view wrapped_argument = your_argument.c_str();
                   return argument == wrapped_argument;
			   }) != this->m_parsed_command_line_arguments.end();
}

bool ktkEngineConfig::IsUserSpecifiedValidRenderer(void) const noexcept
{
	ktk::size_t validation{0};
	for (const auto& argument : this->m_parsed_command_line_arguments)
	{
        if (argument.starts_with(KOTEK_TEXT("--render_")))
		{
			++validation;
		}
	}

	KOTEK_ASSERT(validation <= 1,
		"something is wrong and your command line contains more than one "
		"--render_renderername_verison or "
		"--render_renderernameversion_subversion");

	return validation <= 1;
}

bool ktkEngineConfig::IsUserSpecifiedRendererOpenGLInCommandLine(
	void) const noexcept
{
	KOTEK_ASSERT(this->IsUserSpecifiedValidRenderer(), "bad user! bad!");

	bool result{};

	for (const auto& argument : this->m_parsed_command_line_arguments)
	{
        if (argument.starts_with(KOTEK_TEXT("--render_gl")))
		{
			result = true;
			break;
		}
	}

	return result;
}

bool ktkEngineConfig::IsUserSpecifiedRendererDirectXInCommandLine(
	void) const noexcept
{
	KOTEK_ASSERT(this->IsUserSpecifiedValidRenderer(), "bad user! bad!");

	bool result{};

	for (const auto& argument : this->m_parsed_command_line_arguments)
	{
        if (argument.starts_with(KOTEK_TEXT("--render_dx")))
		{
			result = true;
			break;
		}
	}

	return result;
}

bool ktkEngineConfig::IsUserSpecifiedRendererVulkanInCommandLine(
	void) const noexcept
{
	KOTEK_ASSERT(this->IsUserSpecifiedValidRenderer(), "bad user! bad!");

	bool result{};

	for (const auto& argument : this->m_parsed_command_line_arguments)
	{
        if (argument.starts_with(KOTEK_TEXT("--render_vk")))
		{
			result = true;
			break;
		}
	}

	return result;
}

bool ktkEngineConfig::IsApplicationWorking(void) const noexcept
{
	return this->m_is_running;
}

void ktkEngineConfig::SetApplicationWorking(bool status) noexcept
{
	this->m_is_running = status;
}

void ktkEngineConfig::Set_UserLibrary(
	const ktk::filesystem::path& path_to_library) noexcept
{
	this->m_user_dll = ktk::dll::shared_library(path_to_library.c_str());
}

void* ktkEngineConfig::Get_UserLibrary(void) noexcept
{
	return &this->m_user_dll;
}

void ktkEngineConfig::Parse_CommandLine(void) noexcept
{
	KOTEK_ASSERT(this->m_argc != -1,
		"you must set argc before calling set argv method!");

    this->m_parsed_command_line_arguments = ktk::unordered_set<ktk::cstring>(
		this->m_argv, this->m_argv + this->m_argc);
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
