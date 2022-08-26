#include "../include/kotek_ui_imgui_wrapper.h"

#include <kotek.ui.imgui/include/kotek_ui_imgui.h>

namespace Kotek
{
	namespace UI
	{
		ktkImguiWrapper::ktkImguiWrapper(void) {}

		ktkImguiWrapper::~ktkImguiWrapper(void) {}

		void ktkImguiWrapper::ImGui_ImplGlfw_NewFrame(void)
		{
			::ImGui_ImplGlfw_NewFrame();
		}

		bool ktkImguiWrapper::ImGui_ImplOpenGL3_Init(const char* glsl_version)
		{
			return ::ImGui_ImplOpenGL3_Init();
		}

		void ktkImguiWrapper::ImGui_ImplOpenGL3_NewFrame(void)
		{
			::ImGui_ImplOpenGL3_NewFrame();
		}

		void ktkImguiWrapper::ImGui_ImplOpenGL3_Shutdown(void)
		{
			::ImGui_ImplOpenGL3_Shutdown();
		}

		void ktkImguiWrapper::ImGui_ImplGlfw_Shutdown(void)
		{
			::ImGui_ImplGlfw_Shutdown();
		}

		bool ktkImguiWrapper::ImGui_ImplGlfw_InitForOpenGL(
			void* window_handle, bool install_callbacks)
		{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
			return ::ImGui_ImplGlfw_InitForOpenGL(
				static_cast<GLFWwindow*>(window_handle), install_callbacks);
#else
			return false;
#endif
		}

		void* ktkImguiWrapper::CreateContext(void* shared_font_atlas)
		{
			return ImGui::CreateContext(
				static_cast<ImFontAtlas*>(shared_font_atlas));
		}

		void ktkImguiWrapper::DestroyContext(void* context)
		{
			ImGui::DestroyContext(static_cast<ImGuiContext*>(context));
		}

		void* ktkImguiWrapper::GetIO(void)
		{
			return &ImGui::GetIO();
		}

		void* ktkImguiWrapper::GetStyle(void)
		{
			return &ImGui::GetStyle();
		}

		void ktkImguiWrapper::StyleColorsDark(void* style)
		{
			ImGui::StyleColorsDark(static_cast<ImGuiStyle*>(style));
		}

		void ktkImguiWrapper::NewFrame(void)
		{
			ImGui::NewFrame();
		}

		void ktkImguiWrapper::Render(void)
		{
			ImGui::Render();
		}
	} // namespace UI
} // namespace Kotek
