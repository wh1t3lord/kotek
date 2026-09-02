#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

/// @brief \~english upper bound of the plugin override slot table, parallel
/// to the generated module registry (kotek_plugin_registry.h); the whole
/// system is static-table based (embedded discipline), a violated bound is a
/// build-configuration bug and asserts at startup
#define KOTEK_DEF_PLUGIN_OVERRIDE_MAX_MODULES 512

/// @brief \~english bounded path buffer (MAX_PATH on Windows)
#define KOTEK_DEF_PLUGIN_OVERRIDE_MAX_PATH 260

/// @brief \~english bound of the loaded-plugin dll handle cache (PLUGIN
/// linkage); handles live for the whole process, modules are never that many
#define KOTEK_DEF_PLUGIN_INVOKE_MAX_HANDLES 256

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

/// @brief \~english lifecycle of one override slot (parallel to the generated
/// module registry, same index space)
enum class ePluginOverrideSlotState : unsigned char
{
	kNone = 0,   ///< no override registered for this module
	kRegistered, ///< override dll path known, not loaded yet
	kLoaded,     ///< override dll loaded, handle is valid
	kFailed      ///< load was attempted and failed (fall back)
};

struct ktkPluginOverrideSlot
{
	char m_dll_path[KOTEK_DEF_PLUGIN_OVERRIDE_MAX_PATH];
	/// @brief \~english HMODULE (Windows) / dlopen handle, kept as void* so
	/// this public header stays OS-header free
	void* m_p_handle;
	ePluginOverrideSlotState m_state;
};

struct ktkPluginInvokeHandle
{
	const char* m_p_dll_name;
	/// @brief \~english HMODULE (Windows) / dlopen handle, see
	/// ktkPluginOverrideSlot::m_p_handle
	void* m_p_handle;
};

/// @brief \~english all plugin override + invoke registry state, owned by
/// ktkMainManager (task K24 batch 2a — previously five file-scope statics in
/// kotek_plugin_override.cpp / kotek_plugin_invoke.cpp). Heap-allocated by
/// the manager constructor (~144 KB — too large for main()'s 1 MB stack,
/// measured overflow with ktkFileSystem-constructing tests) and freed by its
/// destructor: no lazy init, no Meyers singletons, no static storage. The
/// invoke half is only driven under KOTEK_USE_LINKAGE_PLUGIN; it stays
/// unconditional so the layout does not depend on the linkage mode.
struct ktkPluginState
{
	/// @brief \~english zeroes both tables and resets the plugins directory
	/// to the default "plugins" (relative to the working directory)
	ktkPluginState(void);

	ktkPluginOverrideSlot
		m_override_slots[KOTEK_DEF_PLUGIN_OVERRIDE_MAX_MODULES];
	char m_plugins_dir[KOTEK_DEF_PLUGIN_OVERRIDE_MAX_PATH];
	bool m_override_initialized;

	ktkPluginInvokeHandle
		m_invoke_handles[KOTEK_DEF_PLUGIN_INVOKE_MAX_HANDLES];
	unsigned long m_invoke_handles_count;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
