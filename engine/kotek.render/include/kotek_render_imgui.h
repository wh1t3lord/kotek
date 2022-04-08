#pragma once

#include <kotek.core/include/kotek_std.h>

namespace Kotek
{
	namespace imgui
	{
		void EditDragVec2(const char* p_header_name, ktk::math::vec2_t* p_vec,
			ktk::math::base_decimal_t speed = 0.01f,
			ktk::math::base_decimal_t v_min = -ktk::math::kMax_Float,
			ktk::math::base_decimal_t v_max = ktk::math::kMax_Float) noexcept;

		void EditDragVec3(const char* p_header_name, ktk::math::vec3_t* p_vec,
			ktk::math::base_decimal_t speed = 0.01f,
			ktk::math::base_decimal_t v_min = -ktk::math::kMax_Float,
			ktk::math::base_decimal_t v_max = ktk::math::kMax_Float) noexcept;

		void EditDragVec4(const char* p_header_name, ktk::math::vec4_t* p_vec,
			ktk::math::base_decimal_t speed = 0.01f,
			ktk::math::base_decimal_t v_min = -ktk::math::kMax_Float,
			ktk::math::base_decimal_t v_max = ktk::math::kMax_Float) noexcept;

		void EditDragVec4(const char* p_header_name, ktk::math::quat_t* p_vec,
			ktk::math::base_decimal_t speed = 0.01f,
			ktk::math::base_decimal_t v_min = -ktk::math::kMax_Float,
			ktk::math::base_decimal_t v_max = ktk::math::kMax_Float) noexcept;
	} // namespace imgui
} // namespace Kotek