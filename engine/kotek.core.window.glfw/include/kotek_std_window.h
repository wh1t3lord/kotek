#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.os/include/kotek_core_os.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>

namespace Kotek
{
	namespace Core
	{
		enum class eEngineFeature;
	} // namespace Core

} // namespace Kotek

namespace Kotek
{
	namespace Core
	{
		class ktkWindow
		{
		public:
			ktkWindow(Core::eEngineFeature current_render);
			ktkWindow(const ktk::string& title_name, Core::eEngineFeature current_render);
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
			void Initialize(Core::eEngineFeature current_render);

			void ObtainInformationAboutDisplay(void);

		private:
			int m_screen_size_width;
			int m_screen_size_height;
			GLFWwindow* m_p_window;
			ktk::string m_title_name;
		};
	} // namespace Engine
} // namespace Kotek