#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager;

/// @brief \~english the entry-point verb of a module invocation, mirrors the
/// verb token of KOTEK_INVOKE_MODULE (INIT/SHUTDOWN/SERIALIZE/DESERIALIZE)
enum class ePluginOverrideVerb : unsigned char
{
	kINIT,
	kSHUTDOWN,
	kSERIALIZE,
	kDESERIALIZE
};

/// @brief \~english override-first lookup for every module-entry invocation
/// (task K21). Consults the plugin override registry (plugins/ folder next
/// to the data folders, see ktkPluginOverrideStartup): if an override dll is
/// registered for the module that owns \a p_symbol_name, the dll's exported
/// entry is called instead of the built-in one. Compiled in EVERY linkage
/// mode — overrides work for static .lib, shared .dll and PLUGIN builds.
///
/// Tri-state result (the KOTEK_INVOKE_MODULE macro is structured as
/// "override ?: built-in fallback" on it):
///   < 0  no override registered for this module (or the override dll /
///        symbol failed to load — a warning is logged and the caller must
///        fall back to the built-in path)
///   0    the override entry was called and returned false
///   1    the override entry was called and returned true
///
/// Lookup is a linear scan over the generated module registry
/// (kotek_plugin_registry.h) — module entries are invoked rarely, so a scan
/// over a small static table is the intended design (lookup-table-on-vector
/// philosophy). Loaded dll handles stay alive for the process lifetime: an
/// override dll is its own module with its own CRT, and unloading it while
/// other modules may still hold interface pointers into it is unsafe.
int ktkPluginTryOverride(ePluginOverrideVerb verb, const char* p_symbol_name,
	ktkMainManager* p_manager);

/// @brief \~english performs the startup work of the plugin override system:
/// initializes the registry (idempotent — the first ktkPluginTryOverride
/// also initializes it lazily) and handles the engine flags
/// --kotek_plugins_template / --kotek_plugins_modules: when either is
/// present the corresponding file is written into plugins/, a message is
/// printed and the process exits with code 0. Called from
/// InitializeModule_Core_Main_Manager (engine config is parsed by then).
void ktkPluginOverrideStartup(ktkMainManager* p_manager);

/// @brief \~english writes \a p_plugins_dir/plugins.template.json: every
/// known module name with an empty dll field for the user to fill (the
/// schema of plugins.json, variant B registration). Returns false when the
/// file could not be written.
bool ktkPluginOverrideWriteTemplate(const char* p_plugins_dir);

/// @brief \~english writes \a p_plugins_dir/plugins.modules.json: a plain
/// json array of the known module names (codegen output for tooling).
/// Returns false when the file could not be written.
bool ktkPluginOverrideWriteModulesList(const char* p_plugins_dir);

/// @brief \~english overrides the scanned plugins directory (default
/// "plugins", relative to the working directory of the exe). Tooling/tests
/// only — call before the first module invocation or pair with
/// ktkPluginOverrideResetForTests.
void ktkPluginOverrideSetDirectory(const char* p_plugins_dir);

/// @brief \~english drops all registration state (tests only): the next
/// ktkPluginTryOverride re-scans the plugins directory. Already-loaded dll
/// handles are intentionally kept (the OS reclaims them at exit; reloading
/// the same dll is ref-counted by the OS loader).
void ktkPluginOverrideResetForTests(void);

/// @brief \~english query API (tests/tooling): 1 when an override is
/// registered for \a p_module_name (the dll path is copied into \a
/// p_out_dll_path when the buffer is non-null), 0 otherwise. Does not load
/// anything.
int ktkPluginOverrideFind(const char* p_module_name, char* p_out_dll_path,
	unsigned long out_dll_path_capacity);

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
