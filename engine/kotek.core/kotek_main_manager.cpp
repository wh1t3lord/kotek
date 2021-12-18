#include "kotek_main_manager.h"
#include "kotek_file.h"

namespace Kotek
{
	namespace Core
	{
		ktkMainManager::ktkMainManager(int argc, char** argv) :
			m_parsed_command_line_arguments(argv, argv + argc)
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

		kotek_i_render_device* ktkMainManager::getRenderDevice(
			void) const noexcept
		{
			return this->m_manager_render_device.get();
		}

		void ktkMainManager::setRenderDevice(
			ktk::shared_ptr<kotek_i_render_device> pointer) noexcept
		{
			this->m_manager_render_device = pointer;
		}

		kotek_i_render_resource_manager*
		ktkMainManager::getRenderResourceManager(void) const noexcept
		{
			return this->m_manager_render_resource.get();
		}

		void ktkMainManager::setRenderResourceManager(
			ktk::shared_ptr<kotek_i_render_resource_manager> pointer) noexcept
		{
			this->m_manager_render_resource = pointer;
		}

		kotek_i_render_swapchain* ktkMainManager::getRenderSwapchainManager(
			void) const noexcept
		{
			return this->m_manager_swapchain.get();
		}

		void ktkMainManager::setRenderSwapchainManager(
			ktk::shared_ptr<kotek_i_render_swapchain> pointer) noexcept
		{
			this->m_manager_swapchain = pointer;
		}

		bool ktkMainManager::isFeatureEnabled(
			engine_feature_index_t id) const noexcept
		{
			if (this->m_engine_flags.find(id) == this->m_engine_flags.end())
			{
				KOTEK_MESSAGE(
					"engine doesn't register feature by id: [{}]", id);
				return false;
			}

			return this->m_engine_flags.at(id);
		}

		void ktkMainManager::setFeatureStatus(
			engine_feature_index_t id, bool status) noexcept
		{
			this->m_engine_flags[id] = status;
		}

		int ktkMainManager::getARGC(void) const noexcept
		{
			return this->m_argc;
		}

		char** ktkMainManager::getARGV(void) const noexcept
		{
			return this->m_argv;
		}

		void ktkMainManager::LoadDynamicLibraryUserGame(
			const ktk::string& library_name) noexcept
		{
			this->m_dynamic_library_user_game.SetLibraryName(library_name);
			this->m_dynamic_library_user_game.Load();
		}

		void ktkMainManager::UnLoadDynamicLibraryUserGame() noexcept
		{
			this->m_dynamic_library_user_game.UnLoad();
		}

#ifdef KOTEK_PLATFORM_WINDOWS
		FARPROC ktkMainManager::GetUserCallbackFromUserGameLibrary(
			const ktk::string& function_name) noexcept
		{
			KOTEK_ASSERT(function_name.empty() == false,
				"you can't pass an empty function name");

			return this->m_dynamic_library_user_game.GetUserCallback(
				function_name);
		}
#elif KOTEK_PLATFORM_LINUX
#endif

		bool ktkMainManager::IsContainsConsoleCommandLineArgument(
			const ktk::string& your_argument) const noexcept
		{
			return std::find_if(this->m_parsed_command_line_arguments.begin(),
					   this->m_parsed_command_line_arguments.end(),
					   [your_argument](const ktk::string& argument) -> bool {
						   return argument == your_argument;
					   }) != this->m_parsed_command_line_arguments.end();
		}

	} // namespace Core
} // namespace Kotek
