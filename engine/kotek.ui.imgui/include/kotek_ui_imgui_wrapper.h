#pragma once

#include <kotek.core.api/include/kotek_api.h>

namespace Kotek
{
	namespace UI
	{
		class ktkImguiWrapper : public Core::ktkIImguiWrapper
		{
		public:
			ktkImguiWrapper(void);
			~ktkImguiWrapper(void);

			void ImGui_ImplGlfw_NewFrame(void) override;

			bool ImGui_ImplOpenGL3_Init(
				const char* glsl_version = nullptr) override;
			void ImGui_ImplOpenGL3_NewFrame(void) override;
			void ImGui_ImplOpenGL3_Shutdown(void) override;

			/// \~russian @brief Обертка над ImGui_ImplGlfw_Shutdown
			/// @param void, ничего не принимает в качестве аргументов
			///
			/// \~english @brief Wraps ImGui_ImplGlfw_Shutdown function
			/// @param void, nothing takes as input
			void ImGui_ImplGlfw_Shutdown(void) override;

			/// \~russian @brief Обертка над ImGui_ImplGlfw_InitForOpenGL
			/// функцией
			/// @param window_handle указатель на дескриптор окна для GLFW
			/// библиотеки это GLFWwindow*
			/// @param install_callbacks см. документацию ImGui о
			/// ImGui_ImplGlfw_InitForOpenGL
			///
			/// \~english @brief Wraps ImGui_ImplGlfw_InitForOpenGL function
			/// @param window_handle it is GLFWwindow* type
			/// @param install_callbacks see ImGui's documentation about
			/// ImGui_ImplGlfw_InitForOpenGL
			///
			/// @code
			///
			/// // somewhere in user code context that defines ui initialization
			/// for OpenGL
			///
			/// // somehow obtained
			/// Kotek::Core::ktkMainManager* p_main_manager = ...;
			///
			/// Kotek::Core::ktkIImguiWrapper* p_imgui_wrapper =
			/// p_main_manager->Get_ImguiWrapper();
			///
			/// GLFWwindow* p_handle =
			/// static_cast<GLFWwindow*>(p_main_manager->GetGameManager()->GetWindowHandle());
			///
			/// p_imgui_wrapper->ImGui_ImplGlfw_InitForOpenGL(p_handle, true);
			///
			/// @endcode
			bool ImGui_ImplGlfw_InitForOpenGL(
				void* window_handle, bool install_callbacks) override;

			/// \~russian @brief Вызывает ImGui::CreateContext
			/// @param shared_font_atlas см. описание ImGui::CreateContext
			/// @return ImFontAtlas* (см. документацию ImGui)
			///
			/// \~english @brief Wraps ImGui::CreateContext function
			/// @param shared_font_atlas see ImGui's documentation about
			/// ImGui::CreateContext function
			/// @return ImFontAtlas* (see ImGui's documentation)
			///
			/// @code
			///
			/// // we somehow got our main manager
			/// Kotek::Core::ktkMainManager* p_main_manager = ...;
			///
			/// Kotek::Core::ktkIImguiWrapper* p_wrapper =
			/// p_main_manager->Get_ImguiWrapper();
			///
			/// ImFontAtlas* p_atlas =
			/// static_cast<ImFontAtlas*>(p_wrapper->CreateContext());
			/// @endcode
			void* CreateContext(void* shared_font_atlas = nullptr) override;

			/// \~russian @brief Вызывает ImGui::DestroyContext
			/// @param context см. документацию ImGui по ImGui::DestroyContext
			///
			/// \~english @brief Wraps ImGui::DestroyContext
			/// @param context see ImGui's documentation about
			/// ImGui::DestroyContext
			void DestroyContext(void* context = nullptr) override;

			/// \~russian @brief Обертка над ImGui::GetIO() функцией
			/// @param void, ничего не принимает
			/// @return void* раскрывается как ImGuiIO*
			///
			/// \~english @brief Wraps ImGui::GetIO() function
			/// @param void, nothing takes as input
			/// @return void* is ImGuiIO*
			///
			/// @code
			/// // we somehow got our main manager
			/// Kotek::Core::ktkMainManager* p_main_manager = ...;
			///
			/// Kotek::Core::ktkIImguiWrapper* p_wrapper =
			/// p_main_manager->Get_ImguiWrapper(); ImGuiIO* p_io =
			/// static_cast<ImGuiIO*>(p_wrapper->GetIO());
			/// @endcode
			void* GetIO(void) override;

			/// \~russian @brief Обертка над ImGui::GetStyle() функцией
			/// @param  void, ничего не принимает
			/// @return void* раскрывается как ImGuiStyle*
			///
			/// \~english @brief Wraps ImGui::GetStyle() function
			/// @param void, nothing takes as input
			/// @return void* is ImGuiStyle*
			///
			/// @code
			/// // we somehow got our main manager
			/// Kotek::Core::ktkMainManager* p_main_manager = ...;
			/// Kotek::Core::ktkIImguiWrapper* p_wrapper =
			/// p_main_manager->Get_ImguiWrapper();
			///
			/// ImGuiStyle* p_style =
			/// static_cast<ImGuiStyle*>(p_wrapper->GetStyle());
			///
			/// @endcode
			void* GetStyle(void) override;

			/// \~russian @brief Обертка над ImGui::StyleColorsDark() функцией
			/// @param style см. документацию ImGui о ImGui::StyleColorsDark
			/// функции
			///
			/// \~english @brief Wraps ImGui::StyleColorsDark() function
			/// @param style see ImGui's documentation about
			/// ImGui::StyleColorsDark function
			///
			/// @code
			/// // we got somehow our initialized main manager, better to see original use of ImGui::StyleColorsDark in ImGui examples
			/// Kotek::Core::ktkMainManager* p_main_manager = ...;
			///
			/// Kotek::Core::ktkIImguiWrapper* p_imgui_wrapper =
			/// p_main_manager->Get_ImguiWrapper();
			///
			/// p_imgui_wrapper->StyleColorsDark();
			///
			/// @endcode
			void StyleColorsDark(void* style = nullptr) override;

			void NewFrame(void) override;

			/// \~russian @brief Обертка над ImGui::Render() функцией
			/// @param void, ничего не принимает в качестве аргументов
			///
			/// \~english @brief Wraps ImGui::Render() function
			/// @param void, nothing takes as input
			///
			/// @code
			/// // we got somehow our main manager, better to see original use of ImGui::Render in ImGui examples
			/// Kotek::Core::ktkMainManager* p_main_manager = ...;
			///
			/// Kotek::Core::ktkIImguiWrapper* p_imgui_wrapper =
			/// p_main_manager->Get_ImguiWrapper();
			///
			/// p_imgui_wrapper->Render();
			///
			/// @endcode
			void Render(void) override;
		};
	} // namespace UI
} // namespace Kotek
