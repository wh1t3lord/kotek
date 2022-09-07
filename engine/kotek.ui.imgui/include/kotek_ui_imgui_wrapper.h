#pragma once

#include <kotek.core.api/include/kotek_api.h>

#include "imgui.h"

namespace Kotek
{
	namespace UI
	{
		class ktkImguiWrapper : public Core::ktkIImguiWrapper
		{
		public:
			ktkImguiWrapper(void);
			~ktkImguiWrapper(void);

			void ImGui_ImplGlfw_NewFrame(void);

			bool ImGui_ImplOpenGL3_Init(const char* glsl_version = nullptr);
			void ImGui_ImplOpenGL3_NewFrame(void);
			void ImGui_ImplOpenGL3_Shutdown(void);

			/// \~russian @brief Обертка над ImGui_ImplGlfw_Shutdown
			/// @param void, ничего не принимает в качестве аргументов
			///
			/// \~english @brief Wraps ImGui_ImplGlfw_Shutdown function
			/// @param void, nothing takes as input
			void ImGui_ImplGlfw_Shutdown(void);

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
				void* window_handle, bool install_callbacks);

			void* CreateContext(void* shared_font_atlas = NULL);
			void DestroyContext(void* ctx = NULL);
			ImGuiContext* GetCurrentContext();
			void SetCurrentContext(ImGuiContext* ctx);
			void* GetIO();
			void* GetStyle();
			void NewFrame();
			void EndFrame();
			void Render();
			ImDrawData* GetDrawData();

			void ShowDemoWindow(bool* p_open = NULL);
			void ShowMetricsWindow(bool* p_open = NULL);
			void ShowStackToolWindow(bool* p_open = NULL);
			void ShowAboutWindow(bool* p_open = NULL);
			void ShowStyleEditor(ImGuiStyle* ref = NULL);
			bool ShowStyleSelector(const char* label);
			void ShowFontSelector(const char* label);
			void ShowUserGuide();
			const char* GetVersion();
			void StyleColorsDark(void* dst = NULL);
			void StyleColorsLight(ImGuiStyle* dst = NULL);
			void StyleColorsClassic(ImGuiStyle* dst = NULL);

			bool Begin(const char* name, bool* p_open = NULL,
				ImGuiWindowFlags flags = 0);
			void End();

			bool BeginChild(const char* str_id,
				const ImVec2& size = ImVec2(0, 0), bool border = false,
				ImGuiWindowFlags flags = 0);
			bool BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0, 0),
				bool border = false, ImGuiWindowFlags flags = 0);
			void EndChild();

			void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond = 0,
				const ImVec2& pivot = ImVec2(0, 0));
			void SetNextWindowSize(const ImVec2& size, ImGuiCond cond = 0);
			void SetNextWindowSizeConstraints(const ImVec2& size_min,
				const ImVec2& size_max,
				ImGuiSizeCallback custom_callback = NULL,
				void* custom_callback_data = NULL);
			void SetNextWindowContentSize(const ImVec2& size);
			void SetNextWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
			void SetNextWindowFocus();
			void SetNextWindowBgAlpha(float alpha);
			void SetNextWindowViewport(ImGuiID viewport_id);
			void SetWindowPos(const ImVec2& pos, ImGuiCond cond = 0);
			void SetWindowSize(const ImVec2& size, ImGuiCond cond = 0);
			void SetWindowCollapsed(bool collapsed, ImGuiCond cond = 0);
			void SetWindowFocus();
			void SetWindowFontScale(float scale);
			void SetWindowPos(
				const char* name, const ImVec2& pos, ImGuiCond cond = 0);
			void SetWindowSize(
				const char* name, const ImVec2& size, ImGuiCond cond = 0);
			void SetWindowCollapsed(
				const char* name, bool collapsed, ImGuiCond cond = 0);
			void SetWindowFocus(const char* name);

			float GetScrollX();
			float GetScrollY();
			void SetScrollX(float scroll_x);
			void SetScrollY(float scroll_y);
			float GetScrollMaxX();
			float GetScrollMaxY();
			void SetScrollHereX(float center_x_ratio = 0.5f);
			void SetScrollHereY(float center_y_ratio = 0.5f);
			void SetScrollFromPosX(float local_x, float center_x_ratio = 0.5f);
			void SetScrollFromPosY(float local_y, float center_y_ratio = 0.5f);

			void PushFont(ImFont* font);
			void PopFont();
			void PushStyleColor(ImGuiCol idx, ImU32 col);
			void PushStyleColor(ImGuiCol idx, const ImVec4& col);
			void PopStyleColor(int count = 1);
			void PushStyleVar(ImGuiStyleVar idx, float val);
			void PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
			void PopStyleVar(int count = 1);
			void PushAllowKeyboardFocus(bool allow_keyboard_focus);
			void PopAllowKeyboardFocus();
			void PushButtonRepeat(bool repeat);
			void PopButtonRepeat();

			void PushItemWidth(float item_width);
			void PopItemWidth();
			void SetNextItemWidth(float item_width);
			float CalcItemWidth();
			void PushTextWrapPos(float wrap_local_pos_x = 0.0f);
			void PopTextWrapPos();

			ImFont* GetFont();
			float GetFontSize();
			ImVec2 GetFontTexUvWhitePixel();
			ImU32 GetColorU32(ImGuiCol idx, float alpha_mul = 1.0f);
			ImU32 GetColorU32(const ImVec4& col);
			ImU32 GetColorU32(ImU32 col);
			const ImVec4& GetStyleColorVec4(ImGuiCol idx);

			void PushID(const char* str_id);
			void PushID(const char* str_id_begin, const char* str_id_end);
			void PushID(const void* ptr_id);
			void PushID(int int_id);
			void PopID();
			ImGuiID GetID(const char* str_id);
			ImGuiID GetID(const char* str_id_begin, const char* str_id_end);
			ImGuiID GetID(const void* ptr_id);

			void TextUnformatted(const char* text, const char* text_end = NULL);
			void Text(const char* fmt, ...) IM_FMTARGS(1);
			void TextV(const char* fmt, va_list args) IM_FMTLIST(1);
			void TextColored(const ImVec4& col, const char* fmt, ...)
				IM_FMTARGS(2);
			void TextColoredV(const ImVec4& col, const char* fmt, va_list args)
				IM_FMTLIST(2);
			void TextDisabled(const char* fmt, ...) IM_FMTARGS(1);
			void TextDisabledV(const char* fmt, va_list args) IM_FMTLIST(1);
			void TextWrapped(const char* fmt, ...) IM_FMTARGS(1);
			void TextWrappedV(const char* fmt, va_list args) IM_FMTLIST(1);
			void LabelText(const char* label, const char* fmt, ...)
				IM_FMTARGS(2);
			void LabelTextV(const char* label, const char* fmt, va_list args)
				IM_FMTLIST(2);
			void BulletText(const char* fmt, ...) IM_FMTARGS(1);
			void BulletTextV(const char* fmt, va_list args) IM_FMTLIST(1);

			bool Button(const char* label, const ImVec2& size = ImVec2(0, 0));
			bool SmallButton(const char* label);
			bool InvisibleButton(const char* str_id, const ImVec2& size,
				ImGuiButtonFlags flags = 0);
			bool ArrowButton(const char* str_id, ImGuiDir dir);
			void Image(ImTextureID user_texture_id, const ImVec2& size,
				const ImVec2& uv0 = ImVec2(0, 0),
				const ImVec2& uv1 = ImVec2(1, 1),
				const ImVec4& tint_col = ImVec4(1, 1, 1, 1),
				const ImVec4& border_col = ImVec4(0, 0, 0, 0));
			bool ImageButton(ImTextureID user_texture_id, const ImVec2& size,
				const ImVec2& uv0 = ImVec2(0, 0),
				const ImVec2& uv1 = ImVec2(1, 1), int frame_padding = -1,
				const ImVec4& bg_col = ImVec4(0, 0, 0, 0),
				const ImVec4& tint_col = ImVec4(1, 1, 1, 1)); // <0 frame_
			bool Checkbox(const char* label, bool* v);
			bool CheckboxFlags(const char* label, int* flags, int flags_value);
			bool CheckboxFlags(const char* label, unsigned int* flags,
				unsigned int flags_value);
			bool RadioButton(const char* label, bool active);
			bool RadioButton(const char* label, int* v, int v_button);
			void ProgressBar(float fraction,
				const ImVec2& size_arg = ImVec2(-FLT_MIN, 0),
				const char* overlay = NULL);
			void Bullet();

			bool BeginCombo(const char* label, const char* preview_value,
				ImGuiComboFlags flags = 0);
			void EndCombo();
			bool Combo(const char* label, int* current_item,
				const char* const items[], int items_count,
				int popup_max_height_in_items = -1);
			bool Combo(const char* label, int* current_item,
				const char* items_separated_by_zeros,
				int popup_max_height_in_items = -1);
			bool Combo(const char* label, int* current_item,
				bool (*items_getter)(
					void* data, int idx, const char** out_text),
				void* data, int items_count,
				int popup_max_height_in_items = -1);
			bool DragFloat(const char* label, float* v, float v_speed = 1.0f,
				float v_min = 0.0f, float v_max = 0.0f,
				const char* format = "%.3f", ImGuiSliderFlags flags = 0);
			bool DragFloat2(const char* label, float v[2], float v_speed = 1.0f,
				float v_min = 0.0f, float v_max = 0.0f,
				const char* format = "%.3f", ImGuiSliderFlags flags = 0);
			bool DragFloat3(const char* label, float v[3], float v_speed = 1.0f,
				float v_min = 0.0f, float v_max = 0.0f,
				const char* format = "%.3f", ImGuiSliderFlags flags = 0);
			bool DragFloat4(const char* label, float v[4], float v_speed = 1.0f,
				float v_min = 0.0f, float v_max = 0.0f,
				const char* format = "%.3f", ImGuiSliderFlags flags = 0);
			bool DragFloatRange2(const char* label, float* v_current_min,
				float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f,
				float v_max = 0.0f, const char* format = "%.3f",
				const char* format_max = NULL, ImGuiSliderFlags flags = 0);
			bool DragInt(const char* label, int* v, float v_speed = 1.0f,
				int v_min = 0, int v_max = 0, const char* format = "%d",
				ImGuiSliderFlags flags = 0);
			bool DragInt2(const char* label, int v[2], float v_speed = 1.0f,
				int v_min = 0, int v_max = 0, const char* format = "%d",
				ImGuiSliderFlags flags = 0);
			bool DragInt3(const char* label, int v[3], float v_speed = 1.0f,
				int v_min = 0, int v_max = 0, const char* format = "%d",
				ImGuiSliderFlags flags = 0);
			bool DragInt4(const char* label, int v[4], float v_speed = 1.0f,
				int v_min = 0, int v_max = 0, const char* format = "%d",
				ImGuiSliderFlags flags = 0);
			bool DragIntRange2(const char* label, int* v_current_min,
				int* v_current_max, float v_speed = 1.0f, int v_min = 0,
				int v_max = 0, const char* format = "%d",
				const char* format_max = NULL, ImGuiSliderFlags flags = 0);
			bool DragScalar(const char* label, ImGuiDataType data_type,
				void* p_data, float v_speed = 1.0f, const void* p_min = NULL,
				const void* p_max = NULL, const char* format = NULL,
				ImGuiSliderFlags flags = 0);
			bool DragScalarN(const char* label, ImGuiDataType data_type,
				void* p_data, int components, float v_speed = 1.0f,
				const void* p_min = NULL, const void* p_max = NULL,
				const char* format = NULL, ImGuiSliderFlags flags = 0);
			bool SliderFloat(const char* label, float* v, float v_min,
				float v_max, const char* format = "%.3f",
				ImGuiSliderFlags flags = 0);
			bool SliderFloat2(const char* label, float v[2], float v_min,
				float v_max, const char* format = "%.3f",
				ImGuiSliderFlags flags = 0);
			bool SliderFloat3(const char* label, float v[3], float v_min,
				float v_max, const char* format = "%.3f",
				ImGuiSliderFlags flags = 0);
			bool SliderFloat4(const char* label, float v[4], float v_min,
				float v_max, const char* format = "%.3f",
				ImGuiSliderFlags flags = 0);
			bool SliderAngle(const char* label, float* v_rad,
				float v_degrees_min = -360.0f, float v_degrees_max = +360.0f,
				const char* format = "%.0f deg", ImGuiSliderFlags flags = 0);
			bool SliderInt(const char* label, int* v, int v_min, int v_max,
				const char* format = "%d", ImGuiSliderFlags flags = 0);
			bool SliderInt2(const char* label, int v[2], int v_min, int v_max,
				const char* format = "%d", ImGuiSliderFlags flags = 0);
			bool SliderInt3(const char* label, int v[3], int v_min, int v_max,
				const char* format = "%d", ImGuiSliderFlags flags = 0);
			bool SliderInt4(const char* label, int v[4], int v_min, int v_max,
				const char* format = "%d", ImGuiSliderFlags flags = 0);
			bool SliderScalar(const char* label, ImGuiDataType data_type,
				void* p_data, const void* p_min, const void* p_max,
				const char* format = NULL, ImGuiSliderFlags flags = 0);
			bool SliderScalarN(const char* label, ImGuiDataType data_type,
				void* p_data, int components, const void* p_min,
				const void* p_max, const char* format = NULL,
				ImGuiSliderFlags flags = 0);
			bool VSliderFloat(const char* label, const ImVec2& size, float* v,
				float v_min, float v_max, const char* format = "%.3f",
				ImGuiSliderFlags flags = 0);
			bool VSliderInt(const char* label, const ImVec2& size, int* v,
				int v_min, int v_max, const char* format = "%d",
				ImGuiSliderFlags flags = 0);
			bool VSliderScalar(const char* label, const ImVec2& size,
				ImGuiDataType data_type, void* p_data, const void* p_min,
				const void* p_max, const char* format = NULL,
				ImGuiSliderFlags flags = 0);
			bool InputText(const char* label, char* buf, size_t buf_size,
				ImGuiInputTextFlags flags = 0,
				ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
			bool InputTextMultiline(const char* label, char* buf,
				size_t buf_size, const ImVec2& size = ImVec2(0, 0),
				ImGuiInputTextFlags flags = 0,
				ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
			bool InputTextWithHint(const char* label, const char* hint,
				char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0,
				ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
			bool InputFloat(const char* label, float* v, float step = 0.0f,
				float step_fast = 0.0f, const char* format = "%.3f",
				ImGuiInputTextFlags flags = 0);
			bool InputFloat2(const char* label, float v[2],
				const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
			bool InputFloat3(const char* label, float v[3],
				const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
			bool InputFloat4(const char* label, float v[4],
				const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
			bool InputInt(const char* label, int* v, int step = 1,
				int step_fast = 100, ImGuiInputTextFlags flags = 0);
			bool InputInt2(
				const char* label, int v[2], ImGuiInputTextFlags flags = 0);
			bool InputInt3(
				const char* label, int v[3], ImGuiInputTextFlags flags = 0);
			bool InputInt4(
				const char* label, int v[4], ImGuiInputTextFlags flags = 0);
			bool InputDouble(const char* label, double* v, double step = 0.0,
				double step_fast = 0.0, const char* format = "%.6f",
				ImGuiInputTextFlags flags = 0);
			bool InputScalar(const char* label, ImGuiDataType data_type,
				void* p_data, const void* p_step = NULL,
				const void* p_step_fast = NULL, const char* format = NULL,
				ImGuiInputTextFlags flags = 0);
			bool InputScalarN(const char* label, ImGuiDataType data_type,
				void* p_data, int components, const void* p_step = NULL,
				const void* p_step_fast = NULL, const char* format = NULL,
				ImGuiInputTextFlags flags = 0);
			bool ColorEdit3(
				const char* label, float col[3], ImGuiColorEditFlags flags = 0);
			bool ColorEdit4(
				const char* label, float col[4], ImGuiColorEditFlags flags = 0);
			bool ColorPicker3(
				const char* label, float col[3], ImGuiColorEditFlags flags = 0);
			bool ColorPicker4(const char* label, float col[4],
				ImGuiColorEditFlags flags = 0, const float* ref_col = NULL);
			bool ColorButton(const char* desc_id, const ImVec4& col,
				ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0));
			void SetColorEditOptions(ImGuiColorEditFlags flags);
			bool TreeNode(const char* label);
			bool TreeNode(const char* str_id, const char* fmt, ...)
				IM_FMTARGS(2);
			bool TreeNode(const void* ptr_id, const char* fmt, ...)
				IM_FMTARGS(2);
			bool TreeNodeV(const char* str_id, const char* fmt, va_list args)
				IM_FMTLIST(2);
			bool TreeNodeV(const void* ptr_id, const char* fmt, va_list args)
				IM_FMTLIST(2);
			bool TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0);
			bool TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags,
				const char* fmt, ...) IM_FMTARGS(3);
			bool TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags,
				const char* fmt, ...) IM_FMTARGS(3);
			bool TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags,
				const char* fmt, va_list args) IM_FMTLIST(3);
			bool TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags,
				const char* fmt, va_list args) IM_FMTLIST(3);
			void TreePush(const char* str_id);
			void TreePush(const void* ptr_id = NULL);
			void TreePop();
			float GetTreeNodeToLabelSpacing();
			bool CollapsingHeader(
				const char* label, ImGuiTreeNodeFlags flags = 0);
			bool CollapsingHeader(const char* label, bool* p_visible,
				ImGuiTreeNodeFlags flags = 0);
			void SetNextItemOpen(bool is_open, ImGuiCond cond = 0);
			bool BeginListBox(
				const char* label, const ImVec2& size = ImVec2(0, 0));
			void EndListBox();
			bool ListBox(const char* label, int* current_item,
				const char* const items[], int items_count,
				int height_in_items = -1);
			bool ListBox(const char* label, int* current_item,
				bool (*items_getter)(
					void* data, int idx, const char** out_text),
				void* data, int items_count, int height_in_items = -1);
			void PlotLines(const char* label, const float* values,
				int values_count, int values_offset = 0,
				const char* overlay_text = NULL, float scale_min = FLT_MAX,
				float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0),
				int stride = sizeof(float));
			void PlotLines(const char* label,
				float (*values_getter)(void* data, int idx), void* data,
				int values_count, int values_offset = 0,
				const char* overlay_text = NULL, float scale_min = FLT_MAX,
				float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
			void PlotHistogram(const char* label, const float* values,
				int values_count, int values_offset = 0,
				const char* overlay_text = NULL, float scale_min = FLT_MAX,
				float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0),
				int stride = sizeof(float));
			void PlotHistogram(const char* label,
				float (*values_getter)(void* data, int idx), void* data,
				int values_count, int values_offset = 0,
				const char* overlay_text = NULL, float scale_min = FLT_MAX,
				float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0));
			void Value(const char* prefix, bool b);
			void Value(const char* prefix, int v);
			void Value(const char* prefix, unsigned int v);
			void Value(
				const char* prefix, float v, const char* float_format = NULL);

			bool BeginMenuBar();
			void EndMenuBar();
			bool BeginMainMenuBar();
			void EndMainMenuBar();
			bool BeginMenu(const char* label, bool enabled = true);
			void EndMenu();
			bool MenuItem(const char* label, const char* shortcut = NULL,
				bool selected = false, bool enabled = true);
			bool MenuItem(const char* label, const char* shortcut,
				bool* p_selected, bool enabled = true);

			void BeginTooltip();
			void EndTooltip();
			void SetTooltip(const char* fmt, ...) IM_FMTARGS(1);
			void SetTooltipV(const char* fmt, va_list args) IM_FMTLIST(1);

			bool BeginPopup(const char* str_id, ImGuiWindowFlags flags = 0);
			bool BeginPopupModal(const char* name, bool* p_open = NULL,
				ImGuiWindowFlags flags = 0);
			void EndPopup();

			void OpenPopup(const char* str_id, ImGuiPopupFlags popup_flags = 0);
			void OpenPopup(ImGuiID id, ImGuiPopupFlags popup_flags = 0);
			void OpenPopupOnItemClick(
				const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
			void CloseCurrentPopup();

			bool BeginPopupContextItem(
				const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
			bool BeginPopupContextWindow(
				const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);
			bool BeginPopupContextVoid(
				const char* str_id = NULL, ImGuiPopupFlags popup_flags = 1);

			bool IsPopupOpen(const char* str_id, ImGuiPopupFlags flags = 0);

			bool BeginTable(const char* str_id, int column,
				ImGuiTableFlags flags = 0,
				const ImVec2& outer_size = ImVec2(0.0f, 0.0f),
				float inner_width = 0.0f);
			void EndTable();
			void TableNextRow(
				ImGuiTableRowFlags row_flags = 0, float min_row_height = 0.0f);
			bool TableNextColumn();
			bool TableSetColumnIndex(int column_n);

			void TableSetupColumn(const char* label,
				ImGuiTableColumnFlags flags = 0,
				float init_width_or_weight = 0.0f, ImGuiID user_id = 0);
			void TableSetupScrollFreeze(int cols, int rows);
			void TableHeadersRow();
			void TableHeader(const char* label);

			ImGuiTableSortSpecs* TableGetSortSpecs();

			int TableGetColumnCount();
			int TableGetColumnIndex();
			int TableGetRowIndex();
			const char* TableGetColumnName(int column_n = -1);
			ImGuiTableColumnFlags TableGetColumnFlags(int column_n = -1);
			void TableSetColumnEnabled(int column_n, bool v);
			void TableSetBgColor(
				ImGuiTableBgTarget target, ImU32 color, int column_n = -1);

			void Columns(
				int count = 1, const char* id = NULL, bool border = true);
			void NextColumn();
			int GetColumnIndex();
			float GetColumnWidth(int column_index = -1);
			void SetColumnWidth(int column_index, float width);
			float GetColumnOffset(int column_index = -1);
			void SetColumnOffset(int column_index, float offset_x);
			int GetColumnsCount();

			bool BeginTabBar(const char* str_id, ImGuiTabBarFlags flags = 0);
			void EndTabBar();
			bool BeginTabItem(const char* label, bool* p_open = NULL,
				ImGuiTabItemFlags flags = 0);
			void EndTabItem();
			bool TabItemButton(const char* label, ImGuiTabItemFlags flags = 0);
			void SetTabItemClosed(const char* tab_or_docked_window_label);

			ImGuiID DockSpace(ImGuiID id, const ImVec2& size = ImVec2(0, 0),
				ImGuiDockNodeFlags flags = 0,
				const ImGuiWindowClass* window_class = NULL);
			ImGuiID DockSpaceOverViewport(const ImGuiViewport* viewport = NULL,
				ImGuiDockNodeFlags flags = 0,
				const ImGuiWindowClass* window_class = NULL);
			void SetNextWindowDockID(ImGuiID dock_id, ImGuiCond cond = 0);
			void SetNextWindowClass(const ImGuiWindowClass* window_class);
			ImGuiID GetWindowDockID();
			bool IsWindowDocked();

			void LogToTTY(int auto_open_depth = -1);
			void LogToFile(
				int auto_open_depth = -1, const char* filename = NULL);
			void LogToClipboard(int auto_open_depth = -1);
			void LogFinish();
			void LogButtons();
			void LogText(const char* fmt, ...) IM_FMTARGS(1);
			void LogTextV(const char* fmt, va_list args) IM_FMTLIST(1);

			bool BeginDragDropSource(ImGuiDragDropFlags flags = 0);
			bool SetDragDropPayload(const char* type, const void* data,
				size_t sz, ImGuiCond cond = 0);
			void EndDragDropSource();
			bool BeginDragDropTarget();
			const ImGuiPayload* AcceptDragDropPayload(
				const char* type, ImGuiDragDropFlags flags = 0);
			void EndDragDropTarget();
			const ImGuiPayload* GetDragDropPayload();

			void BeginDisabled(bool disabled = true);
			void EndDisabled();

			void PushClipRect(const ImVec2& clip_rect_min,
				const ImVec2& clip_rect_max,
				bool intersect_with_current_clip_rect);
			void PopClipRect();

			void SetItemDefaultFocus();
			void SetKeyboardFocusHere(int offset = 0);

			bool IsItemHovered(ImGuiHoveredFlags flags = 0);
			bool IsItemActive();
			bool IsItemFocused();
			bool IsItemClicked(ImGuiMouseButton mouse_button = 0);
			bool IsItemVisible();
			bool IsItemEdited();
			bool IsItemActivated();
			bool IsItemDeactivated();
			bool IsItemDeactivatedAfterEdit();
			bool IsItemToggledOpen();
			bool IsAnyItemHovered();
			bool IsAnyItemActive();
			bool IsAnyItemFocused();
			ImVec2 GetItemRectMin();
			ImVec2 GetItemRectMax();
			ImVec2 GetItemRectSize();
			void SetItemAllowOverlap();

			ImGuiViewport* GetMainViewport();

			bool IsRectVisible(const ImVec2& size);
			bool IsRectVisible(const ImVec2& rect_min, const ImVec2& rect_max);
			double GetTime();
			int GetFrameCount();
			ImDrawList* GetBackgroundDrawList();
			ImDrawList* GetForegroundDrawList();
			ImDrawList* GetBackgroundDrawList(ImGuiViewport* viewport);
			ImDrawList* GetForegroundDrawList(ImGuiViewport* viewport);
			ImDrawListSharedData* GetDrawListSharedData();
			const char* GetStyleColorName(ImGuiCol idx);
			void SetStateStorage(ImGuiStorage* storage);
			ImGuiStorage* GetStateStorage();
			void CalcListClipping(int items_count, float items_height,
				int* out_items_display_start, int* out_items_display_end);
			bool BeginChildFrame(
				ImGuiID id, const ImVec2& size, ImGuiWindowFlags flags = 0);
			void EndChildFrame();

			ImVec2 CalcTextSize(const char* text, const char* text_end = NULL,
				bool hide_text_after_double_hash = false,
				float wrap_width = -1.0f);

			ImVec4 ColorConvertU32ToFloat4(ImU32 in);
			ImU32 ColorConvertFloat4ToU32(const ImVec4& in);
			void ColorConvertRGBtoHSV(float r, float g, float b, float& out_h,
				float& out_s, float& out_v);
			void ColorConvertHSVtoRGB(float h, float s, float v, float& out_r,
				float& out_g, float& out_b);

			int GetKeyIndex(ImGuiKey imgui_key);
			bool IsKeyDown(int user_key_index);
			bool IsKeyPressed(int user_key_index, bool repeat = true);
			bool IsKeyReleased(int user_key_index);
			int GetKeyPressedAmount(
				int key_index, float repeat_delay, float rate);
			void CaptureKeyboardFromApp(
				bool want_capture_keyboard_value = true);

			bool IsMouseDown(ImGuiMouseButton button);
			bool IsMouseClicked(ImGuiMouseButton button, bool repeat = false);
			bool IsMouseReleased(ImGuiMouseButton button);
			bool IsMouseDoubleClicked(ImGuiMouseButton button);
			bool IsMouseHoveringRect(
				const ImVec2& r_min, const ImVec2& r_max, bool clip = true);
			bool IsMousePosValid(const ImVec2* mouse_pos = NULL);
			bool IsAnyMouseDown();
			ImVec2 GetMousePos();
			ImVec2 GetMousePosOnOpeningCurrentPopup();
			bool IsMouseDragging(
				ImGuiMouseButton button, float lock_threshold = -1.0f);
			ImVec2 GetMouseDragDelta(
				ImGuiMouseButton button = 0, float lock_threshold = -1.0f);
			void ResetMouseDragDelta(ImGuiMouseButton button = 0);
			ImGuiMouseCursor GetMouseCursor();
			void SetMouseCursor(ImGuiMouseCursor cursor_type);
			void CaptureMouseFromApp(bool want_capture_mouse_value = true);

			const char* GetClipboardText();
			void SetClipboardText(const char* text);

			void LoadIniSettingsFromDisk(const char* ini_filename);
			void LoadIniSettingsFromMemory(
				const char* ini_data, size_t ini_size = 0);
			void SaveIniSettingsToDisk(const char* ini_filename);
			const char* SaveIniSettingsToMemory(size_t* out_ini_size = NULL);

			bool DebugCheckVersionAndDataLayout(const char* version_str,
				size_t sz_io, size_t sz_style, size_t sz_vec2, size_t sz_vec4,
				size_t sz_drawvert, size_t sz_drawidx);

			void SetAllocatorFunctions(ImGuiMemAllocFunc alloc_func,
				ImGuiMemFreeFunc free_func, void* user_data = NULL);
			void GetAllocatorFunctions(ImGuiMemAllocFunc* p_alloc_func,
				ImGuiMemFreeFunc* p_free_func, void** p_user_data);
			void* MemAlloc(size_t size);
			void MemFree(void* ptr);

			ImGuiPlatformIO& GetPlatformIO();
			void UpdatePlatformWindows();
			void RenderPlatformWindowsDefault(void* platform_render_arg = NULL,
				void* renderer_render_arg = NULL);
			void DestroyPlatformWindows();
			ImGuiViewport* FindViewportByID(ImGuiID id);
			ImGuiViewport* FindViewportByPlatformHandle(void* platform_handle);
		};
	} // namespace UI
} // namespace Kotek
