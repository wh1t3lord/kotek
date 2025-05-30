#include "../include/kotek_callbacks.h"
#include "../include/kotek_engine.h"
#include "../include/kotek_game.h"
#include <kotek.render/include/kotek_render.h>

#ifdef KOTEK_DEBUG
	#include <gtest/gtest.h>
#endif

bool isUserCallbackUpdateFunctionContainsLoop = false;

#ifdef KOTEK_USE_DEVELOPMENT_TYPE_SHARED
using ktkUserCallbackInitialize = bool(kun_kotek kun_core ktkMainManager*);
using ktkUserCallbackShutdown = bool(kun_kotek kun_core ktkMainManager*);
using ktkUserCallbackUpdate = void(kun_kotek kun_core ktkMainManager*);
using ktkUserCallbackInitializeRender = bool(
	kun_kotek kun_core ktkMainManager*);

Kotek::ktk::function<ktkUserCallbackInitialize>
	p_user_callback_initialize_game_library;
Kotek::ktk::function<ktkUserCallbackShutdown>
	p_user_callback_shutdown_game_library;
Kotek::ktk::function<ktkUserCallbackUpdate> p_user_callback_update_game_library;
Kotek::ktk::function<ktkUserCallbackInitializeRender>
	p_user_callback_initialize_render_from_game_library;
#endif

#ifdef KOTEK_USE_DEVELOPMENT_TYPE_STATIC
	#include KOTEK_USER_GAME_MODULE_HEADER_FILE
#endif

KOTEK_BEGIN_NAMESPACE_KOTEK

namespace Game
{
	bool registerCommands(Core::ktkMainManager* p_main_manager) noexcept
	{
		return true;
	}

	bool InitializeModule_Game(Core::ktkMainManager* p_main_manager)
	{
		if (p_main_manager->Get_Splash())
		{
			p_main_manager->Get_Splash()->Set_Text("[game]: init");
			p_main_manager->Get_Splash()->Set_Progress();
		}

#ifdef KOTEK_USE_DEVELOPMENT_TYPE_SHARED
		auto path_to_system_json =
			p_main_manager->GetFileSystem()->GetFolderByEnum(
				Core::eFolderIndex::kFolderIndex_Root);

		path_to_system_json /= "sys_info.json";

		Core::ktkFileText file;

		Core::ktkResourceLoaderFile_Text resource_loader_text(p_main_manager);

		auto status = resource_loader_text.Load(
			path_to_system_json, kun_core ktkResourceHandle(&file, true));
		KOTEK_ASSERT(status, "can't load text: {}",
			reinterpret_cast<const char*>(
				path_to_system_json.u8string().c_str()));

		const auto& field_initialize_callback_name =
			file.Get<ktk::ustring>(Core::kSysInfoFieldName_InitializeCallback);
		const auto& field_shutdown_callback_name =
			file.Get<ktk::ustring>(Core::kSysInfoFieldName_ShutdownCallback);
		const auto& field_update_callback_name =
			file.Get<ktk::ustring>(Core::kSysInfoFieldName_UpdateCallback);

		const auto& field_library_name =
			file.Get<ktk::ustring>(Core::kSysInfoFieldName_UserLibraryName);
		const auto& field_initialize_render_callback_name =
			file.Get<ktk::ustring>(
				Core::kSysInfoFieldName_InitializeCallback_Render);

		KOTEK_ASSERT(field_library_name.empty() == false,
			"you can't have an invalid name of library, because you need "
			"to load it!!!");

		kun_kotek static_path_t path_to_user_dll;
		{
			const auto& root_path = ktk::dll::program_location().parent_path();
			path_to_user_dll = root_path.c_str();
			path_to_user_dll /= field_library_name;
		}

		p_main_manager->Get_EngineConfig()->Set_UserLibrary(path_to_user_dll);
		auto* p_user_dll = static_cast<ktk::dll::shared_library*>(
			p_main_manager->Get_EngineConfig()->Get_UserLibrary());

		p_user_callback_initialize_game_library =
			p_user_dll->get<ktkUserCallbackInitialize>(
				reinterpret_cast<const char*>(
					field_initialize_callback_name.c_str()));

		p_user_callback_shutdown_game_library =
			p_user_dll->get<ktkUserCallbackShutdown>(
				reinterpret_cast<const char*>(
					field_shutdown_callback_name.c_str()));

		p_user_callback_update_game_library =
			p_user_dll->get<ktkUserCallbackUpdate>(
				reinterpret_cast<const char*>(
					field_update_callback_name.c_str()));

		p_user_callback_initialize_render_from_game_library =
			p_user_dll->get<ktkUserCallbackInitializeRender>(
				reinterpret_cast<const char*>(
					field_initialize_render_callback_name.c_str()));

		KOTEK_ASSERT(p_user_callback_initialize_game_library != nullptr,
			"can't obtain function from game user library {}: {}",
			reinterpret_cast<const char*>(field_library_name.c_str()),
			reinterpret_cast<const char*>(
				field_initialize_callback_name.c_str()));

		KOTEK_ASSERT(p_user_callback_shutdown_game_library != nullptr,
			"can't obtain function from game user library {}: {}",
			reinterpret_cast<const char*>(field_library_name.c_str()),
			reinterpret_cast<const char*>(
				field_shutdown_callback_name.c_str()));

		KOTEK_ASSERT(p_user_callback_update_game_library != nullptr,
			"can't obtain function from game user library {}: {}",
			reinterpret_cast<const char*>(field_library_name.c_str()),
			reinterpret_cast<const char*>(field_update_callback_name.c_str()));

		KOTEK_ASSERT(
			p_user_callback_initialize_render_from_game_library != nullptr,
			"can't obtain function from game user library {}: {}",
			reinterpret_cast<const char*>(field_library_name.c_str()),
			reinterpret_cast<const char*>(field_update_callback_name.c_str()));

		if (p_user_callback_initialize_game_library)
		{
			p_user_callback_initialize_game_library(p_main_manager);
			KOTEK_ASSERT(p_main_manager->GetGameManager(),
				"you must set game manager to main manager!!!!");
		}
#elif defined(KOTEK_USE_DEVELOPMENT_TYPE_STATIC)
		::KOTEK_USER_FUNCTION_INITIALIZE_MODULE_GAME(p_main_manager);
		KOTEK_ASSERT(p_main_manager->GetGameManager(),
			"you must set game manager to main manager!");
#else
	#error Unknown development type, see what you specified in your cmd/cmake GUI. The macro accepts only two variables STATIC or SHARED
#endif

		return true;
	}

	bool ShutdownModule_Game(Core::ktkMainManager* p_main_manager)
	{
#ifdef KOTEK_USE_DEVELOPMENT_TYPE_SHARED
		if (p_user_callback_shutdown_game_library)
			p_user_callback_shutdown_game_library(p_main_manager);
#elif defined(KOTEK_USE_DEVELOPMENT_TYPE_STATIC)
		::KOTEK_USER_FUNCTION_SHUTDOWN_MODULE_GAME(p_main_manager);
#else
	#error Unknown development type, see what you specified in your cmd/cmake GUI. The macro accepts only two variables STATIC or SHARED
#endif
		// TODO: unload with resource manager
		//	p_main_manager.UnLoadUserGameLibrary();

		return true;
	}
} // namespace Game

namespace Engine
{
	void ValidateMainManager(Core::ktkMainManager* p_main_manager) noexcept
	{
		// TODO: keep in updated form

		KOTEK_ASSERT(p_main_manager->GetFileSystem(),
			"you didn't initialize filesystem manager field in main "
			"manager");
		KOTEK_ASSERT(p_main_manager->Get_Input(),
			"you didn't initialize input manager field in "
			"main manager");

		if (p_main_manager->Get_EngineConfig()
				->IsContainsConsoleCommandLineArgument(
					kConsoleCommandArg_Editor) == false)
		{
			KOTEK_ASSERT(p_main_manager->getRenderDevice(),
				"you didn't initialize render device manager field in main "
				"manager");
			KOTEK_ASSERT(p_main_manager->GetRenderResourceManager(),
				"you didn't initialize render resource manager in main "
				"manager");
			KOTEK_ASSERT(p_main_manager->getRenderSwapchainManager(),
				"you didn't initialize render swapchain manager in main "
				"manager");
		}

		KOTEK_ASSERT(p_main_manager->GetGameManager(),
			"you didn't initialize game manager in your game library or "
			"you forgot to pass game manager to main manager");
	}

	void PrintCompiler(void) noexcept
	{
#if defined(__llvm__) || defined(__clang__)
		KOTEK_MESSAGE("Compiled with: Clang {}", __clang_version__);

#elif (_MSC_VER > 0)

		// _MSC_VER description took from
		// https://docs.microsoft.com/en-us/cpp/preprocessor/predefined-macros?view=msvc-160
		// https://learn.microsoft.com/en-us/cpp/overview/compiler-versions?view=msvc-170#service-releases-starting-with-visual-studio-2017

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
		KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.8, 16.9");
	#elif (_MSC_VER == 1929)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2019 version 16.10, 16.11");
	#elif (_MSC_VER == 1930)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 RTW (17.0)");
	#elif (_MSC_VER == 1931)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.1");
	#elif (_MSC_VER == 1932)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.2");
	#elif (_MSC_VER == 1933)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.3");
	#elif (_MSC_VER == 1934)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.4");
	#elif (_MSC_VER == 1935)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.5");
	#elif (_MSC_VER == 1936)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.6");
	#elif (_MSC_VER == 1937)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.7");
	#elif (_MSC_VER == 1938)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.8");
	#elif (_MSC_VER == 1939)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.9");
	#elif (_MSC_VER == 1940)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.10");
	#elif (_MSC_VER == 1941)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.11");
	#elif (_MSC_VER == 1942)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.12");
	#elif (_MSC_VER == 1943)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.13");
	#elif (_MSC_VER == 1944)
		KOTEK_MESSAGE("Compiled with: Visual Studio 2022 version 17.14");
	#else
		#error update this preprocessor and add new _MSC_VER
	#endif

#endif
	}

	void PrintBoostVersion() {}

	bool Serialize_Engine(Core::ktkMainManager* p_main_manager)
	{
		// TODO: remember status from every calling you can't return hardcoded
		// true result...
		kun_core SerializeModule_Core(p_main_manager);

		return true;
	}

	bool Deserialize_Engine(Core::ktkMainManager* p_manager)
	{
		if (p_manager->Get_Splash())
		{
			p_manager->Get_Splash()->Set_Text("[engine]: deserialize");
			p_manager->Get_Splash()->Set_Progress();
		}

		// TODO: remember status from every calling
		kun_core DeserializeModule_Core(p_manager);

		return true;
	}

	bool Hide_SplashWindow(kun_core ktkMainManager* p_manager)
	{
		bool result{};

		if (p_manager)
		{
			if (p_manager->Get_ARGC() > 0)
			{
				if (p_manager->Get_ARGV())
				{
					char** p_args = p_manager->Get_ARGV();
					for (char i = 0; i < p_manager->Get_ARGC(); ++i)
					{
						char* p_argument = p_args[i];

						if (p_argument)
						{
							if (strstr(
									p_argument, kConsoleCommandArg_No_Splash))
							{
								result = true;
							}
						}
					}
				}
			}
		}

		return result;
	}

	bool InitializeEngine(Core::ktkMainManager* p_main_manager)
	{
		if (!p_main_manager)
			return false;

		PrintCompiler();

		bool is_need_to_show_splash_window = Hide_SplashWindow(p_main_manager);

		if (!is_need_to_show_splash_window)
		{
			kun_core ktkWindowSplash* p_window_splash =
				new kun_core ktkWindowSplash();

			p_main_manager->Set_Splash(p_window_splash);

			kun_kotek kun_ktk kun_mt thread thread_splash(
				[p_main_manager]()
				{
					if (p_main_manager)
					{
						kun_kotek kun_core ktkIWindowSplash* p_window =
							p_main_manager->Get_Splash();

						if (p_window)
						{
							if (!p_window->Is_Initialized())
							{
								float max_progress = 150.0f;
								p_window->Create(
									-1, -1, nullptr, &max_progress);
							}

							p_window->Update();
						}
					}
				});
			thread_splash.detach();

			while (p_window_splash->Is_Initialized() == false ||
				p_window_splash->Is_Show() == false)
			{
			}
		}

		if (p_main_manager->Get_Splash())
		{
			p_main_manager->Get_Splash()->Set_Text("init...");
			p_main_manager->Get_Splash()->Set_Progress();
		}

		kun_core InitializeModule_Core(p_main_manager);

		// TODO: must gurantee that write/read operations are not in
		// InitializeStage, InitializeStage only initializes and validates and
		// does nothing with write and read operations

		Deserialize_Engine(p_main_manager);

		// TODO: restore when you implement ImGui
		kun_game registerCommands(p_main_manager);

		kun_game InitializeModule_Game(p_main_manager);

		kun_ui InitializeModule_UI(p_main_manager);

#ifdef KOTEK_USE_DEVELOPMENT_TYPE_SHARED
		if (p_user_callback_initialize_render_from_game_library)
			p_user_callback_initialize_render_from_game_library(p_main_manager);
#elif defined(KOTEK_USE_DEVELOPMENT_TYPE_STATIC)
		::KOTEK_USER_FUNCTION_INITIALIZE / _MODULE_RENDER(p_main_manager);
#else
	#error Unknown development type, see what you specified in your cmd/cmake GUI. The macro accepts only two variables STATIC or SHARED
#endif

		Engine::ValidateMainManager(p_main_manager);

#ifdef KOTEK_DEBUG
	#ifdef KOTEK_USE_TESTS_RUNTIME
		KOTEK_MESSAGE("[UNIT TESTING]");
		int argc = p_main_manager->Get_EngineConfig()->GetARGC();
		testing::FLAGS_gtest_catch_exceptions = true;
		testing::FLAGS_gtest_break_on_failure = true;
		testing::FLAGS_gtest_print_time = true;
		testing::FLAGS_gtest_throw_on_failure = true;
		testing::InitGoogleTest(
			&argc, p_main_manager->Get_EngineConfig()->GetARGV());

		auto status = RUN_ALL_TESTS();
		KOTEK_ASSERT(status == 0, "unit tests failed!");
		KOTEK_MESSAGE("[UNIT TESTING]");
	#endif
#endif

		return true;
	}

	bool ExecuteEngine(kun_core ktkMainManager* p_main_manager)
	{
		if (!p_main_manager)
			return false;

#ifdef KOTEK_USE_DEVELOPMENT_TYPE_SHARED
		p_user_callback_update_game_library(p_main_manager);
#elif defined(KOTEK_USE_DEVELOPMENT_TYPE_STATIC)
		::KOTEK_USER_FUNCTION_UPDATE_MODULE_GAME(p_main_manager);
#else
	#error Unknown development type, see what you specified in your cmd/cmake GUI. The macro accepts only two variables STATIC or SHARED
#endif
		return true;
	}

	bool ShutdownEngine(kun_core ktkMainManager* p_main_manager)
	{
		if (!p_main_manager)
			return false;

		kun_kotek kun_core ktkIWindowSplash* p_window =
			p_main_manager->Get_Splash();

		if (p_window)
		{
			delete p_window;
			p_main_manager->Set_Splash(nullptr);
		}

		Serialize_Engine(p_main_manager);

		kun_game ShutdownModule_Game(p_main_manager);
		kun_ui ShutdownModule_UI(p_main_manager);
		kun_core ShutdownModule_Core(p_main_manager);

		return true;
	}

	bool serializeEngine(void)
	{
		return true;
	}

	bool deserializeEngine(void)
	{
		return true;
	}
} // namespace Engine

KOTEK_END_NAMESPACE_KOTEK
