#include "../include/kotek_std_config.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkEngineConfig::ktkEngineConfig(void) :
	m_argc{-1}, m_argv{}, m_is_running{true}
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
	KOTEK_ASSERT(
		id != eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX &&
			id != eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL,
		"you can't pass system flags for setting, it doesn't make any sense");

	if (status)
	{
		// we must have only one (maximum two, the second flag determine general 
		// disable DirectX
		eEngineFeatureRenderer render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_12;
		this->m_engine_feature_renderer_flags &= ~render_feature;
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_11;
		this->m_engine_feature_renderer_flags &= ~render_feature;
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_10;
		this->m_engine_feature_renderer_flags &= ~render_feature;
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_9;
		this->m_engine_feature_renderer_flags &= ~render_feature;
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_8;
		this->m_engine_feature_renderer_flags &= ~render_feature;
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_7;
		this->m_engine_feature_renderer_flags &= ~render_feature;

		// disable OpenGL
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL1_0;
		this->m_engine_feature_renderer_flags &= ~render_feature;
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL2_0;
		this->m_engine_feature_renderer_flags &= ~render_feature;
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL3_3;
		this->m_engine_feature_renderer_flags &= ~render_feature;
		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL4_6;
		this->m_engine_feature_renderer_flags &= ~render_feature;

		render_feature = eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan;
		this->m_engine_feature_renderer_flags &= ~render_feature;

		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_Software;
		this->m_engine_feature_renderer_flags &= ~render_feature;

		render_feature = eEngineFeatureRenderer::kEngine_Render_Renderer_ANGLE;
		this->m_engine_feature_renderer_flags &= ~render_feature;

		render_feature =
			eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX;
		this->m_engine_feature_renderer_flags &= ~render_feature;

		render_feature = eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL;
		this->m_engine_feature_renderer_flags &= ~render_feature;

		this->m_engine_feature_renderer_flags |= render_feature;

		if (render_feature >
				eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX &&
			render_feature <
				eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL)
		{
			this->m_engine_feature_renderer_flags |=
				eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX;
		}
		else if (render_feature >
				eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL &&
			render_feature <
				eEngineFeatureRenderer::kEngine_Render_Renderer_Software)
		{
			this->m_engine_feature_renderer_flags |=
				eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL;
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

ktk::string ktkEngineConfig::GetRenderName(void) const noexcept
{
	auto for_validation_purpose = this->GetEngineFeatureRenderer();

#ifdef KOTEK_DEBUG
	KOTEK_MESSAGE("current renderer id: {}",
		static_cast<ktk::enum_base_t>(for_validation_purpose));
#endif

	if (this->IsFeatureEnabled(
			eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL3_3))
	{
		return kRenderer_OpenGL3_3_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_OpenGL4_6))
	{
		return kRenderer_OpenGL4_6_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan))
	{
		return kRenderer_Vulkan_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_12))
	{
		return kRenderer_DirectX_12_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_11))
	{
		return kRenderer_DirectX_11_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_10))
	{
		return kRenderer_DirectX_10_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_9))
	{
		return kRenderer_DirectX_9_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_8))
	{
		return kRenderer_DirectX_8_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_7))
	{
		return kRenderer_DirectX_7_Name;
	}
	else if (this->IsFeatureEnabled(
				 eEngineFeatureRenderer::kEngine_Render_Renderer_Software))
	{
		return kRenderer_Software_Name;
	}

	KOTEK_ASSERT(false, "can't obtain render name");

	return kRenderer_Unknown_Name;
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

	return (render_type ==
			   eEngineFeatureRenderer::kEngine_Render_Renderer_DirectX_12) ||
		(render_type == eEngineFeatureRenderer::kEngine_Render_Renderer_Vulkan);
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