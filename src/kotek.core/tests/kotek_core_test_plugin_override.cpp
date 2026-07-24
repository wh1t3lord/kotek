#include "../include/kotek_core.h"

#include <kotek.core.defines.static.tests/include/kotek_core_defines_static_tests.h>

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

	#include <kotek.core.main_manager/include/kotek_main_manager.h>
	#include <kotek.core.main_manager/include/kotek_plugin_override.h>
	#include <kotek.core.main_manager/include/kotek_plugin_invoke.h>

	#include <gtest/gtest.h>

	#include <filesystem>
	#include <fstream>
	#include <sstream>
	#include <string>

#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

#if defined(KOTEK_USE_TESTS) && defined(KOTEK_DEBUG)

// functional proofs of the plugin override system (task K21):
//  - registry: name-convention registration found, json registration found,
//    json wins over the name convention, malformed json cannot desync the
//    scanner
//  - invocation: an override dll's entry is called INSTEAD of the built-in
//    one; the built-in fallback runs when no override is registered
//  - the two engine flags' file writers produce the expected files
//
// the tests drive the production code paths (ktkPluginOverrideSetDirectory /
// ktkPluginOverrideResetForTests) against isolated temp plugins/ folders and
// a real override dll (kotek.core.tests.plugin, built as a
// SHARED library and located via KOTEK_TEST_PLUGIN_OVERRIDE_DLL_PATH).

namespace
{
	// the module name of the test double, registered into the generated
	// module registry by its CMakeLists (folder/target name is the source
	// of truth)
	constexpr const char* k_test_module_name =
		"kotek.core.tests.plugin";

	// a module that is guaranteed to be in the registry (it registers its
	// entries through kotek_add_library) and that no test places an
	// override dll for
	constexpr const char* k_known_module_name = "kotek.core.main_manager";

	constexpr const char* k_marker_file_name =
		"kotek_plugin_override_tests.marker";

	bool g_builtin_init_called = false;
	bool g_builtin_shutdown_called = false;

	std::string read_text_file(const std::filesystem::path& path)
	{
		std::ifstream stream(path, std::ios::binary);
		std::ostringstream content;
		content << stream.rdbuf();
		return content.str();
	}
} // namespace

// the built-in implementation the KOTEK_INVOKE_MODULE fallback path calls
// when no override is registered — it must live in the very namespace the
// macro qualifies (::Kotek::Core::<symbol>), like every real module entry
bool InitializeModule_Core_Tests_Plugin(
	ktkMainManager*)
{
	g_builtin_init_called = true;
	return true;
}

bool ShutdownModule_Core_Tests_Plugin(
	ktkMainManager*)
{
	g_builtin_shutdown_called = true;
	return true;
}

namespace
{
	class KotekPluginOverride : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			std::error_code error;
			m_temp_dir = std::filesystem::temp_directory_path(error) /
				"kotek_plugin_override_tests" /
				::testing::UnitTest::GetInstance()
					->current_test_info()
					->name();

			std::filesystem::remove_all(m_temp_dir, error);
			std::filesystem::create_directories(m_temp_dir, error);

			std::filesystem::remove(k_marker_file_name, error);

			g_builtin_init_called = false;
			g_builtin_shutdown_called = false;
		}

		void TearDown() override
		{
			// restore production defaults: the engine shutdown chain keeps
			// invoking module entries after the tests ran
			ktkPluginOverrideSetDirectory("plugins");
			ktkPluginOverrideResetForTests();

			std::error_code error;
			std::filesystem::remove_all(m_temp_dir, error);
			std::filesystem::remove(k_marker_file_name, error);
		}

		// copies the real test-double dll into the temp plugins folder
		// under the given file name
		void place_override_dll(const std::string& dll_file_name)
		{
			const std::filesystem::path target =
				m_temp_dir / dll_file_name;

			std::error_code error;
			std::filesystem::copy_file(
				std::filesystem::path(
					KOTEK_TEST_PLUGIN_OVERRIDE_DLL_PATH),
				target, std::filesystem::copy_options::overwrite_existing,
				error);

			ASSERT_FALSE(error) << "failed to copy the test-double dll: "
								<< error.message();
			ASSERT_TRUE(std::filesystem::exists(target));
		}

		void use_temp_dir_as_plugins_folder(void)
		{
			ktkPluginOverrideSetDirectory(
				m_temp_dir.generic_string().c_str());
			ktkPluginOverrideResetForTests();
		}

		std::filesystem::path m_temp_dir;
	};
} // namespace

TEST_F(KotekPluginOverride, RegistryFindsNameConventionDll)
{
	place_override_dll(
		std::string(k_test_module_name) + ".dll");
	use_temp_dir_as_plugins_folder();

	char found_path[260]{};

	ASSERT_EQ(ktkPluginOverrideFind(
				  k_test_module_name, found_path, sizeof(found_path)),
		1);

	const std::string registered_path(found_path);
	ASSERT_NE(registered_path.find(k_test_module_name),
		std::string::npos);
	ASSERT_NE(registered_path.find(".dll"), std::string::npos);

	// a known module without a dll on disk is not registered
	ASSERT_EQ(ktkPluginOverrideFind(
				  k_known_module_name, found_path, sizeof(found_path)),
		0);

	// an unknown module name is not registered
	ASSERT_EQ(ktkPluginOverrideFind("kotek.does.not.exist", found_path,
				  sizeof(found_path)),
		0);
}

TEST_F(KotekPluginOverride, RegistryFindsJsonMappingAndJsonWins)
{
	// json maps the module to a user-chosen file name AND a decoy
	// name-convention dll exists at the same time — json must win
	place_override_dll("my_custom_plugin.dll");
	place_override_dll(
		std::string(k_test_module_name) + ".dll");

	{
		std::ofstream json_file(m_temp_dir / "plugins.json",
			std::ios::binary | std::ios::trunc);
		json_file << "{\n\t\"modules\":\n\t{\n\t\t\""
				  << k_test_module_name
				  << "\": \"my_custom_plugin.dll\",\n\t\t\""
				  << "kotek.unknown.module"
				  << "\": \"ignored.dll\"\n\t}\n}\n";
	}

	use_temp_dir_as_plugins_folder();

	char found_path[260]{};

	ASSERT_EQ(ktkPluginOverrideFind(
				  k_test_module_name, found_path, sizeof(found_path)),
		1);

	// json wins over the name convention
	ASSERT_NE(std::string(found_path).find("my_custom_plugin.dll"),
		std::string::npos);

	// the unknown module in json was ignored without disturbing the scan
	ASSERT_EQ(ktkPluginOverrideFind(
				  k_known_module_name, found_path, sizeof(found_path)),
		0);
}

TEST_F(KotekPluginOverride, RegistrySurvivesMalformedJson)
{
	place_override_dll(
		std::string(k_test_module_name) + ".dll");

	{
		// truncated inside the modules object — the scanner must stop
		// gracefully and still apply the name convention
		std::ofstream json_file(m_temp_dir / "plugins.json",
			std::ios::binary | std::ios::trunc);
		json_file << "{\"modules\": {\"kotek.core.main_manager\": \"x.d";
	}

	use_temp_dir_as_plugins_folder();

	char found_path[260]{};

	ASSERT_EQ(ktkPluginOverrideFind(
				  k_test_module_name, found_path, sizeof(found_path)),
		1);
	ASSERT_NE(std::string(found_path).find(k_test_module_name),
		std::string::npos);
}

TEST_F(KotekPluginOverride, OverrideIsCalledInsteadOfBuiltin)
{
	place_override_dll(
		std::string(k_test_module_name) + ".dll");
	use_temp_dir_as_plugins_folder();

	ktkMainManager manager;

	bool status = KOTEK_INVOKE_MODULE(INIT, CORE,
		InitializeModule_Core_Tests_Plugin, &manager);

	ASSERT_TRUE(status);

	// the override ran, the built-in fallback did not
	ASSERT_FALSE(g_builtin_init_called);
	ASSERT_TRUE(std::filesystem::exists(k_marker_file_name));
	ASSERT_NE(read_text_file(k_marker_file_name).find("init"),
		std::string::npos);

	status = KOTEK_INVOKE_MODULE(SHUTDOWN, CORE,
		ShutdownModule_Core_Tests_Plugin, &manager);

	ASSERT_TRUE(status);
	ASSERT_FALSE(g_builtin_shutdown_called);
	ASSERT_NE(read_text_file(k_marker_file_name).find("shutdown"),
		std::string::npos);
}

TEST_F(KotekPluginOverride, BuiltinFallbackWhenNoOverrideExists)
{
	// empty plugins folder: nothing registered
	use_temp_dir_as_plugins_folder();

	ktkMainManager manager;

	// the tri-state contract the macro falls back on
	ASSERT_EQ(ktkPluginTryOverride(ePluginOverrideVerb::kINIT,
				  "InitializeModule_Core_Tests_Plugin",
				  &manager),
		-1);

	bool status = KOTEK_INVOKE_MODULE(INIT, CORE,
		InitializeModule_Core_Tests_Plugin, &manager);

	ASSERT_TRUE(status);
	ASSERT_TRUE(g_builtin_init_called);
	ASSERT_FALSE(std::filesystem::exists(k_marker_file_name));
}

TEST_F(KotekPluginOverride, FlagWritersProduceExpectedFiles)
{
	ASSERT_TRUE(ktkPluginOverrideWriteTemplate(
		m_temp_dir.generic_string().c_str()));

	const std::filesystem::path template_path =
		m_temp_dir / "plugins.template.json";

	ASSERT_TRUE(std::filesystem::exists(template_path));

	const std::string template_content = read_text_file(template_path);

	ASSERT_NE(template_content.find("\"modules\""), std::string::npos);
	// every known module with an empty dll field, ready to be filled
	ASSERT_NE(template_content.find(std::string("\"") +
				  k_test_module_name + "\": \"\""),
		std::string::npos);
	ASSERT_NE(template_content.find(std::string("\"") +
				  k_known_module_name + "\": \"\""),
		std::string::npos);

	ASSERT_TRUE(ktkPluginOverrideWriteModulesList(
		m_temp_dir.generic_string().c_str()));

	const std::filesystem::path modules_path =
		m_temp_dir / "plugins.modules.json";

	ASSERT_TRUE(std::filesystem::exists(modules_path));

	const std::string modules_content = read_text_file(modules_path);

	ASSERT_EQ(modules_content.front(), '[');
	ASSERT_EQ(modules_content.rfind(']') != std::string::npos, true);
	ASSERT_NE(modules_content.find(k_test_module_name),
		std::string::npos);
	ASSERT_NE(modules_content.find(k_known_module_name),
		std::string::npos);
}

#endif

// link anchor (always defined, external linkage on purpose): gtest TUs in a
// static lib are unreferenced archive members, so the linker drops their obj
// and the tests never register — /INCREMENTAL then preserves that state
// forever (the legacy suites in this module only survive from historic
// links). RegisterAllTests in main_core_dll.cpp references every registrar,
// and main_core_dll.obj is always linked (it defines InitializeModule_Core),
// which pulls this TU's obj out of kotek.core.lib — the established idiom of
// this module's runtime tests.
void RegisterTests_PluginOverride_ForModule_Core(void) {}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
