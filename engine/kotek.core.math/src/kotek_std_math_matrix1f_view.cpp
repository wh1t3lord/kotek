#include "../include/kotek_std_math_matrix1f_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_matrix1f_const_view.h"
#include "../include/kotek_std_math_matrix2f_const_view.h"
#include "../include/kotek_std_math_matrix3f_const_view.h"
#include "../include/kotek_std_math_matrix4f_const_view.h"

#include "../include/kotek_std_math_matrix2f_view.h"
#include "../include/kotek_std_math_matrix3f_view.h"
#include "../include/kotek_std_math_matrix4f_view.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

matrix1f_view_t::matrix1f_view_t(float* p_values) : m_p_values(p_values) {}

float matrix1f_view_t::x(void) const noexcept
{
	return this->m_p_values[0];
}
float& matrix1f_view_t::x(void) noexcept
{
	return this->m_p_values[0];
}

float matrix1f_view_t::operator[](unsigned char index) const noexcept
{
	KOTEK_ASSERT(index == 0, "out of range");
	return this->m_p_values[0];
}

float& matrix1f_view_t::operator[](unsigned char index) noexcept
{
	KOTEK_ASSERT(index == 0, "out of range");
	return this->m_p_values[0];
}

// PLUS

matrix1f_view_t& matrix1f_view_t::operator+=(const vector1f& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(const vector2f& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(const vector3f& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(const vector4f& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(
	const matrix1f_view_t& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(
	const matrix1f_const_view_t& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(
	const matrix2f_view_t& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(
	const matrix2f_const_view_t& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(
	const matrix3f_view_t& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(
	const matrix3f_const_view_t& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(
	const matrix4f_view_t& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator+=(
	const matrix4f_const_view_t& vec) noexcept
{
	this->m_p_values[0] += vec.x();
	return *this;
}

// MINUS

matrix1f_view_t& matrix1f_view_t::operator-=(const vector1f& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(const vector2f& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(const vector3f& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(const vector4f& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(
	const matrix1f_view_t& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(
	const matrix1f_const_view_t& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(
	const matrix2f_view_t& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(
	const matrix2f_const_view_t& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(
	const matrix3f_view_t& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(
	const matrix3f_const_view_t& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(
	const matrix4f_view_t& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator-=(
	const matrix4f_const_view_t& vec) noexcept
{
	this->m_p_values[0] -= vec.x();
	return *this;
}

// MULTIPLY

matrix1f_view_t& matrix1f_view_t::operator*=(const vector1f& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(const vector2f& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(const vector3f& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(const vector4f& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(
	const matrix1f_view_t& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(
	const matrix1f_const_view_t& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(
	const matrix2f_view_t& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(
	const matrix2f_const_view_t& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(
	const matrix3f_view_t& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(
	const matrix3f_const_view_t& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(
	const matrix4f_view_t& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator*=(
	const matrix4f_const_view_t& vec) noexcept
{
	this->m_p_values[0] *= vec.x();
	return *this;
}

// DIVISION

matrix1f_view_t& matrix1f_view_t::operator/=(const vector1f& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(const vector2f& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(const vector3f& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(const vector4f& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(
	const matrix1f_view_t& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(
	const matrix1f_const_view_t& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(
	const matrix2f_view_t& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(
	const matrix2f_const_view_t& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(
	const matrix3f_view_t& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(
	const matrix3f_const_view_t& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(
	const matrix4f_view_t& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

matrix1f_view_t& matrix1f_view_t::operator/=(
	const matrix4f_const_view_t& vec) noexcept
{
	this->m_p_values[0] /= vec.x();
	return *this;
}

float* matrix1f_view_t::data(void) const noexcept
{
	return this->m_p_values;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK