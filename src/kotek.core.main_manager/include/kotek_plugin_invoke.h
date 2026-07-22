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

/// @brief \~english releases all cached dll handles (call at the very end
/// of engine shutdown, after every module was shut down)
void ktkPluginUnloadAll(void);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

#ifdef KOTEK_USE_LINKAGE_PLUGIN
/// @brief \~english in PLUGIN mode module entry points are invoked through
/// the explicit loader (LoadLibrary + GetProcAddress); in STATIC/SHARED
/// modes the call is a plain direct call and the macro vanishes
	#define KOTEK_INVOKE_MODULE_INIT(symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeInit(manager, #symbol)
	#define KOTEK_INVOKE_MODULE_INIT_V(symbol, manager, version) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeInitVersion( \
			manager, #symbol, (unsigned)(version))
	#define KOTEK_INVOKE_MODULE_SHUTDOWN(symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeShutdown(manager, #symbol)
	// for entry points living outside Kotek::Core (e.g. Kotek::UI): PLUGIN
	// mode resolves by symbol name regardless of namespace; STATIC mode needs
	// the namespace qualifier for the direct call
	#define KOTEK_INVOKE_MODULE_INIT_NS(ns, symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeInit(manager, #symbol)
	#define KOTEK_INVOKE_MODULE_SHUTDOWN_NS(ns, symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeShutdown(manager, #symbol)
#else
	#define KOTEK_INVOKE_MODULE_INIT(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_MODULE_INIT_V(symbol, manager, version) \
		symbol(manager, version)
	#define KOTEK_INVOKE_MODULE_SHUTDOWN(symbol, manager) symbol(manager)
	#define KOTEK_INVOKE_MODULE_INIT_NS(ns, symbol, manager) ns symbol(manager)
	#define KOTEK_INVOKE_MODULE_SHUTDOWN_NS(ns, symbol, manager) \
		ns symbol(manager)
#endif
