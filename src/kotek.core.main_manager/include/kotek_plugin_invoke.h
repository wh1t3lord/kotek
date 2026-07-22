#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

/// @brief \~english signature of every module entry point
/// (InitializeModule_*/ShutdownModule_*)
using ktkPluginModuleEntry_t = bool (*)(ktkMainManager*);

/// @brief \~english signature of module entry points that take an extra
/// version/selector argument (render backends: eEngineSupportedRenderer,
/// passed by value with identical ABI to unsigned)
using ktkPluginModuleEntryVersion_t = bool (*)(ktkMainManager*, unsigned);

/// @brief \~english resolves the plugin module that exports
/// \a p_init_symbol_name from the generated manifest
/// (kotek_plugin_manifest.h), loads its dll (cached, the handle stays
/// alive for the process lifetime unless ktkPluginUnloadAll is called)
/// and invokes the entry point. Implemented in this module; the manifest
/// table is compiled in when KOTEK_LINKAGE=PLUGIN is active.
bool ktkPluginInvokeInit(
	ktkMainManager* p_manager, const char* p_init_symbol_name);

/// @brief \~english same as ktkPluginInvokeInit but for entry points that
/// take a version/selector argument (render backends)
bool ktkPluginInvokeInitVersion(
	ktkMainManager* p_manager, const char* p_init_symbol_name,
	unsigned version);

/// @brief \~english same as ktkPluginInvokeInit but resolves and calls the
/// module's shutdown entry point
bool ktkPluginInvokeShutdown(
	ktkMainManager* p_manager, const char* p_shutdown_symbol_name);

/// @brief \~english same as ktkPluginInvokeInit but for the module's
/// serialization entry point (SerializeModule_*). The module is located by
/// deriving its init symbol name from the serialize symbol name
/// (SerializeModule_<X> -> InitializeModule_<X>, the strict module
/// convention) and the serialize symbol itself is then resolved inside the
/// same dll.
bool ktkPluginInvokeSerialize(
	ktkMainManager* p_manager, const char* p_serialize_symbol_name);

/// @brief \~english same as ktkPluginInvokeSerialize but for
/// DeserializeModule_*
bool ktkPluginInvokeDeserialize(
	ktkMainManager* p_manager, const char* p_deserialize_symbol_name);

/// @brief \~english releases all cached dll handles (call at the very end
/// of engine shutdown, after every module was shut down)
void ktkPluginUnloadAll(void);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#ifdef KOTEK_USE_LINKAGE_PLUGIN
// generated per-entry linkage flags (KOTEK_ENTRY_<symbol> = 1 linked, 0 plugin)
	#include <kotek_entry_config.h>

/// @brief \~english in PLUGIN mode every module entry call is selected at
/// compile time by the generated KOTEK_ENTRY_<symbol> flag: linked modules
/// (static/implicit) are called directly, plugin modules are resolved through
/// the explicit loader (LoadLibrary + GetProcAddress). In STATIC/SHARED modes
/// the macros compile to plain direct calls.
	#define KOTEK_INVOKE_ENTRY_0_INIT(symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeInit(manager, #symbol)
	#define KOTEK_INVOKE_ENTRY_1_INIT(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_ENTRY_0_SHUTDOWN(symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeShutdown(manager, #symbol)
	#define KOTEK_INVOKE_ENTRY_1_SHUTDOWN(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_ENTRY_0_SERIALIZE(symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeSerialize(manager, #symbol)
	#define KOTEK_INVOKE_ENTRY_1_SERIALIZE(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_ENTRY_0_DESERIALIZE(symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeDeserialize(manager, #symbol)
	#define KOTEK_INVOKE_ENTRY_1_DESERIALIZE(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_PICK_(kind, flag, symbol, manager) \
		KOTEK_INVOKE_ENTRY_##flag##_##kind(symbol, manager)
	#define KOTEK_INVOKE_PICK(kind, flag, symbol, manager) \
		KOTEK_INVOKE_PICK_(kind, flag, symbol, manager)

	#define KOTEK_INVOKE_MODULE_INIT(symbol, manager) \
		KOTEK_INVOKE_PICK(INIT, KOTEK_ENTRY_##symbol, symbol, manager)
	#define KOTEK_INVOKE_MODULE_SHUTDOWN(symbol, manager) \
		KOTEK_INVOKE_PICK(SHUTDOWN, KOTEK_ENTRY_##symbol, symbol, manager)
	#define KOTEK_INVOKE_MODULE_SERIALIZE(symbol, manager) \
		KOTEK_INVOKE_PICK(SERIALIZE, KOTEK_ENTRY_##symbol, symbol, manager)
	#define KOTEK_INVOKE_MODULE_DESERIALIZE(symbol, manager) \
		KOTEK_INVOKE_PICK(DESERIALIZE, KOTEK_ENTRY_##symbol, symbol, manager)
	// namespace-qualified variants (needed by non-plugin modes for direct
	// calls outside Kotek::Core); namespace is irrelevant in PLUGIN mode
	#define KOTEK_INVOKE_MODULE_INIT_NS(ns, symbol, manager) \
		KOTEK_INVOKE_MODULE_INIT(symbol, manager)
	#define KOTEK_INVOKE_MODULE_SHUTDOWN_NS(ns, symbol, manager) \
		KOTEK_INVOKE_MODULE_SHUTDOWN(symbol, manager)
	#define KOTEK_INVOKE_MODULE_SERIALIZE_NS(ns, symbol, manager) \
		KOTEK_INVOKE_MODULE_SERIALIZE(symbol, manager)
	#define KOTEK_INVOKE_MODULE_DESERIALIZE_NS(ns, symbol, manager) \
		KOTEK_INVOKE_MODULE_DESERIALIZE(symbol, manager)
	// version-taking render backend entries are always plugin dlls
	#define KOTEK_INVOKE_MODULE_INIT_V(symbol, manager, version) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeInitVersion( \
			manager, #symbol, (unsigned)(version))
#else
	#define KOTEK_INVOKE_MODULE_INIT(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_MODULE_INIT_V(symbol, manager, version) \
		symbol(manager, version)
	#define KOTEK_INVOKE_MODULE_SHUTDOWN(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_MODULE_SERIALIZE(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_MODULE_DESERIALIZE(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_MODULE_INIT_NS(ns, symbol, manager) ns symbol(manager)
	#define KOTEK_INVOKE_MODULE_SHUTDOWN_NS(ns, symbol, manager) \
		ns symbol(manager)
	#define KOTEK_INVOKE_MODULE_SERIALIZE_NS(ns, symbol, manager) \
		ns symbol(manager)
	#define KOTEK_INVOKE_MODULE_DESERIALIZE_NS(ns, symbol, manager) \
		ns symbol(manager)
#endif
