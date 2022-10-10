#pragma once

#include <kotek.core.api/include/kotek_api.h>

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
	ktkIInput* GetInput(void) const noexcept;

	ktkIGameManager* GetGameManager(void) const noexcept;
	void SetGameManager(ktkIGameManager* p_game_manager) noexcept;

	ktkIResourceManager* GetResourceManager(void) const noexcept;
	void SetResourceManager(ktkIResourceManager* p_manager) noexcept;

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

	void Set_EngineConfig(ktkIEngineConfig* pointer) noexcept;
	ktkIEngineConfig* Get_EngineConfig(void) const noexcept;

	ktkIWindowManager* Get_WindowManager(void) const noexcept;
	void Set_WindowManager(ktkIWindowManager* p_window_manager) noexcept;

	ktkIImguiWrapper* Get_ImguiWrapper(void) const noexcept;
	void Set_ImguiWrapper(ktkIImguiWrapper* p_manager) noexcept;

	ktkIGameUIManager* Get_GameUIEngine(void) const noexcept;
	void Set_GameUIEngine(ktkIGameUIManager* p_manager) noexcept;

	void Initialize(void);
	void Shutdown(void);

private:
	int m_argc;
	char** m_argv;
	ktkIEngineConfig* m_p_manager_config;
	kotek_i_renderer* m_p_manager_renderer;
	ktkIGameManager* m_p_game_manager;
	ktkIResourceManager* m_p_resource_manager;
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
};

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
