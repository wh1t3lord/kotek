#pragma once

#include "kotek_sdk_ui_element.h"

namespace Kotek
{
	namespace Core
	{
		class ktkMainManager;
		class kotek_i_render_device;
		class kotek_i_render_swapchain;
		class kotek_i_render_graph;
		class kotek_i_render_imgui;
		class kotek_i_render_resource_manager;
		class kotek_i_renderer;
		class ktkProfiler;
		class ktkConsole;
	} // namespace Core

	namespace Engine
	{
		class ktkWindow;
	}
} // namespace Kotek

struct GLFWwindow;

namespace Kotek
{
	namespace Core
	{
		class kotek_i_render_device
		{
		public:
			virtual ~kotek_i_render_device(void) {}

			// TODO: change signature on void
			virtual void initialize(Core::ktkMainManager& main_manager) = 0;

			virtual void shutdown(void) = 0;

			// TODO: change signature on void
			virtual void resize(kotek_i_render_swapchain* p_raw_swapchain,
				kotek_i_renderer* p_raw_renderer,
				kotek_i_render_resource_manager* p_raw_resource_manager,
				int width, int height) = 0;
			virtual int getWidth(void) const noexcept = 0;
			virtual int getHeight(void) const noexcept = 0;
			virtual void GPUFlush(void) = 0;
		};

		class kotek_i_render_swapchain
		{
		public:
			virtual ~kotek_i_render_swapchain(void) {}

			// TODO: change signature on void
			virtual void initialize(kotek_i_render_device* p_render_device) = 0;

			// TODO: change signature on void
			virtual void shutdown(kotek_i_render_device* p_render_device) = 0;

			// TODO: change signature on void, but int keep
			virtual void resize(kotek_i_render_device* p_render_device,
				int width, int height) = 0;
		};

		class kotek_i_render_resource_manager
		{
		public:
			virtual ~kotek_i_render_resource_manager(void) {}

			// TODO: change signature on void
			virtual void initialize(kotek_i_render_device* p_raw_device,
				kotek_i_render_swapchain* p_raw_swapchain) = 0;

			// TODO: change signature on void
			virtual void shutdown(kotek_i_render_device* p_raw_device) = 0;
		};

		class kotek_i_render_imgui
		{
		public:
			virtual ~kotek_i_render_imgui(void) {}

			// TODO: change signature on void
			virtual void initialize(ktkMainManager& main_manager) noexcept = 0;

			// TODO: change signature on void
			virtual void shutdown(
				kotek_i_render_device* p_raw_device) noexcept = 0;
		};

		class kotek_i_render_graph
		{
		public:
			virtual ~kotek_i_render_graph(void) {}

			virtual void initialize(void) = 0;
			virtual void shutdown(void) = 0;
		};

		class kotek_i_renderer
		{
		public:
			virtual ~kotek_i_renderer(void) {}
			virtual void draw(void) = 0;
			virtual void Shutdown(void) = 0;
			virtual void Resize(void) = 0;
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

			
			virtual kotek_i_renderer* GetRenderer(
				void) const noexcept = 0;

			virtual void* GetWindowHandle(void) const noexcept = 0;
			virtual ktkProfiler* GetProfiler(void) const noexcept = 0;
			virtual int GetWindowWidth(void) const noexcept = 0;
			virtual int GetWindowHeight(void) const noexcept = 0;
			virtual ktkConsole* GetConsole(void) const noexcept = 0;

			virtual void* CreateSurface(void* p_instance, const void* p_callbacks) = 0;
		};

		bool initializeModule_Core_API(void);
		bool serializeModule_Core_API(void);
		bool deserializeModule_Core_API(void);
		bool shutdownModule_Core_API(void);
	} // namespace Core
} // namespace Kotek