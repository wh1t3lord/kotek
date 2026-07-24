// test double of a user-provided override dll for the plugin override system
// (task K21). It emulates an external module replacement: only the uniform
// module entry contract bool(ktkMainManager*) is exported (the manager is
// opaque here — the module-boundary rules are honored by touching nothing
// that crosses the CRT boundary; the entry just writes a marker file via C
// stdio so the exe-side gtest can prove WHICH implementation ran).

#include <cstdio>
#include <cstring>

#ifdef _WIN32
	#define KOTEK_TEST_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
	#define KOTEK_TEST_PLUGIN_EXPORT \
		extern "C" __attribute__((visibility("default")))
#endif

namespace
{
	constexpr const char* k_marker_file_name =
		"kotek_plugin_override_tests.marker";

	void write_marker(const char* p_line)
	{
		// the working directory of the loading process (the exe running the
		// tests) is the rendezvous point both sides know
		FILE* p_file = std::fopen(k_marker_file_name, "ab");

		if (p_file == nullptr)
			return;

		std::fwrite(p_line, 1, std::strlen(p_line), p_file);
		std::fclose(p_file);
	}
} // namespace

KOTEK_TEST_PLUGIN_EXPORT bool InitializeModule_Core_Tests_Plugin(void*)
{
	write_marker("init\n");
	return true;
}

KOTEK_TEST_PLUGIN_EXPORT bool ShutdownModule_Core_Tests_Plugin(void*)
{
	write_marker("shutdown\n");
	return true;
}

KOTEK_TEST_PLUGIN_EXPORT bool SerializeModule_Core_Tests_Plugin(void*)
{
	write_marker("serialize\n");
	return true;
}

KOTEK_TEST_PLUGIN_EXPORT bool DeserializeModule_Core_Tests_Plugin(void*)
{
	write_marker("deserialize\n");
	return true;
}
