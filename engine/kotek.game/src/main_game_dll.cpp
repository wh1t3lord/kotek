#include <kotek.core/include/kotek_core.h>
#include <kotek.core/include/kotek_main_manager.h>
#include <kotek.core/include/kotek_std.h>
#include <kotek.render/include/kotek_render.h>
#include "../include/kotek_callbacks.h"
#include "../include/kotek_engine.h"
#include "../include/kotek_game.h"

#ifdef KOTEK_DEBUG
	#define BOOST_TEST_MODULE kotek_engine_test_module
	#define BOOST_TEST_ALTERNATIVE_INIT_API
	#include <boost/test/unit_test.hpp>
#endif

#include <kotek.core/include/kotek_file.h>

bool isUserCallbackUpdateFunctionContainsLoop = false;

using ktkUserCallbackInitialize = bool(Kotek::Core::ktkMainManager*);
using ktkUserCallbackShutdown = bool(Kotek::Core::ktkMainManager*);
using ktkUserCallbackUpdate = void(Kotek::Core::ktkMainManager*);
using ktkUserCallbackInitializeRender = bool(Kotek::Core::ktkMainManager*);

Kotek::ktk::function<ktkUserCallbackInitialize>
	p_user_callback_initialize_game_library;
Kotek::ktk::function<ktkUserCallbackShutdown>
	p_user_callback_shutdown_game_library;
Kotek::ktk::function<ktkUserCallbackUpdate> p_user_callback_update_game_library;
Kotek::ktk::function<ktkUserCallbackInitializeRender>
	p_user_callback_initialize_render_from_game_library;

namespace Kotek
{
	namespace Game
	{
		bool registerCommands(Core::ktkMainManager& main_manager) noexcept
		{
			return true;
		}

		bool InitializeModule_Game(Core::ktkMainManager& main_manager)
		{
			auto path_to_system_json =
				main_manager.GetFileSystem()->GetFolderByEnum(
					Core::folder_index_t::kFolderIndex_Root);

			path_to_system_json.append_path("sys_info.json");

			Core::ktkFile file;

			KOTEK_ASSERT(file.Load(main_manager, path_to_system_json),
				"you must load file successfully! Can't load sys_info.json");

			const auto& field_initialize_callback_name =
				file.GetString(Core::kSysInfoFieldName_InitializeCallback);
			const auto& field_shutdown_callback_name =
				file.GetString(Core::kSysInfoFieldName_ShutdownCallback);
			const auto& field_update_callback_name =
				file.GetString(Core::kSysInfoFieldName_UpdateCallback);

#ifdef KOTEK_PLATFORM_WINDOWS
			const auto& field_library_name =
				file.GetString(Core::kSysInfoFieldName_UserLibraryNameWindows);
#elif KOTEK_PLATFORM_LINUX
			KOTEK_ASSERT(false, "we don't test such feature, but it supposes to support on Linux platform too");
#endif
			const auto& field_initialize_render_callback_name = file.GetString(
				Core::kSysInfoFieldName_InitializeCallback_Render);

			KOTEK_ASSERT(field_library_name.empty() == false,
				"you can't have an invalid name of library, because you need "
				"to load it!!!");

			auto executable_path = ktk::dll::program_location().parent_path();
			ktk::string resulted_path = executable_path.string();
			
			resulted_path.append_path(field_library_name);

			main_manager.LoadUserGameLibrary(resulted_path);
			const auto& user_dll = main_manager.GetUserLibrary();

			
			p_user_callback_initialize_game_library =
				user_dll.get<ktkUserCallbackInitialize>(field_initialize_callback_name.get_as_legacy().c_str());

			p_user_callback_shutdown_game_library =
				user_dll.get<ktkUserCallbackShutdown>(
					field_shutdown_callback_name.get_as_legacy().c_str());

			p_user_callback_update_game_library =
				user_dll.get<ktkUserCallbackUpdate>(field_update_callback_name.get_as_legacy().c_str());

			p_user_callback_initialize_render_from_game_library =
				user_dll.get<ktkUserCallbackInitializeRender>(field_initialize_render_callback_name.get_as_legacy().c_str());

			KOTEK_ASSERT(p_user_callback_initialize_game_library != nullptr,
				"can't obtain function from game user library {}: {}",
				field_library_name.get_as_is(),
				field_initialize_callback_name.get_as_is());

			KOTEK_ASSERT(p_user_callback_shutdown_game_library != nullptr,
				"can't obtain function from game user library {}: {}",
				field_library_name.get_as_is(),
				field_shutdown_callback_name.get_as_is());

			KOTEK_ASSERT(p_user_callback_update_game_library != nullptr,
				"can't obtain function from game user library {}: {}",
				field_library_name.get_as_is(),
				field_update_callback_name.get_as_is());

			KOTEK_ASSERT(
				p_user_callback_initialize_render_from_game_library != nullptr,
				"can't obtain function from game user library {}: {}",
				field_library_name.get_as_is(),
				field_update_callback_name.get_as_is());

			if (p_user_callback_initialize_game_library)
				p_user_callback_initialize_game_library(&main_manager);

			return true;
		}

		bool ShutdownModule_Game(Core::ktkMainManager& main_manager)
		{
			if (p_user_callback_shutdown_game_library)
				p_user_callback_shutdown_game_library(&main_manager);

			main_manager.UnLoadUserGameLibrary();

			return true;
		}
	} // namespace Game

	namespace Engine
	{
		void ValidateMainManager(Core::ktkMainManager& main_manager) noexcept
		{
			// TODO: keep in updated form

			KOTEK_ASSERT(main_manager.GetFileSystem(),
				"you didn't initialize filesystem manager field in main "
				"manager");
			KOTEK_ASSERT(main_manager.GetInput(),
				"you didn't initialize input manager field in "
				"main manager");

			if (main_manager.IsContainsConsoleCommandLineArgument(
					Core::kConsoleCommandArg_Editor) == false)
			{
				KOTEK_ASSERT(main_manager.getRenderDevice(),
					"you didn't initialize render device manager field in main "
					"manager");
				KOTEK_ASSERT(main_manager.GetRenderResourceManager(),
					"you didn't initialize render resource manager in main "
					"manager");
				KOTEK_ASSERT(main_manager.getRenderSwapchainManager(),
					"you didn't initialize render swapchain manager in main "
					"manager");
			}

			KOTEK_ASSERT(main_manager.GetGameManager(),
				"you didn't initialize game manager in your game library or "
				"you forgot to pass game manager to main manager");
		}

		void PrintCompiler(void) noexcept
		{
#if defined(__llvm__) || defined(__clang__)
			KOTEK_MESSAGE("Compiled with: Clang {}",
				Kotek::ktk::cast::to_string(__clang_version__));

#elif (_MSC_VER > 0)

			// _MSC_VER description took from
			// https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-160

	#if (_MSC_VER == 1200)
			KOTEK_MESSAGE("Compiled with: Visual Studio 6.0");
	#elif (_MSC_VER == 1300)
			KOTEK_MESSAGE("Compiled with: Visual Studio .NET 2002 (7.0)");
	#elif (_MSC_VER == 1310)
			KOTEK_MESSAGE("Compiled with: Visual Studio .NET 2003 (7.1)");
	#elif (_MSC_VER == 1400)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2005 (8.0)");
	#elif (_MSC_VER == 1500)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2008 (9.0)");
	#elif (_MSC_VER == 1600)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2010 (10.0)");
	#elif (_MSC_VER == 1700)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2012 (11.0)");
	#elif (_MSC_VER == 1800)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2013 (12.0)");
	#elif (_MSC_VER == 1900)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2015 (14.0)");
	#elif (_MSC_VER == 1910)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2017 RTW (15.0)");
	#elif (_MSC_VER == 1911)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2017 version 15.3");
	#elif (_MSC_VER == 1912)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2017 version 15.5");
	#elif (_MSC_VER == 1913)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2017 version 15.6");
	#elif (_MSC_VER == 1914)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2017 version 15.7");
	#elif (_MSC_VER == 1915)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2017 version 15.8");
	#elif (_MSC_VER == 1916)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2017 version 15.9");
	#elif (_MSC_VER == 1920)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2019 RTW (16.0)");
	#elif (_MSC_VER == 1921)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.1");
	#elif (_MSC_VER == 1922)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.2");
	#elif (_MSC_VER == 1923)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.3");
	#elif (_MSC_VER == 1924)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.4");
	#elif (_MSC_VER == 1925)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.5");
	#elif (_MSC_VER == 1926)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.6");
	#elif (_MSC_VER == 1927)
			KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.7");
	#elif (_MSC_VER == 1928)
			KOTEK_MESSAGE(
				"Compiled with: Visual Studio 2019 version 16.8, 16.9");
	#elif (_MSC_VER == 1929)
			KOTEK_MESSAGE(
				"Compiled with: Visual Studio 2019 version 16.10, 16.11");
	#endif

#endif
		}

		bool InitializeEngine(Core::ktkMainManager& main_manager)
		{
			PrintCompiler();
			
			Core::InitializeModule_Core(main_manager);

			// TODO: restore when you implement ImGui
			Game::registerCommands(main_manager);

			Game::InitializeModule_Game(main_manager);

			Render::InitializeModule_Render(main_manager);

			if (p_user_callback_initialize_render_from_game_library)
				p_user_callback_initialize_render_from_game_library(
					&main_manager);

			Engine::ValidateMainManager(main_manager);

#ifdef KOTEK_DEBUG
	#ifdef KOTEK_USE_TESTS_RUNTIME
			KOTEK_MESSAGE("UNIT TESTING UNIT TESTING UNIT "
						  "TESTING\n\n\n\n\n\n\n\n\n\n\n\n");

			ktk::vector<const char*> argv_test = {"C:/test"};
			auto status = boost::unit_test_framework::unit_test_main(
				init_unit_test, 1, const_cast<char**>(argv_test.data()));

			KOTEK_ASSERT(status == 0, "you have got failed tests");

			KOTEK_MESSAGE("\n\n\n\n\nUNIT TESTING UNIT TESTING UNIT TESTING");
	#endif
#endif

			return true;
		}

		bool ExecuteEngine(Core::ktkMainManager& main_manager)
		{
			p_user_callback_update_game_library(&main_manager);

			return true;
		}

		bool ShutdownEngine(Core::ktkMainManager& main_manager)
		{
			main_manager.GetProfiler()->Shutdown();

			Core::ShutdownModule_Core();
			Render::ShutdownModule_Render(main_manager);
			Game::ShutdownModule_Game(main_manager);

			return true;
		}

		bool serializeEngine(void) { return true; }

		bool deserializeEngine(void) { return true; }
	} // namespace Engine
} // namespace Kotek
