#include "../include/kotek_std_config.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkEngineConfig::ktkEngineConfig(void) :
	m_argc{-1}, m_argv{}, m_is_running{true}, m_engine_feature_flags{},
	m_engine_feature_render_flags{}, m_engine_feature_sdk_flags{},
	m_engine_feature_window_flags{},
	m_engine_current_directx_version{eEngineSupportedDirectXVersion::kUnknown},
	m_engine_current_opengl_version{eEngineSupportedOpenGLVersion::kUnknown},
	m_engine_current_vulkan_version{eEngineSupportedVulkanVersion::kUnknown}
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
	return false;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureRenderer id) const noexcept
{
	return false;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureSDK id) const noexcept
{
	return false;
}

bool ktkEngineConfig::IsFeatureEnabled(eEngineFeatureWindow id) const noexcept
{
	return false;
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
		this->m_engine_feature_renderer_flags = id;

		if (id == eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest)
		{
			this->SetFeatureStatus(
				eEngineSupportedOpenGLVersion::kOpenGL_Latest, true);
		}
	}
	else
	{
		this->m_engine_feature_renderer_flags = eEngineFeatureRenderer::kNone;
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
	KOTEK_ASSERT(this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest ||
			this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::
					kEngine_Render_Renderer_OpenGL_SpecifiedByUser,
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
		this->m_engine_current_opengl_version = version;
	}
	else
	{
		this->m_engine_current_opengl_version =
			eEngineSupportedOpenGLVersion::kUnknown;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineSupportedDirectXVersion version, bool status) noexcept
{
	KOTEK_ASSERT(this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::
					kEngine_Render_Renderer_DirectX_Latest ||
			this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::
					kEngine_Render_Renderer_DirectX_SpecifiedByUser,
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
		this->m_engine_current_directx_version = version;
	}
	else
	{
		this->m_engine_current_directx_version =
			eEngineSupportedDirectXVersion::kUnknown;
	}
}

void ktkEngineConfig::SetFeatureStatus(
	eEngineSupportedVulkanVersion version, bool status) noexcept
{
	KOTEK_ASSERT(this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest ||
			this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::
					kEngine_Render_Renderer_Vulkan_SpecifiedByUser,
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
		this->m_engine_current_vulkan_version = version;
	}
	else
	{
		this->m_engine_current_vulkan_version =
			eEngineSupportedVulkanVersion::kUnknown;
	}
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

eEngineSupportedDirectXVersion ktkEngineConfig::GetCurrentDirectXVersion(
	void) const noexcept
{
	KOTEK_ASSERT(this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::
					kEngine_Render_Renderer_DirectX_Latest ||
			this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::
					kEngine_Render_Renderer_DirectX_SpecifiedByUser,
		"Your renderer must be DirectX for calling this method! Your Renderer "
		"is: {}",
		helper::Translate_EngineFeatureRenderer(
			this->m_engine_feature_renderer_flags));

	return this->m_engine_current_directx_version;
}

eEngineSupportedOpenGLVersion ktkEngineConfig::GetCurrentOpenGLVersion(
	void) const noexcept
{
	KOTEK_ASSERT(this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest ||
			this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::
					kEngine_Render_Renderer_OpenGL_SpecifiedByUser,
		"Your renderer must be OpenGL for calling this method! Your Renderer "
		"is: {}",
		helper::Translate_EngineFeatureRenderer(
			this->m_engine_feature_renderer_flags));

	return this->m_engine_current_opengl_version;
}

eEngineSupportedVulkanVersion ktkEngineConfig::GetCurrentVulkanVersion(
	void) const noexcept
{
	KOTEK_ASSERT(this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest ||
			this->m_engine_feature_renderer_flags ==
				eEngineFeatureRenderer::
					kEngine_Render_Renderer_Vulkan_SpecifiedByUser,
		"your renderer must be Vulkan for calling this method! Your Renderer "
		"is: {}",
		helper::Translate_EngineFeatureRenderer(
			this->m_engine_feature_renderer_flags));

	return this->m_engine_current_vulkan_version;
}

ktk::string ktkEngineConfig::GetRenderName(void) const noexcept
{
	switch (this->m_engine_feature_renderer_flags)
	{
	case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_Latest:
	{
		return helper::Translate_EngineSupportedOpenGLVersion(
			this->m_engine_current_opengl_version);
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_SpecifiedByUser:
	{
		return helper::Translate_EngineSupportedOpenGLVersion(
			this->m_engine_current_opengl_version);
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest:
	{
		return helper::Translate_EngineSupportedDirectXVersion(
			this->m_engine_current_directx_version);
	}
	case eEngineFeatureRenderer::
		kEngine_Render_Renderer_DirectX_SpecifiedByUser:
	{
		return helper::Translate_EngineSupportedDirectXVersion(
			this->m_engine_current_directx_version);
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest:
	{
		return helper::Translate_EngineSupportedVulkanVersion(
			this->m_engine_current_vulkan_version);
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_SpecifiedByUser:
	{
		return helper::Translate_EngineSupportedVulkanVersion(
			this->m_engine_current_vulkan_version);
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
		KOTEK_ASSERT(this->m_engine_current_opengl_version ==
				eEngineSupportedOpenGLVersion::kOpenGL_Latest,
			"something is wrong! Your specified renderer is OpenGL latest and "
			"your version must be kOpenGL_Latest, but it is not true!");

		status = true;
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL_SpecifiedByUser:
	{
		if (this->m_engine_current_opengl_version ==
			eEngineSupportedOpenGLVersion::kOpenGL_Latest)
			status = true;
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_Latest:
	{
		KOTEK_ASSERT(this->m_engine_current_directx_version ==
				eEngineSupportedDirectXVersion::kDirectX_Latest,
			"something is wrong! your specified renderer is DirectX latest and "
			"your version must be kDirectX_Latest, but it is not true!");

		status = true;
	}
	case eEngineFeatureRenderer::
		kEngine_Render_Renderer_DirectX_SpecifiedByUser:
	{
		if (this->m_engine_current_directx_version ==
			eEngineSupportedDirectXVersion::kDirectX_Latest)
			status == true;
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_Latest:
	{
		KOTEK_ASSERT(this->m_engine_current_vulkan_version ==
				eEngineSupportedVulkanVersion::kVulkan_Latest,
			"something is wrong! you specified renderer as Vulkan Latest and "
			"your version must be kVulkan_Latest but it is not that!");

		status = true;
	}
	case eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan_SpecifiedByUser:
	{
		if (this->m_engine_current_vulkan_version ==
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
	const ktk::string& your_argument) const noexcept
{
	return std::find_if(this->m_parsed_command_line_arguments.begin(),
			   this->m_parsed_command_line_arguments.end(),
			   [your_argument](const ktk::string& argument) -> bool {
				   return argument == your_argument;
			   }) != this->m_parsed_command_line_arguments.end();
}

bool ktkEngineConfig::IsUserSpecifiedValidRenderer(void) const noexcept
{
	ktk::size_t validation{0};
	for (const auto& argument : this->m_parsed_command_line_arguments)
	{
		if (argument.get_as_is().starts_with(KOTEK_TEXT("--render_")))
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
		if (argument.get_as_is().starts_with(KOTEK_TEXT("--render_gl")))
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
		if (argument.get_as_is().starts_with(KOTEK_TEXT("--render_dx")))
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
		if (argument.get_as_is().starts_with(KOTEK_TEXT("--render_vk")))
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

	this->m_parsed_command_line_arguments =
		ktk::vector<ktk::string>(this->m_argv, this->m_argv + this->m_argc);
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK