#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

struct matrix1f_view_t
{
	matrix1f_view_t(float* p_values);

	float x(void) const noexcept;
	float& x(void) noexcept;

	float operator[](unsigned char index) const noexcept;
	float& operator[](unsigned char index) noexcept;

	// PLUS

	matrix1f_view_t& operator+=(const vector1f& vec) noexcept;
	matrix1f_view_t& operator+=(const vector2f& vec) noexcept;
	matrix1f_view_t& operator+=(const vector3f& vec) noexcept;
	matrix1f_view_t& operator+=(const vector4f& vec) noexcept;
	matrix1f_view_t& operator+=(const matrix1f_view_t& vec) noexcept;
	matrix1f_view_t& operator+=(const matrix1f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator+=(const matrix2f_view_t& vec) noexcept;
	matrix1f_view_t& operator+=(const matrix2f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator+=(const matrix3f_view_t& vec) noexcept;
	matrix1f_view_t& operator+=(const matrix3f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator+=(const matrix4f_view_t& vec) noexcept;
	matrix1f_view_t& operator+=(const matrix4f_const_view_t& vec) noexcept;

	// MINUS

	matrix1f_view_t& operator-=(const vector1f& vec) noexcept;
	matrix1f_view_t& operator-=(const vector2f& vec) noexcept;
	matrix1f_view_t& operator-=(const vector3f& vec) noexcept;
	matrix1f_view_t& operator-=(const vector4f& vec) noexcept;
	matrix1f_view_t& operator-=(const matrix1f_view_t& vec) noexcept;
	matrix1f_view_t& operator-=(const matrix1f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator-=(const matrix2f_view_t& vec) noexcept;
	matrix1f_view_t& operator-=(const matrix2f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator-=(const matrix3f_view_t& vec) noexcept;
	matrix1f_view_t& operator-=(const matrix3f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator-=(const matrix4f_view_t& vec) noexcept;
	matrix1f_view_t& operator-=(const matrix4f_const_view_t& vec) noexcept;

	// MULTIPLY

	matrix1f_view_t& operator*=(const vector1f& vec) noexcept;
	matrix1f_view_t& operator*=(const vector2f& vec) noexcept;
	matrix1f_view_t& operator*=(const vector3f& vec) noexcept;
	matrix1f_view_t& operator*=(const vector4f& vec) noexcept;
	matrix1f_view_t& operator*=(const matrix1f_view_t& vec) noexcept;
	matrix1f_view_t& operator*=(const matrix1f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator*=(const matrix2f_view_t& vec) noexcept;
	matrix1f_view_t& operator*=(const matrix2f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator*=(const matrix3f_view_t& vec) noexcept;
	matrix1f_view_t& operator*=(const matrix3f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator*=(const matrix4f_view_t& vec) noexcept;
	matrix1f_view_t& operator*=(const matrix4f_const_view_t& vec) noexcept;

	// DIVISION

	matrix1f_view_t& operator/=(const vector1f& vec) noexcept;
	matrix1f_view_t& operator/=(const vector2f& vec) noexcept;
	matrix1f_view_t& operator/=(const vector3f& vec) noexcept;
	matrix1f_view_t& operator/=(const vector4f& vec) noexcept;
	matrix1f_view_t& operator/=(const matrix1f_view_t& vec) noexcept;
	matrix1f_view_t& operator/=(const matrix1f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator/=(const matrix2f_view_t& vec) noexcept;
	matrix1f_view_t& operator/=(const matrix2f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator/=(const matrix3f_view_t& vec) noexcept;
	matrix1f_view_t& operator/=(const matrix3f_const_view_t& vec) noexcept;
	matrix1f_view_t& operator/=(const matrix4f_view_t& vec) noexcept;
	matrix1f_view_t& operator/=(const matrix4f_const_view_t& vec) noexcept;

	float* data(void) const noexcept;

	inline static constexpr unsigned char size_of(void) noexcept
	{
		return sizeof(float[1]);
	}

private:
	float* m_p_values;
};

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK