#include "../include/kotek_main_manager.h"
#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE
ktkMainManager::ktkMainManager(int argc, char** argv) :
	m_argc{argc}, m_argv{argv}, m_p_manager_config{}, m_p_manager_renderer{},
	m_p_game_manager{}, m_p_resource_manager{}, m_p_manager_filesystem{},
	m_p_manager_input{}, m_p_manager_render_device{},
	m_p_manager_render_resource{}, m_p_manager_render_graph{},
	m_p_manager_swapchain{}, m_p_manager_profiler{}, m_p_manager_window{},
	m_p_manager_imgui_wrapper{}, m_p_game_ui_engine{}, m_p_logger{}, m_p_splash{}
{
}

ktkMainManager::ktkMainManager() :
	m_argc{}, m_argv{}, m_p_manager_config{}, m_p_manager_renderer{},
	m_p_game_manager{}, m_p_resource_manager{}, m_p_manager_filesystem{},
	m_p_manager_input{}, m_p_manager_render_device{},
	m_p_manager_render_resource{}, m_p_manager_render_graph{},
	m_p_manager_swapchain{}, m_p_manager_profiler{}, m_p_manager_window{},
	m_p_manager_imgui_wrapper{}, m_p_game_ui_engine{}, m_p_logger{},
	m_p_splash{}
{
}

ktkMainManager::~ktkMainManager(void) {}

void ktkMainManager::Set_Profiler(ktkIProfiler* p_instance) noexcept
{
	this->m_p_manager_profiler = p_instance;
}

ktkIProfiler* ktkMainManager::GetProfiler(void) const noexcept
{
	return this->m_p_manager_profiler;
}

ktkIFileSystem* ktkMainManager::GetFileSystem(void) const noexcept
{
	return this->m_p_manager_filesystem;
}

void ktkMainManager::Set_FileSystem(ktkIFileSystem* p_instance) noexcept
{
	this->m_p_manager_filesystem = p_instance;
}

void ktkMainManager::Set_Input(ktkIInput* p_instance) noexcept
{
	this->m_p_manager_input = p_instance;
}

ktkIInput* ktkMainManager::GetInput(void) const noexcept
{
	return this->m_p_manager_input;
}

ktkIGameManager* ktkMainManager::GetGameManager(void) const noexcept
{
	return this->m_p_game_manager;
}

void ktkMainManager::SetGameManager(ktkIGameManager* p_game_manager) noexcept
{
	this->m_p_game_manager = p_game_manager;
}

ktkIResourceManager* ktkMainManager::GetResourceManager(void) const noexcept
{
	return this->m_p_resource_manager;
}

void ktkMainManager::SetResourceManager(ktkIResourceManager* p_manager) noexcept
{
	this->m_p_resource_manager = p_manager;
}

ktkIRenderDevice* ktkMainManager::getRenderDevice(void) const noexcept
{
	return this->m_p_manager_render_device;
}

void ktkMainManager::setRenderDevice(ktkIRenderDevice* pointer) noexcept
{
	this->m_p_manager_render_device = pointer;
}

ktkIRenderResourceManager* ktkMainManager::GetRenderResourceManager(
	void) const noexcept
{
	return this->m_p_manager_render_resource;
}

void ktkMainManager::SetRenderResourceManager(
	ktkIRenderResourceManager* pointer) noexcept
{
	this->m_p_manager_render_resource = pointer;
}

ktkIRenderSwapchain* ktkMainManager::getRenderSwapchainManager(
	void) const noexcept
{
	return this->m_p_manager_swapchain;
}

void ktkMainManager::setRenderSwapchainManager(
	ktkIRenderSwapchain* pointer) noexcept
{
	this->m_p_manager_swapchain = pointer;
}

void ktkMainManager::Set_EngineConfig(ktkIEngineConfig* pointer) noexcept
{
	this->m_p_manager_config = pointer;
}

ktkIEngineConfig* ktkMainManager::Get_EngineConfig(void) const noexcept
{
	return this->m_p_manager_config;
}

ktkIWindowManager* ktkMainManager::Get_WindowManager(void) const noexcept
{
	return this->m_p_manager_window;
}

void ktkMainManager::Set_WindowManager(
	ktkIWindowManager* p_window_manager) noexcept
{
	this->m_p_manager_window = p_window_manager;
}

ktkIImguiWrapper* ktkMainManager::Get_ImguiWrapper(void) const noexcept
{
	return this->m_p_manager_imgui_wrapper;
}

void ktkMainManager::Set_ImguiWrapper(ktkIImguiWrapper* p_manager) noexcept
{
	this->m_p_manager_imgui_wrapper = p_manager;
}

ktkIGameUIManager* ktkMainManager::Get_GameUIEngine(void) const noexcept
{
	return this->m_p_game_ui_engine;
}

void ktkMainManager::Set_GameUIEngine(ktkIGameUIManager* p_manager) noexcept
{
	this->m_p_game_ui_engine = p_manager;
}

ktkILogger* ktkMainManager::Get_Logger(void) const noexcept 
{
	return this->m_p_logger;
}

void ktkMainManager::Set_Logger(ktkILogger* p_logger) noexcept 
{
	this->m_p_logger = p_logger;
}

ktkIWindowSplash* ktkMainManager::Get_Splash(void) const noexcept 
{
	return this->m_p_splash;
}

void ktkMainManager::Set_Splash(ktkIWindowSplash* p_window) noexcept 
{
	this->m_p_splash = p_window;
}

void ktkMainManager::Initialize(void)
{
	if (this->m_p_manager_config)
	{
		this->m_p_manager_config->SetARGC(this->m_argc);
		this->m_p_manager_config->SetARGV(this->m_argv);
	}
}

void ktkMainManager::Shutdown(void) {}

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK
