#include "kotek_render_imgui.h"

namespace Kotek
{
	namespace imgui
	{
		void EditDragVec2(const char* p_header_name, ktk::math::vec2_t* p_vec,
			ktk::math::base_decimal_t speed, ktk::math::base_decimal_t v_min,
			ktk::math::base_decimal_t v_max) noexcept
		{
			if (p_vec == nullptr)
				return;

			if (p_header_name == nullptr)
				return;

			float data[2] = {p_vec->Get_X(), p_vec->Get_Y()};

			if (ImGui::DragFloat2(p_header_name, data, speed, v_min, v_max))
			{
				p_vec->Set_X(data[0]);
				p_vec->Set_Y(data[1]);
			}
		}

		void EditDragVec3(const char* p_header_name, ktk::math::vec3_t* p_vec,
			ktk::math::base_decimal_t speed, ktk::math::base_decimal_t v_min,
			ktk::math::base_decimal_t v_max) noexcept
		{
			if (p_vec == nullptr)
				return;

			if (p_header_name == nullptr)
				return;

			float data[3] = {p_vec->Get_X(), p_vec->Get_Y(), p_vec->Get_Z()};

			if (ImGui::DragFloat3(p_header_name, data, speed, v_min, v_max))
			{
				p_vec->Set_X(data[0]);
				p_vec->Set_Y(data[1]);
				p_vec->Set_Z(data[2]);
			}
		}

		void EditDragVec4(const char* p_header_name, ktk::math::vec4_t* p_vec,
			ktk::math::base_decimal_t speed, ktk::math::base_decimal_t v_min,
			ktk::math::base_decimal_t v_max) noexcept
		{
			if (p_vec == nullptr)
				return;

			if (p_header_name == nullptr)
				return;

			float data[4] = {
				p_vec->Get_X(), p_vec->Get_Y(), p_vec->Get_Z(), p_vec->Get_W()};

			if (ImGui::DragFloat4(p_header_name, data, speed, v_min, v_max))
			{
				p_vec->Set_X(data[0]);
				p_vec->Set_Y(data[1]);
				p_vec->Set_Z(data[2]);
				p_vec->Set_W(data[3]);
			}
		}

		void EditDragVec4(const char* p_header_name, ktk::math::quat_t* p_vec,
			ktk::math::base_decimal_t speed, ktk::math::base_decimal_t v_min,
			ktk::math::base_decimal_t v_max) noexcept
		{
			if (p_vec == nullptr)
				return;

			if (p_header_name == nullptr)
				return;

			float data[4] = {
				p_vec->Get_X(), p_vec->Get_Y(), p_vec->Get_Z(), p_vec->Get_W()};

			if (ImGui::DragFloat4(p_header_name, data, speed, v_min, v_max))
			{
				p_vec->Set_X(data[0]);
				p_vec->Set_Y(data[1]);
				p_vec->Set_Z(data[2]);
				p_vec->Set_W(data[3]);
			}
		}
	} // namespace imgui
} // namespace Kotek
