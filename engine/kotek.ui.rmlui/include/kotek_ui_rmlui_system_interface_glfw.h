#pragma once

#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>

#ifdef KOTEK_USE_RMLUI_LIBRARY
	#include <RmlUi/Core/SystemInterface.h>
#endif

class GLFWwindow;
class GLFWcursor;

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

class ktkSystemInterface_GLFW : public Rml::SystemInterface
{
public:
	ktkSystemInterface_GLFW();
	~ktkSystemInterface_GLFW();

	// Optionally, provide or change the window to be used for setting the mouse
	// cursors and clipboard text.
	void SetWindow(GLFWwindow* window);

	// -- Inherited from Rml::SystemInterface  --

	double GetElapsedTime() override;

	void SetMouseCursor(const Rml::String& cursor_name) override;

	void SetClipboardText(const Rml::String& text) override;
	void GetClipboardText(Rml::String& text) override;

private:
	GLFWwindow* window = nullptr;

	GLFWcursor* cursor_pointer = nullptr;
	GLFWcursor* cursor_cross = nullptr;
	GLFWcursor* cursor_text = nullptr;
};

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
