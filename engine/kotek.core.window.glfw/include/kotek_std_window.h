#pragma once

#include <kotek.core.defines.static.os/include/kotek_core_defines_static_os.h>
#include <kotek.core.containers.string/include/kotek_core_containers_string.h>
#include <kotek.core.os/include/kotek_core_os.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>
#include <kotek.core.defines_dependent.message/include/kotek_core_defines_dependent_message.h>
#include <kotek.core.api/include/kotek_api.h>

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
		class ktkWindow : public ktkIWindow
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

			void RegisterUserMainManager(
				Core::ktkMainManager* p_manager) noexcept;

			int GetWidth(void) const noexcept override;
			int GetHeight(void) const noexcept override;
			void* GetHandle(void) const noexcept override;

			void Initialize(Core::eEngineFeature current_render) override;
			void Shutdown(void) override;

			void MakeContextCurrent(void) noexcept override;
			void PollEvents(void) override;
			bool Is_NeedToClose(void) override;

		private:
			void ObtainInformationAboutDisplay(void);

		private:
			int m_screen_size_width;
			int m_screen_size_height;
			GLFWwindow* m_p_window;
			ktk::string m_title_name;
		};
	} // namespace Engine
} // namespace Kotek