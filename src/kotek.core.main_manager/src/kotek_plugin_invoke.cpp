#include "../include/kotek_plugin_invoke.h"

#ifdef KOTEK_USE_LINKAGE_PLUGIN

	#include <kotek_plugin_manifest.h>

	#ifdef _WIN32
		#include <Windows.h>
	#else
		#include <dlfcn.h>
	#endif

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

namespace
{
	struct plugin_handle_t
	{
		const char* p_dll_name;
	#ifdef _WIN32
		HMODULE handle;
	#else
		void* handle;
	#endif
	};

	// handles live for the whole process; modules are never that many
	plugin_handle_t g_plugin_handles[256];
	unsigned long g_plugin_handles_count = 0;

	#ifdef _WIN32
	HMODULE plugin_load(const char* p_dll_name) { return LoadLibraryA(p_dll_name); }
	void* plugin_sym(HMODULE handle, const char* p_symbol)
	{
		return reinterpret_cast<void*>(GetProcAddress(handle, p_symbol));
	}
	void plugin_unload(HMODULE handle) { FreeLibrary(handle); }
	#else
	void* plugin_load(const char* p_dll_name)
	{
		return dlopen(p_dll_name, RTLD_NOW | RTLD_LOCAL);
	}
	void* plugin_sym(void* handle, const char* p_symbol)
	{
		return dlsym(handle, p_symbol);
	}
	void plugin_unload(void* handle) { dlclose(handle); }
	#endif

	void* plugin_resolve(const char* p_symbol_name, bool is_init)
	{
		const char* p_dll_name = nullptr;

		for (unsigned long i = 0; i < g_kotek_plugin_modules_count; ++i)
		{
			const char* p_entry_symbol =
				is_init ? g_kotek_plugin_modules[i].p_init_symbol
						: g_kotek_plugin_modules[i].p_shutdown_symbol;

			if (p_entry_symbol && strcmp(p_entry_symbol, p_symbol_name) == 0)
			{
				p_dll_name = g_kotek_plugin_modules[i].p_dll_name;
				break;
			}
		}

		if (p_dll_name == nullptr)
			return nullptr;

		decltype(plugin_load(nullptr)) handle = nullptr;

		for (unsigned long i = 0; i < g_plugin_handles_count; ++i)
		{
			if (strcmp(g_plugin_handles[i].p_dll_name, p_dll_name) == 0)
			{
				handle = g_plugin_handles[i].handle;
				break;
			}
		}

		if (handle == nullptr)
		{
			if (g_plugin_handles_count >=
				sizeof(g_plugin_handles) / sizeof(g_plugin_handles[0]))
			{
				return nullptr;
			}

			handle = plugin_load(p_dll_name);

			if (handle == nullptr)
				return nullptr;

			g_plugin_handles[g_plugin_handles_count].p_dll_name = p_dll_name;
			g_plugin_handles[g_plugin_handles_count].handle = handle;
			++g_plugin_handles_count;
		}

		return plugin_sym(handle, p_symbol_name);
	}

	bool plugin_invoke(ktkMainManager* p_manager, const char* p_symbol_name,
		bool is_init)
	{
		void* p_function = plugin_resolve(p_symbol_name, is_init);

		if (p_function == nullptr)
			return false;

		return reinterpret_cast<ktkPluginModuleEntry_t>(p_function)(p_manager);
	}
} // namespace

bool ktkPluginInvokeInit(ktkMainManager* p_manager, const char* p_init_symbol_name)
{
	return plugin_invoke(p_manager, p_init_symbol_name, true);
}

bool ktkPluginInvokeInitVersion(
	ktkMainManager* p_manager, const char* p_init_symbol_name,
	unsigned version)
{
	void* p_function = plugin_resolve(p_init_symbol_name, true);

	if (p_function == nullptr)
		return false;

	return reinterpret_cast<ktkPluginModuleEntryVersion_t>(
		p_function)(p_manager, version);
}

bool ktkPluginInvokeShutdown(
	ktkMainManager* p_manager, const char* p_shutdown_symbol_name)
{
	return plugin_invoke(p_manager, p_shutdown_symbol_name, false);
}

void ktkPluginUnloadAll(void)
{
	for (unsigned long i = 0; i < g_plugin_handles_count; ++i)
	{
		plugin_unload(g_plugin_handles[i].handle);
		g_plugin_handles[i].handle = nullptr;
	}

	g_plugin_handles_count = 0;
}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#else

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

// non-PLUGIN modes: KOTEK_INVOKE_MODULE_* macros compile to direct calls, so
// these are never invoked; provided only so the symbols exist if someone
// calls them explicitly.
bool ktkPluginInvokeInit(ktkMainManager*, const char*) { return false; }
bool ktkPluginInvokeInitVersion(ktkMainManager*, const char*, unsigned)
{
	return false;
}
bool ktkPluginInvokeShutdown(ktkMainManager*, const char*) { return false; }
void ktkPluginUnloadAll(void) {}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#endif
