#include "../include/kotek_std_window.h"
#include <kotek.core.api/include/kotek_api.h>

namespace Kotek
{
	namespace Core
	{
		ktkWindow::ktkWindow(void) : m_p_window{nullptr} {}

		ktkWindow::ktkWindow(const ktk::string& title_name) :
			m_p_window{nullptr}, m_title_name{title_name}
		{
		}

		ktkWindow::~ktkWindow(void) {}

		void ktkWindow::CloseWindow(void) noexcept
		{
			if (this->m_p_window == nullptr)
				return;

			glfwSetWindowShouldClose(this->m_p_window, GLFW_TRUE);
		}

		void ktkWindow::ShowWindow(void) noexcept
		{
			glfwShowWindow(this->m_p_window);
		}

		void ktkWindow::HideWindow(void) noexcept
		{
			glfwHideWindow(this->m_p_window);
		}

		int ktkWindow::GetWidth(void) const noexcept
		{
			if (this->m_p_window == nullptr)
			{
				KOTEK_MESSAGE_WARNING(
					"you can't call this until you initialize window");
				return 0;
			}

			int result_width;
			int dummy_height;

			glfwGetWindowSize(this->m_p_window, &result_width, &dummy_height);

			return result_width;
		}

		int ktkWindow::GetHeight(void) const noexcept
		{
			if (this->m_p_window == nullptr)
			{
				KOTEK_MESSAGE_WARNING(
					"you can't call this until you initialize window");
				return 0;
			}

			int result_height;

			int dummy_width;

			glfwGetWindowSize(this->m_p_window, &dummy_width, &result_height);

			return result_height;
		}

		void ktkWindow::RegisterUserMainManager(
			Core::ktkMainManager* p_manager) noexcept
		{
			KOTEK_ASSERT(p_manager, "you can't pass an invalid manager");
			KOTEK_ASSERT(this->m_p_window, "you can't have an invalid window");

			glfwSetWindowUserPointer(this->m_p_window, p_manager);
		}

		void* ktkWindow::GetHandle(void) const noexcept
		{
			return this->m_p_window;
		}

		void ktkWindow::Initialize(Core::eEngineFeature current_render)
		{
			if (!glfwInit())
			{
				KOTEK_ASSERT(false, "can't initialize GLFW");
				return;
			}

			if (current_render <
					Core::eEngineFeature::kEngine_Render_Renderer_OpenGL3_3 ||
				current_render >
					Core::eEngineFeature::kEngine_Render_Renderer_OpenGL4_6)
			{
				glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			}
			else
			{
				if (current_render ==
					Core::eEngineFeature::kEngine_Render_Renderer_OpenGL3_3)
				{
					glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
					glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				}
				else if (current_render ==
					Core::eEngineFeature::kEngine_Render_Renderer_OpenGL4_6)
				{
					glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
					glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
				}

				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			}

			this->ObtainInformationAboutDisplay();

			this->m_p_window = glfwCreateWindow(this->m_screen_size_width,
				this->m_screen_size_height, "Kotek Engine", nullptr, nullptr);

			if (!this->m_p_window)
			{
				glfwTerminate();
				KOTEK_ASSERT(false, "can't create GLFW window");
				return;
			}
		}

		void ktkWindow::Shutdown(void)
		{
			if (this->m_p_window)
			{
				this->CloseWindow();
				glfwDestroyWindow(this->m_p_window);
				glfwTerminate();
				this->m_p_window = nullptr;
			}
		}

		void ktkWindow::MakeContextCurrent(void) noexcept
		{
			if (this->m_p_window)
			{
				glfwMakeContextCurrent(this->m_p_window);

#ifdef KOTEK_DEBUG
				const char* description_error{};
				if (glfwGetError(&description_error))
				{
					KOTEK_MESSAGE(
						"{}", ktk::string(description_error).get_as_is());
				}
#endif
			}
		}

		void ktkWindow::PollEvents(void)
		{
			glfwPollEvents();

#ifdef KOTEK_DEBUG
			const char* description_error{};
			if (glfwGetError(&description_error))
			{
				KOTEK_MESSAGE("{}", ktk::string(description_error).get_as_is());
			}
#endif
		}

		bool ktkWindow::Is_NeedToClose(void)
		{
			return glfwWindowShouldClose(this->m_p_window);
		}

		void ktkWindow::ObtainInformationAboutDisplay(void)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

			if (!mode)
			{
				const char* message;
				glfwGetError(&message);
				KOTEK_ASSERT(false, "{}", ktk::string(message).get_as_is());
				return;
			}

#ifdef KOTEK_DEBUG
			KOTEK_MESSAGE("display width: {}", mode->width);
			KOTEK_MESSAGE("display height: {}", mode->height);
#endif

			this->m_screen_size_height = mode->height;
			this->m_screen_size_width = mode->width;
		}

	} // namespace Core
} // namespace Kotek