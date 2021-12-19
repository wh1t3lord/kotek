#pragma once

#ifdef KOTEK_USE_MATH_LIBRARY_GLM
	#include <glm/glm.hpp>
	#include <glm/gtx/quaternion.hpp>
#endif

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
#ifdef KOTEK_USE_MATH_LIBRARY_GLM
			using base_vec1_t = glm::vec1;
			using base_vec2_t = glm::vec2;
			using base_vec3_t = glm::vec3;
			using base_vec4_t = glm::vec4;
			using base_mat2x2_t = glm::mat2x2;
			using base_mat3x3_t = glm::mat3x3;
			using base_mat4x4_t = glm::mat4x4;
			using base_quat_t = glm::quat;
#endif
		} // namespace math
	} // namespace ktk
} // namespace Kotek
