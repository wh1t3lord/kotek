#pragma once

#include <kotek.core.defines.static.math/include/kotek_core_defines_static_math.h>
#include <kotek.core.types.numerics/include/kotek_core_types_numerics.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

#include <cmath>

#ifdef KOTEK_USE_MATH_LIBRARY_GLM
	#define GLM_ENABLE_EXPERIMENTAL
	#include <glm/glm.hpp>
	#include <glm/gtx/quaternion.hpp>
	#include <glm/gtc/type_ptr.hpp>
#elif defined(KOTEK_USE_MATH_LIBRARY_DXM)
	#include <DirectXMath.h>
#endif

#include <limits>

#undef min
#undef max

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

constexpr float kEpsilon_Float =
	std::numeric_limits<float>::epsilon();
constexpr double kEpsilon_Double =
	std::numeric_limits<double>::epsilon();
constexpr long double kEpsilon_LongDouble =
	std::numeric_limits<long double>::epsilon();

// @ minimal positive
constexpr float kMin_Float = std::numeric_limits<float>::min();
constexpr double kMin_Double =
	std::numeric_limits<double>::min();
constexpr long double kMin_LongDouble =
	std::numeric_limits<long double>::min();

constexpr float kMax_Float = std::numeric_limits<float>::max();
constexpr double kMax_Double =
	std::numeric_limits<double>::max();
constexpr long double kMax_LongDouble =
	std::numeric_limits<long double>::max();

/// <summary>
/// when you initialized matrixxf_const_view_t or
/// matrixxf_view_t but you try to access field that doesn't
/// exist due to limit of row count like you passed 4x2 matrix
/// (4 columns and 2 rows) but you try to access element by
/// [3][2] like on third row but there's no third row and since
/// we need to return some invalid value...
/// </summary>
constexpr float kInvalidRowAccessOutOfRange = 0.0f;

using math_id_t = unsigned int;

using base_decimal_t = float;

struct matrixnf_view_t;
struct matrixnf_const_view_t;

struct vectornf_view_t;
struct vectornf_const_view_t;


class vector4f;
class vector3f;
class vector2f;
class vector1f;

class matrix2x2f;
class matrix3x3f;
class matrix4x4f;

// TODO: provide separation for float and double base types
// without switching user defines what he needs and he can
// choose what part to disable like disable double or float
// implementation
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

namespace math = KUN_KOTEK KUN_KTK KN_MATH;

KOTEK_END_NAMESPACE_KOTEK