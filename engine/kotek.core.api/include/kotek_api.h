#pragma once

#include "kotek_api_resource_manager.h"
#include "kotek_sdk_ui_element.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
		class ktkIRenderDevice;
		class ktkIRenderSwapchain;
		class ktkIRenderGraph;
		class kotek_i_render_imgui;
		class ktkIRenderResourceManager;
		class kotek_i_renderer;
		class ktkProfiler;
		class ktkConsole;
	} // namespace Core

	namespace Engine
	{
		class ktkWindow;
	}

	namespace ktk
	{
		class string;
	}
} // namespace Kotek

struct GLFWwindow;

namespace Kotek
{
	namespace Core
	{
		class ktkIRenderDevice
		{
		public:
			virtual ~ktkIRenderDevice(void) {}

			virtual void Initialize(Core::ktkMainManager& main_manager) = 0;
			virtual void Shutdown(void) = 0;
			virtual void Resize(ktkIRenderSwapchain* p_raw_swapchain,
				kotek_i_renderer* p_raw_renderer,
				ktkIRenderResourceManager* p_raw_resource_manager, int width,
				int height) = 0;

			virtual int GetWidth(void) const noexcept = 0;
			virtual int GetHeight(void) const noexcept = 0;
			virtual void GPUFlush(void) = 0;
		};

		class ktkIRenderSwapchain
		{
		public:
			virtual ~ktkIRenderSwapchain(void) {}

			virtual void Initialize(ktkIRenderDevice* p_render_device) = 0;
			virtual void Shutdown(ktkIRenderDevice* p_render_device) = 0;
			virtual void Resize(
				ktkIRenderDevice* p_render_device, int width, int height) = 0;
		};

		class ktkIRenderResourceManager
		{
		public:
			virtual ~ktkIRenderResourceManager(void) {}

			// TODO: change signature on void
			virtual void initialize(ktkIRenderDevice* p_raw_device,
				ktkIRenderSwapchain* p_raw_swapchain) = 0;

			// TODO: change signature on void
			virtual void shutdown(ktkIRenderDevice* p_raw_device) = 0;

			virtual void Resize(ktkIRenderDevice* p_raw_device,
				ktkIRenderSwapchain* p_raw_swapchain) = 0;
		};

		class kotek_i_render_imgui
		{
		public:
			virtual ~kotek_i_render_imgui(void) {}

			// TODO: change signature on void
			virtual void initialize(ktkMainManager& main_manager) noexcept = 0;

			// TODO: change signature on void
			virtual void shutdown(ktkIRenderDevice* p_raw_device) noexcept = 0;
		};

		class ktkIRenderGraph
		{
		public:
			virtual ~ktkIRenderGraph(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class kotek_i_renderer
		{
		public:
			virtual ~kotek_i_renderer(void) {}
			virtual void draw(void) = 0;
			virtual void Shutdown(void) = 0;
			virtual void Resize(void) = 0;
			virtual ktk::string GetName(void) const noexcept = 0;
		};

		class ktkIConsole
		{
		public:
			virtual ~ktkIConsole(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class ktkIFileSystem
		{
		public:
			virtual ~ktkIFileSystem(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class ktkIInput
		{
		public:
			virtual ~ktkIInput(void) {}

			virtual void Initialize(void) = 0;
			virtual void Shutdown(void) = 0;
		};

		class ktkIGameManager
		{
		public:
			virtual ~ktkIGameManager(void) {}

			virtual void Initialize(
				Kotek::Core::ktkMainManager* p_main_manager) = 0;

			virtual void Shutdown(
				Kotek::Core::ktkMainManager* p_main_manager) = 0;

			virtual kotek_i_renderer* GetRenderer(void) const noexcept = 0;

			virtual void* GetWindowHandle(void) const noexcept = 0;
			virtual ktkProfiler* GetProfiler(void) const noexcept = 0;
			virtual int GetWindowWidth(void) const noexcept = 0;
			virtual int GetWindowHeight(void) const noexcept = 0;
			virtual ktkConsole* GetConsole(void) const noexcept = 0;

			// @ returns USER render resource manager it's not kotek
			virtual void* GetRenderResourceManager(void) const noexcept = 0;
			virtual void* CreateSurface(ktkMainManager* p_main_manager,
				void* p_instance, const void* p_callbacks) = 0;
		};

		bool InitializeModule_Core_API(ktkMainManager*);
		bool ShutdownModule_Core_API(ktkMainManager*);
		bool SerializeModule_Core_API(ktkMainManager*);
		bool DeserializeModule_Core_API(ktkMainManager*);
	} // namespace Core
} // namespace Kotek