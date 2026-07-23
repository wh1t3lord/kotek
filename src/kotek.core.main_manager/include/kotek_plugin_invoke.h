#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.main_manager/include/kotek_plugin_override.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

/// @brief \~english signature of every module entry point
/// (InitializeModule_*/ShutdownModule_*)
using ktkPluginModuleEntry_t = bool (*)(ktkMainManager*);

/// @brief \~english resolves the plugin module that exports
/// \a p_init_symbol_name from the generated manifest
/// (kotek_plugin_manifest.h), loads its dll (cached, the handle stays
/// alive for the process lifetime unless ktkPluginUnloadAll is called)
/// and invokes the entry point. Implemented in this module; the manifest
/// table is compiled in when KOTEK_LINKAGE=PLUGIN is active.
bool ktkPluginInvokeInit(
	ktkMainManager* p_manager, const char* p_init_symbol_name);

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

/// @brief \~english THE single module-entry macro for every verb
/// (INIT/SHUTDOWN/SERIALIZE/DESERIALIZE). Usage everywhere:
///     KOTEK_INVOKE_MODULE(INIT, CORE, InitializeModule_Core, p_manager);
///     KOTEK_INVOKE_MODULE(SHUTDOWN, UI, ShutdownModule_UI, p_manager);
/// OVERRIDE-FIRST (task K21): every invocation first consults the plugin
/// override registry via ktkPluginTryOverride (tri-state: negative = no
/// override registered -> built-in fallback; non-negative = the override
/// entry was called and the value is its bool result). The built-in
/// fallback keeps the previous behavior: in PLUGIN mode the generated
/// KOTEK_ENTRY_<symbol> flag selects the explicit loader (0) or a direct
/// call (1) per call site; in all other linkage modes it is a plain
/// namespace-qualified direct call. All module entry points share the
/// uniform signature bool(ktkMainManager*) — that uniformity is what makes
/// a single macro possible.
	#define KOTEK_INVOKE_ENTRY_0_INIT(ns, symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeInit(manager, #symbol)
	#define KOTEK_INVOKE_ENTRY_0_SHUTDOWN(ns, symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeShutdown(manager, #symbol)
	#define KOTEK_INVOKE_ENTRY_0_SERIALIZE(ns, symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeSerialize(manager, #symbol)
	#define KOTEK_INVOKE_ENTRY_0_DESERIALIZE(ns, symbol, manager) \
		::KUN_KOTEK KUN_CORE ktkPluginInvokeDeserialize(manager, #symbol)
	#define KOTEK_INVOKE_ENTRY_1_INIT(ns, symbol, manager) \
		::KUN_KOTEK KUN_##ns symbol(manager)
	#define KOTEK_INVOKE_ENTRY_1_SHUTDOWN(ns, symbol, manager) \
		::KUN_KOTEK KUN_##ns symbol(manager)
	#define KOTEK_INVOKE_ENTRY_1_SERIALIZE(ns, symbol, manager) \
		::KUN_KOTEK KUN_##ns symbol(manager)
	#define KOTEK_INVOKE_ENTRY_1_DESERIALIZE(ns, symbol, manager) \
		::KUN_KOTEK KUN_##ns symbol(manager)
	#define KOTEK_INVOKE_PICK_(verb, flag, ns, symbol, manager) \
		KOTEK_INVOKE_ENTRY_##flag##_##verb(ns, symbol, manager)
	#define KOTEK_INVOKE_PICK(verb, flag, ns, symbol, manager) \
		KOTEK_INVOKE_PICK_(verb, flag, ns, symbol, manager)

	#define KOTEK_INVOKE_MODULE(verb, ns, symbol, manager)                  \
		([&]() -> bool {                                                     \
			const int _kotek_plugin_override_status =                        \
				::KUN_KOTEK KUN_CORE ktkPluginTryOverride(                   \
					::KUN_KOTEK KUN_CORE ePluginOverrideVerb::k##verb,       \
					#symbol, manager);                                       \
			if (_kotek_plugin_override_status >= 0)                          \
				return _kotek_plugin_override_status != 0;                   \
			return KOTEK_INVOKE_PICK(                                        \
				verb, KOTEK_ENTRY_##symbol, ns, symbol, manager);            \
		}())
#else
	#define KOTEK_INVOKE_MODULE(verb, ns, symbol, manager)                  \
		([&]() -> bool {                                                     \
			const int _kotek_plugin_override_status =                        \
				::KUN_KOTEK KUN_CORE ktkPluginTryOverride(                   \
					::KUN_KOTEK KUN_CORE ePluginOverrideVerb::k##verb,       \
					#symbol, manager);                                       \
			if (_kotek_plugin_override_status >= 0)                          \
				return _kotek_plugin_override_status != 0;                   \
			return ::KUN_KOTEK KUN_##ns symbol(manager);                     \
		}())
#endif
