#include "../include/kotek_engine_window_impl.h"
#include <kotek.core/include/kotek_main_manager.h>

namespace Kotek
{
	namespace Engine
	{
		ktkWindow::ktkWindow(Core::eEngineFeature current_render) :
			m_p_window(nullptr)
		{
			this->Initialize(current_render);
		}

		ktkWindow::ktkWindow(const ktk::string& title_name,
			Core::eEngineFeature current_render) :
			m_p_window(nullptr),
			m_title_name(title_name)
		{
			this->Initialize(current_render);
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

		GLFWwindow* ktkWindow::GetHandle(void) const noexcept
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

			if (current_render !=
				Core::eEngineFeature::kEngine_Render_Renderer_OpenGL)
			{
				glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			}
			else
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

			if (current_render ==
				Core::eEngineFeature::kEngine_Render_Renderer_OpenGL)
			{
				glfwMakeContextCurrent(this->m_p_window);

				const char* p_description;

				if (glfwGetError(&p_description) != GLFW_NO_ERROR)
				{
					KOTEK_MESSAGE_ERROR_LEGACY(p_description);
				}

				if (!gladLoadGLLoader(
						reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
				{
					KOTEK_ASSERT(false,
						"failed to gladLoadGLLoader. Can't initialize OpenGL "
						"for this system");
					return;
				}
			}
		}

		void ktkWindow::Shutdown(void)
		{
			this->CloseWindow();
			glfwDestroyWindow(this->m_p_window);
			glfwTerminate();
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

	} // namespace Engine
} // namespace Kotek