#pragma once

#include "../kotek.core/kotek_std.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_vulkan.h"
#include "imgui_impl_opengl3.h"
#include "kotek_engine_keycodes.h"
#include "vk_mem_alloc.h"

#ifdef KOTEK_PLATFORM_WINDOWS
	#include "imgui_impl_dx12.h"
	#include "imgui_impl_dx9.h"
	#include "imgui_impl_win32.h"
	#include <ShellScalingApi.h>
	#include <dwmapi.h>
	#include <windows.h>
#elif KOTEK_PLATFORM_LINUX
#endif

namespace Kotek
{
	// sui = sdkui
	namespace sui = ImGui;
} // namespace Kotek

namespace Kotek
{
	namespace Engine
	{
		class ktkWindow
		{
		public:
			ktkWindow(void);
			ktkWindow(const ktk::string& title_name);
			~ktkWindow(void);

			/// <summary>
			/// Be careful with that method, because it shutdowns Engine and
			/// Window!
			/// </summary>
			/// <param name=""></param>
			/// <returns></returns>
			void CloseWindow(void) noexcept;
			void ShowWindow(void) noexcept;
			void HideWindow(void) noexcept;

			int GetWidth(void) const noexcept;
			int GetHeight(void) const noexcept;

			void RegisterUserMainManager(
				Core::ktkMainManager* p_manager) noexcept;

			GLFWwindow* GetHandle(void) const noexcept;

			void Shutdown(void);

		private:
			void Initialize(void);

			void ObtainInformationAboutDisplay(void);

		private:
			int m_screen_size_width;
			int m_screen_size_height;
			GLFWwindow* m_p_window;
			ktk::string m_title_name;
		};
	} // namespace Engine
} // namespace Kotek