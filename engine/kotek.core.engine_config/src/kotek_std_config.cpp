#include "../include/kotek_std_config.h"

namespace Kotek
{
	namespace Core
	{
		ktkEngineConfig::ktkEngineConfig(void) : m_argc{}, m_argv{} {}

		ktkEngineConfig::~ktkEngineConfig(void) {}

		void ktkEngineConfig::Initialize(void) {}

		void ktkEngineConfig::Shutdown(void) {}

		bool ktkEngineConfig::IsFeatureEnabled(eEngineFeature id) const noexcept
		{
			if (this->m_engine_flags.find(id) == this->m_engine_flags.end())
			{
				KOTEK_MESSAGE_WARNING(
					"engine doesn't register feature by id: [{}]",
					static_cast<ktk::enum_base_t>(id));

				return false;
			}

			return this->m_engine_flags.at(id);
		}

		void ktkEngineConfig::SetFeatureStatus(
			eEngineFeature id, bool status) noexcept
		{
			this->m_engine_flags[id] = status;

			if (this->IsFeatureRender(id))
			{
				for (const auto& [feature_id, feature_status] :
					this->m_engine_flags)
				{
					if (feature_id != id)
					{
						if (this->IsFeatureRender(feature_id))
						{
							this->m_engine_flags[feature_id] = false;
						}
					}
				}
			}
		}

		ktk::string ktkEngineConfig::GetRenderName(void) const noexcept
		{
			if (this->IsFeatureEnabled(
					eEngineFeature::kEngine_Render_Renderer_OpenGL3_3))
			{
				return kRenderName_OpenGL;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_OpenGL4_6))
			{
				return kRenderName_OpenGL;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_Vulkan))
			{
				return kRenderName_Vulkan;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_12))
			{
				return kRenderName_DirectX12;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_11))
			{
				return kRenderName_DirectX11;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_9))
			{
				return kRenderName_DirectX9;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_Software))
			{
				return kRenderName_Software;
			}

			KOTEK_ASSERT(false, "can't obtain render name");

			return ktk::string("RENDER_NAME_UNDEFINED");
		}

		eEngineFeature ktkEngineConfig::GetRenderFeature(void) const noexcept
		{
			if (this->IsFeatureEnabled(
					eEngineFeature::kEngine_Render_Renderer_OpenGL3_3))
			{
				return eEngineFeature::kEngine_Render_Renderer_OpenGL3_3;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_OpenGL4_6))
			{
				return eEngineFeature::kEngine_Render_Renderer_OpenGL4_6;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_Vulkan))
			{
				return eEngineFeature::kEngine_Render_Renderer_Vulkan;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_12))
			{
				return eEngineFeature::kEngine_Render_Renderer_DirectX_12;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_11))
			{
				return eEngineFeature::kEngine_Render_Renderer_DirectX_11;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_9))
			{
				return eEngineFeature::kEngine_Render_Renderer_DirectX_9;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_Software))
			{
				return eEngineFeature::kEngine_Render_Renderer_Software;
			}

			KOTEK_ASSERT(false, "can't return undefined renderer...");

			return eEngineFeature::kEngine_Feature_Unknown;
		}

		bool ktkEngineConfig::IsCurrentRenderLegacy(void) const noexcept
		{
			return !this->IsCurrentRenderModern();
		}

		bool ktkEngineConfig::IsCurrentRenderModern(void) const noexcept
		{
			auto render_type = this->GetRenderFeature();

			return (render_type ==
					   eEngineFeature::kEngine_Render_Renderer_DirectX_12) ||
				(render_type == eEngineFeature::kEngine_Render_Renderer_Vulkan);
		}

		int ktkEngineConfig::GetARGC(void) const noexcept
		{
			return this->m_argc;
		}

		char** ktkEngineConfig::GetARGV(void) const noexcept
		{
			return this->m_argv;
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

		bool ktkEngineConfig::IsFeatureRender(
			eEngineFeature feature) const noexcept
		{
			return (feature ==
					   eEngineFeature::kEngine_Render_Renderer_Software) ||
				(feature ==
					eEngineFeature::kEngine_Render_Renderer_OpenGL3_3) ||
				(feature ==
					eEngineFeature::kEngine_Render_Renderer_OpenGL4_6) ||
				(feature ==
					eEngineFeature::kEngine_Render_Renderer_DirectX_9) ||
				(feature ==
					eEngineFeature::kEngine_Render_Renderer_DirectX_11) ||
				(feature ==
					eEngineFeature::kEngine_Render_Renderer_DirectX_12) ||
				(feature == eEngineFeature::kEngine_Render_Renderer_Vulkan);
		}
	} // namespace Core
} // namespace Kotek