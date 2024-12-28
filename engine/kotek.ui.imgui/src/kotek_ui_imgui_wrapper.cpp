#include "../include/kotek_ui_imgui_wrapper.h"

#include <kotek.ui.imgui/include/kotek_ui_imgui.h>
#include <kotek.core.math/include/kotek_core_math.h>

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

ktkImguiWrapper::ktkImguiWrapper(void) {}

ktkImguiWrapper::~ktkImguiWrapper(void) {}

void ktkImguiWrapper::EditDragVec2f(
	const char* label, ktk::math::vector2f* p_vec)
{
	if (p_vec == nullptr)
		return;

	if (this->CollapsingHeader(label))
	{
		float value_x = p_vec->x();
		if (this->DragFloat("X##Vec2f_X", &value_x))
		{
			p_vec->x() = value_x;
		}

		float value_y = p_vec->y();
		if (this->DragFloat("Y##Vec2f_Y", &value_y))
		{
			p_vec->y() = value_y;
		}
	}
}

void ktkImguiWrapper::EditDragVec3f(
	const char* label, ktk::math::vector3f* p_vec)
{
	if (p_vec == nullptr)
		return;

	if (this->CollapsingHeader(label))
	{
		float value_x = p_vec->x();
		if (this->DragFloat("X##Vec3f_X", &value_x))
		{
			p_vec->x() = value_x;
		}

		float value_y = p_vec->y();
		if (this->DragFloat("Y##Vec3f_Y", &value_y))
		{
			p_vec->y() = value_y;
		}

		float value_z = p_vec->z();
		if (this->DragFloat("Z##Vec3f_Z", &value_z))
		{
			p_vec->z() = value_z;
		}
	}
}

void ktkImguiWrapper::EditDragVec4f(
	const char* label, ktk::math::vector4f* p_vec)
{
	if (p_vec == nullptr)
		return;

	if (this->CollapsingHeader(label))
	{
		float value_x = p_vec->x();
		if (this->DragFloat("X##Vec4f_X", &value_x))
		{
			p_vec->x() = value_x;
		}

		float value_y = p_vec->y();
		if (this->DragFloat("Y##Vec4f_Y", &value_y))
		{
			p_vec->y() = value_y;
		}

		float value_z = p_vec->z();
		if (this->DragFloat("Z##Vec4f_Z", &value_z))
		{
			p_vec->z() = value_z;
		}

		float value_w = p_vec->w();
		if (this->DragFloat("W##Vec4f_W", &value_w))
		{
			p_vec->w() = value_w;
		}
	}
}

void ktkImguiWrapper::EditDragMat2x2f(
	const char* label, ktk::math::matrix2x2f* p_mat)
{
	if (p_mat == nullptr)
		return;

	if (this->CollapsingHeader(label))
	{
		if (this->CollapsingHeader("Row 0"))
		{
			float value_x = p_mat->Get_00();
			if (this->DragFloat("X (00)", &value_x))
			{
				p_mat->Set_00(value_x);
			}

			float value_y = p_mat->Get_01();
			if (this->DragFloat("Y (01)", &value_y))
			{
				p_mat->Set_01(value_y);
			}
		}

		if (this->CollapsingHeader("Row 1"))
		{
			float value_x = p_mat->Get_10();
			if (this->DragFloat("X (10)", &value_x))
			{
				p_mat->Set_10(value_x);
			}

			float value_y = p_mat->Get_11();
			if (this->DragFloat("Y (11)", &value_y))
			{
				p_mat->Set_11(value_y);
			}
		}
	}
}

void ktkImguiWrapper::EditDragMat3x3f(
	const char* label, ktk::math::matrix3x3f* p_mat)
{
	if (p_mat == nullptr)
		return;

	if (this->CollapsingHeader(label))
	{
		if (this->CollapsingHeader("Row 0"))
		{
			float value_x = p_mat->Get_00();
			if (this->DragFloat("X (00)", &value_x))
			{
				p_mat->Set_00(value_x);
			}

			float value_y = p_mat->Get_01();
			if (this->DragFloat("Y (01)", &value_y))
			{
				p_mat->Set_01(value_y);
			}

			float value_z = p_mat->Get_02();
			if (this->DragFloat("Z (02)", &value_z))
			{
				p_mat->Set_02(value_z);
			}
		}

		if (this->CollapsingHeader("Row 1"))
		{
			float value_x = p_mat->Get_10();
			if (this->DragFloat("X (10)", &value_x))
			{
				p_mat->Set_10(value_x);
			}

			float value_y = p_mat->Get_11();
			if (this->DragFloat("Y (11)", &value_y))
			{
				p_mat->Set_11(value_y);
			}

			float value_z = p_mat->Get_12();
			if (this->DragFloat("Z (12)", &value_z))
			{
				p_mat->Set_12(value_z);
			}
		}

		if (this->CollapsingHeader("Row 2"))
		{
			float value_x = p_mat->Get_20();
			if (this->DragFloat("X (20)", &value_x))
			{
				p_mat->Set_20(value_x);
			}

			float value_y = p_mat->Get_21();
			if (this->DragFloat("Y (21)", &value_y))
			{
				p_mat->Set_21(value_y);
			}

			float value_z = p_mat->Get_22();
			if (this->DragFloat("Z (22)", &value_z))
			{
				p_mat->Set_22(value_z);
			}
		}
	}
}

void ktkImguiWrapper::EditDragMat4x4f(
	const char* label, ktk::math::matrix4x4f* p_mat)
{
	if (p_mat == nullptr)
		return;

	if (this->CollapsingHeader(label))
	{
		if (this->CollapsingHeader("Row 0"))
		{
			float value_x = p_mat->operator[](0)[0];
			if (this->DragFloat("X (00)", &value_x))
			{
				p_mat->operator[](0)[0]=(value_x);
			}

			float value_y = p_mat->operator[](0)[1];
			if (this->DragFloat("Y (01)", &value_y))
			{
				p_mat->operator[](0)[1]=(value_y);
			}

			float value_z = p_mat->operator[](0)[2];
			if (this->DragFloat("Z (02)", &value_z))
			{
				p_mat->operator[](0)[2]=(value_z);
			}

			float value_w = p_mat->operator[](0)[3];
			if (this->DragFloat("W (03)", &value_w))
			{
				p_mat->operator[](0)[3]=(value_w);
			}
		}

		if (this->CollapsingHeader("Row 1"))
		{
			float value_x = p_mat->operator[](1)[0];
			if (this->DragFloat("X (10)", &value_x))
			{
				p_mat->operator[](1)[0]=(value_x);
			}

			float value_y = p_mat->operator[](1)[1];
			if (this->DragFloat("Y (11)", &value_y))
			{
				p_mat->operator[](1)[1]=(value_y);
			}

			float value_z = p_mat->operator[](1)[2];
			if (this->DragFloat("Z (12)", &value_z))
			{
				p_mat->operator[](1)[2]=(value_z);
			}

			float value_w = p_mat->operator[](1)[3];
			if (this->DragFloat("W (13)", &value_w))
			{
				p_mat->operator[](1)[3]=(value_w);
			}
		}

		if (this->CollapsingHeader("Row 2"))
		{
			float value_x = p_mat->operator[](2)[0];
			if (this->DragFloat("X (20)", &value_x))
			{
				p_mat->operator[](2)[0]=(value_x);
			}

			float value_y = p_mat->operator[](2)[1];
			if (this->DragFloat("Y (21)", &value_y))
			{
				p_mat->operator[](2)[1]=(value_y);
			}

			float value_z = p_mat->operator[](2)[2];
			if (this->DragFloat("Z (22)", &value_z))
			{
				p_mat->operator[](2)[2]=(value_z);
			}

			float value_w = p_mat->operator[](2)[3];
			if (this->DragFloat("W (23)", &value_w))
			{
				p_mat->operator[](2)[3]=(value_w);
			}
		}

		if (this->CollapsingHeader("Row 4"))
		{
			float value_x = p_mat->operator[](3)[0];
			if (this->DragFloat("X (30)", &value_x))
			{
				p_mat->operator[](3)[0]=(value_x);
			}

			float value_y = p_mat->operator[](3)[1];
			if (this->DragFloat("Y (31)", &value_y))
			{
				p_mat->operator[](3)[1]=(value_y);
			}

			float value_z = p_mat->operator[](3)[2];
			if (this->DragFloat("Z (32)", &value_z))
			{
				p_mat->operator[](3)[2]=(value_z);
			}

			float value_w = p_mat->operator[](3)[3];
			if (this->DragFloat("W (33)", &value_w))
			{
				p_mat->operator[](3)[3]=(value_w);
			}
		}
	}
}

void ktkImguiWrapper::EditDragQuatf(
	const char* label, ktk::math::quaternionf* p_quat)
{
	if (p_quat == nullptr)
		return;

	if (this->CollapsingHeader(label))
	{
		float value_x = p_quat->Get_X();
		if (this->DragFloat("X", &value_x))
		{
			p_quat->Set_X(value_x);
		}

		float value_y = p_quat->Get_Y();
		if (this->DragFloat("Y", &value_y))
		{
			p_quat->Set_Y(value_y);
		}

		float value_z = p_quat->Get_Z();
		if (this->DragFloat("Z", &value_z))
		{
			p_quat->Set_Z(value_z);
		}

		float value_w = p_quat->Get_W();
		if (this->DragFloat("W", &value_w))
		{
			p_quat->Set_W(value_w);
		}
	}
}

bool ktkImguiWrapper::ImGui_ImplGlfw_InitForOpenGL(
	GLFWwindow* window, bool install_callbacks)
{
	return ::ImGui_ImplGlfw_InitForOpenGL(window, install_callbacks);
}

bool ktkImguiWrapper::ImGui_ImplGlfw_InitForVulkan(
	GLFWwindow* window, bool install_callbacks)
{
	return ::ImGui_ImplGlfw_InitForVulkan(window, install_callbacks);
}

bool ktkImguiWrapper::ImGui_ImplGlfw_InitForOther(
	GLFWwindow* window, bool install_callbacks)
{
	return ::ImGui_ImplGlfw_InitForOther(window, install_callbacks);
}

void ktkImguiWrapper::ImGui_ImplGlfw_Shutdown()
{
	::ImGui_ImplGlfw_Shutdown();
}

void ktkImguiWrapper::ImGui_ImplGlfw_NewFrame()
{
	::ImGui_ImplGlfw_NewFrame();
}

void ktkImguiWrapper::ImGui_ImplGlfw_WindowFocusCallback(
	GLFWwindow* window, int focused)
{
	::ImGui_ImplGlfw_WindowFocusCallback(window, focused);
}

void ktkImguiWrapper::ImGui_ImplGlfw_CursorEnterCallback(
	GLFWwindow* window, int entered)
{
	::ImGui_ImplGlfw_CursorEnterCallback(window, entered);
}

void ktkImguiWrapper::ImGui_ImplGlfw_MouseButtonCallback(
	GLFWwindow* window, int button, int action, int mods)
{
	::ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
}

void ktkImguiWrapper::ImGui_ImplGlfw_ScrollCallback(
	GLFWwindow* window, double xoffset, double yoffset)
{
	::ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
}

void ktkImguiWrapper::ImGui_ImplGlfw_KeyCallback(
	GLFWwindow* window, int key, int scancode, int action, int mods)
{
	::ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
}

void ktkImguiWrapper::ImGui_ImplGlfw_CharCallback(
	GLFWwindow* window, unsigned int c)
{
	::ImGui_ImplGlfw_CharCallback(window, c);
}

void ktkImguiWrapper::ImGui_ImplGlfw_MonitorCallback(
	GLFWmonitor* monitor, int event)
{
	::ImGui_ImplGlfw_MonitorCallback(monitor, event);
}

void ktkImguiWrapper::ImGui_ImplGlfw_CursorPosCallback(
	GLFWwindow* window, double x, double y)
{
	::ImGui_ImplGlfw_CursorPosCallback(window, x, y);
}

bool ktkImguiWrapper::ImGui_ImplOpenGL3_Init(const char* glsl_version)
{
	return ::ImGui_ImplOpenGL3_Init(glsl_version);
}

void ktkImguiWrapper::ImGui_ImplOpenGL3_Shutdown()
{
	::ImGui_ImplOpenGL3_Shutdown();
}

void ktkImguiWrapper::ImGui_ImplOpenGL3_NewFrame()
{
	::ImGui_ImplOpenGL3_NewFrame();
}

void ktkImguiWrapper::ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data)
{
	::ImGui_ImplOpenGL3_RenderDrawData(draw_data);
}

bool ktkImguiWrapper::ImGui_ImplOpenGL3_CreateFontsTexture()
{
	return ::ImGui_ImplOpenGL3_CreateFontsTexture();
}

void ktkImguiWrapper::ImGui_ImplOpenGL3_DestroyFontsTexture()
{
	::ImGui_ImplOpenGL3_DestroyFontsTexture();
}

bool ktkImguiWrapper::ImGui_ImplOpenGL3_CreateDeviceObjects()
{
	return ::ImGui_ImplOpenGL3_CreateDeviceObjects();
}

void ktkImguiWrapper::ImGui_ImplOpenGL3_DestroyDeviceObjects()
{
	::ImGui_ImplOpenGL3_DestroyDeviceObjects();
}

void* ktkImguiWrapper::CreateContext(void* shared_font_atlas)
{
	return ::ImGui::CreateContext(static_cast<ImFontAtlas*>(shared_font_atlas));
}

void ktkImguiWrapper::DestroyContext(void* context)
{
	::ImGui::DestroyContext(static_cast<ImGuiContext*>(context));
}

ImGuiIO& ktkImguiWrapper::GetIO(void)
{
	return ::ImGui::GetIO();
}

ImGuiStyle& ktkImguiWrapper::GetStyle(void)
{
	return ::ImGui::GetStyle();
}

void ktkImguiWrapper::StyleColorsDark(void* style)
{
	::ImGui::StyleColorsDark(static_cast<ImGuiStyle*>(style));
}

void ktkImguiWrapper::NewFrame(void)
{
	::ImGui::NewFrame();
}

void ktkImguiWrapper::Render(void)
{
	::ImGui::Render();
}
ImGuiContext* ktkImguiWrapper::GetCurrentContext()
{
	return ::ImGui::GetCurrentContext();
}
void ktkImguiWrapper::SetCurrentContext(ImGuiContext* ctx)
{
	::ImGui::SetCurrentContext(ctx);
}
void ktkImguiWrapper::EndFrame()
{
	::ImGui::EndFrame();
}
ImDrawData* ktkImguiWrapper::GetDrawData()
{
	return ::ImGui::GetDrawData();
}

void ktkImguiWrapper::ShowDemoWindow(bool* p_open)
{
	::ImGui::ShowDemoWindow(p_open);
}
void ktkImguiWrapper::ShowMetricsWindow(bool* p_open)
{
	::ImGui::ShowMetricsWindow(p_open);
}
void ktkImguiWrapper::ShowStackToolWindow(bool* p_open)
{
	::ImGui::ShowStackToolWindow(p_open);
}
void ktkImguiWrapper::ShowAboutWindow(bool* p_open)
{
	::ImGui::ShowAboutWindow(p_open);
}
void ktkImguiWrapper::ShowStyleEditor(ImGuiStyle* ref)
{
	::ImGui::ShowStyleEditor(ref);
}
bool ktkImguiWrapper::ShowStyleSelector(const char* label)
{
	return ::ImGui::ShowStyleSelector(label);
}
void ktkImguiWrapper::ShowFontSelector(const char* label)
{
	::ImGui::ShowFontSelector(label);
}
void ktkImguiWrapper::ShowUserGuide()
{
	::ImGui::ShowUserGuide();
}
const char* ktkImguiWrapper::GetVersion()
{
	return ::ImGui::GetVersion();
}
void ktkImguiWrapper::StyleColorsLight(ImGuiStyle* dst)
{
	::ImGui::StyleColorsLight(dst);
}
void ktkImguiWrapper::StyleColorsClassic(ImGuiStyle* dst)
{
	::ImGui::StyleColorsClassic(dst);
}
bool ktkImguiWrapper::Begin(
	const char* name, bool* p_open, ImGuiWindowFlags flags)
{
	return ::ImGui::Begin(name, p_open, flags);
}
void ktkImguiWrapper::End()
{
	::ImGui::End();
}
bool ktkImguiWrapper::BeginChild(
	const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
	return ::ImGui::BeginChild(str_id, size, border, flags);
}
bool ktkImguiWrapper::BeginChild(
	ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
{
	return ::ImGui::BeginChild(id, size, border, flags);
}
void ktkImguiWrapper::EndChild()
{
	::ImGui::EndChild();
}
void ktkImguiWrapper::SetNextWindowPos(
	const ImVec2& pos, ImGuiCond cond, const ImVec2& pivot)
{
	::ImGui::SetNextWindowPos(pos, cond, pivot);
}
void ktkImguiWrapper::SetNextWindowSize(const ImVec2& size, ImGuiCond cond)
{
	::ImGui::SetNextWindowSize(size, cond);
}
void ktkImguiWrapper::SetNextWindowSizeConstraints(const ImVec2& size_min,
	const ImVec2& size_max, ImGuiSizeCallback custom_callback,
	void* custom_callback_data)
{
	::ImGui::SetNextWindowSizeConstraints(
		size_min, size_max, custom_callback, custom_callback_data);
}
void ktkImguiWrapper::SetNextWindowContentSize(const ImVec2& size)
{
	::ImGui::SetNextWindowContentSize(size);
}
void ktkImguiWrapper::SetNextWindowCollapsed(bool collapsed, ImGuiCond cond)
{
	::ImGui::SetNextWindowCollapsed(collapsed, cond);
}
void ktkImguiWrapper::SetNextWindowFocus()
{
	::ImGui::SetNextWindowFocus();
}
void ktkImguiWrapper::SetNextWindowBgAlpha(float alpha)
{
	::ImGui::SetNextWindowBgAlpha(alpha);
}

void ktkImguiWrapper::SetNextWindowViewport(ImGuiID viewport_id)
{
#ifdef KOTEK_USE_IMGUI_DOCKING
	::ImGui::SetNextWindowViewport(viewport_id);
#endif
}

void ktkImguiWrapper::SetWindowPos(const ImVec2& pos, ImGuiCond cond)
{
	::ImGui::SetWindowPos(pos, cond);
}
void ktkImguiWrapper::SetWindowSize(const ImVec2& size, ImGuiCond cond)
{
	::ImGui::SetWindowSize(size, cond);
}
void ktkImguiWrapper::SetWindowCollapsed(bool collapsed, ImGuiCond cond)
{
	::ImGui::SetWindowCollapsed(collapsed, cond);
}
void ktkImguiWrapper::SetWindowFocus()
{
	::ImGui::SetWindowFocus();
}
void ktkImguiWrapper::SetWindowFontScale(float scale)
{
	::ImGui::SetWindowFontScale(scale);
}
void ktkImguiWrapper::SetWindowPos(
	const char* name, const ImVec2& pos, ImGuiCond cond)
{
	::ImGui::SetWindowPos(name, pos, cond);
}
void ktkImguiWrapper::SetWindowSize(
	const char* name, const ImVec2& size, ImGuiCond cond)
{
	::ImGui::SetWindowSize(name, size, cond);
}
void ktkImguiWrapper::SetWindowCollapsed(
	const char* name, bool collapsed, ImGuiCond cond)
{
	::ImGui::SetWindowCollapsed(name, collapsed, cond);
}
void ktkImguiWrapper::SetWindowFocus(const char* name)
{
	::ImGui::SetWindowFocus(name);
}

float ktkImguiWrapper::GetScrollX()
{
	return ::ImGui::GetScrollX();
}
float ktkImguiWrapper::GetScrollY()
{
	return ::ImGui::GetScrollY();
}
void ktkImguiWrapper::SetScrollX(float scroll_x)
{
	::ImGui::SetScrollX(scroll_x);
}
void ktkImguiWrapper::SetScrollY(float scroll_y)
{
	::ImGui::SetScrollY(scroll_y);
}
float ktkImguiWrapper::GetScrollMaxX()
{
	return ::ImGui::GetScrollMaxX();
}
float ktkImguiWrapper::GetScrollMaxY()
{
	return ::ImGui::GetScrollMaxY();
}
void ktkImguiWrapper::SetScrollHereX(float center_x_ratio)
{
	::ImGui::SetScrollHereX(center_x_ratio);
}
void ktkImguiWrapper::SetScrollHereY(float center_y_ratio)
{
	::ImGui::SetScrollHereY(center_y_ratio);
}
void ktkImguiWrapper::SetScrollFromPosX(float local_x, float center_x_ratio)
{
	::ImGui::SetScrollFromPosX(local_x, center_x_ratio);
}
void ktkImguiWrapper::SetScrollFromPosY(float local_y, float center_y_ratio)
{
	::ImGui::SetScrollFromPosY(local_y, center_y_ratio);
}
void ktkImguiWrapper::PushFont(ImFont* font)
{
	::ImGui::PushFont(font);
}
void ktkImguiWrapper::PopFont()
{
	::ImGui::PopFont();
}
void ktkImguiWrapper::PushStyleColor(ImGuiCol idx, ImU32 col)
{
	::ImGui::PushStyleColor(idx, col);
}
void ktkImguiWrapper::PushStyleColor(ImGuiCol idx, const ImVec4& col)
{
	::ImGui::PushStyleColor(idx, col);
}
void ktkImguiWrapper::PopStyleColor(int count)
{
	::ImGui::PopStyleColor(count);
}
void ktkImguiWrapper::PushStyleVar(ImGuiStyleVar idx, float val)
{
	::ImGui::PushStyleVar(idx, val);
}
void ktkImguiWrapper::PushStyleVar(ImGuiStyleVar idx, const ImVec2& val)
{
	::ImGui::PushStyleVar(idx, val);
}
void ktkImguiWrapper::PopStyleVar(int count)
{
	::ImGui::PopStyleVar(count);
}
void ktkImguiWrapper::PushAllowKeyboardFocus(bool allow_keyboard_focus)
{
	::ImGui::PushAllowKeyboardFocus(allow_keyboard_focus);
}
void ktkImguiWrapper::PopAllowKeyboardFocus()
{
	::ImGui::PopAllowKeyboardFocus();
}
void ktkImguiWrapper::PushButtonRepeat(bool repeat)
{
	::ImGui::PushButtonRepeat(repeat);
}
void ktkImguiWrapper::PopButtonRepeat()
{
	::ImGui::PopButtonRepeat();
}
void ktkImguiWrapper::PushItemWidth(float item_width)
{
	::ImGui::PushItemWidth(item_width);
}
void ktkImguiWrapper::PopItemWidth()
{
	::ImGui::PopItemWidth();
}
void ktkImguiWrapper::SetNextItemWidth(float item_width)
{
	::ImGui::SetNextItemWidth(item_width);
}
float ktkImguiWrapper::CalcItemWidth()
{
	return ::ImGui::CalcItemWidth();
}
void ktkImguiWrapper::PushTextWrapPos(float wrap_local_pos_x)
{
	::ImGui::PushTextWrapPos(wrap_local_pos_x);
}
void ktkImguiWrapper::PopTextWrapPos()
{
	::ImGui::PopTextWrapPos();
}
ImFont* ktkImguiWrapper::GetFont()
{
	return ::ImGui::GetFont();
}
float ktkImguiWrapper::GetFontSize()
{
	return ::ImGui::GetFontSize();
}
ImVec2 ktkImguiWrapper::GetFontTexUvWhitePixel()
{
	return ::ImGui::GetFontTexUvWhitePixel();
}
ImU32 ktkImguiWrapper::GetColorU32(ImGuiCol idx, float alpha_mul)
{
	return ::ImGui::GetColorU32(idx, alpha_mul);
}
ImU32 ktkImguiWrapper::GetColorU32(const ImVec4& col)
{
	return ::ImGui::GetColorU32(col);
}
ImU32 ktkImguiWrapper::GetColorU32(ImU32 col)
{
	return ::ImGui::GetColorU32(col);
}
const ImVec4& ktkImguiWrapper::GetStyleColorVec4(ImGuiCol idx)
{
	return ::ImGui::GetStyleColorVec4(idx);
}

void ktkImguiWrapper::Separator()
{
	::ImGui::Separator();
}

void ktkImguiWrapper::SameLine(float offset_from_start_x, float spacing)
{
	::ImGui::SameLine(offset_from_start_x, spacing);
}

void ktkImguiWrapper::NewLine()
{
	::ImGui::NewLine();
}

void ktkImguiWrapper::Spacing()
{
	::ImGui::Spacing();
}

void ktkImguiWrapper::Dummy(const ImVec2& size)
{
	::ImGui::Dummy(size);
}

void ktkImguiWrapper::Indent(float indent_w)
{
	::ImGui::Indent(indent_w);
}

void ktkImguiWrapper::Unindent(float indent_w)
{
	::ImGui::Unindent(indent_w);
}

void ktkImguiWrapper::BeginGroup()
{
	::ImGui::BeginGroup();
}

void ktkImguiWrapper::EndGroup()
{
	::ImGui::EndGroup();
}

ImVec2 ktkImguiWrapper::GetCursorPos()
{
	return ImVec2();
}
float ktkImguiWrapper::GetCursorPosX()
{
	return 0.0f;
}
float ktkImguiWrapper::GetCursorPosY()
{
	return 0.0f;
}
void ktkImguiWrapper::SetCursorPos(const ImVec2& local_pos) {}
void ktkImguiWrapper::SetCursorPosX(float local_x) {}
void ktkImguiWrapper::SetCursorPosY(float local_y) {}
ImVec2 ktkImguiWrapper::GetCursorStartPos()
{
	return ImVec2();
}
ImVec2 ktkImguiWrapper::GetCursorScreenPos()
{
	return ImVec2();
}
void ktkImguiWrapper::SetCursorScreenPos(const ImVec2& pos) {}
void ktkImguiWrapper::AlignTextToFramePadding() {}
float ktkImguiWrapper::GetTextLineHeight()
{
	return 0.0f;
}
float ktkImguiWrapper::GetTextLineHeightWithSpacing()
{
	return 0.0f;
}
float ktkImguiWrapper::GetFrameHeight()
{
	return 0.0f;
}
float ktkImguiWrapper::GetFrameHeightWithSpacing()
{
	return 0.0f;
}
void ktkImguiWrapper::PushID(const char* str_id)
{
	::ImGui::PushID(str_id);
}
void ktkImguiWrapper::PushID(const char* str_id_begin, const char* str_id_end)
{
	::ImGui::PushID(str_id_begin, str_id_end);
}
void ktkImguiWrapper::PushID(const void* ptr_id)
{
	::ImGui::PushID(ptr_id);
}
void ktkImguiWrapper::PushID(int int_id)
{
	::ImGui::PushID(int_id);
}
void ktkImguiWrapper::PopID()
{
	::ImGui::PopID();
}
ImGuiID ktkImguiWrapper::GetID(const char* str_id)
{
	return ::ImGui::GetID(str_id);
}
ImGuiID ktkImguiWrapper::GetID(const char* str_id_begin, const char* str_id_end)
{
	return ::ImGui::GetID(str_id_begin, str_id_end);
}
ImGuiID ktkImguiWrapper::GetID(const void* ptr_id)
{
	return ::ImGui::GetID(ptr_id);
}
void ktkImguiWrapper::TextUnformatted(const char* text, const char* text_end)
{
	::ImGui::TextUnformatted(text, text_end);
}
void ktkImguiWrapper::Text(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	::ImGui::TextV(fmt, args);
	va_end(args);
}
void ktkImguiWrapper::TextV(const char* fmt, va_list args)
{
	::ImGui::TextV(fmt, args);
}
void ktkImguiWrapper::TextColored(const ImVec4& col, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	::ImGui::TextColored(col, fmt, args);
	va_end(args);
}
void ktkImguiWrapper::TextColoredV(
	const ImVec4& col, const char* fmt, va_list args)
{
	::ImGui::TextColoredV(col, fmt, args);
}
void ktkImguiWrapper::TextDisabled(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	::ImGui::TextDisabledV(fmt, args);
	va_end(args);
}
void ktkImguiWrapper::TextDisabledV(const char* fmt, va_list args)
{
	::ImGui::TextDisabledV(fmt, args);
}
void ktkImguiWrapper::TextWrapped(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	::ImGui::TextWrappedV(fmt, args);
	va_end(args);
}
void ktkImguiWrapper::TextWrappedV(const char* fmt, va_list args)
{
	::ImGui::TextWrappedV(fmt, args);
}
void ktkImguiWrapper::LabelText(const char* label, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	::ImGui::LabelTextV(label, fmt, args);
	va_end(args);
}
void ktkImguiWrapper::LabelTextV(
	const char* label, const char* fmt, va_list args)
{
	::ImGui::LabelTextV(label, fmt, args);
}
void ktkImguiWrapper::BulletText(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	::ImGui::BulletTextV(fmt, args);
	va_end(args);
}
void ktkImguiWrapper::BulletTextV(const char* fmt, va_list args)
{
	::ImGui::BulletTextV(fmt, args);
}
bool ktkImguiWrapper::Button(const char* label, const ImVec2& size)
{
	return ::ImGui::Button(label, size);
}
bool ktkImguiWrapper::SmallButton(const char* label)
{
	return ::ImGui::SmallButton(label);
}
bool ktkImguiWrapper::InvisibleButton(
	const char* str_id, const ImVec2& size, ImGuiButtonFlags flags)
{
	return ::ImGui::InvisibleButton(str_id, size, flags);
}
bool ktkImguiWrapper::ArrowButton(const char* str_id, ImGuiDir dir)
{
	return ::ImGui::ArrowButton(str_id, dir);
}
void ktkImguiWrapper::Image(ImTextureID user_texture_id, const ImVec2& size,
	const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col,
	const ImVec4& border_col)
{
	::ImGui::Image(user_texture_id, size, uv0, uv1, tint_col, border_col);
}
bool ktkImguiWrapper::ImageButton(const char* str_id,
	ImTextureID user_texture_id, const ImVec2& image_size, const ImVec2& uv0,
	const ImVec2& uv1, const ImVec4& bg_col, const ImVec4& tint_col)
{
	return ImGui::ImageButton(
		str_id, user_texture_id, image_size, uv0, uv1, bg_col, tint_col);
}
bool ktkImguiWrapper::Checkbox(const char* label, bool* v)
{
	return ::ImGui::Checkbox(label, v);
}
bool ktkImguiWrapper::CheckboxFlags(
	const char* label, int* flags, int flags_value)
{
	return ::ImGui::CheckboxFlags(label, flags, flags_value);
}
bool ktkImguiWrapper::CheckboxFlags(
	const char* label, unsigned int* flags, unsigned int flags_value)
{
	return ::ImGui::CheckboxFlags(label, flags, flags_value);
}
bool ktkImguiWrapper::RadioButton(const char* label, bool active)
{
	return ::ImGui::RadioButton(label, active);
}
bool ktkImguiWrapper::RadioButton(const char* label, int* v, int v_button)
{
	return ::ImGui::RadioButton(label, v, v_button);
}
void ktkImguiWrapper::ProgressBar(
	float fraction, const ImVec2& size_arg, const char* overlay)
{
	::ImGui::ProgressBar(fraction, size_arg, overlay);
}
void ktkImguiWrapper::Bullet()
{
	::ImGui::Bullet();
}
bool ktkImguiWrapper::BeginCombo(
	const char* label, const char* preview_value, ImGuiComboFlags flags)
{
	return ::ImGui::BeginCombo(label, preview_value, flags);
}
void ktkImguiWrapper::EndCombo()
{
	::ImGui::EndCombo();
}
bool ktkImguiWrapper::Combo(const char* label, int* current_item,
	const char* const items[], int items_count, int popup_max_height_in_items)
{
	return ::ImGui::Combo(
		label, current_item, items, items_count, popup_max_height_in_items);
}
bool ktkImguiWrapper::Combo(const char* label, int* current_item,
	const char* items_separated_by_zeros, int popup_max_height_in_items)
{
	return ::ImGui::Combo(label, current_item, items_separated_by_zeros,
		popup_max_height_in_items);
}
bool ktkImguiWrapper::Combo(const char* label, int* current_item,
	bool (*items_getter)(void* data, int idx, const char** out_text),
	void* data, int items_count, int popup_max_height_in_items)
{
	return ::ImGui::Combo(label, current_item, items_getter, data, items_count,
		popup_max_height_in_items);
}
bool ktkImguiWrapper::DragFloat(const char* label, float* v, float v_speed,
	float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragFloat(label, v, v_speed, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::DragFloat2(const char* label, float v[2], float v_speed,
	float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::DragFloat3(const char* label, float v[3], float v_speed,
	float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::DragFloat4(const char* label, float v[4], float v_speed,
	float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::DragFloatRange2(const char* label, float* v_current_min,
	float* v_current_max, float v_speed, float v_min, float v_max,
	const char* format, const char* format_max, ImGuiSliderFlags flags)
{
	return ::ImGui::DragFloatRange2(label, v_current_min, v_current_max,
		v_speed, v_min, v_max, format, format_max, flags);
}
bool ktkImguiWrapper::DragInt(const char* label, int* v, float v_speed,
	int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragInt(label, v, v_speed, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::DragInt2(const char* label, int v[2], float v_speed,
	int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragInt2(label, v, v_speed, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::DragInt3(const char* label, int v[3], float v_speed,
	int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragInt3(label, v, v_speed, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::DragInt4(const char* label, int v[4], float v_speed,
	int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragInt4(label, v, v_speed, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::DragIntRange2(const char* label, int* v_current_min,
	int* v_current_max, float v_speed, int v_min, int v_max, const char* format,
	const char* format_max, ImGuiSliderFlags flags)
{
	return ::ImGui::DragIntRange2(label, v_current_min, v_current_max, v_speed,
		v_min, v_max, format, format_max, flags);
}
bool ktkImguiWrapper::DragScalar(const char* label, ImGuiDataType data_type,
	void* p_data, float v_speed, const void* p_min, const void* p_max,
	const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragScalar(
		label, data_type, p_data, v_speed, p_min, p_max, format, flags);
}
bool ktkImguiWrapper::DragScalarN(const char* label, ImGuiDataType data_type,
	void* p_data, int components, float v_speed, const void* p_min,
	const void* p_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::DragScalarN(label, data_type, p_data, components, v_speed,
		p_min, p_max, format, flags);
}
bool ktkImguiWrapper::SliderFloat(const char* label, float* v, float v_min,
	float v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderFloat(label, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::SliderFloat2(const char* label, float v[2], float v_min,
	float v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderFloat2(label, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::SliderFloat3(const char* label, float v[3], float v_min,
	float v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderFloat3(label, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::SliderFloat4(const char* label, float v[4], float v_min,
	float v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderFloat4(label, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::SliderAngle(const char* label, float* v_rad,
	float v_degrees_min, float v_degrees_max, const char* format,
	ImGuiSliderFlags flags)
{
	return ::ImGui::SliderAngle(
		label, v_rad, v_degrees_min, v_degrees_max, format, flags);
}
bool ktkImguiWrapper::SliderInt(const char* label, int* v, int v_min, int v_max,
	const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderInt(label, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::SliderInt2(const char* label, int v[2], int v_min,
	int v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderInt2(label, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::SliderInt3(const char* label, int v[3], int v_min,
	int v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderInt3(label, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::SliderInt4(const char* label, int v[4], int v_min,
	int v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderInt4(label, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::SliderScalar(const char* label, ImGuiDataType data_type,
	void* p_data, const void* p_min, const void* p_max, const char* format,
	ImGuiSliderFlags flags)
{
	return ::ImGui::SliderScalar(
		label, data_type, p_data, p_min, p_max, format, flags);
}
bool ktkImguiWrapper::SliderScalarN(const char* label, ImGuiDataType data_type,
	void* p_data, int components, const void* p_min, const void* p_max,
	const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::SliderScalarN(
		label, data_type, p_data, components, p_min, p_max, format, flags);
}
bool ktkImguiWrapper::VSliderFloat(const char* label, const ImVec2& size,
	float* v, float v_min, float v_max, const char* format,
	ImGuiSliderFlags flags)
{
	return ::ImGui::VSliderFloat(label, size, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::VSliderInt(const char* label, const ImVec2& size, int* v,
	int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::VSliderInt(label, size, v, v_min, v_max, format, flags);
}
bool ktkImguiWrapper::VSliderScalar(const char* label, const ImVec2& size,
	ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max,
	const char* format, ImGuiSliderFlags flags)
{
	return ::ImGui::VSliderScalar(
		label, size, data_type, p_data, p_min, p_max, format, flags);
}
bool ktkImguiWrapper::InputText(const char* label, char* buf, size_t buf_size,
	ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
	return ::ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
}
bool ktkImguiWrapper::InputTextMultiline(const char* label, char* buf,
	size_t buf_size, const ImVec2& size, ImGuiInputTextFlags flags,
	ImGuiInputTextCallback callback, void* user_data)
{
	return ::ImGui::InputTextMultiline(
		label, buf, buf_size, size, flags, callback, user_data);
}
bool ktkImguiWrapper::InputTextWithHint(const char* label, const char* hint,
	char* buf, size_t buf_size, ImGuiInputTextFlags flags,
	ImGuiInputTextCallback callback, void* user_data)
{
	return ::ImGui::InputTextWithHint(
		label, hint, buf, buf_size, flags, callback, user_data);
}
bool ktkImguiWrapper::InputFloat(const char* label, float* v, float step,
	float step_fast, const char* format, ImGuiInputTextFlags flags)
{
	return ::ImGui::InputFloat(label, v, step, step_fast, format, flags);
}
bool ktkImguiWrapper::InputFloat2(const char* label, float v[2],
	const char* format, ImGuiInputTextFlags flags)
{
	return ::ImGui::InputFloat2(label, v, format, flags);
}
bool ktkImguiWrapper::InputFloat3(const char* label, float v[3],
	const char* format, ImGuiInputTextFlags flags)
{
	return ::ImGui::InputFloat3(label, v, format, flags);
}
bool ktkImguiWrapper::InputFloat4(const char* label, float v[4],
	const char* format, ImGuiInputTextFlags flags)
{
	return ::ImGui::InputFloat4(label, v, format, flags);
}
bool ktkImguiWrapper::InputInt(const char* label, int* v, int step,
	int step_fast, ImGuiInputTextFlags flags)
{
	return ::ImGui::InputInt(label, v, step, step_fast, flags);
}
bool ktkImguiWrapper::InputInt2(
	const char* label, int v[2], ImGuiInputTextFlags flags)
{
	return ::ImGui::InputInt(label, v, flags);
}
bool ktkImguiWrapper::InputInt3(
	const char* label, int v[3], ImGuiInputTextFlags flags)
{
	return ::ImGui::InputInt(label, v, flags);
}
bool ktkImguiWrapper::InputInt4(
	const char* label, int v[4], ImGuiInputTextFlags flags)
{
	return ::ImGui::InputInt(label, v, flags);
}
bool ktkImguiWrapper::InputDouble(const char* label, double* v, double step,
	double step_fast, const char* format, ImGuiInputTextFlags flags)
{
	return ::ImGui::InputDouble(label, v, step, step_fast, format, flags);
}
bool ktkImguiWrapper::InputScalar(const char* label, ImGuiDataType data_type,
	void* p_data, const void* p_step, const void* p_step_fast,
	const char* format, ImGuiInputTextFlags flags)
{
	return ::ImGui::InputScalar(
		label, data_type, p_data, p_step, p_step_fast, format, flags);
}
bool ktkImguiWrapper::InputScalarN(const char* label, ImGuiDataType data_type,
	void* p_data, int components, const void* p_step, const void* p_step_fast,
	const char* format, ImGuiInputTextFlags flags)
{
	return ::ImGui::InputScalarN(label, data_type, p_data, components, p_step,
		p_step_fast, format, flags);
}
bool ktkImguiWrapper::ColorEdit3(
	const char* label, float col[3], ImGuiColorEditFlags flags)
{
	return ::ImGui::ColorEdit3(label, col, flags);
}
bool ktkImguiWrapper::ColorEdit4(
	const char* label, float col[4], ImGuiColorEditFlags flags)
{
	return ::ImGui::ColorEdit4(label, col, flags);
}
bool ktkImguiWrapper::ColorPicker3(
	const char* label, float col[3], ImGuiColorEditFlags flags)
{
	return ::ImGui::ColorPicker3(label, col, flags);
}
bool ktkImguiWrapper::ColorPicker4(const char* label, float col[4],
	ImGuiColorEditFlags flags, const float* ref_col)
{
	return ::ImGui::ColorPicker4(label, col, flags, ref_col);
}
bool ktkImguiWrapper::ColorButton(const char* desc_id, const ImVec4& col,
	ImGuiColorEditFlags flags, ImVec2 size)
{
	return ::ImGui::ColorButton(desc_id, col, flags, size);
}
void ktkImguiWrapper::SetColorEditOptions(ImGuiColorEditFlags flags)
{
	return ::ImGui::SetColorEditOptions(flags);
}
bool ktkImguiWrapper::TreeNode(const char* label)
{
	return ::ImGui::TreeNode(label);
}
bool ktkImguiWrapper::TreeNode(const char* str_id, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool status = ::ImGui::TreeNode(str_id, fmt, args);
	va_end(args);

	return status;
}
bool ktkImguiWrapper::TreeNode(const void* ptr_id, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool status = ::ImGui::TreeNode(ptr_id, fmt, args);
	va_end(args);

	return status;
}
bool ktkImguiWrapper::TreeNodeV(
	const char* str_id, const char* fmt, va_list args)
{
	return ::ImGui::TreeNodeV(str_id, fmt, args);
}
bool ktkImguiWrapper::TreeNodeV(
	const void* ptr_id, const char* fmt, va_list args)
{
	return ::ImGui::TreeNodeV(ptr_id, fmt, args);
}
bool ktkImguiWrapper::TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags)
{
	return ::ImGui::TreeNodeEx(label, flags);
}
bool ktkImguiWrapper::TreeNodeEx(
	const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool status = ::ImGui::TreeNodeEx(str_id, flags, fmt, args);
	va_end(args);

	return status;
}
bool ktkImguiWrapper::TreeNodeEx(
	const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	bool status = ::ImGui::TreeNodeEx(ptr_id, flags, fmt, args);
	va_end(args);

	return status;
}
bool ktkImguiWrapper::TreeNodeExV(
	const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args)
{
	return ::ImGui::TreeNodeExV(str_id, flags, fmt, args);
}
bool ktkImguiWrapper::TreeNodeExV(
	const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args)
{
	return ::ImGui::TreeNodeExV(ptr_id, flags, fmt, args);
}
void ktkImguiWrapper::TreePush(const char* str_id)
{
	::ImGui::TreePush(str_id);
}
void ktkImguiWrapper::TreePush(const void* ptr_id)
{
	::ImGui::TreePush(ptr_id);
}
void ktkImguiWrapper::TreePop()
{
	::ImGui::TreePop();
}
float ktkImguiWrapper::GetTreeNodeToLabelSpacing()
{
	return ::ImGui::GetTreeNodeToLabelSpacing();
}
bool ktkImguiWrapper::CollapsingHeader(
	const char* label, ImGuiTreeNodeFlags flags)
{
	return ::ImGui::CollapsingHeader(label, flags);
}
bool ktkImguiWrapper::CollapsingHeader(
	const char* label, bool* p_visible, ImGuiTreeNodeFlags flags)
{
	return ::ImGui::CollapsingHeader(label, p_visible, flags);
}
void ktkImguiWrapper::SetNextItemOpen(bool is_open, ImGuiCond cond)
{
	::ImGui::SetNextItemOpen(is_open, cond);
}
bool ktkImguiWrapper::Selectable(const char* label, bool selected,
	ImGuiSelectableFlags flags, const ImVec2& size)
{
	return ::ImGui::Selectable(label, selected, flags, size);
}
bool ktkImguiWrapper::Selectable(const char* label, bool* p_selected,
	ImGuiSelectableFlags flags, const ImVec2& size)
{
	return ::ImGui::Selectable(label, p_selected, flags, size);
}
bool ktkImguiWrapper::BeginListBox(const char* label, const ImVec2& size)
{
	return ::ImGui::BeginListBox(label, size);
}
void ktkImguiWrapper::EndListBox()
{
	::ImGui::EndListBox();
}
bool ktkImguiWrapper::ListBox(const char* label, int* current_item,
	const char* const items[], int items_count, int height_in_items)
{
	return ::ImGui::ListBox(
		label, current_item, items, items_count, height_in_items);
}
bool ktkImguiWrapper::ListBox(const char* label, int* current_item,
	bool (*items_getter)(void* data, int idx, const char** out_text),
	void* data, int items_count, int height_in_items)
{
	return ::ImGui::ListBox(
		label, current_item, items_getter, data, items_count, height_in_items);
}
void ktkImguiWrapper::PlotLines(const char* label, const float* values,
	int values_count, int values_offset, const char* overlay_text,
	float scale_min, float scale_max, ImVec2 graph_size, int stride)
{
	::ImGui::PlotLines(label, values, values_count, values_offset, overlay_text,
		scale_min, scale_max, graph_size, stride);
}
void ktkImguiWrapper::PlotLines(const char* label,
	float (*values_getter)(void* data, int idx), void* data, int values_count,
	int values_offset, const char* overlay_text, float scale_min,
	float scale_max, ImVec2 graph_size)
{
	::ImGui::PlotLines(label, values_getter, data, values_count, values_offset,
		overlay_text, scale_min, scale_max, graph_size);
}
void ktkImguiWrapper::PlotHistogram(const char* label, const float* values,
	int values_count, int values_offset, const char* overlay_text,
	float scale_min, float scale_max, ImVec2 graph_size, int stride)
{
	::ImGui::PlotHistogram(label, values, values_count, values_offset,
		overlay_text, scale_min, scale_max, graph_size, stride);
}
void ktkImguiWrapper::PlotHistogram(const char* label,
	float (*values_getter)(void* data, int idx), void* data, int values_count,
	int values_offset, const char* overlay_text, float scale_min,
	float scale_max, ImVec2 graph_size)
{
	::ImGui::PlotHistogram(label, values_getter, data, values_count,
		values_offset, overlay_text, scale_min, scale_max, graph_size);
}
void ktkImguiWrapper::Value(const char* prefix, bool b)
{
	::ImGui::Value(prefix, b);
}
void ktkImguiWrapper::Value(const char* prefix, int v)
{
	::ImGui::Value(prefix, v);
}
void ktkImguiWrapper::Value(const char* prefix, unsigned int v)
{
	::ImGui::Value(prefix, v);
}
void ktkImguiWrapper::Value(
	const char* prefix, float v, const char* float_format)
{
	::ImGui::Value(prefix, v, float_format);
}
bool ktkImguiWrapper::BeginMenuBar()
{
	return ::ImGui::BeginMenuBar();
}
void ktkImguiWrapper::EndMenuBar()
{
	::ImGui::EndMenuBar();
}
bool ktkImguiWrapper::BeginMainMenuBar()
{
	return ::ImGui::BeginMainMenuBar();
}
void ktkImguiWrapper::EndMainMenuBar()
{
	::ImGui::EndMainMenuBar();
}
bool ktkImguiWrapper::BeginMenu(const char* label, bool enabled)
{
	return ::ImGui::BeginMenu(label, enabled);
}
void ktkImguiWrapper::EndMenu()
{
	::ImGui::EndMenu();
}
bool ktkImguiWrapper::MenuItem(
	const char* label, const char* shortcut, bool selected, bool enabled)
{
	return ::ImGui::MenuItem(label, shortcut, selected, enabled);
}
bool ktkImguiWrapper::MenuItem(
	const char* label, const char* shortcut, bool* p_selected, bool enabled)
{
	return ::ImGui::MenuItem(label, shortcut, p_selected, enabled);
}
void ktkImguiWrapper::BeginTooltip()
{
	::ImGui::BeginTooltip();
}
void ktkImguiWrapper::EndTooltip()
{
	::ImGui::EndTooltip();
}
bool ktkImguiWrapper::BeginPopup(const char* str_id, ImGuiWindowFlags flags)
{
	return ::ImGui::BeginPopup(str_id, flags);
}
bool ktkImguiWrapper::BeginPopupModal(
	const char* name, bool* p_open, ImGuiWindowFlags flags)
{
	return ::ImGui::BeginPopupModal(name, p_open, flags);
}
void ktkImguiWrapper::EndPopup()
{
	::ImGui::EndPopup();
}
void ktkImguiWrapper::OpenPopup(const char* str_id, ImGuiPopupFlags popup_flags)
{
	::ImGui::OpenPopup(str_id, popup_flags);
}
void ktkImguiWrapper::OpenPopup(ImGuiID id, ImGuiPopupFlags popup_flags)
{
	::ImGui::OpenPopup(id, popup_flags);
}
void ktkImguiWrapper::OpenPopupOnItemClick(
	const char* str_id, ImGuiPopupFlags popup_flags)
{
	::ImGui::OpenPopupOnItemClick(str_id, popup_flags);
}
void ktkImguiWrapper::CloseCurrentPopup()
{
	::ImGui::CloseCurrentPopup();
}
bool ktkImguiWrapper::BeginPopupContextItem(
	const char* str_id, ImGuiPopupFlags popup_flags)
{
	return ::ImGui::BeginPopupContextItem(str_id, popup_flags);
}
bool ktkImguiWrapper::BeginPopupContextWindow(
	const char* str_id, ImGuiPopupFlags popup_flags)
{
	return ::ImGui::BeginPopupContextWindow(str_id, popup_flags);
}
bool ktkImguiWrapper::BeginPopupContextVoid(
	const char* str_id, ImGuiPopupFlags popup_flags)
{
	return ::ImGui::BeginPopupContextVoid(str_id, popup_flags);
}
bool ktkImguiWrapper::IsPopupOpen(const char* str_id, ImGuiPopupFlags flags)
{
	return ::ImGui::IsPopupOpen(str_id, flags);
}
bool ktkImguiWrapper::BeginTable(const char* str_id, int column,
	ImGuiTableFlags flags, const ImVec2& outer_size, float inner_width)
{
	return ::ImGui::BeginTable(str_id, column, flags, outer_size, inner_width);
}
void ktkImguiWrapper::EndTable()
{
	::ImGui::EndTable();
}
void ktkImguiWrapper::TableNextRow(
	ImGuiTableRowFlags row_flags, float min_row_height)
{
	::ImGui::TableNextRow(row_flags, min_row_height);
}
bool ktkImguiWrapper::TableNextColumn()
{
	return ::ImGui::TableNextColumn();
}
bool ktkImguiWrapper::TableSetColumnIndex(int column_n)
{
	return ::ImGui::TableSetColumnIndex(column_n);
}
void ktkImguiWrapper::TableSetupColumn(const char* label,
	ImGuiTableColumnFlags flags, float init_width_or_weight, ImGuiID user_id)
{
	::ImGui::TableSetupColumn(label, flags, init_width_or_weight, user_id);
}
void ktkImguiWrapper::TableSetupScrollFreeze(int cols, int rows)
{
	::ImGui::TableSetupScrollFreeze(cols, rows);
}
void ktkImguiWrapper::TableHeadersRow()
{
	::ImGui::TableHeadersRow();
}
void ktkImguiWrapper::TableHeader(const char* label)
{
	::ImGui::TableHeader(label);
}
ImGuiTableSortSpecs* ktkImguiWrapper::TableGetSortSpecs()
{
	return ::ImGui::TableGetSortSpecs();
}
int ktkImguiWrapper::TableGetColumnCount()
{
	return ::ImGui::TableGetColumnCount();
}
int ktkImguiWrapper::TableGetColumnIndex()
{
	return ::ImGui::TableGetColumnIndex();
}
int ktkImguiWrapper::TableGetRowIndex()
{
	return ::ImGui::TableGetRowIndex();
}
const char* ktkImguiWrapper::TableGetColumnName(int column_n)
{
	return ::ImGui::TableGetColumnName(column_n);
}
ImGuiTableColumnFlags ktkImguiWrapper::TableGetColumnFlags(int column_n)
{
	return ::ImGui::TableGetColumnFlags();
}
void ktkImguiWrapper::TableSetColumnEnabled(int column_n, bool v)
{
	::ImGui::TableSetColumnEnabled(column_n, v);
}
void ktkImguiWrapper::TableSetBgColor(
	ImGuiTableBgTarget target, ImU32 color, int column_n)
{
	::ImGui::TableSetBgColor(target, color, column_n);
}
void ktkImguiWrapper::Columns(int count, const char* id, bool border)
{
	::ImGui::Columns(count, id, border);
}
void ktkImguiWrapper::NextColumn()
{
	::ImGui::NextColumn();
}
int ktkImguiWrapper::GetColumnIndex()
{
	return ::ImGui::GetColumnIndex();
}
float ktkImguiWrapper::GetColumnWidth(int column_index)
{
	return ::ImGui::GetColumnWidth(column_index);
}
void ktkImguiWrapper::SetColumnWidth(int column_index, float width)
{
	::ImGui::SetColumnWidth(column_index, width);
}
float ktkImguiWrapper::GetColumnOffset(int column_index)
{
	return ::ImGui::GetColumnOffset(column_index);
}
void ktkImguiWrapper::SetColumnOffset(int column_index, float offset_x)
{
	::ImGui::SetColumnOffset(column_index, offset_x);
}
int ktkImguiWrapper::GetColumnsCount()
{
	return ::ImGui::GetColumnsCount();
}
bool ktkImguiWrapper::BeginTabBar(const char* str_id, ImGuiTabBarFlags flags)
{
	return ::ImGui::BeginTabBar(str_id, flags);
}
void ktkImguiWrapper::EndTabBar()
{
	::ImGui::EndTabBar();
}
bool ktkImguiWrapper::BeginTabItem(
	const char* label, bool* p_open, ImGuiTabItemFlags flags)
{
	return ::ImGui::BeginTabItem(label, p_open, flags);
}
void ktkImguiWrapper::EndTabItem()
{
	::ImGui::EndTabItem();
}
bool ktkImguiWrapper::TabItemButton(const char* label, ImGuiTabItemFlags flags)
{
	return ::ImGui::TabItemButton(label, flags);
}
void ktkImguiWrapper::SetTabItemClosed(const char* tab_or_docked_window_label)
{
	::ImGui::SetTabItemClosed(tab_or_docked_window_label);
}

#ifdef KOTEK_USE_IMGUI_DOCKING
ImGuiID ktkImguiWrapper::DockSpace(ImGuiID id, const ImVec2& size,
	ImGuiDockNodeFlags flags, const ImGuiWindowClass* window_class)
{
	return ::ImGui::DockSpace(id, size, flags, window_class);
}
ImGuiID ktkImguiWrapper::DockSpaceOverViewport(const ImGuiViewport* viewport,
	ImGuiDockNodeFlags flags, const ImGuiWindowClass* window_class)
{
	return ::ImGui::DockSpaceOverViewport(viewport, flags, window_class);
}
void ktkImguiWrapper::SetNextWindowDockID(ImGuiID dock_id, ImGuiCond cond)
{
	::ImGui::SetNextWindowDockID(dock_id, cond);
}
void ktkImguiWrapper::SetNextWindowClass(const ImGuiWindowClass* window_class)
{
	::ImGui::SetNextWindowClass(window_class);
}
ImGuiID ktkImguiWrapper::GetWindowDockID()
{
	return ::ImGui::GetWindowDockID();
}
bool ktkImguiWrapper::IsWindowDocked()
{
	return ::ImGui::IsWindowDocked();
}
#endif

void ktkImguiWrapper::LogToTTY(int auto_open_depth)
{
	::ImGui::LogToTTY(auto_open_depth);
}
void ktkImguiWrapper::LogToFile(int auto_open_depth, const char* filename)
{
	::ImGui::LogToFile(auto_open_depth, filename);
}
void ktkImguiWrapper::LogToClipboard(int auto_open_depth)
{
	::ImGui::LogToClipboard(auto_open_depth);
}
void ktkImguiWrapper::LogFinish()
{
	::ImGui::LogFinish();
}
void ktkImguiWrapper::LogButtons()
{
	::ImGui::LogButtons();
}
bool ktkImguiWrapper::BeginDragDropSource(ImGuiDragDropFlags flags)
{
	return ::ImGui::BeginDragDropSource(flags);
}
bool ktkImguiWrapper::SetDragDropPayload(
	const char* type, const void* data, size_t sz, ImGuiCond cond)
{
	return ::ImGui::SetDragDropPayload(type, data, sz, cond);
}
void ktkImguiWrapper::EndDragDropSource()
{
	::ImGui::EndDragDropSource();
}
bool ktkImguiWrapper::BeginDragDropTarget()
{
	return ::ImGui::BeginDragDropTarget();
}
const ImGuiPayload* ktkImguiWrapper::AcceptDragDropPayload(
	const char* type, ImGuiDragDropFlags flags)
{
	return ::ImGui::AcceptDragDropPayload(type, flags);
}
void ktkImguiWrapper::EndDragDropTarget()
{
	::ImGui::EndDragDropTarget();
}
const ImGuiPayload* ktkImguiWrapper::GetDragDropPayload()
{
	return ::ImGui::GetDragDropPayload();
}
void ktkImguiWrapper::BeginDisabled(bool disabled)
{
	::ImGui::BeginDisabled(disabled);
}
void ktkImguiWrapper::EndDisabled()
{
	::ImGui::EndDisabled();
}
void ktkImguiWrapper::PushClipRect(const ImVec2& clip_rect_min,
	const ImVec2& clip_rect_max, bool intersect_with_current_clip_rect)
{
	::ImGui::PushClipRect(
		clip_rect_min, clip_rect_max, intersect_with_current_clip_rect);
}
void ktkImguiWrapper::PopClipRect()
{
	::ImGui::PopClipRect();
}
void ktkImguiWrapper::SetItemDefaultFocus()
{
	::ImGui::SetItemDefaultFocus();
}
void ktkImguiWrapper::SetKeyboardFocusHere(int offset)
{
	::ImGui::SetKeyboardFocusHere(offset);
}
bool ktkImguiWrapper::IsItemHovered(ImGuiHoveredFlags flags)
{
	return ::ImGui::IsItemHovered(flags);
}
bool ktkImguiWrapper::IsItemActive()
{
	return ::ImGui::IsItemActive();
}
bool ktkImguiWrapper::IsItemFocused()
{
	return ::ImGui::IsItemFocused();
}
bool ktkImguiWrapper::IsItemClicked(ImGuiMouseButton mouse_button)
{
	return ::ImGui::IsItemClicked(mouse_button);
}
bool ktkImguiWrapper::IsItemVisible()
{
	return ::ImGui::IsItemVisible();
}
bool ktkImguiWrapper::IsItemEdited()
{
	return ::ImGui::IsItemEdited();
}
bool ktkImguiWrapper::IsItemActivated()
{
	return ::ImGui::IsItemActivated();
}
bool ktkImguiWrapper::IsItemDeactivated()
{
	return ::ImGui::IsItemDeactivated();
}
bool ktkImguiWrapper::IsItemDeactivatedAfterEdit()
{
	return ::ImGui::IsItemDeactivatedAfterEdit();
}
bool ktkImguiWrapper::IsItemToggledOpen()
{
	return ::ImGui::IsItemToggledOpen();
}
bool ktkImguiWrapper::IsAnyItemHovered()
{
	return ::ImGui::IsAnyItemHovered();
}
bool ktkImguiWrapper::IsAnyItemActive()
{
	return ::ImGui::IsAnyItemActive();
}
bool ktkImguiWrapper::IsAnyItemFocused()
{
	return ::ImGui::IsAnyItemFocused();
}
ImVec2 ktkImguiWrapper::GetItemRectMin()
{
	return ::ImGui::GetItemRectMin();
}
ImVec2 ktkImguiWrapper::GetItemRectMax()
{
	return ::ImGui::GetItemRectMax();
}
ImVec2 ktkImguiWrapper::GetItemRectSize()
{
	return ::ImGui::GetItemRectSize();
}
void ktkImguiWrapper::SetItemAllowOverlap()
{
	::ImGui::SetItemAllowOverlap();
}
ImGuiViewport* ktkImguiWrapper::GetMainViewport()
{
	return ::ImGui::GetMainViewport();
}
bool ktkImguiWrapper::IsRectVisible(const ImVec2& size)
{
	return ::ImGui::IsRectVisible(size);
}
bool ktkImguiWrapper::IsRectVisible(
	const ImVec2& rect_min, const ImVec2& rect_max)
{
	return ::ImGui::IsRectVisible(rect_min, rect_max);
}
double ktkImguiWrapper::GetTime()
{
	return ::ImGui::GetTime();
}
int ktkImguiWrapper::GetFrameCount()
{
	return ::ImGui::GetFrameCount();
}
ImDrawList* ktkImguiWrapper::GetBackgroundDrawList()
{
	return ::ImGui::GetBackgroundDrawList();
}
ImDrawList* ktkImguiWrapper::GetForegroundDrawList()
{
	return ::ImGui::GetForegroundDrawList();
}

ImDrawList* ktkImguiWrapper::GetBackgroundDrawList(ImGuiViewport* viewport)
{
#ifdef KOTEK_USE_IMGUI_DOCKING
	return ::ImGui::GetBackgroundDrawList(viewport);
#else
	return nullptr;
#endif
}
ImDrawList* ktkImguiWrapper::GetForegroundDrawList(ImGuiViewport* viewport)
{
#ifdef KOTEK_USE_IMGUI_DOCKING
	return ::ImGui::GetForegroundDrawList(viewport);
#else
	return nullptr;
#endif
}
ImDrawListSharedData* ktkImguiWrapper::GetDrawListSharedData()
{
	return ::ImGui::GetDrawListSharedData();
}
const char* ktkImguiWrapper::GetStyleColorName(ImGuiCol idx)
{
	return ::ImGui::GetStyleColorName(idx);
}
void ktkImguiWrapper::SetStateStorage(ImGuiStorage* storage)
{
	::ImGui::SetStateStorage(storage);
}
ImGuiStorage* ktkImguiWrapper::GetStateStorage()
{
	return ::ImGui::GetStateStorage();
}
bool ktkImguiWrapper::BeginChildFrame(
	ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags)
{
	return ::ImGui::BeginChildFrame(id, size, flags);
}
void ktkImguiWrapper::EndChildFrame()
{
	::ImGui::EndChildFrame();
}
ImVec2 ktkImguiWrapper::CalcTextSize(const char* text, const char* text_end,
	bool hide_text_after_double_hash, float wrap_width)
{
	return ::ImGui::CalcTextSize(
		text, text_end, hide_text_after_double_hash, wrap_width);
}
ImVec4 ktkImguiWrapper::ColorConvertU32ToFloat4(ImU32 in)
{
	return ::ImGui::ColorConvertU32ToFloat4(in);
}
ImU32 ktkImguiWrapper::ColorConvertFloat4ToU32(const ImVec4& in)
{
	return ::ImGui::ColorConvertFloat4ToU32(in);
}
void ktkImguiWrapper::ColorConvertRGBtoHSV(
	float r, float g, float b, float& out_h, float& out_s, float& out_v)
{
	::ImGui::ColorConvertRGBtoHSV(r, g, b, out_h, out_s, out_v);
}
void ktkImguiWrapper::ColorConvertHSVtoRGB(
	float h, float s, float v, float& out_r, float& out_g, float& out_b)
{
	::ImGui::ColorConvertHSVtoRGB(h, s, v, out_r, out_g, out_b);
}
int ktkImguiWrapper::GetKeyIndex(ImGuiKey imgui_key)
{
	return ::ImGui::GetKeyIndex(imgui_key);
}
bool ktkImguiWrapper::IsKeyDown(int user_key_index)
{
	return ::ImGui::IsKeyDown(static_cast<ImGuiKey>(user_key_index));
}
bool ktkImguiWrapper::IsKeyPressed(int user_key_index, bool repeat)
{
	return ::ImGui::IsKeyPressed(static_cast<ImGuiKey>(user_key_index), repeat);
}
bool ktkImguiWrapper::IsKeyReleased(int user_key_index)
{
	return ::ImGui::IsKeyReleased(static_cast<ImGuiKey>(user_key_index));
}
int ktkImguiWrapper::GetKeyPressedAmount(
	int key_index, float repeat_delay, float rate)
{
	return ::ImGui::GetKeyPressedAmount(
		static_cast<ImGuiKey>(key_index), repeat_delay, rate);
}
void ktkImguiWrapper::SetNextFrameWantCaptureKeyboard(
	bool want_capture_keyboard_value)
{
	::ImGui::SetNextFrameWantCaptureKeyboard(want_capture_keyboard_value);
}
bool ktkImguiWrapper::IsMouseDown(ImGuiMouseButton button)
{
	return ::ImGui::IsMouseDown(button);
}
bool ktkImguiWrapper::IsMouseClicked(ImGuiMouseButton button, bool repeat)
{
	return ::ImGui::IsMouseClicked(button, repeat);
}
bool ktkImguiWrapper::IsMouseReleased(ImGuiMouseButton button)
{
	return ::ImGui::IsMouseReleased(button);
}
bool ktkImguiWrapper::IsMouseDoubleClicked(ImGuiMouseButton button)
{
	return ::ImGui::IsMouseDoubleClicked(button);
}
bool ktkImguiWrapper::IsMouseHoveringRect(
	const ImVec2& r_min, const ImVec2& r_max, bool clip)
{
	return ::ImGui::IsMouseHoveringRect(r_min, r_max, clip);
}
bool ktkImguiWrapper::IsMousePosValid(const ImVec2* mouse_pos)
{
	return ::ImGui::IsMousePosValid(mouse_pos);
}
bool ktkImguiWrapper::IsAnyMouseDown()
{
	return ::ImGui::IsAnyMouseDown();
}
ImVec2 ktkImguiWrapper::GetMousePos()
{
	return ::ImGui::GetMousePos();
}
ImVec2 ktkImguiWrapper::GetMousePosOnOpeningCurrentPopup()
{
	return ::ImGui::GetMousePosOnOpeningCurrentPopup();
}
bool ktkImguiWrapper::IsMouseDragging(
	ImGuiMouseButton button, float lock_threshold)
{
	return ::ImGui::IsMouseDragging(button, lock_threshold);
}
ImVec2 ktkImguiWrapper::GetMouseDragDelta(
	ImGuiMouseButton button, float lock_threshold)
{
	return ::ImGui::GetMouseDragDelta(button, lock_threshold);
}
void ktkImguiWrapper::ResetMouseDragDelta(ImGuiMouseButton button)
{
	::ImGui::ResetMouseDragDelta(button);
}
ImGuiMouseCursor ktkImguiWrapper::GetMouseCursor()
{
	return ::ImGui::GetMouseCursor();
}
void ktkImguiWrapper::SetMouseCursor(ImGuiMouseCursor cursor_type)
{
	::ImGui::SetMouseCursor(cursor_type);
}
void ktkImguiWrapper::SetNextFrameWantCaptureMouse(
	bool want_capture_mouse_value)
{
	::ImGui::SetNextFrameWantCaptureMouse(want_capture_mouse_value);
}
const char* ktkImguiWrapper::GetClipboardText()
{
	return ::ImGui::GetClipboardText();
}
void ktkImguiWrapper::SetClipboardText(const char* text)
{
	::ImGui::SetClipboardText(text);
}
void ktkImguiWrapper::LoadIniSettingsFromDisk(const char* ini_filename)
{
	::ImGui::LoadIniSettingsFromDisk(ini_filename);
}
void ktkImguiWrapper::LoadIniSettingsFromMemory(
	const char* ini_data, size_t ini_size)
{
	::ImGui::LoadIniSettingsFromMemory(ini_data, ini_size);
}
void ktkImguiWrapper::SaveIniSettingsToDisk(const char* ini_filename)
{
	::ImGui::SaveIniSettingsToDisk(ini_filename);
}
const char* ktkImguiWrapper::SaveIniSettingsToMemory(size_t* out_ini_size)
{
	return ::ImGui::SaveIniSettingsToMemory(out_ini_size);
}
bool ktkImguiWrapper::DebugCheckVersionAndDataLayout(const char* version_str,
	size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4,
	size_t sz_drawvert, size_t sz_drawidx)
{
	return ::ImGui::DebugCheckVersionAndDataLayout(version_str, sz_io, sz_style,
		sz_vec2, sz_vec4, sz_drawvert, sz_drawidx);
}
void ktkImguiWrapper::SetAllocatorFunctions(
	ImGuiMemAllocFunc alloc_func, ImGuiMemFreeFunc free_func, void* user_data)
{
	::ImGui::SetAllocatorFunctions(alloc_func, free_func, user_data);
}
void ktkImguiWrapper::GetAllocatorFunctions(ImGuiMemAllocFunc* p_alloc_func,
	ImGuiMemFreeFunc* p_free_func, void** p_user_data)
{
	::ImGui::GetAllocatorFunctions(p_alloc_func, p_free_func, p_user_data);
}
void* ktkImguiWrapper::MemAlloc(size_t size)
{
	return ::ImGui::MemAlloc(size);
}
void ktkImguiWrapper::MemFree(void* ptr)
{
	::ImGui::MemFree(ptr);
}

#ifdef KOTEK_USE_IMGUI_DOCKING
ImGuiPlatformIO& ktkImguiWrapper::GetPlatformIO()
{
	return ::ImGui::GetPlatformIO();
}
#endif
void ktkImguiWrapper::UpdatePlatformWindows()
{
#ifdef KOTEK_USE_IMGUI_DOCKING
	::ImGui::UpdatePlatformWindows();
#endif
}
void ktkImguiWrapper::RenderPlatformWindowsDefault(
	void* platform_render_arg, void* renderer_render_arg)
{
#ifdef KOTEK_USE_IMGUI_DOCKING
	::ImGui::RenderPlatformWindowsDefault(
		platform_render_arg, renderer_render_arg);
#endif
}
void ktkImguiWrapper::DestroyPlatformWindows()
{
#ifdef KOTEK_USE_IMGUI_DOCKING
	::ImGui::DestroyPlatformWindows();
#endif
}
ImGuiViewport* ktkImguiWrapper::FindViewportByID(ImGuiID id)
{
#ifdef KOTEK_USE_IMGUI_DOCKING
	return ::ImGui::FindViewportByID(id);
#else
	return nullptr;
#endif
}
ImGuiViewport* ktkImguiWrapper::FindViewportByPlatformHandle(
	void* platform_handle)
{
#ifdef KOTEK_USE_IMGUI_DOCKING
	return ::ImGui::FindViewportByPlatformHandle(platform_handle);
#else
	return nullptr;
#endif
}

void ktkImguiWrapper::SetTooltip(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	::ImGui::SetTooltip(fmt, args);
	va_end(args);
}

void ktkImguiWrapper::SetTooltipV(const char* fmt, va_list args)
{
	::ImGui::SetTooltipV(fmt, args);
}
void ktkImguiWrapper::LogText(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	::ImGui::LogText(fmt, args);
	va_end(args);
}
void ktkImguiWrapper::LogTextV(const char* fmt, va_list args)
{
	::ImGui::LogTextV(fmt, args);
}

KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
