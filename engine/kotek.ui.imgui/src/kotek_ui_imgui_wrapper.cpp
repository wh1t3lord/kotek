#include "../include/kotek_ui_imgui_wrapper.h"

#include <kotek.ui.imgui/include/kotek_ui_imgui.h>

namespace Kotek
{
	namespace UI
	{
		ktkImguiWrapper::ktkImguiWrapper(void) {}

		ktkImguiWrapper::~ktkImguiWrapper(void) {}

		void ktkImguiWrapper::ImGui_ImplGlfw_NewFrame(void)
		{
			::ImGui_ImplGlfw_NewFrame();
		}

		bool ktkImguiWrapper::ImGui_ImplOpenGL3_Init(const char* glsl_version)
		{
			return ::ImGui_ImplOpenGL3_Init();
		}

		void ktkImguiWrapper::ImGui_ImplOpenGL3_NewFrame(void)
		{
			::ImGui_ImplOpenGL3_NewFrame();
		}

		void ktkImguiWrapper::ImGui_ImplOpenGL3_Shutdown(void)
		{
			::ImGui_ImplOpenGL3_Shutdown();
		}

		void ktkImguiWrapper::ImGui_ImplGlfw_Shutdown(void)
		{
			::ImGui_ImplGlfw_Shutdown();
		}

		bool ktkImguiWrapper::ImGui_ImplGlfw_InitForOpenGL(
			void* window_handle, bool install_callbacks)
		{
#ifdef KOTEK_USE_WINDOW_LIBRARY_GLFW
			return ::ImGui_ImplGlfw_InitForOpenGL(
				static_cast<GLFWwindow*>(window_handle), install_callbacks);
#else
			return false;
#endif
		}

		void* ktkImguiWrapper::CreateContext(void* shared_font_atlas)
		{
			return ImGui::CreateContext(
				static_cast<ImFontAtlas*>(shared_font_atlas));
		}

		void ktkImguiWrapper::DestroyContext(void* context)
		{
			ImGui::DestroyContext(static_cast<ImGuiContext*>(context));
		}

		void* ktkImguiWrapper::GetIO(void)
		{
			return &ImGui::GetIO();
		}

		void* ktkImguiWrapper::GetStyle(void)
		{
			return &ImGui::GetStyle();
		}

		void ktkImguiWrapper::StyleColorsDark(void* style)
		{
			ImGui::StyleColorsDark(static_cast<ImGuiStyle*>(style));
		}

		void ktkImguiWrapper::NewFrame(void)
		{
			ImGui::NewFrame();
		}

		void ktkImguiWrapper::Render(void)
		{
			ImGui::Render();
		}
		ImGuiContext* ktkImguiWrapper::GetCurrentContext()
		{
			return ImGui::GetCurrentContext();
		}
		void          ktkImguiWrapper::SetCurrentContext(ImGuiContext* ctx)
		{
			ImGui::SetCurrentContext(ctx);
		}                            
		void          ktkImguiWrapper::NewFrame()
		{
			ImGui::NewFrame();
		}                              
		void          ktkImguiWrapper::EndFrame()
		{
			ImGui::EndFrame();
		}                              
		void          ktkImguiWrapper::Render()
		{
			ImGui::Render();
		}                                
		ImDrawData*   ktkImguiWrapper::GetDrawData()
		{
			return ImGui::GetDrawData();
		}           

		void          ktkImguiWrapper::ShowDemoWindow(bool* p_open)
		{
			ImGui::ShowDemoWindow(p_open);
		}       
		void          ktkImguiWrapper::ShowMetricsWindow(bool* p_open)
		{
			ImGui::ShowMetricsWindow(p_open);
		}    
		void          ktkImguiWrapper::ShowStackToolWindow(bool* p_open)
		{
			ImGui::ShowStackToolWindow(p_open);
		}  
		void          ktkImguiWrapper::ShowAboutWindow(bool* p_open)
		{
			ImGui::ShowAboutWindow(p_open);
		}      
		void          ktkImguiWrapper::ShowStyleEditor(ImGuiStyle* ref)
		{
			ImGui::ShowStyleEditor(ref);
		}   
		bool          ktkImguiWrapper::ShowStyleSelector(const char* label)
		{
			ImGui::ShowStyleSelector(label);
		}      
		void          ktkImguiWrapper::ShowFontSelector(const char* label)
		{
			ImGui::ShowFontSelector(label);
		}       
		void          ktkImguiWrapper::ShowUserGuide()
		{
			ImGui::ShowUserGuide();
		}                           
		const char*   ktkImguiWrapper::GetVersion()
		{
			return ImGui::GetVersion();
		}                              
		void          ktkImguiWrapper::StyleColorsLight(ImGuiStyle* dst)
		{
			ImGui::StyleColorsLight(dst);
		}  
		void          ktkImguiWrapper::StyleColorsClassic(ImGuiStyle* dst)
		{
			ImGui::StyleColorsClassic(dst);
		}
		bool          ktkImguiWrapper::Begin(const char* name, bool* p_open, ImGuiWindowFlags flags)
		{
			return ImGui::Begin(name,p_open,flags);
		}
		void          ktkImguiWrapper::End()
		{
			ImGui::End();
		}
		bool          ktkImguiWrapper::BeginChild(const char* str_id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
		{
			return ImGui::BeginChild(str_id,size,border,flags);
		}
		bool          ktkImguiWrapper::BeginChild(ImGuiID id, const ImVec2& size, bool border, ImGuiWindowFlags flags)
		{
			return ImGui::BeginChild(id,
size,
border,
flags);
		}
		void          ktkImguiWrapper::EndChild()
		{
			ImGui::EndChild();
		}
		void          ktkImguiWrapper::SetNextWindowPos(const ImVec2& pos, ImGuiCond cond, const ImVec2& pivot)
		{
			ImGui::SetNextWindowPos(pos, cond, pivot);
		}
		void          ktkImguiWrapper::SetNextWindowSize(const ImVec2& size, ImGuiCond cond)
		{
			ImGui::SetNextWindowSize(size, cond);
		}                  
		void          ktkImguiWrapper::SetNextWindowSizeConstraints(const ImVec2& size_min, const ImVec2& size_max, ImGuiSizeCallback custom_callback, void* custom_callback_data)
		{
			ImGui::SetNextWindowSizeConstraints(size_min, size_max, custom_callback, custom_callback_data);
		} 
		void          ktkImguiWrapper::SetNextWindowContentSize(const ImVec2& size)
		{
			ImGui::SetNextWindowContentSize(size);
		}                               
		void          ktkImguiWrapper::SetNextWindowCollapsed(bool collapsed, ImGuiCond cond)
		{
			ImGui::SetNextWindowCollapsed(collapsed, cond);
		}                 
		void          ktkImguiWrapper::SetNextWindowFocus()
		{
			ImGui::SetNextWindowFocus();
		}                                                       
		void          ktkImguiWrapper::SetNextWindowBgAlpha(float alpha)
		{
			ImGui::SetNextWindowBgAlpha(alpha);
		}                                          
		void          ktkImguiWrapper::SetNextWindowViewport(ImGuiID viewport_id)
		{
			ImGui::SetNextWindowViewport(viewport_id);
		}                                 
		void          ktkImguiWrapper::SetWindowPos(const ImVec2& pos, ImGuiCond cond)
		{
			ImGui::SetWindowPos(pos, cond);
		}                        
		void          ktkImguiWrapper::SetWindowSize(const ImVec2& size, ImGuiCond cond)
		{
			ImGui::SetWindowSize(size, cond);
		}                      
		void          ktkImguiWrapper::SetWindowCollapsed(bool collapsed, ImGuiCond cond)
		{
			ImGui::SetWindowCollapsed(collapsed, cond);
		}                     
		void          ktkImguiWrapper::SetWindowFocus()
		{
			ImGui::SetWindowFocus();
		}                                                           
		void          ktkImguiWrapper::SetWindowFontScale(float scale)
		{
			ImGui::SetWindowFontScale(scale);
		}                                            
		void          ktkImguiWrapper::SetWindowPos(const char* name, const ImVec2& pos, ImGuiCond cond)
		{
			ImGui::SetWindowPos(name, pos, cond);
		}      
		void          ktkImguiWrapper::SetWindowSize(const char* name, const ImVec2& size, ImGuiCond cond)
		{
			ImGui::SetWindowSize(name, size, cond);
		}    
		void          ktkImguiWrapper::SetWindowCollapsed(const char* name, bool collapsed, ImGuiCond cond)
		{
			ImGui::SetWindowCollapsed(name, collapsed, cond);
		}   
		void          ktkImguiWrapper::SetWindowFocus(const char* name)
		{
			ImGui::SetWindowFocus(name);
		}

		float         ktkImguiWrapper::GetScrollX()
		{
			return ImGui::GetScrollX();
		}                                                 
		float         ktkImguiWrapper::GetScrollY()
		{
			return ImGui::GetScrollY();
		}                                                 
		void          ktkImguiWrapper::SetScrollX(float scroll_x)
		{
			ImGui::SetScrollX(scroll_x);
		}                                   
		void          ktkImguiWrapper::SetScrollY(float scroll_y)
		{
			ImGui::SetScrollY(scroll_y);
		}                                   
		float         ktkImguiWrapper::GetScrollMaxX()
		{
			return ImGui::GetScrollMaxX();
		}                                              
		float         ktkImguiWrapper::GetScrollMaxY()
		{
			return ImGui::GetScrollMaxY();
		}                                              
		void          ktkImguiWrapper::SetScrollHereX(float center_x_ratio)
		{
			ImGui::SetScrollHereX(center_x_ratio);
		}                  
		void          ktkImguiWrapper::SetScrollHereY(float center_y_ratio)
		{
			ImGui::SetScrollHereY(center_y_ratio);
		}                  
		void          ktkImguiWrapper::SetScrollFromPosX(float local_x, float center_x_ratio)
		{
			ImGui::SetScrollFromPosX(local_x, center_x_ratio);
		}
		void          ktkImguiWrapper::SetScrollFromPosY(float local_y, float center_y_ratio)
		{
			ImGui::SetScrollFromPosY(local_y, center_y_ratio);
		}  
		void          ktkImguiWrapper::PushFont(ImFont* font)
		{
			ImGui::PushFont(font);
		}                            
		void          ktkImguiWrapper::PopFont()
		{
			ImGui::PopFont();
		}
		void          ktkImguiWrapper::PushStyleColor(ImGuiCol idx, ImU32 col)
		{
			ImGui::PushStyleColor(idx, col);
		}           
		void          ktkImguiWrapper::PushStyleColor(ImGuiCol idx, const ImVec4& col)
		{
			ImGui::PushStyleColor(idx, col);
		}
		void          ktkImguiWrapper::PopStyleColor(int count)
		{
			ImGui::PopStyleColor(count);
		}
		void          ktkImguiWrapper::PushStyleVar(ImGuiStyleVar idx, float val)
		{
			ImGui::PushStyleVar(idx, val);
		}        
		void          ktkImguiWrapper::PushStyleVar(ImGuiStyleVar idx, const ImVec2& val)
		{
			ImGui::PushStyleVar(idx, val);
		}
		void          ktkImguiWrapper::PopStyleVar(int count)
		{
			ImGui::PopStyleVar(count);
		}
		void          ktkImguiWrapper::PushAllowKeyboardFocus(bool allow_keyboard_focus)
		{
			ImGui::PushAllowKeyboardFocus(allow_keyboard_focus);
		} 
		void          ktkImguiWrapper::PopAllowKeyboardFocus()
		{
			ImGui::PopAllowKeyboardFocus();
		}
		void          ktkImguiWrapper::PushButtonRepeat(bool repeat)
		{
			ImGui::PushButtonRepeat(repeat);
		}                     
		void          ktkImguiWrapper::PopButtonRepeat()
		{
			ImGui::PopButtonRepeat();
		}        
		void          ktkImguiWrapper::PushItemWidth(float item_width)
		{
			ImGui::PushItemWidth(item_width);
		}               
		void          ktkImguiWrapper::PopItemWidth()
		{
			ImGui::PopItemWidth();
		}
		void          ktkImguiWrapper::SetNextItemWidth(float item_width)
		{
			ImGui::SetNextItemWidth(item_width);
		}            
		float         ktkImguiWrapper::CalcItemWidth()
		{
			return ImGui::CalcItemWidth();
		}                               
		void          ktkImguiWrapper::PushTextWrapPos(float wrap_local_pos_x)
		{
			ImGui::PushTextWrapPos(wrap_local_pos_x);
		}
		void          ktkImguiWrapper::PopTextWrapPos()
		{
			ImGui::PopTextWrapPos();
		}     
		ImFont*       ktkImguiWrapper::GetFont()
		{
			return ImGui::GetFont();
		}                                        
		float         ktkImguiWrapper::GetFontSize()
		{
			return ImGui::GetFontSize();
		}                                    
		ImVec2        ktkImguiWrapper::GetFontTexUvWhitePixel()
		{
			return ImGui::GetFontTexUvWhitePixel();
		}                         
		ImU32         ktkImguiWrapper::GetColorU32(ImGuiCol idx, float alpha_mul)
		{
			return ImGui::GetColorU32(idx, alpha_mul);
		}
		ImU32         ktkImguiWrapper::GetColorU32(const ImVec4& col)
		{
			return ImGui::GetColorU32(col);
		}                   
		ImU32         ktkImguiWrapper::GetColorU32(ImU32 col)
		{
			return ImGui::GetColorU32(col);
		}                           
		const ImVec4& ktkImguiWrapper::GetStyleColorVec4(ImGuiCol idx)
		{
			return ImGui::GetStyleColorVec4(idx);
		}
		void          ktkImguiWrapper::PushID(const char* str_id)
		{
			ImGui::PushID(str_id);
		}                              
		void          ktkImguiWrapper::PushID(const char* str_id_begin, const char* str_id_end)
		{
			ImGui::PushID(str_id_begin, str_id_end);
		}
		void          ktkImguiWrapper::PushID(const void* ptr_id)
		{
			ImGui::PushID(ptr_id);
		}                              
		void          ktkImguiWrapper::PushID(int int_id)
		{
			ImGui::PushID(int_id);
		}                                      
		void          ktkImguiWrapper::PopID()
		{
			ImGui::PopID();
		}                                                 
		ImGuiID       ktkImguiWrapper::GetID(const char* str_id)
		{
			return ImGui::GetID(str_id);
		}                               
		ImGuiID       ktkImguiWrapper::GetID(const char* str_id_begin, const char* str_id_end)
		{
			return ImGui::GetID(str_id_begin, str_id_end);
		}
		ImGuiID       ktkImguiWrapper::GetID(const void* ptr_id)
		{
			return ImGui::GetID(ptr_id);
		}
		void          ktkImguiWrapper::TextUnformatted(const char* text, const char* text_end)
		{
			ImGui::TextUnformatted(text, text_end);
		} 
		void          ktkImguiWrapper::Text(const char* fmt, ...)                                    
		{
			va_list args;
			va_start(args, fmt);
			ImGui::Text(fmt, args);
			va_end(args);
		}
		void          ktkImguiWrapper::TextV(const char* fmt, va_list args)                          
		{
			ImGui::TextV(fmt, args);
		}
		void          ktkImguiWrapper::TextColored(const ImVec4& col, const char* fmt, ...)          
		{
			va_list args;
			va_start(args, fmt);
			ImGui::TextColored(col, fmt, args);
			va_end(args);
		}
		void          ktkImguiWrapper::TextColoredV(const ImVec4& col, const char* fmt, va_list args)
		{
			ImGui::TextColoredV(col, fmt, args);
		}
		void          ktkImguiWrapper::TextDisabled(const char* fmt, ...)                            
		{
			va_list args;
			va_start(args, fmt);
			ImGui::TextDisabled(fmt, args);
			va_end(args);
		}
		void          ktkImguiWrapper::TextDisabledV(const char* fmt, va_list args)                  
		{
			ImGui::TextDisabledV(fmt, args);
		}
		void          ktkImguiWrapper::TextWrapped(const char* fmt, ...)                             
		{
			va_list args;
			va_start(args, fmt);
			ImGui::TextWrapped(fmt, args);
			va_end(args);
		}
		void          ktkImguiWrapper::TextWrappedV(const char* fmt, va_list args)                   
		{
			ImGui::TextWrappedV(fmt, args);
		}
		void          ktkImguiWrapper::LabelText(const char* label, const char* fmt, ...)            
		{
			va_list args;
			va_start(args, fmt);
			ImGui::LabelText(label, fmt, args);
			va_end(fmt);
		}
		void          ktkImguiWrapper::LabelTextV(const char* label, const char* fmt, va_list args)  
		{
			ImGui::LabelTextV(label, fmt, args);
		}
		void          ktkImguiWrapper::BulletText(const char* fmt, ...)                              
		{
			va_list args;
			va_start(args, fmt);
			ImGui::BulletText(fmt, args);
			va_end(args);
		}
		void          ktkImguiWrapper::BulletTextV(const char* fmt, va_list args)                    
		{
			ImGui::BulletTextV(fmt, args);
		} 
		bool          ktkImguiWrapper::Button(const char* label, const ImVec2& size)
		{
			return ImGui::Button(label, size);
		}   
		bool          ktkImguiWrapper::SmallButton(const char* label)
		{
			return ImGui::SmallButton(label);
		}                              
		bool          ktkImguiWrapper::InvisibleButton(const char* str_id, const ImVec2& size, ImGuiButtonFlags flags)
		{
			return ImGui::InvisibleButton(str_id, size, flags);
		} 
		bool          ktkImguiWrapper::ArrowButton(const char* str_id, ImGuiDir dir)
		{
			return ImGui::ArrowButton(str_id, dir);
		}                 
		void          ktkImguiWrapper::Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col)
		{
			ImGui::Image(user_texture_id, size, uv0, uv1, tint_col, border_col);
		}
		bool          ktkImguiWrapper::ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0,  const ImVec2& uv1, int frame_padding, const ImVec4& bg_col, const ImVec4& tint_col)
		{
			return ImGui::ImageButton(user_texture_id, size, uv0, uv1, frame_padding, bg_col, tint_col);
		}
		bool          ktkImguiWrapper::Checkbox(const char* label, bool* v)
		{
			return ImGui::Checkbox(label, v);
		}
		bool          ktkImguiWrapper::CheckboxFlags(const char* label, int* flags, int flags_value)
		{
			return ImGui::CheckboxFlags(label, flags, flags_value);
		}
		bool          ktkImguiWrapper::CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value)
		{
			return ImGui::CheckboxFlags(label, flags, flags_value);
		}
		bool          ktkImguiWrapper::RadioButton(const char* label, bool active)
		{
			return ImGui::RadioButton(label, active);
		}                    
		bool          ktkImguiWrapper::RadioButton(const char* label, int* v, int v_button)
		{
			return ImGui::RadioButton(label, v, v_button);
		}          
		void          ktkImguiWrapper::ProgressBar(float fraction, const ImVec2& size_arg, const char* overlay)
		{
			ImGui::ProgressBar(fraction, size_arg, overlay);
		}
		void          ktkImguiWrapper::Bullet()
		{
			ImGui::Bullet();
		}
		bool          ktkImguiWrapper::BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags)
		{
			return ImGui::BeginCombo(label, preview_value, flags);
		}
		void          ktkImguiWrapper::EndCombo()
		{
			ImGui::EndCombo();
		} 
		bool          ktkImguiWrapper::Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items)
		{
			return ImGui::Combo(label, current_item, items, items_count, popup_max_height_in_items);
		}
		bool          ktkImguiWrapper::Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items)
		{
			return ImGui::Combo(label, current_item, items_separated_by_zeros, popup_max_height_in_items);
		}     
		bool          ktkImguiWrapper::Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items)
		{
			return ImGui::Combo(label, current_item, items_getter, data, items_count, popup_max_height_in_items);
		}
		bool          ktkImguiWrapper::DragFloat(const char* label, float* v, float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragFloat(label, v, v_speed, v_min, v_max, format, flags);
		}    
		bool          ktkImguiWrapper::DragFloat2(const char* label, float v[2], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragFloat2(label, v, v_speed, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::DragFloat3(const char* label, float v[3], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragFloat3(label, v, v_speed, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::DragFloat4(const char* label, float v[4], float v_speed, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragFloat4(label, v, v_speed, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed, float v_min, float v_max, const char* format, const char* format_max, ImGuiSliderFlags flags)
		{
			return ImGui::DragFloatRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, format, format_max, flags);
		}
		bool          ktkImguiWrapper::DragInt(const char* label, int* v, float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragInt(label, v, v_speed, v_min, v_max, format, flags);
		} 
		bool          ktkImguiWrapper::DragInt2(const char* label, int v[2], float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragInt2(label, v, v_speed, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::DragInt3(const char* label, int v[3], float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragInt3(label, v, v_speed, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::DragInt4(const char* label, int v[4], float v_speed, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragInt4(label, v, v_speed, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed, int v_min, int v_max, const char* format, const char* format_max, ImGuiSliderFlags flags)
		{
			return ImGui::DragIntRange2(label, v_current_min, v_current_max, v_speed, v_min, v_max, format, format_max, flags);
		}
		bool          ktkImguiWrapper::DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragScalar(label, data_type, p_data, v_speed, p_min, p_max, format, flags);
		}
		bool          ktkImguiWrapper::DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::DragScalarN(label, data_type, p_data, components, v_speed, p_min, p_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderFloat(label, v, v_min, v_max, format, flags);
		}      
		bool          ktkImguiWrapper::SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderFloat2(label, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderFloat3(label, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderFloat4(label, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderAngle(const char* label, float* v_rad, float v_degrees_min, float v_degrees_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderAngle(label, v_rad, v_degrees_min, v_degrees_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderInt(const char* label, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderInt(label, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderInt2(label, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderInt3(label, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderInt4(label, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderScalar(label, data_type, p_data, p_min, p_max, format, flags);
		}
		bool          ktkImguiWrapper::SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::SliderScalarN(label, data_type, p_data, components, p_min, p_max, format, flags);
		}
		bool          ktkImguiWrapper::VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::VSliderFloat(label, size, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::VSliderInt(label, size, v, v_min, v_max, format, flags);
		}
		bool          ktkImguiWrapper::VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format, ImGuiSliderFlags flags)
		{
			return ImGui::VSliderScalar(label, size, data_type, p_data, p_min, p_max, format, flags);
		}
		bool          ktkImguiWrapper::InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
		{
			return ImGui::InputText(label, buf, buf_size, flags, callback, user_data);
		}
		bool          ktkImguiWrapper::InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
		{
			return ImGui::InputTextMultiline(label, buf, buf_size, size, flags, callback, user_data);
		}
		bool          ktkImguiWrapper::InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
		{
			return ImGui::InputTextWithHint(label, hint, buf, buf_size, flags, callback, user_data);
		}
		bool          ktkImguiWrapper::InputFloat(const char* label, float* v, float step, float step_fast, const char* format, ImGuiInputTextFlags flags)
		{
			return ImGui::InputFloat(label, v, step, step_fast, format, flags);
		}
		bool          ktkImguiWrapper::InputFloat2(const char* label, float v[2], const char* format, ImGuiInputTextFlags flags)
		{
			return ImGui::InputFloat2(label, v, format, flags);
		}
		bool          ktkImguiWrapper::InputFloat3(const char* label, float v[3], const char* format, ImGuiInputTextFlags flags)
		{
			return ImGui::InputFloat3(label, v, format, flags);
		}
		bool          ktkImguiWrapper::InputFloat4(const char* label, float v[4], const char* format, ImGuiInputTextFlags flags)
		{
			return ImGui::InputFloat4(label, v, format, flags);
		}
		bool          ktkImguiWrapper::InputInt(const char* label, int* v, int step, int step_fast, ImGuiInputTextFlags flags)
		{
			return ImGui::InputInt(label, v, step, step_fast, flags);
		}
		bool          ktkImguiWrapper::InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags)
		{
			return ImGui::InputInt(label, v, flags);
		}
		bool          ktkImguiWrapper::InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags)
		{
			return ImGui::InputInt(label, v, flags);
		}
		bool          ktkImguiWrapper::InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags)
		{
			return ImGui::InputInt(label, v, flags);
		}
		bool          ktkImguiWrapper::InputDouble(const char* label, double* v, double step, double step_fast, const char* format, ImGuiInputTextFlags flags)
		{
			return ImGui::InputDouble(label, v, step, step_fast, format, flags);
		}
		bool          ktkImguiWrapper::InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step, const void* p_step_fast, const char* format, ImGuiInputTextFlags flags)
		{
			return ImGui::InputScalar(label, data_type, p_data, p_step, p_step_fast, format, flags);
		}
		bool          ktkImguiWrapper::InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step, const void* p_step_fast, const char* format, ImGuiInputTextFlags flags)
		{
			return ImGui::InputScalarN(label, data_type, p_data, components, p_step, p_step_fast, format, flags);
		}
		bool          ktkImguiWrapper::ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags)
		{
			return ImGui::ColorEdit3(label, col, flags);
		}
		bool          ktkImguiWrapper::ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags)
		{
			return ImGui::ColorEdit4(label, col, flags);
		}
		bool          ktkImguiWrapper::ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags)
		{
			return ImGui::ColorPicker3(label, col, flags);
		}
		bool          ktkImguiWrapper::ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags, const float* ref_col)
		{
			return ImGui::ColorPicker4(label, col, flags, ref_col);
		}
		bool          ktkImguiWrapper::ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags, ImVec2 size)
		{
			return ImGui::ColorButton(desc_id, col, flags, size);
		} 
		void          ktkImguiWrapper::SetColorEditOptions(ImGuiColorEditFlags flags)
		{
			return ImGui::SetColorEditOptions(flags);
		}                     
		bool          ktkImguiWrapper::TreeNode(const char* label)
		{
			return ImGui::TreeNode(label);
		}
		bool          ktkImguiWrapper::TreeNode(const char* str_id, const char* fmt, ...)
		{
			va_list args;
			va_start(args, fmt);
			bool status = ImGui::TreeNode(str_id, fmt, args);
			va_end(args);

			return status;
		}   
		bool          ktkImguiWrapper::TreeNode(const void* ptr_id, const char* fmt, ...)
		{
			va_list args;
			va_start(args, fmt);
			bool status = ImGui::TreeNode(ptr_id, fmt,	args);
			va_end(args);

			return status;
		}   
		bool          ktkImguiWrapper::TreeNodeV(const char* str_id, const char* fmt, va_list args)
		{
			return ImGui::TreeNodeV(str_id, fmt, args);
		}
		bool          ktkImguiWrapper::TreeNodeV(const void* ptr_id, const char* fmt, va_list args)
		{
			return ImGui::TreeNodeV(ptr_id, fmt, args);
		}
		bool          ktkImguiWrapper::TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags)
		{
			return ImGui::TreeNodeEx(label, flags);
		}
		bool          ktkImguiWrapper::TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...)
		{
			va_list args;
			va_start(args, fmt);
			bool status = ImGui::TreeNodeEx(str_id, flags, fmt, args);
			va_end(args);

			return status;
		}
		bool          ktkImguiWrapper::TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...)
		{
			va_list args;
			va_start(args, fmt);
			bool status = ImGui::TreeNodeEx(ptr_id, flags, fmt, args);
			va_end(args);

			return status;
		}
		bool          ktkImguiWrapper::TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args)
		{
			return ImGui::TreeNodeExV(str_id, flags, fmt, args);
		}
		bool          ktkImguiWrapper::TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args)
		{
			return ImGui::TreeNodeExV(ptr_id, flags, fmt, args);
		}
		void          ktkImguiWrapper::TreePush(const char* str_id)
		{
			ImGui::TreePush(str_id);
		}                                       
		void          ktkImguiWrapper::TreePush(const void* ptr_id)
		{
			ImGui::TreePush(ptr_id);
		}                                
		void          ktkImguiWrapper::TreePop()
		{
			ImGui::TreePop();
		}                                                          
		float         ktkImguiWrapper::GetTreeNodeToLabelSpacing()
		{
			return ImGui::GetTreeNodeToLabelSpacing();
		}                                      
		bool          ktkImguiWrapper::CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags)
		{
			return ImGui::CollapsingHeader(label, flags);
		}  
		bool          ktkImguiWrapper::CollapsingHeader(const char* label, bool* p_visible, ImGuiTreeNodeFlags flags)
		{
			return ImGui::CollapsingHeader(label, p_visible, flags);
		} 
		void          ktkImguiWrapper::SetNextItemOpen(bool is_open, ImGuiCond cond)
		{
			ImGui::SetNextItemOpen(is_open, cond);
		}               
		bool          ktkImguiWrapper::BeginListBox(const char* label, const ImVec2& size)
		{
			return ImGui::BeginListBox(label, size);
		}
		void          ktkImguiWrapper::EndListBox()
		{
			ImGui::EndListBox();
		}                                                       
		bool          ktkImguiWrapper::ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items)
		{
			return ImGui::ListBox(label, current_item, items, items_count, height_in_items);
		}
		bool          ktkImguiWrapper::ListBox(const char* label, int* current_item, bool (*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items)
		{
			return ImGui::ListBox(label, current_item, items_getter, data, items_count, height_in_items);
		}
		void          ktkImguiWrapper::PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float)){}
		void          ktkImguiWrapper::PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0)){}
		void          ktkImguiWrapper::PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float)){}
		void          ktkImguiWrapper::PlotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0)){}                                                                                          
	} // namespace UI
} // namespace Kotek
