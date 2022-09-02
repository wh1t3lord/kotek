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

		ImGuiContext* ktkImguiWrapper::CreateContext(ImFontAtlas* shared_font_atlas)
		{
			return ImGui::CreateContext(shared_font_atlas);
		}
		void          ktkImguiWrapper::DestroyContext(ImGuiContext* ctx)
		{
			ImGui::DestroyContext(ctx);
		}
		ImGuiContext* ktkImguiWrapper::GetCurrentContext()
		{
			return ImGui::GetCurrentContext();
		}
		void          ktkImguiWrapper::SetCurrentContext(ImGuiContext* ctx)
		{
			ImGui::SetCurrentContext(ctx);
		}
		ImGuiIO&      ktkImguiWrapper::GetIO()
		{
			return ImGui::GetIO();
		}                                 
		ImGuiStyle&   ktkImguiWrapper::GetStyle()
		{
			return ImGui::GetStyle();
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
		void          ktkImguiWrapper::StyleColorsDark(ImGuiStyle* dst)
		{
			ImGui::StyleColorsDark(dst);
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
			ImGui::Text(fmt, ...);
		}
		void          ktkImguiWrapper::TextV(const char* fmt, va_list args)                          
		{
			ImGui::TextV(fmt, args);
		}
		void          ktkImguiWrapper::TextColored(const ImVec4& col, const char* fmt, ...)          
		{
			ImGui::TextColored(col, fmt, ...);
		}
		void          ktkImguiWrapper::TextColoredV(const ImVec4& col, const char* fmt, va_list args)
		{
			ImGui::TextColoredV(col, fmt, args);
		}
		void          ktkImguiWrapper::TextDisabled(const char* fmt, ...)                            
		{
			ImGui::TextDisabled(fmt, ...);
		}
		void          ktkImguiWrapper::TextDisabledV(const char* fmt, va_list args)                  
		{
			ImGui::TextDisabledV(fmt, args);
		}
		void          ktkImguiWrapper::TextWrapped(const char* fmt, ...)                             
		{
			ImGui::TextWrapped(fmt, ...);
		}
		void          ktkImguiWrapper::TextWrappedV(const char* fmt, va_list args)                   
		{
			ImGui::TextWrappedV(fmt, args);
		}
		void          ktkImguiWrapper::LabelText(const char* label, const char* fmt, ...)            
		{
			ImGui::LabelText(label, fmt, ...);
		}
		void          ktkImguiWrapper::LabelTextV(const char* label, const char* fmt, va_list args)  
		{
			ImGui::LabelTextV(label, fmt, args);
		}
		void          ktkImguiWrapper::BulletText(const char* fmt, ...)                              
		{
			ImGui::BulletText(fmt, ...);
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
		bool          ktkImguiWrapper::BeginCombo(const char* label, const char* preview_value, ImGuiComboFlags flags = 0){}
		void          ktkImguiWrapper::EndCombo(){} 
		bool          ktkImguiWrapper::Combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1){}
		bool          ktkImguiWrapper::Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1){}     
		bool          ktkImguiWrapper::Combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1){}
		bool          ktkImguiWrapper::DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}    
		bool          ktkImguiWrapper::DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0){} 
		bool          ktkImguiWrapper::DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragIntRange2(const char* label, int* v_current_min, int* v_current_max, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d", const char* format_max = NULL, ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragScalar(const char* label, ImGuiDataType data_type, void* p_data, float v_speed = 1.0f, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::DragScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, float v_speed = 1.0f, const void* p_min = NULL, const void* p_max = NULL, const char* format = NULL, ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}      
		bool          ktkImguiWrapper::SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::SliderScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* format = "%.3f", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* format = "%d", ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::VSliderScalar(const char* label, const ImVec2& size, ImGuiDataType data_type, void* p_data, const void* p_min, const void* p_max, const char* format = NULL, ImGuiSliderFlags flags = 0){}
		bool          ktkImguiWrapper::InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL){}
		bool          ktkImguiWrapper::InputTextMultiline(const char* label, char* buf, size_t buf_size, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL){}
		bool          ktkImguiWrapper::InputTextWithHint(const char* label, const char* hint, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL){}
		bool          ktkImguiWrapper::InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, const char* format = "%.3f", ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputFloat2(const char* label, float v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputFloat3(const char* label, float v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputFloat4(const char* label, float v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputInt2(const char* label, int v[2], ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputInt3(const char* label, int v[3], ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputInt4(const char* label, int v[4], ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputDouble(const char* label, double* v, double step = 0.0, double step_fast = 0.0, const char* format = "%.6f", ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputScalar(const char* label, ImGuiDataType data_type, void* p_data, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::InputScalarN(const char* label, ImGuiDataType data_type, void* p_data, int components, const void* p_step = NULL, const void* p_step_fast = NULL, const char* format = NULL, ImGuiInputTextFlags flags = 0){}
		bool          ktkImguiWrapper::ColorEdit3(const char* label, float col[3], ImGuiColorEditFlags flags = 0){}
		bool          ktkImguiWrapper::ColorEdit4(const char* label, float col[4], ImGuiColorEditFlags flags = 0){}
		bool          ktkImguiWrapper::ColorPicker3(const char* label, float col[3], ImGuiColorEditFlags flags = 0){}
		bool          ktkImguiWrapper::ColorPicker4(const char* label, float col[4], ImGuiColorEditFlags flags = 0, const float* ref_col = NULL){}
		bool          ktkImguiWrapper::ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0)){} 
		void          ktkImguiWrapper::SetColorEditOptions(ImGuiColorEditFlags flags){}                     
		bool          ktkImguiWrapper::TreeNode(const char* label){}
		bool          ktkImguiWrapper::TreeNode(const char* str_id, const char* fmt, ...) IM_FMTARGS(2){}   
		bool          ktkImguiWrapper::TreeNode(const void* ptr_id, const char* fmt, ...) IM_FMTARGS(2){}   
		bool          ktkImguiWrapper::TreeNodeV(const char* str_id, const char* fmt, va_list args) IM_FMTLIST(2){}
		bool          ktkImguiWrapper::TreeNodeV(const void* ptr_id, const char* fmt, va_list args) IM_FMTLIST(2){}
		bool          ktkImguiWrapper::TreeNodeEx(const char* label, ImGuiTreeNodeFlags flags = 0){}
		bool          ktkImguiWrapper::TreeNodeEx(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3){}
		bool          ktkImguiWrapper::TreeNodeEx(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, ...) IM_FMTARGS(3){}
		bool          ktkImguiWrapper::TreeNodeExV(const char* str_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3){}
		bool          ktkImguiWrapper::TreeNodeExV(const void* ptr_id, ImGuiTreeNodeFlags flags, const char* fmt, va_list args) IM_FMTLIST(3){}
		void          ktkImguiWrapper::TreePush(const char* str_id){}                                       
		void          ktkImguiWrapper::TreePush(const void* ptr_id = NULL){}                                
		void          ktkImguiWrapper::TreePop(){}                                                          
		float         ktkImguiWrapper::GetTreeNodeToLabelSpacing(){}                                      
		bool          ktkImguiWrapper::CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0){}  
		bool          ktkImguiWrapper::CollapsingHeader(const char* label, bool* p_visible, ImGuiTreeNodeFlags flags = 0){} 
		void          ktkImguiWrapper::SetNextItemOpen(bool is_open, ImGuiCond cond = 0){}                  
		bool          ktkImguiWrapper::BeginListBox(const char* label, const ImVec2& size = ImVec2(0, 0)){} 
		void          ktkImguiWrapper::EndListBox(){}                                                       
		bool          ktkImguiWrapper::ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1){}
		bool          ktkImguiWrapper::ListBox(const char* label, int* current_item, bool (*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1){}
		void          ktkImguiWrapper::PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float)){}
		void          ktkImguiWrapper::PlotLines(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0)){}
		void          ktkImguiWrapper::PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0), int stride = sizeof(float)){}
		void          ktkImguiWrapper::PlotHistogram(const char* label, float(*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0, 0)){}                                                                                          
	} // namespace UI
} // namespace Kotek
