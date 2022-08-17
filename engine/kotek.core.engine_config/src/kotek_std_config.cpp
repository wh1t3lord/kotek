#include "../include/kotek_std_config.h"

namespace Kotek
{
	namespace Core
	{
		ktkEngineConfig::ktkEngineConfig(void) :
			m_argc{-1}, m_argv{}, m_is_running{true}
		{
		}

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
			auto for_validation_purpose = this->GetRenderFeature();

#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("current renderer id: {}", static_cast<ktk::enum_base_t>(for_validation_purpose));
#endif

			if (this->IsFeatureEnabled(
					eEngineFeature::kEngine_Render_Renderer_OpenGL3_3))
			{
				return kRenderer_OpenGL3_3_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_OpenGL4_6))
			{
				return kRenderer_OpenGL4_6_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_Vulkan))
			{
				return kRenderer_Vulkan_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_12))
			{
				return kRenderer_DirectX_12_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_11))
			{
				return kRenderer_DirectX_11_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_10))
			{
				return kRenderer_DirectX_10_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_9))
			{
				return kRenderer_DirectX_9_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_8))
			{
				return kRenderer_DirectX_8_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_DirectX_7))
			{
				return kRenderer_DirectX_7_Name;
			}
			else if (this->IsFeatureEnabled(
						 eEngineFeature::kEngine_Render_Renderer_Software))
			{
				return kRenderer_Software_Name;
			}

			KOTEK_ASSERT(false, "can't obtain render name");

			return kRenderer_Unknown_Name;
		}

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

			KOTEK_ASSERT(validation_count > 0,
				"you must have some initialized renderer!");

			KOTEK_ASSERT(validation_count == 1,
				"You can't have more than one initialized renderer.");

			return result;
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
			this->m_user_dll =
				ktk::dll::shared_library(path_to_library.c_str());
		}

		void* ktkEngineConfig::Get_UserLibrary(void) noexcept
		{
			return &this->m_user_dll;
		}

		bool ktkEngineConfig::IsFeatureRender(
			eEngineFeature feature) const noexcept
		{
			return (feature >
					   eEngineFeature::kEngine_Render_Renderer_DirectX) &&
				(feature <= eEngineFeature::kEngine_Render_Renderer_Software);
		}

		void ktkEngineConfig::Parse_CommandLine(void) noexcept 
		{
			KOTEK_ASSERT(this->m_argc != -1,
				"you must set argc before calling set argv method!");

			this->m_parsed_command_line_arguments = ktk::vector<ktk::string>(
				this->m_argv, this->m_argv + this->m_argc);
		}
	} // namespace Core
} // namespace Kotek