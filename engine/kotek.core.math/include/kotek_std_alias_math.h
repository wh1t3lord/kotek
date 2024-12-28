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
constexpr long double kMin_LongDouble = std::numeric_limits<long double>::min();

constexpr float kMax_Float = std::numeric_limits<float>::max();
constexpr double kMax_Double = std::numeric_limits<double>::max();
constexpr long double kMax_LongDouble = std::numeric_limits<long double>::max();

using base_decimal_t = float;

struct matrix4_view_t;
struct matrix3_view_t;
struct matrix2_view_t;
struct matrix1_view_t;

struct matrix1_view_t
{
	matrix1_view_t(float* p_values) : m_x(p_values[0]) {}

	inline float x(void) const noexcept { return this->m_x; }
	inline float& x(void) noexcept { return this->m_x; }

	inline float operator[](unsigned int index) const noexcept
	{
		KOTEK_ASSERT(index == 0, "out of range");
		return m_x;
	}

	inline float& operator[](unsigned int index) noexcept
	{
		KOTEK_ASSERT(index == 0, "out of range");
		return m_x;
	}

private:
	float& m_x;
};

struct matrix2_view_t
{
	matrix2_view_t(float* p_values) : m_x(p_values[0]), m_y(p_values[1]) {}

	inline float x(void) const noexcept { return this->m_x; }
	inline float& x(void) noexcept { return this->m_x; }

	inline float y(void) const noexcept { return this->m_y; }
	inline float& y(void) noexcept { return this->m_y; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 1, "out of range");
		float* p_arr = static_cast<float*>(&this->m_x);
		return p_arr[index];
	}

	inline float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 1, "out of range");
		float* p_arr = static_cast<float*>(&this->m_x);
		return p_arr[index];
	}

private:
	float& m_x;
	float& m_y;
};

struct matrix3_view_t
{
	matrix3_view_t(float* p_values) :
		m_x(p_values[0]), m_y(p_values[1]), m_z(p_values[2])
	{
	}

	inline float x(void) const noexcept { return this->m_x; }
	inline float& x(void) noexcept { return this->m_x; }

	inline float y(void) const noexcept { return this->m_y; }
	inline float& y(void) noexcept { return this->m_y; }

	inline float z(void) const noexcept { return this->m_z; }
	inline float& z(void) noexcept { return this->m_z; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		float* p_arr = static_cast<float*>(&this->m_x);
		return p_arr[index];
	}

	inline float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		float* p_arr = static_cast<float*>(&this->m_x);
		return p_arr[index];
	}

private:
	float& m_x;
	float& m_y;
	float& m_z;
};

struct matrix4_view_t
{
	matrix4_view_t(float* p_values) :
		m_x(p_values[0]), m_y(p_values[1]), m_z(p_values[2]), m_w(p_values[3])
	{
	}

	inline float x(void) const noexcept { return this->m_x; }
	inline float& x(void) noexcept { return this->m_x; }

	inline float y(void) const noexcept { return this->m_y; }
	inline float& y(void) noexcept { return this->m_y; }

	inline float z(void) const noexcept { return this->m_z; }
	inline float& z(void) noexcept { return this->m_z; }

	inline float w(void) const noexcept { return this->m_w; }
	inline float& w(void) noexcept { return this->m_w; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 3, "out of range");
		float* p_arr = static_cast<float*>(&this->m_x);
		return p_arr[index];
	}

	inline float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 3, "out of range");
		float* p_arr = static_cast<float*>(&this->m_x);
		return p_arr[index];
	}

private:
	float& m_x;
	float& m_y;
	float& m_z;
	float& m_w;
};

// TODO: provide separation for float and double base types
// without switching user defines what he needs and he can choose what part to
// disable like disable double or float implementation
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