#pragma once

#include <kotek.core.defines.static.math/include/kotek_core_defines_static_math.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

#include <cmath>

#ifdef KOTEK_USE_MATH_LIBRARY_GLM
	#include <glm/glm.hpp>
	#include <glm/gtx/quaternion.hpp>
#elif defined(KOTEK_USE_MATH_LIBRARY_DXM)
	#include <DirectXMath.h>
#endif

#include <limits>

#undef min
#undef max

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

	constexpr float kEpsilon_Float = std::numeric_limits<float>::epsilon();
	constexpr double kEpsilon_Double = std::numeric_limits<double>::epsilon();
	constexpr long double kEpsilon_LongDouble =
		std::numeric_limits<long double>::epsilon();

	// @ minimal positive
	constexpr float kMin_Float = std::numeric_limits<float>::min();
	constexpr double kMin_Double = std::numeric_limits<double>::min();
	constexpr long double kMin_LongDouble =
		std::numeric_limits<long double>::min();

	constexpr float kMax_Float = std::numeric_limits<float>::max();
	constexpr double kMax_Double = std::numeric_limits<double>::max();
	constexpr long double kMax_LongDouble =
		std::numeric_limits<long double>::max();

	using base_decimal_t = float;

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

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK