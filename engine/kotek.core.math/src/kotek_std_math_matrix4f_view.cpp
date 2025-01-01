#pragma once

#include "../include/kotek_std_math_matrix4f_view.h"

#include "../include/kotek_std_math_vector1f.h"
#include "../include/kotek_std_math_vector2f.h"
#include "../include/kotek_std_math_vector3f.h"
#include "../include/kotek_std_math_vector4f.h"

#include "../include/kotek_std_math_matrix1f_const_view.h"
#include "../include/kotek_std_math_matrix2f_const_view.h"
#include "../include/kotek_std_math_matrix3f_const_view.h"
#include "../include/kotek_std_math_matrix4f_const_view.h"

#include "../include/kotek_std_math_matrix1f_view.h"
#include "../include/kotek_std_math_matrix2f_view.h"
#include "../include/kotek_std_math_matrix3f_view.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

matrix4f_view_t::matrix4f_view_t(float* p_values) : m_p_values(p_values) {}

float matrix4f_view_t::x(void) const noexcept
{
	return this->m_p_values[0];
}
float& matrix4f_view_t::x(void) noexcept
{
	return this->m_p_values[0];
}

float matrix4f_view_t::y(void) const noexcept
{
	return this->m_p_values[1];
}
float& matrix4f_view_t::y(void) noexcept
{
	return this->m_p_values[1];
}

float matrix4f_view_t::z(void) const noexcept
{
	return this->m_p_values[2];
}
float& matrix4f_view_t::z(void) noexcept
{
	return this->m_p_values[2];
}

float matrix4f_view_t::w(void) const noexcept
{
	return this->m_p_values[3];
}
float& matrix4f_view_t::w(void) noexcept
{
	return this->m_p_values[3];
}

float matrix4f_view_t::operator[](unsigned char index) const
{
	KOTEK_ASSERT(index <= 3, "out of range");
	return this->m_p_values[index];
}

float& matrix4f_view_t::operator[](unsigned char index)
{
	KOTEK_ASSERT(index <= 3, "out of range");
	return this->m_p_values[index];
}

// PLUS

matrix4f_view_t& matrix4f_view_t::operator+=(const vector1f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vector4f(vec.x(), 0.0f, 0.0f, 0.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(const vector2f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vector4f(vec.x(), vec.y(), 0.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(const vector3f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vector4f(vec.x(), 0.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(const vector4f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vector4f(vec.x(), vec.y(), vec.z());

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(
	const matrix1f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(
	const matrix1f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(
	const matrix2f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(
	const matrix2f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(
	const matrix3f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(
	const matrix3f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(
	const matrix4f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator+=(
	const matrix4f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left += vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

// MINUS

matrix4f_view_t& matrix4f_view_t::operator-=(const vector1f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vector4f(vec.x(), 0.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(const vector2f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vector4f(vec.x(), vec.y(), 0.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(const vector3f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vector4f(vec.x(), vec.y(), vec.z()); // w=0.0f because of ctor

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(const vector4f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vector4f(vec.x(), vec.y(), vec.z());

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(
	const matrix1f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(
	const matrix1f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(
	const matrix2f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(
	const matrix2f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(
	const matrix3f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(
	const matrix3f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(
	const matrix4f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator-=(
	const matrix4f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left -= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

// MULTIPLY

matrix4f_view_t& matrix4f_view_t::operator*=(const vector1f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vector4f(vec.x(), 1.0f, 1.0f, 1.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(const vector2f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vector4f(vec.x(), vec.y(), 1.0f, 1.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(const vector3f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vector4f(vec.x(), vec.y(), vec.z(), 1.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(const vector4f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vector4f(vec.x(), vec.y(), vec.z());

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(
	const matrix1f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(
	const matrix1f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(
	const matrix2f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(
	const matrix2f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(
	const matrix3f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(
	const matrix3f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(
	const matrix4f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator*=(
	const matrix4f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left *= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

// DIVISION

matrix4f_view_t& matrix4f_view_t::operator/=(const vector1f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vector4f(vec.x(), 1.0f, 1.0f, 1.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(const vector2f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vector4f(vec.x(), vec.y(), 1.0f, 1.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(const vector3f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vector4f(vec.x(), vec.y(), vec.z(), 1.0f);

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(const vector4f& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vector4f(vec.x(), vec.y(), vec.z());

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(
	const matrix1f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(
	const matrix1f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(
	const matrix2f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(
	const matrix2f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(
	const matrix3f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(
	const matrix3f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(
	const matrix4f_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

matrix4f_view_t& matrix4f_view_t::operator/=(
	const matrix4f_const_view_t& vec) noexcept
{
	vector4f left(this->m_p_values);
	left /= vec;

	this->m_p_values[0] = left.x();
	this->m_p_values[1] = left.y();
	this->m_p_values[2] = left.z();
	this->m_p_values[3] = left.w();

	return *this;
}

float* matrix4f_view_t::data(void) const noexcept
{
	return this->m_p_values;
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK