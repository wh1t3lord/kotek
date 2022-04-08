#pragma once

#include "kotek_std_math_matrix_2x2_f.h"
#include "kotek_std_math_matrix_3x3_f.h"
#include "kotek_std_math_matrix_4x4_f.h"
#include "kotek_std_math_quaternionf.h"
#include "kotek_std_math_vector1f.h"
#include "kotek_std_math_vector2f.h"
#include "kotek_std_math_vector3f.h"
#include "kotek_std_math_vector4f.h"

// We don't know when math libraries will be possible to support changing
// precisions and in that case we can't provide to user the changing types like
// from vector1f -> vector1d and vice versa
// So the engine uses float type only by default

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			using vec1_t = vector1f;
			using vec2_t = vector2f;
			using vec3_t = vector3f;
			using vec4_t = vector4f;
			using mat2x2_t = matrix2x2f;
			using mat3x3_t = matrix3x3f;
			using mat4x4_t = matrix4x4f;
			using quat_t = quaternionf;
		} // namespace math
	}     // namespace ktk
} // namespace Kotek