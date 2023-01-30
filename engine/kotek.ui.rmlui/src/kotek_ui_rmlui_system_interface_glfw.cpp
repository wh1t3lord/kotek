#include "../include/kotek_ui_rmlui_system_interface_glfw.h"

#include <kotek.core.window/include/kotek_core_window.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

ktkSystemInterface_GLFW::ktkSystemInterface_GLFW()
{
	cursor_pointer = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
	cursor_cross = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	cursor_text = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
}

ktkSystemInterface_GLFW::~ktkSystemInterface_GLFW()
{
	glfwDestroyCursor(cursor_pointer);
	glfwDestroyCursor(cursor_cross);
	glfwDestroyCursor(cursor_text);
}

void ktkSystemInterface_GLFW::SetWindow(GLFWwindow* in_window)
{
	window = in_window;
}

double ktkSystemInterface_GLFW::GetElapsedTime()
{
	return glfwGetTime();
}

void ktkSystemInterface_GLFW::SetMouseCursor(const Rml::String& cursor_name)
{
	GLFWcursor* cursor = nullptr;

	if (cursor_name.empty() || cursor_name == "arrow")
		cursor = nullptr;
	else if (cursor_name == "move")
		cursor = cursor_pointer;
	else if (cursor_name == "pointer")
		cursor = cursor_pointer;
	else if (cursor_name == "resize")
		cursor = cursor_pointer;
	else if (cursor_name == "cross")
		cursor = cursor_cross;
	else if (cursor_name == "text")
		cursor = cursor_text;
	else if (cursor_name == "unavailable")
		cursor = nullptr;

	if (window)
		glfwSetCursor(window, cursor);
}

void ktkSystemInterface_GLFW::SetClipboardText(const Rml::String& text_utf8)
{
	if (window)
		glfwSetClipboardString(window, text_utf8.c_str());
}

void ktkSystemInterface_GLFW::GetClipboardText(Rml::String& text)
{
	if (window)
		text = Rml::String(glfwGetClipboardString(window));
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
