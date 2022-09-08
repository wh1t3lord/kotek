#pragma once

#include "kotek_std_math_matrix_2x2_f.h"
#include "kotek_std_math_matrix_3x3_f.h"
#include "kotek_std_math_matrix_4x4_f.h"
#include "kotek_std_math_quaternionf.h"
#include "kotek_std_math_vector1f.h"
#include "kotek_std_math_vector2f.h"
#include "kotek_std_math_vector3f.h"
#include "kotek_std_math_vector4f.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			using vec1f_t = vector1f;
			using vec2f_t = vector2f;
			using vec3f_t = vector3f;
			using vec4f_t = vector4f;
			using mat2x2f_t = matrix2x2f;
			using mat3x3f_t = matrix3x3f;
			using mat4x4f_t = matrix4x4f;
			using quatf_t = quaternionf;

			// TODO: add double implementation
		} // namespace math
	}     // namespace ktk
} // namespace Kotek