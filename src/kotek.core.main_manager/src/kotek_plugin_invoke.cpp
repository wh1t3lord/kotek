#include "../include/kotek_plugin_invoke.h"

#include <kotek.core.main_manager/include/kotek_main_manager.h>
#include <kotek.core.main_manager/include/kotek_plugin_state.h>

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
	#ifdef _WIN32
	void* plugin_load(const char* p_dll_name)
	{
		return reinterpret_cast<void*>(LoadLibraryA(p_dll_name));
	}
	void* plugin_sym(void* handle, const char* p_symbol)
	{
		return reinterpret_cast<void*>(
			GetProcAddress(reinterpret_cast<HMODULE>(handle), p_symbol));
	}
	void plugin_unload(void* handle)
	{
		FreeLibrary(reinterpret_cast<HMODULE>(handle));
	}
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

	const ktkPluginModuleDesc* plugin_find(const char* p_symbol_name,
		bool is_init)
	{
		for (unsigned long i = 0; i < g_kotek_plugin_modules_count; ++i)
		{
			const char* p_entry_symbol =
				is_init ? g_kotek_plugin_modules[i].p_init_symbol
						: g_kotek_plugin_modules[i].p_shutdown_symbol;

			if (p_entry_symbol && strcmp(p_entry_symbol, p_symbol_name) == 0)
				return &g_kotek_plugin_modules[i];
		}

		return nullptr;
	}

	void* plugin_resolve_in_dll(ktkPluginState* p_state,
		const ktkPluginModuleDesc* p_desc, const char* p_symbol_name)
	{
		void* handle = nullptr;

		for (unsigned long i = 0; i < p_state->m_invoke_handles_count; ++i)
		{
			if (strcmp(p_state->m_invoke_handles[i].m_p_dll_name,
					p_desc->p_dll_name) == 0)
			{
				handle = p_state->m_invoke_handles[i].m_p_handle;
				break;
			}
		}

		if (handle == nullptr)
		{
			if (p_state->m_invoke_handles_count >=
				KOTEK_DEF_PLUGIN_INVOKE_MAX_HANDLES)
			{
				return nullptr;
			}

			handle = plugin_load(p_desc->p_dll_name);

			if (handle == nullptr)
				return nullptr;

			p_state->m_invoke_handles[p_state->m_invoke_handles_count]
				.m_p_dll_name = p_desc->p_dll_name;
			p_state->m_invoke_handles[p_state->m_invoke_handles_count]
				.m_p_handle = handle;
			++p_state->m_invoke_handles_count;
		}

		return plugin_sym(handle, p_symbol_name);
	}

	bool plugin_invoke(ktkPluginState* p_state, ktkMainManager* p_manager,
		const char* p_symbol_name, bool is_init)
	{
		const ktkPluginModuleDesc* p_desc =
			plugin_find(p_symbol_name, is_init);

		if (p_desc == nullptr)
			return false;

		void* p_function =
			plugin_resolve_in_dll(p_state, p_desc, p_symbol_name);

		if (p_function == nullptr)
			return false;

		return reinterpret_cast<ktkPluginModuleEntry_t>(p_function)(
			p_manager);
	}

	// resolves a symbol like SerializeModule_<X>/DeserializeModule_<X> by
	// locating the module through its init entry name
	// (InitializeModule_<X>, the strict module convention: only the
	// leading verb changes) and then looking up the requested symbol in
	// the same dll
	bool plugin_invoke_derived(ktkPluginState* p_state,
		ktkMainManager* p_manager, const char* p_symbol_name,
		const char* p_symbol_verb)
	{
		const size_t verb_length = strlen(p_symbol_verb);

		if (strncmp(p_symbol_name, p_symbol_verb, verb_length) != 0)
			return false;

		// "Initialize" + "Module_<X>"
		const char* p_init_verb = "Initialize";
		char init_symbol_name[256];
		size_t rest_length = strlen(p_symbol_name + verb_length);

		if (strlen(p_init_verb) + rest_length + 1 >
			sizeof(init_symbol_name))
			return false;

		strcpy(init_symbol_name, p_init_verb);
		strcat(init_symbol_name, p_symbol_name + verb_length);

		const ktkPluginModuleDesc* p_desc =
			plugin_find(init_symbol_name, true);

		if (p_desc == nullptr)
			return false;

		void* p_function =
			plugin_resolve_in_dll(p_state, p_desc, p_symbol_name);

		if (p_function == nullptr)
			return false;

		return reinterpret_cast<ktkPluginModuleEntry_t>(p_function)(
			p_manager);
	}
} // namespace

bool ktkPluginInvokeInit(ktkMainManager* p_manager, const char* p_init_symbol_name)
{
	if (p_manager == nullptr)
		return false;

	return plugin_invoke(
		&p_manager->Get_PluginState(), p_manager, p_init_symbol_name, true);
}


bool ktkPluginInvokeShutdown(
	ktkMainManager* p_manager, const char* p_shutdown_symbol_name)
{
	if (p_manager == nullptr)
		return false;

	return plugin_invoke(&p_manager->Get_PluginState(), p_manager,
		p_shutdown_symbol_name, false);
}

bool ktkPluginInvokeSerialize(
	ktkMainManager* p_manager, const char* p_serialize_symbol_name)
{
	if (p_manager == nullptr)
		return false;

	return plugin_invoke_derived(&p_manager->Get_PluginState(), p_manager,
		p_serialize_symbol_name, "Serialize");
}

bool ktkPluginInvokeDeserialize(
	ktkMainManager* p_manager, const char* p_deserialize_symbol_name)
{
	if (p_manager == nullptr)
		return false;

	return plugin_invoke_derived(&p_manager->Get_PluginState(), p_manager,
		p_deserialize_symbol_name, "Deserialize");
}

void ktkPluginUnloadAll(ktkMainManager* p_manager)
{
	if (p_manager == nullptr)
		return;

	ktkPluginState* p_state = &p_manager->Get_PluginState();

	for (unsigned long i = 0; i < p_state->m_invoke_handles_count; ++i)
	{
		plugin_unload(p_state->m_invoke_handles[i].m_p_handle);
		p_state->m_invoke_handles[i].m_p_handle = nullptr;
	}

	p_state->m_invoke_handles_count = 0;
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
bool ktkPluginInvokeShutdown(ktkMainManager*, const char*) { return false; }
bool ktkPluginInvokeSerialize(ktkMainManager*, const char*) { return false; }
bool ktkPluginInvokeDeserialize(ktkMainManager*, const char*) { return false; }
void ktkPluginUnloadAll(ktkMainManager*) {}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#endif
