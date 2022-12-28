#include "../include/kotek_std_window.h"
#include <kotek.core.api/include/kotek_api.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_CORE

ktkWindow::ktkWindow(void) :
	m_screen_size_width{}, m_screen_size_height{}, m_p_window{nullptr}
{
	this->SetStringToTitle(
		static_cast<ktk::enum_base_t>(eWindowTitleType::kTitle_ApplicationName),
		"Kotek Engine");
}

ktkWindow::ktkWindow(const ktk::string& title_name) :
	m_screen_size_width{}, m_screen_size_height{}, m_p_window{nullptr}
{
	this->SetStringToTitle(
		static_cast<ktk::enum_base_t>(eWindowTitleType::kTitle_ApplicationName),
		title_name.get_as_legacy().c_str());
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

void ktkWindow::Initialize(Core::eEngineSupportedOpenGLVersion version)
{
	if (!glfwInit())
	{
		KOTEK_ASSERT(false, "can't initialize GLFW");
		return;
	}

	KOTEK_ASSERT(version != Core::eEngineSupportedOpenGLVersion::kUnknown,
		"you must pass a valid version of OpenGL what you want to initialize "
		"for");

	switch (version)
	{
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_1_0:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_1_1:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_1_2:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_1_3:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_1_4:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_1_5:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_2_0:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_2_1:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_3_0:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_3_1:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_3_2:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_3_3:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_4_0:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_4_1:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_4_2:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_4_3:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_4_4:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_4_5:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		break;
	}
	case Core::eEngineSupportedOpenGLVersion::kOpenGL_4_6:
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		break;
	}
	default:
	{
		// TODO: create preprocessor for defininng major and minor version
		// through preprocessor and configurable from cmake for user
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		break;
	}
	}

	// TODO: make changable core or compat profile choosing, again you need to
	// create configurable macro for this
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->ObtainInformationAboutDisplay();

	this->m_p_window = glfwCreateWindow(this->m_screen_size_width,
		this->m_screen_size_height, this->GetTitle().c_str(), nullptr, nullptr);

	if (!this->m_p_window)
	{
		glfwTerminate();
		KOTEK_ASSERT(false, "can't create GLFW window");
		return;
	}
}

void ktkWindow::Initialize(Core::eEngineSupportedDirectXVersion version)
{
	if (!glfwInit())
	{
		KOTEK_ASSERT(false, "can't initialize GLFW");
		return;
	}

	KOTEK_ASSERT(version != Core::eEngineSupportedDirectXVersion::kUnknown,
		"you must pass a valid version of DirectX what you want to initialize "
		"for");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

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

void ktkWindow::Initialize(Core::eEngineSupportedVulkanVersion version)
{
	if (!glfwInit())
	{
		KOTEK_ASSERT(false, "can't initialize GLFW");
		return;
	}

	KOTEK_ASSERT(version != Core::eEngineSupportedVulkanVersion::kUnknown,
		"you must pass a valid version of Vulkan what you want to initialize "
		"for");

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

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
			KOTEK_MESSAGE("{}", ktk::string(description_error).get_as_is());
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

void ktkWindow::SetStringToTitle(
	ktk::enum_base_t id, const char* p_utf8_or_char_string) noexcept
{
	KOTEK_ASSERT(p_utf8_or_char_string,
		"you can't pass an invalid pointer of string here");

	this->m_titles[id] = p_utf8_or_char_string;

	if (this->m_p_window)
	{
		glfwSetWindowTitle(this->m_p_window, this->GetTitle().c_str());
	}
}

void ktkWindow::RemoveStringFromTitle(ktk::enum_base_t id) noexcept
{
	if (this->m_titles.find(id) != this->m_titles.end())
	{
		this->m_titles.erase(id);
	}
}

ktk::string_legacy ktkWindow::GetTitle(void) const noexcept
{
	ktk::string_legacy result;

	for (const auto& [id, string] : this->m_titles)
	{
		result += string;
		result += " ";
	}

	result.pop_back();

	return result;
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

KOTEK_END_NAMESPACE_CORE
KOTEK_END_NAMESPACE_KOTEK