#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>
#include <kotek.core.main_manager/include/kotek_plugin_state.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkIProfiler;
class ktkIFileSystem;
class ktkIInput;
class ktkIGameManager;
class ktkIRenderDevice;
class ktkIRenderResourceManager;
class ktkIRenderSwapchain;
class ktkIRenderer;
class ktkIFrameworkConfig;
class ktkIWindowManager;
class ktkIImguiWrapper;
class ktkIGameUIManager;
class ktkILogger;
class ktkIWindowSplash;
class ktkIRenderGraph;
class ktkIConsole;
class ktkIWindowConsole;

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

class ktkMainManager
{
public:
	ktkMainManager(int argc, char** argv);
	ktkMainManager(void);
	~ktkMainManager(void);

	void Set_Profiler(ktkIProfiler* p_instance) noexcept;
	ktkIProfiler* GetProfiler(void) const noexcept;

	ktkIFileSystem* GetFileSystem(void) const noexcept;
	void Set_FileSystem(ktkIFileSystem* p_instance) noexcept;

	void Set_Input(ktkIInput* p_instance) noexcept;
	ktkIInput* Get_Input(void) const noexcept;

	ktkIGameManager* GetGameManager(void) const noexcept;
	void SetGameManager(ktkIGameManager* p_game_manager) noexcept;

	ktkIRenderDevice* getRenderDevice(void) const noexcept;

	void setRenderDevice(ktkIRenderDevice* pointer) noexcept;

	// @ returns user's resource manager
	// TODO: delete resource manager from here it is a private thing,
	// because wit hall resource handling must be called from one
	// instance and it is GetResourceManager, GetResourceManager could
	// be initialized as user implementated interface or our
	ktkIRenderResourceManager* GetRenderResourceManager(void) const noexcept;

	void SetRenderResourceManager(ktkIRenderResourceManager* pointer) noexcept;

	ktkIRenderSwapchain* getRenderSwapchainManager(void) const noexcept;

	void setRenderSwapchainManager(ktkIRenderSwapchain* pointer) noexcept;

	void Set_FrameworkConfig(ktkIFrameworkConfig* pointer) noexcept;
	ktkIFrameworkConfig* Get_EngineConfig(void) const noexcept;

	ktkIWindowManager* Get_WindowManager(void) const noexcept;
	void Set_WindowManager(ktkIWindowManager* p_window_manager) noexcept;

	ktkIImguiWrapper* Get_ImguiWrapper(void) const noexcept;
	void Set_ImguiWrapper(ktkIImguiWrapper* p_manager) noexcept;

	ktkIGameUIManager* Get_GameUIEngine(void) const noexcept;
	void Set_GameUIEngine(ktkIGameUIManager* p_manager) noexcept;

	ktkILogger* Get_Logger(void) const noexcept;
	void Set_Logger(ktkILogger* p_logger) noexcept;

	ktkIWindowSplash* Get_Splash(void) const noexcept;
	void Set_Splash(ktkIWindowSplash* p_window) noexcept;

	ktkIConsole* Get_Console(void) const noexcept;
	void Set_Console(ktkIConsole* p_console) noexcept;

	ktkIWindowConsole* Get_WindowConsole(void) const noexcept;
	void Set_WindowConsole(ktkIWindowConsole* p_console) noexcept;

	int Get_ARGC(void) const noexcept;
	char** Get_ARGV(void) const noexcept;

	/// @brief \~english plugin override + invoke registry state (tasks
	/// K21/K24), owned by this manager; driven by
	/// ktkPluginTryOverride / ktkPluginInvoke* — additive accessor, the
	/// state initializes with the manager constructor (no lazy init).
	/// Heap-owned: the table is ~144 KB and kotek.exe hosts the manager
	/// on main()'s 1 MB stack — engine tests that construct
	/// ktkFileSystem (~600 KB map) in the same chain measured an
	/// overflow when the state was a by-value member
	ktkPluginState& Get_PluginState(void) noexcept;

	void Initialize(void);
	void Shutdown(void);

private:
	int m_argc;
	char** m_argv;
	ktkIFrameworkConfig* m_p_manager_config;
	ktkIRenderer* m_p_manager_renderer;
	ktkIGameManager* m_p_game_manager;
	ktkIFileSystem* m_p_manager_filesystem;
	ktkIInput* m_p_manager_input;
	ktkIRenderDevice* m_p_manager_render_device;
	ktkIRenderResourceManager* m_p_manager_render_resource;
	ktkIRenderGraph* m_p_manager_render_graph;
	ktkIRenderSwapchain* m_p_manager_swapchain;
	ktkIProfiler* m_p_manager_profiler;
	ktkIWindowManager* m_p_manager_window;
	ktkIImguiWrapper* m_p_manager_imgui_wrapper;
	ktkIGameUIManager* m_p_game_ui_engine;
	ktkILogger* m_p_logger;
	ktkIWindowSplash* m_p_splash;
	ktkIConsole* m_p_console;
	ktkIWindowConsole* m_p_window_console;
	ktkPluginState* m_p_plugin_state;
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
