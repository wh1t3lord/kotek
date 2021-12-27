#pragma once

#ifdef KOTEK_USE_MATH_LIBRARY_GLM
	#include <glm/glm.hpp>
	#include <glm/gtx/quaternion.hpp>
#elif defined(KOTEK_USE_MATH_LIBRARY_DXM)
	#include <DirectXMath.h>
#endif

#include <limits>

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
#pragma region Constants
			constexpr float kEpsilon_Float =
				std::numeric_limits<float>::epsilon();
			constexpr double kEpsilon_Double =
				std::numeric_limits<double>::epsilon();
			constexpr long double kEpsilon_LongDouble =
				std::numeric_limits<long double>::epsilon();

			constexpr float kMin_Float = std::numeric_limits<float>::min();
			constexpr double kMin_Double = std::numeric_limits<double>::min();
			constexpr long double kMin_LongDouble =
				std::numeric_limits<long double>::min();

			constexpr float kMax_Float = std::numeric_limits<float>::max();
			constexpr double kMax_Double = std::numeric_limits<double>::max();
			constexpr long double kMax_LongDouble =
				std::numeric_limits<long double>::max();
#pragma endregion

#pragma region Aliases
			using base_decimal_t = float;
#pragma endregion

#pragma region Math aliases
#ifdef KOTEK_USE_MATH_LIBRARY_GLM
			using base_vec1_t = glm::vec1;
			using base_vec2_t = glm::vec2;
			using base_vec3_t = glm::vec3;
			using base_vec4_t = glm::vec4;

			using base_mat2x2_t = glm::mat2x2;
			using base_mat3x3_t = glm::mat3x3;
			using base_mat4x4_t = glm::mat4x4;

			using base_quat_t = glm::quat;
#elif defined(KOTEK_USE_MATH_LIBRARY_DXM)
			using base_vec1_t = base_decimal_t;
			using base_vec2_t = DirectX::XMFLOAT2;
			using base_vec3_t = DirectX::XMFLOAT3;
			using base_vec4_t = DirectX::XMFLOAT4;

			using base_mat2x2_t = DirectX::XMFLOAT3X3;
			using base_mat3x3_t = DirectX::XMFLOAT3X3;
			using base_mat4x4_t = DirectX::XMFLOAT4X4;

			using base_quat_t = base_vec4_t;
#endif
#pragma endregion
		} // namespace math
	}     // namespace ktk
} // namespace Kotek
