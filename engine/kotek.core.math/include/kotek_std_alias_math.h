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

struct matrix1_const_view_t
{
	matrix1_const_view_t(const float* p_values) : m_p_values(p_values) {}
	matrix1_const_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline const float& x(void) noexcept { return this->m_p_values[0]; }

	inline float operator[](unsigned char index) const noexcept
	{
		KOTEK_ASSERT(index == 0, "out of range");
		return this->m_p_values[0];
	}

	inline const float& operator[](unsigned char index) noexcept
	{
		KOTEK_ASSERT(index == 0, "out of range");
		return this->m_p_values[0];
	}

	inline const float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[1]);
	}

private:
	const float* m_p_values;
};

struct matrix1_view_t
{
	matrix1_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline float& x(void) noexcept { return this->m_p_values[0]; }

	inline float operator[](unsigned char index) const noexcept
	{
		KOTEK_ASSERT(index == 0, "out of range");
		return this->m_p_values[0];
	}

	inline float& operator[](unsigned char index) noexcept
	{
		KOTEK_ASSERT(index == 0, "out of range");
		return this->m_p_values[0];
	}

	inline float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[1]);
	}

private:
	float* m_p_values;
};

struct matrix2_const_view_t
{
	matrix2_const_view_t(float* p_values) : m_p_values(p_values) {}
	matrix2_const_view_t(const float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline const float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline const float& y(void) noexcept { return this->m_p_values[1]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 1, "out of range");
		return this->m_p_values[index];
	}

	inline const float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 1, "out of range");
		return this->m_p_values[index];
	}

	inline const float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return static_cast<unsigned char>(sizeof(const float[2]));
	}

private:
	const float* m_p_values;
};

struct matrix2_view_t
{
	matrix2_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline float& y(void) noexcept { return this->m_p_values[1]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 1, "out of range");
		return this->m_p_values[index];
	}

	inline float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 1, "out of range");
		return this->m_p_values[index];
	}

	inline float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return static_cast<unsigned char>(sizeof(float[2]));
	}

private:
	float* m_p_values;
};

struct matrix3_const_view_t
{
	matrix3_const_view_t(const float* p_values) : m_p_values(p_values) {}

	matrix3_const_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline const float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline const float& y(void) noexcept { return this->m_p_values[1]; }

	inline float z(void) const noexcept { return this->m_p_values[2]; }
	inline const float& z(void) noexcept { return this->m_p_values[2]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		return this->m_p_values[index];
	}

	inline const float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		return this->m_p_values[index];
	}

	inline const float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[3]);
	}

private:
	const float* m_p_values;
};

/// \~english @brief universal representation of matrix's column or row. Sadly
/// but some math libraries doesn't have matrix representation as set of
/// vectors. This class is a representation of row or column for matrix which
/// dimension size is 3 for a row or a column respectively. In order to bind
/// data you just can call method data(void) and call static class method
/// size_of(void). If you just apply sizeof for this class as regulary sizeof
/// works you won't get the real size of expected vector's dimension size so you
/// can't map data with method data and compiler's sizeof operator keep this in
/// mind.
struct matrix3_view_t
{
	matrix3_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline float& y(void) noexcept { return this->m_p_values[1]; }

	inline float z(void) const noexcept { return this->m_p_values[2]; }
	inline float& z(void) noexcept { return this->m_p_values[2]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		return this->m_p_values[index];
	}

	inline float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 2, "out of range");
		return this->m_p_values[index];
	}

	inline float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[3]);
	}

private:
	float* m_p_values;
};

struct matrix4_const_view_t
{
	matrix4_const_view_t(float* p_values) : m_p_values(p_values) {}

	matrix4_const_view_t(const float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline const float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline const float& y(void) noexcept { return this->m_p_values[1]; }

	inline float z(void) const noexcept { return this->m_p_values[2]; }
	inline const float& z(void) noexcept { return this->m_p_values[2]; }

	inline float w(void) const noexcept { return this->m_p_values[3]; }
	inline const float& w(void) noexcept { return this->m_p_values[3]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 3, "out of range");
		return this->m_p_values[index];
	}

	inline const float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 3, "out of range");
		return this->m_p_values[index];
	}

	inline const float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[4]);
	}

private:
	const float* m_p_values;
};

struct matrix4_view_t
{
	matrix4_view_t(float* p_values) : m_p_values(p_values) {}

	inline float x(void) const noexcept { return this->m_p_values[0]; }
	inline float& x(void) noexcept { return this->m_p_values[0]; }

	inline float y(void) const noexcept { return this->m_p_values[1]; }
	inline float& y(void) noexcept { return this->m_p_values[1]; }

	inline float z(void) const noexcept { return this->m_p_values[2]; }
	inline float& z(void) noexcept { return this->m_p_values[2]; }

	inline float w(void) const noexcept { return this->m_p_values[3]; }
	inline float& w(void) noexcept { return this->m_p_values[3]; }

	inline float operator[](unsigned char index) const
	{
		KOTEK_ASSERT(index <= 3, "out of range");
		return this->m_p_values[index];
	}

	inline float& operator[](unsigned char index)
	{
		KOTEK_ASSERT(index <= 3, "out of range");
		return this->m_p_values[index];
	}

	inline float* data(void) const noexcept { return this->m_p_values; }

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[4]);
	}

private:
	float* m_p_values;
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