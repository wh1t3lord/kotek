#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

/// \~english @brief universal representation of matrix's column or row. Sadly
/// but some math libraries doesn't have matrix representation as set of
/// vectors. This class is a representation of row or column for matrix which
/// dimension size is 3 for a row or a column respectively. In order to bind
/// data you just can call method data(void) and call static class method
/// size_of(void). If you just apply sizeof for this class as regulary sizeof
/// works you won't get the real size of expected vector's dimension size so you
/// can't map data with method data and compiler's sizeof operator keep this in
/// mind.
struct matrix3f_view_t
{
	matrix3f_view_t(float* p_values);

	float x(void) const noexcept;
	float& x(void) noexcept;

	float y(void) const noexcept;
	float& y(void) noexcept;

	float z(void) const noexcept;
	float& z(void) noexcept;

	void set(float x, float y, float z) noexcept;

	float operator[](unsigned char index) const;
	float& operator[](unsigned char index);

	// PLUS

	matrix3f_view_t& operator+=(const vector1f& vec) noexcept;
	matrix3f_view_t& operator+=(const vector2f& vec) noexcept;
	matrix3f_view_t& operator+=(const vector3f& vec) noexcept;
	matrix3f_view_t& operator+=(const vector4f& vec) noexcept;
	matrix3f_view_t& operator+=(const matrix1f_view_t& vec) noexcept;
	matrix3f_view_t& operator+=(const matrix1f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator+=(const matrix2f_view_t& vec) noexcept;
	matrix3f_view_t& operator+=(const matrix2f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator+=(const matrix3f_view_t& vec) noexcept;
	matrix3f_view_t& operator+=(const matrix3f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator+=(const matrix4f_view_t& vec) noexcept;
	matrix3f_view_t& operator+=(const matrix4f_const_view_t& vec) noexcept;

	// MINUS

	matrix3f_view_t& operator-=(const vector1f& vec) noexcept;
	matrix3f_view_t& operator-=(const vector2f& vec) noexcept;
	matrix3f_view_t& operator-=(const vector3f& vec) noexcept;
	matrix3f_view_t& operator-=(const vector4f& vec) noexcept;
	matrix3f_view_t& operator-=(const matrix1f_view_t& vec) noexcept;
	matrix3f_view_t& operator-=(const matrix1f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator-=(const matrix2f_view_t& vec) noexcept;
	matrix3f_view_t& operator-=(const matrix2f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator-=(const matrix3f_view_t& vec) noexcept;
	matrix3f_view_t& operator-=(const matrix3f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator-=(const matrix4f_view_t& vec) noexcept;
	matrix3f_view_t& operator-=(const matrix4f_const_view_t& vec) noexcept;

	// MULTIPLY

	matrix3f_view_t& operator*=(const vector1f& vec) noexcept;
	matrix3f_view_t& operator*=(const vector2f& vec) noexcept;
	matrix3f_view_t& operator*=(const vector3f& vec) noexcept;
	matrix3f_view_t& operator*=(const vector4f& vec) noexcept;
	matrix3f_view_t& operator*=(const matrix1f_view_t& vec) noexcept;
	matrix3f_view_t& operator*=(const matrix1f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator*=(const matrix2f_view_t& vec) noexcept;
	matrix3f_view_t& operator*=(const matrix2f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator*=(const matrix3f_view_t& vec) noexcept;
	matrix3f_view_t& operator*=(const matrix3f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator*=(const matrix4f_view_t& vec) noexcept;
	matrix3f_view_t& operator*=(const matrix4f_const_view_t& vec) noexcept;

	// DIVISION

	matrix3f_view_t& operator/=(const vector1f& vec) noexcept;
	matrix3f_view_t& operator/=(const vector2f& vec) noexcept;
	matrix3f_view_t& operator/=(const vector3f& vec) noexcept;
	matrix3f_view_t& operator/=(const vector4f& vec) noexcept;
	matrix3f_view_t& operator/=(const matrix1f_view_t& vec) noexcept;
	matrix3f_view_t& operator/=(const matrix1f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator/=(const matrix2f_view_t& vec) noexcept;
	matrix3f_view_t& operator/=(const matrix2f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator/=(const matrix3f_view_t& vec) noexcept;
	matrix3f_view_t& operator/=(const matrix3f_const_view_t& vec) noexcept;
	matrix3f_view_t& operator/=(const matrix4f_view_t& vec) noexcept;
	matrix3f_view_t& operator/=(const matrix4f_const_view_t& vec) noexcept;

	float* data(void) const noexcept;

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return static_cast<unsigned char>(sizeof(float[3]));
	}

private:
	float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK