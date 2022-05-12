#include "../include/kotek_main_manager.h"
#include "../include/kotek_file.h"

namespace Kotek
{
	namespace Core
	{
		ktkMainManager::ktkMainManager(int argc, char** argv) :
			m_parsed_command_line_arguments(argv, argv + argc),
			m_is_running(true)
		{
			this->initialize(argc, argv);
		}

		ktkMainManager::~ktkMainManager(void) { this->shutdown(); }

		void ktkMainManager::initialize(int argc, char** argv)
		{
			this->m_argc = argc;
			this->m_argv = argv;

			this->m_manager_filesystem = std::make_shared<ktkFileSystem>();
			this->m_manager_input = std::make_shared<ktkInput>();
			this->m_manager_profiler = std::make_shared<ktkProfiler>();

			this->m_manager_filesystem->Initialize();
			this->m_manager_input->Initialize();

			this->m_manager_profiler->Initialize(KOTEK_TEXT("kotek-engine"),
				this->GetFileSystem()->GetFolderByEnum(
					folder_index_t::kFolderIndex_UserData));
		}

		void ktkMainManager::shutdown(void)
		{
			this->m_manager_filesystem->Shutdown();
			this->m_manager_input->Shutdown();
		}

		ktkProfiler* ktkMainManager::GetProfiler(void) const noexcept
		{
			return this->m_manager_profiler.get();
		}

		ktkFileSystem* ktkMainManager::GetFileSystem(void) const noexcept
		{
			return static_cast<ktkFileSystem*>(
				this->m_manager_filesystem.get());
		}

		ktkInput* ktkMainManager::GetInput(void) const noexcept
		{
			return static_cast<ktkInput*>(this->m_manager_input.get());
		}

		ktkIGameManager* ktkMainManager::GetGameManager(void) const noexcept
		{
			return this->m_p_game_manager;
		}

		void ktkMainManager::SetGameManager(
			ktkIGameManager* p_game_manager) noexcept
		{
			this->m_p_game_manager = p_game_manager;
		}

		ktkIResourceManager* ktkMainManager::GetResourceManager(
			void) const noexcept
		{
			return this->m_p_resource_manager;
		}

		void ktkMainManager::SetResourceManager(
			ktkIResourceManager* p_manager) noexcept
		{
			this->m_p_resource_manager = p_manager;
		}

		ktkIRenderDevice* ktkMainManager::getRenderDevice(void) const noexcept
		{
			return this->m_manager_render_device.get();
		}

		void ktkMainManager::setRenderDevice(
			ktk::shared_ptr<ktkIRenderDevice> pointer) noexcept
		{
			this->m_manager_render_device = pointer;
		}

		ktkIRenderResourceManager* ktkMainManager::GetRenderResourceManager(
			void) const noexcept
		{
			return this->m_manager_render_resource.get();
		}

		void ktkMainManager::SetRenderResourceManager(
			ktk::shared_ptr<ktkIRenderResourceManager> pointer) noexcept
		{
			this->m_manager_render_resource = pointer;
		}

		ktkIRenderSwapchain* ktkMainManager::getRenderSwapchainManager(
			void) const noexcept
		{
			return this->m_manager_swapchain.get();
		}

		void ktkMainManager::setRenderSwapchainManager(
			ktk::shared_ptr<ktkIRenderSwapchain> pointer) noexcept
		{
			this->m_manager_swapchain = pointer;
		}

		bool ktkMainManager::IsFeatureEnabled(eEngineFeature id) const noexcept
		{
			if (this->m_engine_flags.find(id) == this->m_engine_flags.end())
			{
				KOTEK_MESSAGE_WARNING(
					"engine doesn't register feature by id: [{}]", static_cast<ktk::enum_base_t>(id));

				return false;
			}

			return this->m_engine_flags.at(id);
		}

		void ktkMainManager::SetFeatureStatus(
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

		ktk::string ktkMainManager::GetRenderName(void) const noexcept
		{
			if (this->IsFeatureEnabled(
					eEngineFeature::kEngine_Render_Renderer_OpenGL))
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

		eEngineFeature ktkMainManager::GetRenderFeature(void) const noexcept
		{
			if (this->IsFeatureEnabled(
					eEngineFeature::kEngine_Render_Renderer_OpenGL))
			{
				return eEngineFeature::kEngine_Render_Renderer_OpenGL;
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

		bool ktkMainManager::IsCurrentRenderLegacy(void) const noexcept
		{
			return !this->IsCurrentRenderModern();
		}

		bool ktkMainManager::IsCurrentRenderModern(void) const noexcept
		{
			auto render_type = this->GetRenderFeature();

			return (render_type ==
					   eEngineFeature::kEngine_Render_Renderer_DirectX_12) ||
				(render_type == eEngineFeature::kEngine_Render_Renderer_Vulkan);
		}

		int ktkMainManager::getARGC(void) const noexcept
		{
			return this->m_argc;
		}

		char** ktkMainManager::getARGV(void) const noexcept
		{
			return this->m_argv;
		}

		bool ktkMainManager::IsContainsConsoleCommandLineArgument(
			const ktk::string& your_argument) const noexcept
		{
			return std::find_if(this->m_parsed_command_line_arguments.begin(),
					   this->m_parsed_command_line_arguments.end(),
					   [your_argument](const ktk::string& argument) -> bool {
						   return argument == your_argument;
					   }) != this->m_parsed_command_line_arguments.end();
		}

		bool ktkMainManager::LoadUserGameLibrary(
			const ktk::string& library_name) noexcept
		{
			this->m_user_dll.load(library_name.get_as_legacy().c_str());

			return true;
		}

		void ktkMainManager::UnLoadUserGameLibrary(void) noexcept
		{
			this->m_user_dll.unload();
		}

		const ktk::dll::shared_library& ktkMainManager::GetUserLibrary(
			void) const noexcept
		{
			return this->m_user_dll;
		}

		bool ktkMainManager::IsApplicationWorking(void) const noexcept
		{
			return this->m_is_running;
		}

		void ktkMainManager::SetApplicationWorking(bool status) noexcept
		{
			this->m_is_running = status;
		}

		bool ktkMainManager::IsFeatureRender(
			eEngineFeature feature) const noexcept
		{
			return (feature ==
					   eEngineFeature::kEngine_Render_Renderer_Software) ||
				(feature == eEngineFeature::kEngine_Render_Renderer_OpenGL) ||
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
