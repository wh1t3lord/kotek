#pragma once

#include <kotek.core.api/include/kotek_api.h>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class vector2f;
class vector3f;
class vector4f;
class matrix2x2f;
class matrix3x3f;
class matrix4x4f;
class quaternionf;

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_UI

class ktkImguiWrapper : public kun_core ktkIImguiWrapper
{
public:
	ktkImguiWrapper(void);
	~ktkImguiWrapper(void);

	void EditDragVec2f(const char* label, ktk::math::vector2f* p_vec) override;
	void EditDragVec3f(const char* label, ktk::math::vector3f* p_vec) override;
	void EditDragVec4f(const char* label, ktk::math::vector4f* p_vec) override;

	void EditDragMat2x2f(
		const char* label, ktk::math::matrix2x2f* p_mat) override;
	void EditDragMat3x3f(
		const char* label, ktk::math::matrix3x3f* p_mat) override;
	void EditDragMat4x4f(
		const char* label, ktk::math::matrix4x4f* p_mat) override;

	void EditDragQuatf(
		const char* label, ktk::math::quaternionf* p_quat) override;

	bool ImGui_ImplGlfw_InitForOpenGL(
		GLFWwindow* window, bool install_callbacks) override;
	bool ImGui_ImplGlfw_InitForVulkan(
		GLFWwindow* window, bool install_callbacks) override;
	bool ImGui_ImplGlfw_InitForOther(
		GLFWwindow* window, bool install_callbacks) override;
	void ImGui_ImplGlfw_Shutdown() override;
	void ImGui_ImplGlfw_NewFrame() override;

	void ImGui_ImplGlfw_WindowFocusCallback(
		GLFWwindow* window, int focused) override;
	void ImGui_ImplGlfw_CursorEnterCallback(
		GLFWwindow* window, int entered) override;
	void ImGui_ImplGlfw_MouseButtonCallback(
		GLFWwindow* window, int button, int action, int mods) override;
	void ImGui_ImplGlfw_ScrollCallback(
		GLFWwindow* window, double xoffset, double yoffset) override;
	void ImGui_ImplGlfw_KeyCallback(GLFWwindow* window, int key, int scancode,
		int action, int mods) override;
	void ImGui_ImplGlfw_CharCallback(
		GLFWwindow* window, unsigned int c) override;
	void ImGui_ImplGlfw_MonitorCallback(
		GLFWmonitor* monitor, int event) override;
	void ImGui_ImplGlfw_CursorPosCallback(
		GLFWwindow* window, double x, double y) override;

	bool ImGui_ImplOpenGL3_Init(const char* glsl_version = NULL) override;
	void ImGui_ImplOpenGL3_Shutdown() override;
	void ImGui_ImplOpenGL3_NewFrame() override;
	void ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data) override;

	bool ImGui_ImplOpenGL3_CreateFontsTexture() override;
	void ImGui_ImplOpenGL3_DestroyFontsTexture() override;
	bool ImGui_ImplOpenGL3_CreateDeviceObjects() override;
	void ImGui_ImplOpenGL3_DestroyDeviceObjects() override;

	void* CreateContext(void* shared_font_atlas = NULL) override;
	void DestroyContext(void* ctx = NULL) override;
	ImGuiContext* GetCurrentContext() override;
	void SetCurrentContext(ImGuiContext* ctx) override;
	ImGuiIO& GetIO() override;
	ImGuiStyle& GetStyle() override;
	void NewFrame() override;
	void EndFrame() override;
	void Render() override;
	ImDrawData* GetDrawData() override;

	void ShowDemoWindow(bool* p_open = NULL) override;
	void ShowMetricsWindow(bool* p_open = NULL) override;
	void ShowStackToolWindow(bool* p_open = NULL) override;
	void ShowAboutWindow(bool* p_open = NULL) override;
	void ShowStyleEditor(ImGuiStyle* ref = NULL) override;
	bool ShowStyleSelector(const char* label) override;
	void ShowFontSelector(const char* label) override;
	void ShowUserGuide() override;
	const char* GetVersion() override;
	void StyleColorsDark(void* dst = NULL) override;
	void StyleColorsLight(ImGuiStyle* dst = NULL) override;
	void StyleColorsClassic(ImGuiStyle* dst = NULL) override;

	bool Begin(const char* name, bool* p_open = NULL,
		ImGuiWindowFlags flags = 0) override;
	void End() override;

	bool BeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0),
		bool border = false, ImGuiWindowFlags flags = 0) override;
	bool BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0),
		bool border = false, ImGuiWindowFlags flags = 0) override;
	void EndChild() override;

	bool IsWindowAppearing() override;
	bool IsWindowCollapsed() override;
	bool IsWindowFocused(ImGuiFocusedFlags flags = 0) override;
	bool IsWindowHovered(ImGuiHoveredFlags flags = 0) override;

	ImDrawList* GetWindowDrawList() override;
	ImVec2 GetWindowPos() override;
	ImVec2 GetWindowSize() override;
	float GetWindowWidth() override;
	float GetWindowHeight() override;

	void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0,
		const ImVec2& pivot = ImVec2(0, 0)) override;
	void SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0) override;
	void SetNextWindowSizeConstraints(const ImVec2& size_min,
		const ImVec2& size_max, ImGuiSizeCallback custom_callback = NULL,
		void* custom_callback_data = NULL) override;
	void SetNextWindowContentSize(const ImVec2& size) override;
	void SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0) override;
	void SetNextWindowFocus() override;
	void SetNextWindowBgAlpha(float alpha) override;
	void SetNextWindowViewport(ImGuiID viewport_id) override;
	void SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0) override;
	void SetWindowSize(const ImVec2& size, ImGuiCond cond = 0) override;
	void SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0) override;
	void SetWindowFocus() override;
	void SetWindowFontScale(float scale) override;
	void SetWindowPos(
		const char* name, const ImVec2& pos, ImGuiCond cond = 0) override;
	void SetWindowSize(
		const char* name, const ImVec2& size, ImGuiCond cond = 0) override;
	void SetWindowCollapsed(
		const char* name, bool collapsed, ImGuiCond cond = 0) override;
	void SetWindowFocus(const char* name) override;

	float GetScrollX() override;
	float GetScrollY() override;
	void SetScrollX(float scroll_x) override;
	void SetScrollY(float scroll_y) override;
	float GetScrollMaxX() override;
	float GetScrollMaxY() override;
	void SetScrollHereX(float center_x_ratio = 0.5f) override;
	void SetScrollHereY(float center_y_ratio = 0.5f) override;
	void SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f) override;
	void SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f) override;

	void PushFont(ImFont* font) override;
	void PopFont() override;
	void PushStyleColor(ImGuiCol idx, ImU32 col) override;
	void PushStyleColor(ImGuiCol idx, const ImVec4& col) override;
	void PopStyleColor(int count = 1) override;
	void PushStyleVar(ImGuiStyleVar idx, float val) override;
	void PushStyleVar(ImGuiStyleVar idx, const ImVec2& val) override;
	void PopStyleVar(int count = 1) override;
	void PushAllowKeyboardFocus(bool allow_keyboard_focus) override;
	void PopAllowKeyboardFocus() override;
	void PushButtonRepeat(bool repeat) override;
	void PopButtonRepeat() override;

	void PushItemWidth(float item_width) override;
	void PopItemWidth() override;
	void SetNextItemWidth(float item_width) override;
	float CalcItemWidth() override;
	void PushTextWrapPos(float wrap_local_pos_x = 0.0f) override;
	void PopTextWrapPos() override;

	ImFont* GetFont() override;
	float GetFontSize() override;
	ImVec2 GetFontTexUvWhitePixel() override;
	ImU32 GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f) override;
	ImU32 GetColorU32(const ImVec4& col) override;
	ImU32 GetColorU32(ImU32 col) override;
	const ImVec4& GetStyleColorVec4(ImGuiCol idx) override;

	void Separator() override;
	void SameLine(
		float offset_from_start_x = 0.0f, float spacing = -1.0f) override;
	void NewLine() override;
	void Spacing() override;
	void Dummy(const ImVec2& size) override;
	void Indent(float indent_w = 0.0f) override;
	void Unindent(float indent_w = 0.0f) override;
	void BeginGroup() override;
	void EndGroup() override;
	ImVec2 GetCursorPos() override;
	float GetCursorPosX() override;
	float GetCursorPosY() override;
	void SetCursorPos(const ImVec2& local_pos) override;
	void SetCursorPosX(float local_x) override;
	void SetCursorPosY(float local_y) override;
	ImVec2 GetCursorStartPos() override;
	ImVec2 GetCursorScreenPos() override;
	void SetCursorScreenPos(const ImVec2& pos) override;
	void AlignTextToFramePadding() override;
	float GetTextLineHeight() override;
	float GetTextLineHeightWithSpacing() override;
	float GetFrameHeight() override;
	float GetFrameHeightWithSpacing() override;

	void PushID(const char* str_id) override;
	void PushID(const char* str_id_begin, const char* str_id_end) override;
	void PushID(const void* ptr_id) override;
	void PushID(int int_id) override;
	void PopID() override;
	ImGuiID GetID(const char* str_id) override;
	ImGuiID GetID(const char* str_id_begin, const char* str_id_end) override;
	ImGuiID GetID(const void* ptr_id) override;

	void TextUnformatted(
		const char* text, const char* text_end = NULL) override;
	void Text(const char* fmt, ...) override;
	void TextV(const char* fmt, va_list args) override;
	void TextColored(const ImVec4& col, const char* fmt, ...) override;
	void TextColoredV(
		const ImVec4& col, const char* fmt, va_list args) override;
	void TextDisabled(const char* fmt, ...) override;
	void TextDisabledV(const char* fmt, va_list args) override;
	void TextWrapped(const char* fmt, ...) override;
	void TextWrappedV(const char* fmt, va_list args) override;
	void LabelText(const char* label, const char* fmt, ...) override;
	void LabelTextV(const char* label, const char* fmt, va_list args) override;
	void BulletText(const char* fmt, ...) override;
	void BulletTextV(const char* fmt, va_list args) override;

	bool Button(const char* label, const ImVec2& size = ImVec2(0, 0)) override;
	bool SmallButton(const char* label) override;
	bool InvisibleButton(const char* str_id, const ImVec2& size,
		ImGuiButtonFlags flags = 0) override;
	bool ArrowButton(const char* str_id, ImGuiDir dir) override;
	void Image(ImTextureID user_texture_id, const ImVec2& size,
		const ImVec2& uv0 = ImVec2(0, 0), const ImVec2& uv1 = ImVec2(1, 1),
		const ImVec4& tint_col = ImVec4(1, 1, 1, 1),
		const ImVec4& border_col = ImVec4(0, 0, 0, 0)) override;
	bool ImageButton(const char* str_id, ImTextureID user_texture_id,
		const ImVec2& image_size, const ImVec2& uv0 = ImVec2(0, 0),
		const ImVec2& uv1 = ImVec2(1, 1),
		const ImVec4& bg_col = ImVec4(0, 0, 0, 0),
		const ImVec4& tint_col = ImVec4(1, 1, 1, 1)) override; // <0 frame_
	bool Checkbox(const char* label, bool* v) override;
	bool CheckboxFlags(const char* label, int* flags, int flags_value) override;
	bool CheckboxFlags(const char* label, unsigned int* flags,
		unsigned int flags_value) override;
	bool RadioButton(const char* label, bool active) override;
	bool RadioButton(const char* label, int* v, int v_button) override;
	void ProgressBar(float fraction,
		const ImVec2& size_arg = ImVec2(-FLT_MIN, 0),
		const char* overlay = NULL) override;
	void Bullet() override;

	bool BeginCombo(const char* label, const char* preview_value,
		ImGuiComboFlags flags = 0) override;
	void EndCombo() override;
	bool Combo(const char* label, int* current_item, const char* const items[],
		int items_count, int popup_max_height_in_items = -1) override;
	bool Combo(const char* label, int* current_item,
		const char* items_separated_by_zeros,
		int popup_max_height_in_items = -1) override;
	bool Combo(const char* label, int* current_item,
		bool (*items_getter)(void* data, int idx, const char** out_text),
		void* data, int items_count,
		int popup_max_height_in_items = -1) override;
	bool DragFloat(const char* label, float* v, float v_speed = 1.0f,
		float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) override;
	bool DragFloat2(const char* label, float v[2], float v_speed = 1.0f,
		float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) override;
	bool DragFloat3(const char* label, float v[3], float v_speed = 1.0f,
		float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) override;
	bool DragFloat4(const char* label, float v[4], float v_speed = 1.0f,
		float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) override;
	bool DragFloatRange2(const char* label, float* v_current_min,
		float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f,
		float v_max = 0.0f, const char* format = "%.3f",
		const char* format_max = NULL, ImGuiSliderFlags flags = 0) override;
	bool DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0,
		int v_max = 0, const char* format = "%d",
		ImGuiSliderFlags flags = 0) override;
	bool DragInt2(const char* label, int v[2], float v_speed = 1.0f,
		int v_min = 0, int v_max = 0, const char* format = "%d",
		ImGuiSliderFlags flags = 0) override;
	bool DragInt3(const char* label, int v[3], float v_speed = 1.0f,
		int v_min = 0, int v_max = 0, const char* format = "%d",
		ImGuiSliderFlags flags = 0) override;
	bool DragInt4(const char* label, int v[4], float v_speed = 1.0f,
		int v_min = 0, int v_max = 0, const char* format = "%d",
		ImGuiSliderFlags flags = 0) override;
	bool DragIntRange2(const char* label, int* v_current_min,
		int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0,
		const char* format = "%d", const char* format_max = NULL,
		ImGuiSliderFlags flags = 0) override;
	bool DragScalar(const char* label, ImGuiDataType data_type, void* p_data,
		float v_speed = 1.0f, const void* p_min = NULL,
		const void* p_max = NULL, const char* format = NULL,
		ImGuiSliderFlags flags = 0) override;
	bool DragScalarN(const char* label, ImGuiDataType data_type, void* p_data,
		int components, float v_speed = 1.0f, const void* p_min = NULL,
		const void* p_max = NULL, const char* format = NULL,
		ImGuiSliderFlags flags = 0) override;
	bool SliderFloat(const char* label, float* v, float v_min, float v_max,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0) override;
	bool SliderFloat2(const char* label, float v[2], float v_min, float v_max,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0) override;
	bool SliderFloat3(const char* label, float v[3], float v_min, float v_max,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0) override;
	bool SliderFloat4(const char* label, float v[4], float v_min, float v_max,
		const char* format = "%.3f", ImGuiSliderFlags flags = 0) override;
	bool SliderAngle(const char* label, float* v_rad,
		float v_degrees_min = -360.0f, float v_degrees_max = +360.0f,
		const char* format = "%.0f deg", ImGuiSliderFlags flags = 0) override;
	bool SliderInt(const char* label, int* v, int v_min, int v_max,
		const char* format = "%d", ImGuiSliderFlags flags = 0) override;
	bool SliderInt2(const char* label, int v[2], int v_min, int v_max,
		const char* format = "%d", ImGuiSliderFlags flags = 0) override;
	bool SliderInt3(const char* label, int v[3], int v_min, int v_max,
		const char* format = "%d", ImGuiSliderFlags flags = 0) override;
	bool SliderInt4(const char* label, int v[4], int v_min, int v_max,
		const char* format = "%d", ImGuiSliderFlags flags = 0) override;
	bool SliderScalar(const char* label, ImGuiDataType data_type, void* p_data,
		const void* p_min, const void* p_max, const char* format = NULL,
		ImGuiSliderFlags flags = 0) override;
	bool SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data,
		int components, const void* p_min, const void* p_max,
		const char* format = NULL, ImGuiSliderFlags flags = 0) override;
	bool VSliderFloat(const char* label, const ImVec2& size, float* v,
		float v_min, float v_max, const char* format = "%.3f",
		ImGuiSliderFlags flags = 0) override;
	bool VSliderInt(const char* label, const ImVec2& size, int* v, int v_min,
		int v_max, const char* format = "%d",
		ImGuiSliderFlags flags = 0) override;
	bool VSliderScalar(const char* label, const ImVec2& size,
		ImGuiDataType data_type, void* p_data, const void* p_min,
		const void* p_max, const char* format = NULL,
		ImGuiSliderFlags flags = 0) override;
	bool InputText(const char* label, char* buf, size_t buf_size,
		ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL,
		void* user_data = NULL) override;
	bool InputTextMultiline(const char* label, char* buf, size_t buf_size,
		const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0,
		ImGuiInputTextCallback callback = NULL,
		void* user_data = NULL) override;
	bool InputTextWithHint(const char* label, const char* hint, char* buf,
		size_t buf_size, ImGuiInputTextFlags flags = 0,
		ImGuiInputTextCallback callback = NULL,
		void* user_data = NULL) override;
	bool InputFloat(const char* label, float* v, float step = 0.0f,
		float step_fast = 0.0f, const char* format = "%.3f",
		ImGuiInputTextFlags flags = 0) override;
	bool InputFloat2(const char* label, float v[2], const char* format = "%.3f",
		ImGuiInputTextFlags flags = 0) override;
	bool InputFloat3(const char* label, float v[3], const char* format = "%.3f",
		ImGuiInputTextFlags flags = 0) override;
	bool InputFloat4(const char* label, float v[4], const char* format = "%.3f",
		ImGuiInputTextFlags flags = 0) override;
	bool InputInt(const char* label, int* v, int step = 1, int step_fast = 100,
		ImGuiInputTextFlags flags = 0) override;
	bool InputInt2(
		const char* label, int v[2], ImGuiInputTextFlags flags = 0) override;
	bool InputInt3(
		const char* label, int v[3], ImGuiInputTextFlags flags = 0) override;
	bool InputInt4(
		const char* label, int v[4], ImGuiInputTextFlags flags = 0) override;
	bool InputDouble(const char* label, double* v, double step = 0.0,
		double step_fast = 0.0, const char* format = "%.6f",
		ImGuiInputTextFlags flags = 0) override;
	bool InputScalar(const char* label, ImGuiDataType data_type, void* p_data,
		const void* p_step = NULL, const void* p_step_fast = NULL,
		const char* format = NULL, ImGuiInputTextFlags flags = 0) override;
	bool InputScalarN(const char* label, ImGuiDataType data_type, void* p_data,
		int components, const void* p_step = NULL,
		const void* p_step_fast = NULL, const char* format = NULL,
		ImGuiInputTextFlags flags = 0) override;
	bool ColorEdit3(const char* label, float col[3],
		ImGuiColorEditFlags flags = 0) override;
	bool ColorEdit4(const char* label, float col[4],
		ImGuiColorEditFlags flags = 0) override;
	bool ColorPicker3(const char* label, float col[3],
		ImGuiColorEditFlags flags = 0) override;
	bool ColorPicker4(const char* label, float col[4],
		ImGuiColorEditFlags flags = 0, const float* ref_col = NULL) override;
	bool ColorButton(const char* desc_id, const ImVec4& col,
		ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0)) override;
	void SetColorEditOptions(ImGuiColorEditFlags flags) override;
	bool TreeNode(const char* label) override;
	bool TreeNode(const char* str_id, const char* fmt, ...) override;
	bool TreeNode(const void* ptr_id, const char* fmt, ...) override;
	bool TreeNodeV(const char* str_id, const char* fmt, va_list args) override;
	bool TreeNodeV(const void* ptr_id, const char* fmt, va_list args) override;
	bool TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0) override;
	bool TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags,
		const char* fmt, ...) override;
	bool TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags,
		const char* fmt, ...) override;
	bool TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags,
		const char* fmt, va_list args) override;
	bool TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags,
		const char* fmt, va_list args) override;
	void TreePush(const char* str_id) override;
	void TreePush(const void* ptr_id = NULL) override;
	void TreePop() override;
	float GetTreeNodeToLabelSpacing() override;
	bool CollapsingHeader(
		const char* label, ImGuiTreeNodeFlags flags = 0) override;
	bool CollapsingHeader(const char* label, bool* p_visible,
		ImGuiTreeNodeFlags flags = 0) override;
	void SetNextItemOpen(bool is_open, ImGuiCond cond = 0) override;
	bool Selectable(const char* label, bool selected = false,
		ImGuiSelectableFlags flags = 0,
		const ImVec2& size = ImVec2(0, 0)) override;
	bool Selectable(const char* label, bool* p_selected,
		ImGuiSelectableFlags flags = 0,
		const ImVec2& size = ImVec2(0, 0)) override;
	bool BeginListBox(
		const char* label, const ImVec2& size = ImVec2(0, 0)) override;
	void EndListBox() override;
	bool ListBox(const char* label, int* current_item,
		const char* const items[], int items_count,
		int height_in_items = -1) override;
	bool ListBox(const char* label, int* current_item,
		bool (*items_getter)(void* data, int idx, const char** out_text),
		void* data, int items_count, int height_in_items = -1) override;
	void PlotLines(const char* label, const float* values, int values_count,
		int values_offset = 0, const char* overlay_text = NULL,
		float scale_min = FLT_MAX, float scale_max = FLT_MAX,
		ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float)) override;
	void PlotLines(const char* label,
		float (*values_getter)(void* data, int idx), void* data,
		int values_count, int values_offset = 0,
		const char* overlay_text = NULL, float scale_min = FLT_MAX,
		float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0)) override;
	void PlotHistogram(const char* label, const float* values, int values_count,
		int values_offset = 0, const char* overlay_text = NULL,
		float scale_min = FLT_MAX, float scale_max = FLT_MAX,
		ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float)) override;
	void PlotHistogram(const char* label,
		float (*values_getter)(void* data, int idx), void* data,
		int values_count, int values_offset = 0,
		const char* overlay_text = NULL, float scale_min = FLT_MAX,
		float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0)) override;
	void Value(const char* prefix, bool b) override;
	void Value(const char* prefix, int v) override;
	void Value(const char* prefix, unsigned int v) override;
	void Value(
		const char* prefix, float v, const char* float_format = NULL) override;

	bool BeginMenuBar() override;
	void EndMenuBar() override;
	bool BeginMainMenuBar() override;
	void EndMainMenuBar() override;
	bool BeginMenu(const char* label, bool enabled = true) override;
	void EndMenu() override;
	bool MenuItem(const char* label, const char* shortcut = NULL,
		bool selected = false, bool enabled = true) override;
	bool MenuItem(const char* label, const char* shortcut, bool* p_selected,
		bool enabled = true) override;

	void BeginTooltip() override;
	void EndTooltip() override;
	void SetTooltip(const char* fmt, ...) override;
	void SetTooltipV(const char* fmt, va_list args) override;

	bool BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0) override;
	bool BeginPopupModal(const char* name, bool* p_open = NULL,
		ImGuiWindowFlags flags = 0) override;
	void EndPopup() override;

	void OpenPopup(
		const char* str_id, ImGuiPopupFlags popup_flags = 0) override;
	void OpenPopup(ImGuiID id, ImGuiPopupFlags popup_flags = 0) override;
	void OpenPopupOnItemClick(
		const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1) override;
	void CloseCurrentPopup() override;

	bool BeginPopupContextItem(
		const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1) override;
	bool BeginPopupContextWindow(
		const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1) override;
	bool BeginPopupContextVoid(
		const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1) override;

	bool IsPopupOpen(const char* str_id, ImGuiPopupFlags flags = 0) override;

	bool BeginTable(const char* str_id, int column, ImGuiTableFlags flags = 0,
		const ImVec2& outer_size = ImVec2(0.0f, 0.0f),
		float inner_width = 0.0f) override;
	void EndTable() override;
	void TableNextRow(
		ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f) override;
	bool TableNextColumn() override;
	bool TableSetColumnIndex(int column_n) override;

	void TableSetupColumn(const char* label, ImGuiTableColumnFlags flags = 0,
		float init_width_or_weight = 0.0f, ImGuiID user_id = 0) override;
	void TableSetupScrollFreeze(int cols, int rows) override;
	void TableHeadersRow() override;
	void TableHeader(const char* label) override;

	ImGuiTableSortSpecs* TableGetSortSpecs() override;

	int TableGetColumnCount() override;
	int TableGetColumnIndex() override;
	int TableGetRowIndex() override;
	const char* TableGetColumnName(int column_n = -1) override;
	ImGuiTableColumnFlags TableGetColumnFlags(int column_n = -1) override;
	void TableSetColumnEnabled(int column_n, bool v) override;
	void TableSetBgColor(
		ImGuiTableBgTarget target, ImU32 color, int column_n = -1) override;

	void Columns(
		int count = 1, const char* id = NULL, bool border = true) override;
	void NextColumn() override;
	int GetColumnIndex() override;
	float GetColumnWidth(int column_index = -1) override;
	void SetColumnWidth(int column_index, float width) override;
	float GetColumnOffset(int column_index = -1) override;
	void SetColumnOffset(int column_index, float offset_x) override;
	int GetColumnsCount() override;

	bool BeginTabBar(const char* str_id, ImGuiTabBarFlags flags = 0) override;
	void EndTabBar() override;
	bool BeginTabItem(const char* label, bool* p_open = NULL,
		ImGuiTabItemFlags flags = 0) override;
	void EndTabItem() override;
	bool TabItemButton(const char* label, ImGuiTabItemFlags flags = 0) override;
	void SetTabItemClosed(const char* tab_or_docked_window_label) override;

#ifdef KOTEK_USE_IMGUI_DOCKING
	ImGuiID DockSpace(ImGuiID id, const ImVec2& size = ImVec2(0, 0),
		ImGuiDockNodeFlags flags = 0,
		const ImGuiWindowClass* window_class = NULL) override;
	ImGuiID DockSpaceOverViewport(const ImGuiViewport* viewport = NULL,
		ImGuiDockNodeFlags flags = 0,
		const ImGuiWindowClass* window_class = NULL) override;
	void SetNextWindowDockID(ImGuiID dock_id, ImGuiCond cond = 0) override;
	void SetNextWindowClass(const ImGuiWindowClass* window_class) override;
	ImGuiID GetWindowDockID() override;
	bool IsWindowDocked() override;
#endif

	void LogToTTY(int auto_open_depth = -1) override;
	void LogToFile(
		int auto_open_depth = -1, const char* filename = NULL) override;
	void LogToClipboard(int auto_open_depth = -1) override;
	void LogFinish() override;
	void LogButtons() override;
	void LogText(const char* fmt, ...) override;
	void LogTextV(const char* fmt, va_list args) override;

	bool BeginDragDropSource(ImGuiDragDropFlags flags = 0) override;
	bool SetDragDropPayload(const char* type, const void* data, size_t sz,
		ImGuiCond cond = 0) override;
	void EndDragDropSource() override;
	bool BeginDragDropTarget() override;
	const ImGuiPayload* AcceptDragDropPayload(
		const char* type, ImGuiDragDropFlags flags = 0) override;
	void EndDragDropTarget() override;
	const ImGuiPayload* GetDragDropPayload() override;

	void BeginDisabled(bool disabled = true) override;
	void EndDisabled() override;

	void PushClipRect(const ImVec2& clip_rect_min, const ImVec2& clip_rect_max,
		bool intersect_with_current_clip_rect) override;
	void PopClipRect() override;

	void SetItemDefaultFocus() override;
	void SetKeyboardFocusHere(int offset = 0) override;

	bool IsItemHovered(ImGuiHoveredFlags flags = 0) override;
	bool IsItemActive() override;
	bool IsItemFocused() override;
	bool IsItemClicked(ImGuiMouseButton mouse_button = 0) override;
	bool IsItemVisible() override;
	bool IsItemEdited() override;
	bool IsItemActivated() override;
	bool IsItemDeactivated() override;
	bool IsItemDeactivatedAfterEdit() override;
	bool IsItemToggledOpen() override;
	bool IsAnyItemHovered() override;
	bool IsAnyItemActive() override;
	bool IsAnyItemFocused() override;
	ImVec2 GetItemRectMin() override;
	ImVec2 GetItemRectMax() override;
	ImVec2 GetItemRectSize() override;
	void SetItemAllowOverlap() override;

	ImGuiViewport* GetMainViewport() override;

	bool IsRectVisible(const ImVec2& size) override;
	bool IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max) override;
	double GetTime() override;
	int GetFrameCount() override;
	ImDrawList* GetBackgroundDrawList() override;
	ImDrawList* GetForegroundDrawList() override;
	ImDrawList* GetBackgroundDrawList(ImGuiViewport* viewport) override;
	ImDrawList* GetForegroundDrawList(ImGuiViewport* viewport) override;
	ImDrawListSharedData* GetDrawListSharedData() override;
	const char* GetStyleColorName(ImGuiCol idx) override;
	void SetStateStorage(ImGuiStorage* storage) override;
	ImGuiStorage* GetStateStorage() override;
	bool BeginChildFrame(
		ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0) override;
	void EndChildFrame() override;

	ImVec2 CalcTextSize(const char* text, const char* text_end = NULL,
		bool hide_text_after_double_hash = false,
		float wrap_width = -1.0f) override;

	ImVec4 ColorConvertU32ToFloat4(ImU32 in) override;
	ImU32 ColorConvertFloat4ToU32(const ImVec4& in) override;
	void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h,
		float& out_s, float& out_v) override;
	void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r,
		float& out_g, float& out_b) override;

	int GetKeyIndex(ImGuiKey imgui_key) override;
	bool IsKeyDown(int user_key_index) override;
	bool IsKeyPressed(int user_key_index, bool repeat = true) override;
	bool IsKeyReleased(int user_key_index) override;
	int GetKeyPressedAmount(
		int key_index, float repeat_delay, float rate) override;
	void SetNextFrameWantCaptureKeyboard(
		bool want_capture_keyboard_value = true) override;

	bool IsMouseDown(ImGuiMouseButton button) override;
	bool IsMouseClicked(ImGuiMouseButton button, bool repeat = false) override;
	bool IsMouseReleased(ImGuiMouseButton button) override;
	bool IsMouseDoubleClicked(ImGuiMouseButton button) override;
	bool IsMouseHoveringRect(
		const ImVec2& r_min, const ImVec2& r_max, bool clip = true) override;
	bool IsMousePosValid(const ImVec2* mouse_pos = NULL) override;
	bool IsAnyMouseDown() override;
	ImVec2 GetMousePos() override;
	ImVec2 GetMousePosOnOpeningCurrentPopup() override;
	bool IsMouseDragging(
		ImGuiMouseButton button, float lock_threshold = -1.0f) override;
	ImVec2 GetMouseDragDelta(
		ImGuiMouseButton button = 0, float lock_threshold = -1.0f) override;
	void ResetMouseDragDelta(ImGuiMouseButton button = 0) override;
	ImGuiMouseCursor GetMouseCursor() override;
	void SetMouseCursor(ImGuiMouseCursor cursor_type) override;
	void SetNextFrameWantCaptureMouse(
		bool want_capture_mouse_value = true) override;

	const char* GetClipboardText() override;
	void SetClipboardText(const char* text) override;

	void LoadIniSettingsFromDisk(const char* ini_filename) override;
	void LoadIniSettingsFromMemory(
		const char* ini_data, size_t ini_size = 0) override;
	void SaveIniSettingsToDisk(const char* ini_filename) override;
	const char* SaveIniSettingsToMemory(size_t* out_ini_size = NULL) override;

	bool DebugCheckVersionAndDataLayout(const char* version_str, size_t sz_io,
		size_t sz_style, size_t sz_vec2, size_t sz_vec4, size_t sz_drawvert,
		size_t sz_drawidx) override;

	void SetAllocatorFunctions(ImGuiMemAllocFunc alloc_func,
		ImGuiMemFreeFunc free_func, void* user_data = NULL) override;
	void GetAllocatorFunctions(ImGuiMemAllocFunc* p_alloc_func,
		ImGuiMemFreeFunc* p_free_func, void** p_user_data) override;
	void* MemAlloc(size_t size) override;
	void MemFree(void* ptr) override;

#ifdef KOTEK_USE_IMGUI_DOCKING
	ImGuiPlatformIO& GetPlatformIO() override;
#endif

	void UpdatePlatformWindows() override;
	void RenderPlatformWindowsDefault(void* platform_render_arg = NULL,
		void* renderer_render_arg = NULL) override;
	void DestroyPlatformWindows() override;
	ImGuiViewport* FindViewportByID(ImGuiID id) override;
	ImGuiViewport* FindViewportByPlatformHandle(void* platform_handle) override;
};
KOTEK_END_NAMESPACE_UI
KOTEK_END_NAMESPACE_KOTEK
