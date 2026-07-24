#pragma once

#include <kotek.core.defines.static.math/include/kotek_core_defines_static_math.h>
#include <kotek.core.defines_dependent.assert/include/kotek_core_defines_dependent_assert.h>

#include <cmath>
#include <limits>

/// \~english
/// @brief kotek's own dependency-free math backend (KOTEK_MATH_LIBRARY=KOTEK_OWN).
///
/// Small POD backing types with scalar implementations of every operation the
/// GLM/DXM backends provide. No third-party includes, no intrinsics (v1 —
/// correctness first; SIMD later where measurements justify). Layout matches
/// the library-wide column-major public contract: vectors store their
/// components contiguously (x, y, z, w), matrices are arrays of column
/// vectors so m_base.m[column][row] is a contiguous float blob identical to
/// glm::matNxN and to the DXM backend's storage.
///
/// Semantics intentionally mirror GLM (the reference backend): vector
/// arithmetic is component-wise, mat*mat / mat*vec / vec*mat are the
/// algebraic products, quaternion multiplication is the Hamilton product
/// (q1 * q2 applies q2's rotation first), slerp takes the short path.
KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

#pragma region vectors

struct vec2
{
	float x;
	float y;

	vec2(void) = default;
	constexpr vec2(float x_, float y_) noexcept : x(x_), y(y_) {}

	constexpr const float& operator[](int index) const noexcept
	{
		return (&x)[index];
	}

	constexpr float& operator[](int index) noexcept
	{
		return (&x)[index];
	}

	constexpr vec2& operator+=(const vec2& data) noexcept
	{
		this->x += data.x;
		this->y += data.y;
		return *this;
	}

	constexpr vec2& operator+=(float value) noexcept
	{
		this->x += value;
		this->y += value;
		return *this;
	}

	constexpr vec2& operator-=(const vec2& data) noexcept
	{
		this->x -= data.x;
		this->y -= data.y;
		return *this;
	}

	constexpr vec2& operator-=(float value) noexcept
	{
		this->x -= value;
		this->y -= value;
		return *this;
	}

	constexpr vec2& operator*=(const vec2& data) noexcept
	{
		this->x *= data.x;
		this->y *= data.y;
		return *this;
	}

	constexpr vec2& operator*=(float value) noexcept
	{
		this->x *= value;
		this->y *= value;
		return *this;
	}

	constexpr vec2& operator/=(const vec2& data) noexcept
	{
		this->x /= data.x;
		this->y /= data.y;
		return *this;
	}

	constexpr vec2& operator/=(float value) noexcept
	{
		float factor = 1.0f / value;
		this->x *= factor;
		this->y *= factor;
		return *this;
	}
};

static_assert(
	sizeof(vec2) == sizeof(float[2]),
	"vec2 must stay a tight (x, y) blob — data() exposes it as float[2]"
);

constexpr vec2 operator+(const vec2& left, const vec2& right) noexcept
{
	return vec2(left.x + right.x, left.y + right.y);
}

constexpr vec2 operator-(const vec2& left, const vec2& right) noexcept
{
	return vec2(left.x - right.x, left.y - right.y);
}

constexpr vec2 operator*(const vec2& left, const vec2& right) noexcept
{
	return vec2(left.x * right.x, left.y * right.y);
}

constexpr vec2 operator*(const vec2& left, float right) noexcept
{
	return vec2(left.x * right, left.y * right);
}

constexpr vec2 operator*(float left, const vec2& right) noexcept
{
	return (right * left);
}

constexpr vec2 operator/(const vec2& left, const vec2& right) noexcept
{
	return vec2(left.x / right.x, left.y / right.y);
}

constexpr vec2 operator/(const vec2& left, float right) noexcept
{
	float factor = 1.0f / right;
	return (left * factor);
}

constexpr vec2 operator-(const vec2& data) noexcept
{
	return vec2(-data.x, -data.y);
}

constexpr bool operator==(const vec2& left, const vec2& right) noexcept
{
	return (left.x == right.x) && (left.y == right.y);
}

constexpr bool operator!=(const vec2& left, const vec2& right) noexcept
{
	return !(left == right);
}

struct vec3
{
	float x;
	float y;
	float z;

	vec3(void) = default;
	constexpr vec3(float x_, float y_, float z_) noexcept :
		x(x_), y(y_), z(z_)
	{
	}

	constexpr const float& operator[](int index) const noexcept
	{
		return (&x)[index];
	}

	constexpr float& operator[](int index) noexcept
	{
		return (&x)[index];
	}

	constexpr vec3& operator+=(const vec3& data) noexcept
	{
		this->x += data.x;
		this->y += data.y;
		this->z += data.z;
		return *this;
	}

	constexpr vec3& operator+=(float value) noexcept
	{
		this->x += value;
		this->y += value;
		this->z += value;
		return *this;
	}

	constexpr vec3& operator-=(const vec3& data) noexcept
	{
		this->x -= data.x;
		this->y -= data.y;
		this->z -= data.z;
		return *this;
	}

	constexpr vec3& operator-=(float value) noexcept
	{
		this->x -= value;
		this->y -= value;
		this->z -= value;
		return *this;
	}

	constexpr vec3& operator*=(const vec3& data) noexcept
	{
		this->x *= data.x;
		this->y *= data.y;
		this->z *= data.z;
		return *this;
	}

	constexpr vec3& operator*=(float value) noexcept
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		return *this;
	}

	constexpr vec3& operator/=(const vec3& data) noexcept
	{
		this->x /= data.x;
		this->y /= data.y;
		this->z /= data.z;
		return *this;
	}

	constexpr vec3& operator/=(float value) noexcept
	{
		float factor = 1.0f / value;
		this->x *= factor;
		this->y *= factor;
		this->z *= factor;
		return *this;
	}
};

static_assert(
	sizeof(vec3) == sizeof(float[3]),
	"vec3 must stay a tight (x, y, z) blob — data() exposes it as float[3]"
);

constexpr vec3 operator+(const vec3& left, const vec3& right) noexcept
{
	return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
}

constexpr vec3 operator-(const vec3& left, const vec3& right) noexcept
{
	return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}

constexpr vec3 operator*(const vec3& left, const vec3& right) noexcept
{
	return vec3(left.x * right.x, left.y * right.y, left.z * right.z);
}

constexpr vec3 operator*(const vec3& left, float right) noexcept
{
	return vec3(left.x * right, left.y * right, left.z * right);
}

constexpr vec3 operator*(float left, const vec3& right) noexcept
{
	return (right * left);
}

constexpr vec3 operator/(const vec3& left, const vec3& right) noexcept
{
	return vec3(left.x / right.x, left.y / right.y, left.z / right.z);
}

constexpr vec3 operator/(const vec3& left, float right) noexcept
{
	float factor = 1.0f / right;
	return (left * factor);
}

constexpr vec3 operator-(const vec3& data) noexcept
{
	return vec3(-data.x, -data.y, -data.z);
}

constexpr bool operator==(const vec3& left, const vec3& right) noexcept
{
	return (left.x == right.x) && (left.y == right.y) &&
		(left.z == right.z);
}

constexpr bool operator!=(const vec3& left, const vec3& right) noexcept
{
	return !(left == right);
}

struct vec4
{
	float x;
	float y;
	float z;
	float w;

	vec4(void) = default;
	constexpr vec4(float x_, float y_, float z_, float w_) noexcept :
		x(x_), y(y_), z(z_), w(w_)
	{
	}

	constexpr const float& operator[](int index) const noexcept
	{
		return (&x)[index];
	}

	constexpr float& operator[](int index) noexcept
	{
		return (&x)[index];
	}

	constexpr vec4& operator+=(const vec4& data) noexcept
	{
		this->x += data.x;
		this->y += data.y;
		this->z += data.z;
		this->w += data.w;
		return *this;
	}

	constexpr vec4& operator+=(float value) noexcept
	{
		this->x += value;
		this->y += value;
		this->z += value;
		this->w += value;
		return *this;
	}

	constexpr vec4& operator-=(const vec4& data) noexcept
	{
		this->x -= data.x;
		this->y -= data.y;
		this->z -= data.z;
		this->w -= data.w;
		return *this;
	}

	constexpr vec4& operator-=(float value) noexcept
	{
		this->x -= value;
		this->y -= value;
		this->z -= value;
		this->w -= value;
		return *this;
	}

	constexpr vec4& operator*=(const vec4& data) noexcept
	{
		this->x *= data.x;
		this->y *= data.y;
		this->z *= data.z;
		this->w *= data.w;
		return *this;
	}

	constexpr vec4& operator*=(float value) noexcept
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		this->w *= value;
		return *this;
	}

	constexpr vec4& operator/=(const vec4& data) noexcept
	{
		this->x /= data.x;
		this->y /= data.y;
		this->z /= data.z;
		this->w /= data.w;
		return *this;
	}

	constexpr vec4& operator/=(float value) noexcept
	{
		float factor = 1.0f / value;
		this->x *= factor;
		this->y *= factor;
		this->z *= factor;
		this->w *= factor;
		return *this;
	}
};

static_assert(
	sizeof(vec4) == sizeof(float[4]),
	"vec4 must stay a tight (x, y, z, w) blob — data() exposes it as float[4]"
);

constexpr vec4 operator+(const vec4& left, const vec4& right) noexcept
{
	return vec4(
		left.x + right.x,
		left.y + right.y,
		left.z + right.z,
		left.w + right.w
	);
}

constexpr vec4 operator-(const vec4& left, const vec4& right) noexcept
{
	return vec4(
		left.x - right.x,
		left.y - right.y,
		left.z - right.z,
		left.w - right.w
	);
}

constexpr vec4 operator*(const vec4& left, const vec4& right) noexcept
{
	return vec4(
		left.x * right.x,
		left.y * right.y,
		left.z * right.z,
		left.w * right.w
	);
}

constexpr vec4 operator*(const vec4& left, float right) noexcept
{
	return vec4(left.x * right, left.y * right, left.z * right, left.w * right);
}

constexpr vec4 operator*(float left, const vec4& right) noexcept
{
	return (right * left);
}

constexpr vec4 operator/(const vec4& left, const vec4& right) noexcept
{
	return vec4(
		left.x / right.x,
		left.y / right.y,
		left.z / right.z,
		left.w / right.w
	);
}

constexpr vec4 operator/(const vec4& left, float right) noexcept
{
	float factor = 1.0f / right;
	return (left * factor);
}

constexpr vec4 operator-(const vec4& data) noexcept
{
	return vec4(-data.x, -data.y, -data.z, -data.w);
}

constexpr bool operator==(const vec4& left, const vec4& right) noexcept
{
	return (left.x == right.x) && (left.y == right.y) &&
		(left.z == right.z) && (left.w == right.w);
}

constexpr bool operator!=(const vec4& left, const vec4& right) noexcept
{
	return !(left == right);
}

#pragma endregion

#pragma region vector functions

constexpr float dot(const vec2& left, const vec2& right) noexcept
{
	return left.x * right.x + left.y * right.y;
}

constexpr float dot(const vec3& left, const vec3& right) noexcept
{
	return left.x * right.x + left.y * right.y + left.z * right.z;
}

constexpr float dot(const vec4& left, const vec4& right) noexcept
{
	return left.x * right.x + left.y * right.y + left.z * right.z +
		left.w * right.w;
}

constexpr vec3 cross(const vec3& left, const vec3& right) noexcept
{
	return vec3(
		left.y * right.z - left.z * right.y,
		left.z * right.x - left.x * right.z,
		left.x * right.y - left.y * right.x
	);
}

constexpr float length_squared(const vec2& data) noexcept
{
	return dot(data, data);
}

constexpr float length_squared(const vec3& data) noexcept
{
	return dot(data, data);
}

constexpr float length_squared(const vec4& data) noexcept
{
	return dot(data, data);
}

inline float length(const vec2& data) noexcept
{
	return std::sqrt(length_squared(data));
}

inline float length(const vec3& data) noexcept
{
	return std::sqrt(length_squared(data));
}

inline float length(const vec4& data) noexcept
{
	return std::sqrt(length_squared(data));
}

inline float distance(const vec2& left, const vec2& right) noexcept
{
	return length(left - right);
}

inline float distance(const vec3& left, const vec3& right) noexcept
{
	return length(left - right);
}

inline float distance(const vec4& left, const vec4& right) noexcept
{
	return length(left - right);
}

inline vec2 normalize(const vec2& data) noexcept
{
	return (data / length(data));
}

inline vec3 normalize(const vec3& data) noexcept
{
	return (data / length(data));
}

inline vec4 normalize(const vec4& data) noexcept
{
	return (data / length(data));
}

#pragma endregion

#pragma region matrices

/// \~english
/// @brief Column-major 2x2 matrix: m[column] is a vec2 column, so
/// m[column][row] addresses a single element and the whole object is a
/// contiguous float[2][2] blob (identical layout to glm::mat2x2).
struct mat2x2
{
	vec2 m[2];

	mat2x2(void) = default;
	constexpr mat2x2(const vec2& column_0, const vec2& column_1) noexcept :
		m{column_0, column_1}
	{
	}

	constexpr mat2x2(
		float c0r0, float c0r1, float c1r0, float c1r1
	) noexcept :
		m{vec2(c0r0, c0r1), vec2(c1r0, c1r1)}
	{
	}

	constexpr const vec2& operator[](int column) const noexcept
	{
		return this->m[column];
	}

	constexpr vec2& operator[](int column) noexcept
	{
		return this->m[column];
	}

	constexpr mat2x2& operator+=(const mat2x2& data) noexcept
	{
		this->m[0] += data.m[0];
		this->m[1] += data.m[1];
		return *this;
	}

	constexpr mat2x2& operator-=(const mat2x2& data) noexcept
	{
		this->m[0] -= data.m[0];
		this->m[1] -= data.m[1];
		return *this;
	}

	constexpr mat2x2& operator*=(const mat2x2& data) noexcept
	{
		// algebraic product: new column c is (*this) * (data column c)
		vec2 column_0 =
			this->m[0] * data.m[0][0] + this->m[1] * data.m[0][1];
		vec2 column_1 =
			this->m[0] * data.m[1][0] + this->m[1] * data.m[1][1];

		this->m[0] = column_0;
		this->m[1] = column_1;
		return *this;
	}

	constexpr mat2x2& operator*=(float value) noexcept
	{
		this->m[0] *= value;
		this->m[1] *= value;
		return *this;
	}

	constexpr mat2x2& operator/=(float value) noexcept
	{
		float factor = 1.0f / value;
		this->m[0] *= factor;
		this->m[1] *= factor;
		return *this;
	}
};

static_assert(
	sizeof(mat2x2) == sizeof(float[2][2]),
	"mat2x2 must stay a tight float[2][2] column-major blob"
);

constexpr mat2x2 operator+(const mat2x2& left, const mat2x2& right) noexcept
{
	return mat2x2(left.m[0] + right.m[0], left.m[1] + right.m[1]);
}

constexpr mat2x2 operator-(const mat2x2& left, const mat2x2& right) noexcept
{
	return mat2x2(left.m[0] - right.m[0], left.m[1] - right.m[1]);
}

/// \~english algebraic product: result column c is left * (right column c)
constexpr vec2 operator*(const mat2x2& left, const vec2& vec) noexcept
{
	return (left.m[0] * vec.x + left.m[1] * vec.y);
}

/// \~english algebraic product: result component c is dot(vec, column c)
constexpr vec2 operator*(const vec2& vec, const mat2x2& right) noexcept
{
	return vec2(dot(vec, right.m[0]), dot(vec, right.m[1]));
}

constexpr mat2x2 operator*(const mat2x2& left, const mat2x2& right) noexcept
{
	return mat2x2(left * right.m[0], left * right.m[1]);
}

constexpr mat2x2 operator*(const mat2x2& left, float right) noexcept
{
	return mat2x2(left.m[0] * right, left.m[1] * right);
}

constexpr mat2x2 operator*(float left, const mat2x2& right) noexcept
{
	return (right * left);
}

constexpr mat2x2 operator/(const mat2x2& left, float right) noexcept
{
	float factor = 1.0f / right;
	return (left * factor);
}

constexpr mat2x2 operator-(const mat2x2& data) noexcept
{
	return mat2x2(-data.m[0], -data.m[1]);
}

constexpr bool operator==(const mat2x2& left, const mat2x2& right) noexcept
{
	return (left.m[0] == right.m[0]) && (left.m[1] == right.m[1]);
}

constexpr bool operator!=(const mat2x2& left, const mat2x2& right) noexcept
{
	return !(left == right);
}

struct mat3x3
{
	vec3 m[3];

	mat3x3(void) = default;
	constexpr mat3x3(
		const vec3& column_0, const vec3& column_1, const vec3& column_2
	) noexcept :
		m{column_0, column_1, column_2}
	{
	}

	constexpr mat3x3(
		float c0r0,
		float c0r1,
		float c0r2,
		float c1r0,
		float c1r1,
		float c1r2,
		float c2r0,
		float c2r1,
		float c2r2
	) noexcept :
		m{vec3(c0r0, c0r1, c0r2), vec3(c1r0, c1r1, c1r2),
			vec3(c2r0, c2r1, c2r2)}
	{
	}

	constexpr const vec3& operator[](int column) const noexcept
	{
		return this->m[column];
	}

	constexpr vec3& operator[](int column) noexcept
	{
		return this->m[column];
	}

	constexpr mat3x3& operator+=(const mat3x3& data) noexcept
	{
		this->m[0] += data.m[0];
		this->m[1] += data.m[1];
		this->m[2] += data.m[2];
		return *this;
	}

	constexpr mat3x3& operator-=(const mat3x3& data) noexcept
	{
		this->m[0] -= data.m[0];
		this->m[1] -= data.m[1];
		this->m[2] -= data.m[2];
		return *this;
	}

	constexpr mat3x3& operator*=(const mat3x3& data) noexcept
	{
		// algebraic product: new column c is (*this) * (data column c)
		vec3 column_0 = this->m[0] * data.m[0][0] +
			this->m[1] * data.m[0][1] + this->m[2] * data.m[0][2];
		vec3 column_1 = this->m[0] * data.m[1][0] +
			this->m[1] * data.m[1][1] + this->m[2] * data.m[1][2];
		vec3 column_2 = this->m[0] * data.m[2][0] +
			this->m[1] * data.m[2][1] + this->m[2] * data.m[2][2];

		this->m[0] = column_0;
		this->m[1] = column_1;
		this->m[2] = column_2;
		return *this;
	}

	constexpr mat3x3& operator*=(float value) noexcept
	{
		this->m[0] *= value;
		this->m[1] *= value;
		this->m[2] *= value;
		return *this;
	}

	constexpr mat3x3& operator/=(float value) noexcept
	{
		float factor = 1.0f / value;
		this->m[0] *= factor;
		this->m[1] *= factor;
		this->m[2] *= factor;
		return *this;
	}
};

static_assert(
	sizeof(mat3x3) == sizeof(float[3][3]),
	"mat3x3 must stay a tight float[3][3] column-major blob"
);

constexpr mat3x3 operator+(const mat3x3& left, const mat3x3& right) noexcept
{
	return mat3x3(
		left.m[0] + right.m[0],
		left.m[1] + right.m[1],
		left.m[2] + right.m[2]
	);
}

constexpr mat3x3 operator-(const mat3x3& left, const mat3x3& right) noexcept
{
	return mat3x3(
		left.m[0] - right.m[0],
		left.m[1] - right.m[1],
		left.m[2] - right.m[2]
	);
}

constexpr vec3 operator*(const mat3x3& left, const vec3& vec) noexcept
{
	return (left.m[0] * vec.x + left.m[1] * vec.y + left.m[2] * vec.z);
}

constexpr vec3 operator*(const vec3& vec, const mat3x3& right) noexcept
{
	return vec3(
		dot(vec, right.m[0]), dot(vec, right.m[1]), dot(vec, right.m[2])
	);
}

constexpr mat3x3 operator*(const mat3x3& left, const mat3x3& right) noexcept
{
	return mat3x3(left * right.m[0], left * right.m[1], left * right.m[2]);
}

constexpr mat3x3 operator*(const mat3x3& left, float right) noexcept
{
	return mat3x3(left.m[0] * right, left.m[1] * right, left.m[2] * right);
}

constexpr mat3x3 operator*(float left, const mat3x3& right) noexcept
{
	return (right * left);
}

constexpr mat3x3 operator/(const mat3x3& left, float right) noexcept
{
	float factor = 1.0f / right;
	return (left * factor);
}

constexpr mat3x3 operator-(const mat3x3& data) noexcept
{
	return mat3x3(-data.m[0], -data.m[1], -data.m[2]);
}

constexpr bool operator==(const mat3x3& left, const mat3x3& right) noexcept
{
	return (left.m[0] == right.m[0]) && (left.m[1] == right.m[1]) &&
		(left.m[2] == right.m[2]);
}

constexpr bool operator!=(const mat3x3& left, const mat3x3& right) noexcept
{
	return !(left == right);
}

struct mat4x4
{
	vec4 m[4];

	mat4x4(void) = default;
	constexpr mat4x4(
		const vec4& column_0,
		const vec4& column_1,
		const vec4& column_2,
		const vec4& column_3
	) noexcept :
		m{column_0, column_1, column_2, column_3}
	{
	}

	constexpr mat4x4(
		float c0r0,
		float c0r1,
		float c0r2,
		float c0r3,
		float c1r0,
		float c1r1,
		float c1r2,
		float c1r3,
		float c2r0,
		float c2r1,
		float c2r2,
		float c2r3,
		float c3r0,
		float c3r1,
		float c3r2,
		float c3r3
	) noexcept :
		m{vec4(c0r0, c0r1, c0r2, c0r3), vec4(c1r0, c1r1, c1r2, c1r3),
			vec4(c2r0, c2r1, c2r2, c2r3), vec4(c3r0, c3r1, c3r2, c3r3)}
	{
	}

	constexpr const vec4& operator[](int column) const noexcept
	{
		return this->m[column];
	}

	constexpr vec4& operator[](int column) noexcept
	{
		return this->m[column];
	}

	constexpr mat4x4& operator+=(const mat4x4& data) noexcept
	{
		this->m[0] += data.m[0];
		this->m[1] += data.m[1];
		this->m[2] += data.m[2];
		this->m[3] += data.m[3];
		return *this;
	}

	constexpr mat4x4& operator-=(const mat4x4& data) noexcept
	{
		this->m[0] -= data.m[0];
		this->m[1] -= data.m[1];
		this->m[2] -= data.m[2];
		this->m[3] -= data.m[3];
		return *this;
	}

	constexpr mat4x4& operator*=(const mat4x4& data) noexcept
	{
		// algebraic product: new column c is (*this) * (data column c)
		vec4 column_0 = this->m[0] * data.m[0][0] +
			this->m[1] * data.m[0][1] + this->m[2] * data.m[0][2] +
			this->m[3] * data.m[0][3];
		vec4 column_1 = this->m[0] * data.m[1][0] +
			this->m[1] * data.m[1][1] + this->m[2] * data.m[1][2] +
			this->m[3] * data.m[1][3];
		vec4 column_2 = this->m[0] * data.m[2][0] +
			this->m[1] * data.m[2][1] + this->m[2] * data.m[2][2] +
			this->m[3] * data.m[2][3];
		vec4 column_3 = this->m[0] * data.m[3][0] +
			this->m[1] * data.m[3][1] + this->m[2] * data.m[3][2] +
			this->m[3] * data.m[3][3];

		this->m[0] = column_0;
		this->m[1] = column_1;
		this->m[2] = column_2;
		this->m[3] = column_3;
		return *this;
	}

	constexpr mat4x4& operator*=(float value) noexcept
	{
		this->m[0] *= value;
		this->m[1] *= value;
		this->m[2] *= value;
		this->m[3] *= value;
		return *this;
	}

	constexpr mat4x4& operator/=(float value) noexcept
	{
		float factor = 1.0f / value;
		this->m[0] *= factor;
		this->m[1] *= factor;
		this->m[2] *= factor;
		this->m[3] *= factor;
		return *this;
	}
};

static_assert(
	sizeof(mat4x4) == sizeof(float[4][4]),
	"mat4x4 must stay a tight float[4][4] column-major blob"
);

constexpr mat4x4 operator+(const mat4x4& left, const mat4x4& right) noexcept
{
	return mat4x4(
		left.m[0] + right.m[0],
		left.m[1] + right.m[1],
		left.m[2] + right.m[2],
		left.m[3] + right.m[3]
	);
}

constexpr mat4x4 operator-(const mat4x4& left, const mat4x4& right) noexcept
{
	return mat4x4(
		left.m[0] - right.m[0],
		left.m[1] - right.m[1],
		left.m[2] - right.m[2],
		left.m[3] - right.m[3]
	);
}

constexpr vec4 operator*(const mat4x4& left, const vec4& vec) noexcept
{
	return (left.m[0] * vec.x + left.m[1] * vec.y + left.m[2] * vec.z +
		left.m[3] * vec.w);
}

constexpr vec4 operator*(const vec4& vec, const mat4x4& right) noexcept
{
	return vec4(
		dot(vec, right.m[0]),
		dot(vec, right.m[1]),
		dot(vec, right.m[2]),
		dot(vec, right.m[3])
	);
}

constexpr mat4x4 operator*(const mat4x4& left, const mat4x4& right) noexcept
{
	return mat4x4(
		left * right.m[0],
		left * right.m[1],
		left * right.m[2],
		left * right.m[3]
	);
}

constexpr mat4x4 operator*(const mat4x4& left, float right) noexcept
{
	return mat4x4(
		left.m[0] * right,
		left.m[1] * right,
		left.m[2] * right,
		left.m[3] * right
	);
}

constexpr mat4x4 operator*(float left, const mat4x4& right) noexcept
{
	return (right * left);
}

constexpr mat4x4 operator/(const mat4x4& left, float right) noexcept
{
	float factor = 1.0f / right;
	return (left * factor);
}

constexpr mat4x4 operator-(const mat4x4& data) noexcept
{
	return mat4x4(-data.m[0], -data.m[1], -data.m[2], -data.m[3]);
}

constexpr bool operator==(const mat4x4& left, const mat4x4& right) noexcept
{
	return (left.m[0] == right.m[0]) && (left.m[1] == right.m[1]) &&
		(left.m[2] == right.m[2]) && (left.m[3] == right.m[3]);
}

constexpr bool operator!=(const mat4x4& left, const mat4x4& right) noexcept
{
	return !(left == right);
}

#pragma endregion

#pragma region matrix functions

constexpr mat2x2 transpose(const mat2x2& mat) noexcept
{
	return mat2x2(
		mat.m[0][0], mat.m[1][0], mat.m[0][1], mat.m[1][1]
	);
}

constexpr mat3x3 transpose(const mat3x3& mat) noexcept
{
	return mat3x3(
		mat.m[0][0],
		mat.m[1][0],
		mat.m[2][0],
		mat.m[0][1],
		mat.m[1][1],
		mat.m[2][1],
		mat.m[0][2],
		mat.m[1][2],
		mat.m[2][2]
	);
}

constexpr mat4x4 transpose(const mat4x4& mat) noexcept
{
	return mat4x4(
		mat.m[0][0],
		mat.m[1][0],
		mat.m[2][0],
		mat.m[3][0],
		mat.m[0][1],
		mat.m[1][1],
		mat.m[2][1],
		mat.m[3][1],
		mat.m[0][2],
		mat.m[1][2],
		mat.m[2][2],
		mat.m[3][2],
		mat.m[0][3],
		mat.m[1][3],
		mat.m[2][3],
		mat.m[3][3]
	);
}

constexpr float determinant(const mat2x2& mat) noexcept
{
	return mat.m[0][0] * mat.m[1][1] - mat.m[1][0] * mat.m[0][1];
}

constexpr float determinant(const mat3x3& mat) noexcept
{
	// expansion along row 0; element (row r, column c) is m[c][r]
	return mat.m[0][0] *
			(mat.m[1][1] * mat.m[2][2] - mat.m[2][1] * mat.m[1][2]) -
		mat.m[1][0] * (mat.m[0][1] * mat.m[2][2] - mat.m[2][1] * mat.m[0][2]) +
		mat.m[2][0] * (mat.m[0][1] * mat.m[1][2] - mat.m[1][1] * mat.m[0][2]);
}

inline float determinant(const mat4x4& mat) noexcept
{
	// expansion along row 0: det = sum_c (-1)^c * m[c][0] * minor(0, c),
	// where minor(0, c) removes row 0 and column c
	float det = 0.0f;

	for (int column = 0; column < 4; ++column)
	{
		// gather the 3x3 minor (columns != c, rows 1..3)
		float minor[3][3]; // [column'][row']

		int minor_column = 0;
		for (int c = 0; c < 4; ++c)
		{
			if (c == column)
				continue;

			for (int r = 0; r < 3; ++r)
			{
				minor[minor_column][r] = mat.m[c][r + 1];
			}

			++minor_column;
		}

		float det_minor = minor[0][0] *
				(minor[1][1] * minor[2][2] - minor[2][1] * minor[1][2]) -
			minor[1][0] *
				(minor[0][1] * minor[2][2] - minor[2][1] * minor[0][2]) +
			minor[2][0] *
				(minor[0][1] * minor[1][2] - minor[1][1] * minor[0][2]);

		float term = mat.m[column][0] * det_minor;
		det = (column & 1) ? (det - term) : (det + term);
	}

	return det;
}

inline mat2x2 inverse(const mat2x2& mat) noexcept
{
	float det = determinant(mat);

	KOTEK_ASSERT(
		det != 0.0f, "matrix is singular, inverse is undefined"
	);

	float factor = 1.0f / det;

	// the 2x2 adjugate is transpose-symmetric: it reads identically in
	// column-major [column][row] storage
	return mat2x2(
		mat.m[1][1] * factor,
		-mat.m[0][1] * factor,
		-mat.m[1][0] * factor,
		mat.m[0][0] * factor
	);
}

inline mat3x3 inverse(const mat3x3& mat) noexcept
{
	float det = determinant(mat);

	KOTEK_ASSERT(
		det != 0.0f, "matrix is singular, inverse is undefined"
	);

	float factor = 1.0f / det;

	// adjugate: inverse(r, c) = cofactor(c, r) / det, where cofactor(i, j)
	// removes row i and column j from the source matrix
	mat3x3 result;

	for (int column = 0; column < 3; ++column)
	{
		for (int row = 0; row < 3; ++row)
		{
			// 2x2 minor removing row == column, column == row
			float minor[2][2]; // [column'][row']

			int minor_column = 0;
			for (int c = 0; c < 3; ++c)
			{
				if (c == row)
					continue;

				int minor_row = 0;
				for (int r = 0; r < 3; ++r)
				{
					if (r == column)
						continue;

					minor[minor_column][minor_row] = mat.m[c][r];
					++minor_row;
				}

				++minor_column;
			}

			float det_minor =
				minor[0][0] * minor[1][1] - minor[1][0] * minor[0][1];

			float cofactor = ((row + column) & 1) ? -det_minor : det_minor;

			result.m[column][row] = cofactor * factor;
		}
	}

	return result;
}

inline mat4x4 inverse(const mat4x4& mat) noexcept
{
	float det = determinant(mat);

	KOTEK_ASSERT(
		det != 0.0f, "matrix is singular, inverse is undefined"
	);

	float factor = 1.0f / det;

	// adjugate: inverse(r, c) = cofactor(c, r) / det
	mat4x4 result;

	for (int column = 0; column < 4; ++column)
	{
		for (int row = 0; row < 4; ++row)
		{
			// 3x3 minor removing row == column, column == row
			float minor[3][3]; // [column'][row']

			int minor_column = 0;
			for (int c = 0; c < 4; ++c)
			{
				if (c == row)
					continue;

				int minor_row = 0;
				for (int r = 0; r < 4; ++r)
				{
					if (r == column)
						continue;

					minor[minor_column][minor_row] = mat.m[c][r];
					++minor_row;
				}

				++minor_column;
			}

			float det_minor = minor[0][0] *
					(minor[1][1] * minor[2][2] - minor[2][1] * minor[1][2]) -
				minor[1][0] *
					(minor[0][1] * minor[2][2] - minor[2][1] * minor[0][2]) +
				minor[2][0] *
					(minor[0][1] * minor[1][2] - minor[1][1] * minor[0][2]);

			float cofactor = ((row + column) & 1) ? -det_minor : det_minor;

			result.m[column][row] = cofactor * factor;
		}
	}

	return result;
}

/// \~english
/// @brief Right-handed look-at matrix, same convention as glm::lookAt
/// (which defaults to lookAtRH).
inline mat4x4 look_at_rh(
	const vec3& eye, const vec3& center, const vec3& up
) noexcept
{
	vec3 forward = normalize(center - eye);
	vec3 side = normalize(cross(forward, up));
	vec3 up_ortho = cross(side, forward);

	mat4x4 result(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	result.m[0][0] = side.x;
	result.m[1][0] = side.y;
	result.m[2][0] = side.z;
	result.m[0][1] = up_ortho.x;
	result.m[1][1] = up_ortho.y;
	result.m[2][1] = up_ortho.z;
	result.m[0][2] = -forward.x;
	result.m[1][2] = -forward.y;
	result.m[2][2] = -forward.z;
	result.m[3][0] = -dot(side, eye);
	result.m[3][1] = -dot(up_ortho, eye);
	result.m[3][2] = dot(forward, eye);

	return result;
}

/// \~english
/// @brief Right-handed perspective projection with the GLM default depth
/// range of [-1, 1] (OpenGL convention, glm::perspective without
/// GLM_FORCE_DEPTH_ZERO_TO_ONE).
inline mat4x4 perspective_rh_no(
	float field_of_view_angle_in_radians,
	float aspect_ratio,
	float plane_near_z,
	float plane_far_z
) noexcept
{
	float tan_half_fov_y =
		std::tan(field_of_view_angle_in_radians * 0.5f);
	float range = plane_far_z - plane_near_z;

	mat4x4 result(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);

	result.m[0][0] = 1.0f / (aspect_ratio * tan_half_fov_y);
	result.m[1][1] = 1.0f / tan_half_fov_y;
	result.m[2][2] = -(plane_far_z + plane_near_z) / range;
	result.m[2][3] = -1.0f;
	result.m[3][2] =
		-(2.0f * plane_far_z * plane_near_z) / range;

	return result;
}

#pragma endregion

#pragma region quaternion

/// \~english
/// @brief Quaternion stored as (x, y, z, w) — the same component order the
/// kotek public contract (quaternionf ctor/accessors) and the DXM backend
/// use. Multiplication is the Hamilton product with GLM semantics:
/// q1 * q2 applies q2's rotation first.
struct quat
{
	float x;
	float y;
	float z;
	float w;

	quat(void) = default;
	constexpr quat(float x_, float y_, float z_, float w_) noexcept :
		x(x_), y(y_), z(z_), w(w_)
	{
	}

	constexpr quat& operator+=(const quat& data) noexcept
	{
		this->x += data.x;
		this->y += data.y;
		this->z += data.z;
		this->w += data.w;
		return *this;
	}

	constexpr quat& operator-=(const quat& data) noexcept
	{
		this->x -= data.x;
		this->y -= data.y;
		this->z -= data.z;
		this->w -= data.w;
		return *this;
	}

	/// \~english Hamilton product (glm::quat::operator*=)
	constexpr quat& operator*=(const quat& data) noexcept
	{
		float new_x = this->w * data.x + this->x * data.w +
			this->y * data.z - this->z * data.y;
		float new_y = this->w * data.y - this->x * data.z +
			this->y * data.w + this->z * data.x;
		float new_z = this->w * data.z + this->x * data.y -
			this->y * data.x + this->z * data.w;
		float new_w = this->w * data.w - this->x * data.x -
			this->y * data.y - this->z * data.z;

		this->x = new_x;
		this->y = new_y;
		this->z = new_z;
		this->w = new_w;
		return *this;
	}

	constexpr quat& operator*=(float value) noexcept
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		this->w *= value;
		return *this;
	}

	constexpr quat& operator/=(float value) noexcept
	{
		float factor = 1.0f / value;
		this->x *= factor;
		this->y *= factor;
		this->z *= factor;
		this->w *= factor;
		return *this;
	}
};

static_assert(
	sizeof(quat) == sizeof(float[4]),
	"quat must stay a tight (x, y, z, w) blob"
);

constexpr quat operator+(const quat& left, const quat& right) noexcept
{
	return quat(
		left.x + right.x,
		left.y + right.y,
		left.z + right.z,
		left.w + right.w
	);
}

constexpr quat operator-(const quat& left, const quat& right) noexcept
{
	return quat(
		left.x - right.x,
		left.y - right.y,
		left.z - right.z,
		left.w - right.w
	);
}

/// \~english Hamilton product with GLM semantics (left * right applies
/// right's rotation first)
constexpr quat operator*(const quat& left, const quat& right) noexcept
{
	return quat(
		left.w * right.x + left.x * right.w + left.y * right.z -
			left.z * right.y,
		left.w * right.y - left.x * right.z + left.y * right.w +
			left.z * right.x,
		left.w * right.z + left.x * right.y - left.y * right.x +
			left.z * right.w,
		left.w * right.w - left.x * right.x - left.y * right.y -
			left.z * right.z
	);
}

constexpr quat operator*(const quat& left, float right) noexcept
{
	return quat(left.x * right, left.y * right, left.z * right, left.w * right);
}

constexpr quat operator*(float left, const quat& right) noexcept
{
	return (right * left);
}

constexpr quat operator/(const quat& left, float right) noexcept
{
	float factor = 1.0f / right;
	return (left * factor);
}

constexpr quat operator-(const quat& data) noexcept
{
	return quat(-data.x, -data.y, -data.z, -data.w);
}

constexpr bool operator==(const quat& left, const quat& right) noexcept
{
	return (left.x == right.x) && (left.y == right.y) &&
		(left.z == right.z) && (left.w == right.w);
}

constexpr bool operator!=(const quat& left, const quat& right) noexcept
{
	return !(left == right);
}

constexpr float dot(const quat& left, const quat& right) noexcept
{
	return left.x * right.x + left.y * right.y + left.z * right.z +
		left.w * right.w;
}

/// \~english conjugate divided by the squared norm (glm::inverse)
constexpr quat inverse(const quat& data) noexcept
{
	float norm_squared = dot(data, data);
	float factor = 1.0f / norm_squared;

	return quat(
		-data.x * factor, -data.y * factor, -data.z * factor, data.w * factor
	);
}

constexpr quat operator/(const quat& left, const quat& right) noexcept
{
	return (left * inverse(right));
}

inline quat normalize(const quat& data) noexcept
{
	float factor = 1.0f / std::sqrt(dot(data, data));
	return (data * factor);
}

/// \~english
/// @brief Spherical linear interpolation, same algorithm as glm::slerp:
/// short path (flip the second quaternion on negative dot), linear mix when
/// the quaternions are nearly aligned.
inline quat slerp(const quat& left, const quat& right, float factor) noexcept
{
	quat z = right;
	float cos_theta = dot(left, right);

	if (cos_theta < 0.0f)
	{
		z = -right;
		cos_theta = -cos_theta;
	}

	if (cos_theta > 1.0f - std::numeric_limits<float>::epsilon())
	{
		// linear interpolation for nearly-aligned quaternions (glm does
		// not renormalize here either)
		return quat(
			left.x + factor * (z.x - left.x),
			left.y + factor * (z.y - left.y),
			left.z + factor * (z.z - left.z),
			left.w + factor * (z.w - left.w)
		);
	}
	else
	{
		float angle = std::acos(cos_theta);
		float sin_angle = std::sin(angle);

		return ((left * std::sin((1.0f - factor) * angle)) +
				   (z * std::sin(factor * angle))) /
			sin_angle;
	}
}

#pragma endregion

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
