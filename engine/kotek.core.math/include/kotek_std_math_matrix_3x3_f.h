#pragma once

#include "kotek_std_alias_math.h"

#include "kotek_std_math_matrix1f_view.h"
#include "kotek_std_math_matrix2f_view.h"
#include "kotek_std_math_matrix3f_view.h"
#include "kotek_std_math_matrix4f_view.h"
#include "kotek_std_math_matrix1f_const_view.h"
#include "kotek_std_math_matrix2f_const_view.h"
#include "kotek_std_math_matrix3f_const_view.h"
#include "kotek_std_math_matrix4f_const_view.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class matrix3x3f
{
public:
	matrix3x3f(float m00, float m01, float m02, float m10, float m11, float m12,
		float m20, float m21, float m22) :
		m_base(m00, m01, m02, m10, m11, m12, m20, m21, m22)
	{
	}
	matrix3x3f(const base_mat3x3_t& data) : m_base(data) {}
	matrix3x3f(const matrix3x3f& data) : m_base(data.m_base) {}
	matrix3x3f(void) : m_base{} {}

	~matrix3x3f(void) = default;

	matrix3x3f& operator=(const matrix3x3f& data)
	{
		this->m_base = data.m_base;
		return *this;
	}

	matrix3x3f& operator=(const base_mat3x3_t& data)
	{
		this->m_base = data;
		return *this;
	}

	matrix3x3f& operator+=(const matrix3x3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._11));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._21));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._31));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._11));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._21));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._31));

		row_original_0 = DirectX::XMVectorAdd(row_original_0, row_argument_0);
		row_original_1 = DirectX::XMVectorAdd(row_original_1, row_argument_1);
		row_original_2 = DirectX::XMVectorAdd(row_original_2, row_argument_2);

		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
			row_original_0);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
			row_original_1);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
			row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base += data.m_base;
#endif
		return *this;
	}

	matrix3x3f& operator+=(const base_mat3x3_t& data) noexcept
	{
		return this->operator+=(data);
	}

	matrix3x3f& operator-=(const matrix3x3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._11));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._21));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._31));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._11));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._21));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._31));

		row_original_0 =
			DirectX::XMVectorSubtract(row_original_0, row_argument_0);
		row_original_1 =
			DirectX::XMVectorSubtract(row_original_1, row_argument_1);
		row_original_2 =
			DirectX::XMVectorSubtract(row_original_2, row_argument_2);

		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
			row_original_0);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
			row_original_1);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
			row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base -= data.m_base;
#endif
		return *this;
	}

	matrix3x3f& operator-=(const base_mat3x3_t& data) noexcept
	{
		return this->operator-=(data);
	}

	matrix3x3f& operator*=(const matrix3x3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMMATRIX m1 = *this;
		DirectX::XMMATRIX m2 = data;

		auto result = DirectX::XMMatrixMultiply(m1, m2);

		DirectX::XMStoreFloat3x3(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= data.m_base;
#endif

		return *this;
	}

	matrix3x3f& operator*=(const base_mat3x3_t& data) noexcept
	{
		return this->operator*=(data);
	}

	matrix3x3f& operator*=(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._11));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._21));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._31));

		row_original_0 = DirectX::XMVectorScale(row_original_0, value);
		row_original_1 = DirectX::XMVectorScale(row_original_1, value);
		row_original_2 = DirectX::XMVectorScale(row_original_2, value);

		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
			row_original_0);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
			row_original_1);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
			row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= value;
#endif

		return *this;
	}

	matrix3x3f& operator/=(const matrix3x3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._11));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._21));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._31));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._11));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._21));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._31));

		row_original_0 =
			DirectX::XMVectorDivide(row_original_0, row_argument_0);
		row_original_1 =
			DirectX::XMVectorDivide(row_original_1, row_argument_1);
		row_original_2 =
			DirectX::XMVectorDivide(row_original_2, row_argument_2);

		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
			row_original_0);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
			row_original_1);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
			row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base /= data.m_base;
#endif
		return *this;
	}

	matrix3x3f& operator/=(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._11));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._21));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._31));

		float factor = 1.f / value;

		row_original_0 = DirectX::XMVectorScale(row_original_0, factor);
		row_original_1 = DirectX::XMVectorScale(row_original_1, factor);
		row_original_2 = DirectX::XMVectorScale(row_original_2, factor);

		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._11),
			row_original_0);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._21),
			row_original_1);
		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&this->m_base._31),
			row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base /= value;
#endif

		return *this;
	}

	matrix3x3f operator+() const noexcept { return *this; }

	matrix3x3f operator-() const noexcept
	{
		matrix3x3f result;
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._11));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._21));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._31));

		row_original_0 = DirectX::XMVectorNegate(row_original_0);
		row_original_1 = DirectX::XMVectorNegate(row_original_1);
		row_original_2 = DirectX::XMVectorNegate(row_original_2);

		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&result.m_base._11),
			row_original_0);

		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&result.m_base._21),
			row_original_1);

		DirectX::XMStoreFloat3(
			reinterpret_cast<DirectX::XMFLOAT3*>(&result.m_base._31),
			row_original_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		result = -this->m_base;
#endif
		return result;
	}

	bool operator==(const matrix3x3f& data) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._11));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._21));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._31));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._11));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._21));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._31));

		bool is_equal_0 =
			DirectX::XMVector3Equal(row_original_0, row_argument_0);
		bool is_equal_1 =
			DirectX::XMVector3Equal(row_original_1, row_argument_1);
		bool is_equal_2 =
			DirectX::XMVector3Equal(row_original_2, row_argument_2);

		return (is_equal_0 && is_equal_1 && is_equal_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base == data.m_base;
#endif
	}

	bool operator!=(const matrix3x3f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._11));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._21));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&this->m_base._31));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._11));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._21));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
			reinterpret_cast<const DirectX::XMFLOAT3*>(&data.m_base._31));

		bool is_equal_0 =
			DirectX::XMVector3NotEqual(row_original_0, row_argument_0);
		bool is_equal_1 =
			DirectX::XMVector3NotEqual(row_original_1, row_argument_1);
		bool is_equal_2 =
			DirectX::XMVector3NotEqual(row_original_2, row_argument_2);

		return (is_equal_0 || is_equal_1 || is_equal_2);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base != data.m_base;
#endif
	}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	operator DirectX::XMMATRIX(void) const noexcept
	{
		return DirectX::XMLoadFloat3x3(&this->m_base);
	}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

	matrix3f_view_t operator[](unsigned char row)
	{
		KOTEK_ASSERT(row != unsigned char(-1),
			"out of range (probably you passed a negative number)");
		KOTEK_ASSERT(row <= 2, "out of range");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return matrix3f_view_t(&this->m_base.m[row][0]);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return &this->m_base[row][0];
#else
		return nullptr;
#endif
	}

	matrix3f_const_view_t operator[](unsigned char row) const
	{
		KOTEK_ASSERT(row != unsigned char(-1),
			"out of range (probably you passed a negative number)");
		KOTEK_ASSERT(row <= 2, "out of range!");

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return matrix3f_const_view_t(&this->m_base.m[row][0]);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return &this->m_base[row][0];
#else
		return nullptr;
#endif
	}

	matrix3x3f& Set_Base(const base_mat3x3_t& data) noexcept
	{
		this->m_base = data;
		return *this;
	}

	base_mat3x3_t& Get_Base(void) noexcept { return this->m_base; }
	const base_mat3x3_t& Get_Base(void) const noexcept { return this->m_base; }

private:
	base_mat3x3_t m_base;
};

inline matrix3x3f operator+(
	const matrix3x3f& left, const matrix3x3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMFLOAT3 right_row_0(right[0].data());
	DirectX::XMFLOAT3 right_row_1(right[1].data());
	DirectX::XMFLOAT3 right_row_2(right[2].data());

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(&left_row_2);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(&right_row_0);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(&right_row_1);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(&right_row_2);

	row_original_0 = DirectX::XMVectorAdd(row_original_0, row_argument_0);
	row_original_1 = DirectX::XMVectorAdd(row_original_1, row_argument_1);
	row_original_2 = DirectX::XMVectorAdd(row_original_2, row_argument_2);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
		row_original_0);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
		row_original_1);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
		row_original_2);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() + right.Get_Base());
#endif
}

inline matrix3x3f operator-(
	const matrix3x3f& left, const matrix3x3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMFLOAT3 right_row_0(right[0].data());
	DirectX::XMFLOAT3 right_row_1(right[1].data());
	DirectX::XMFLOAT3 right_row_2(right[2].data());

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(&left_row_2);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(&right_row_0);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(&right_row_1);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(&right_row_2);

	row_original_0 = DirectX::XMVectorSubtract(row_original_0, row_argument_0);
	row_original_1 = DirectX::XMVectorSubtract(row_original_1, row_argument_1);
	row_original_2 = DirectX::XMVectorSubtract(row_original_2, row_argument_2);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
		row_original_0);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
		row_original_1);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
		row_original_2);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() - right.Get_Base());
#endif
}

inline matrix3x3f operator*(
	const matrix3x3f& left, const matrix3x3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX m1 = left;
	DirectX::XMMATRIX m2 = right;
	auto temp = DirectX::XMMatrixMultiply(m1, m2);

	matrix3x3f result;
	base_mat3x3_t data;
	DirectX::XMStoreFloat3x3(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right.Get_Base());
#endif
}

inline matrix3x3f operator*(const matrix3x3f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(&left_row_2);

	row_original_0 = DirectX::XMVectorScale(row_original_0, value);
	row_original_1 = DirectX::XMVectorScale(row_original_1, value);
	row_original_2 = DirectX::XMVectorScale(row_original_2, value);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
		row_original_0);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
		row_original_1);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
		row_original_2);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * value);
#endif
}

inline matrix3x3f operator*(float value, const matrix3x3f& right) noexcept
{
	return operator*(right, value);
}

inline matrix3x3f operator/(const matrix3x3f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(&left_row_2);

	float factor = 1.f / value;

	row_original_0 = DirectX::XMVectorScale(row_original_0, factor);
	row_original_1 = DirectX::XMVectorScale(row_original_1, factor);
	row_original_2 = DirectX::XMVectorScale(row_original_2, factor);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
		row_original_0);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
		row_original_1);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
		row_original_2);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / value);
#endif
}

inline matrix3x3f operator/(
	const matrix3x3f& left, const matrix3x3f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT3 left_row_0(left[0].data());
	DirectX::XMFLOAT3 left_row_1(left[1].data());
	DirectX::XMFLOAT3 left_row_2(left[2].data());

	DirectX::XMFLOAT3 right_row_0(right[0].data());
	DirectX::XMFLOAT3 right_row_1(right[1].data());
	DirectX::XMFLOAT3 right_row_2(right[2].data());

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(&left_row_2);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(&right_row_0);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(&right_row_1);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(&right_row_2);

	row_original_0 = DirectX::XMVectorDivide(row_original_0, row_argument_0);
	row_original_1 = DirectX::XMVectorDivide(row_original_1, row_argument_1);
	row_original_2 = DirectX::XMVectorDivide(row_original_2, row_argument_2);

	matrix3x3f result;

	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._11),
		row_original_0);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._21),
		row_original_1);
	DirectX::XMStoreFloat3(
		reinterpret_cast<DirectX::XMFLOAT3*>(&result.Get_Base()._31),
		row_original_2);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / right.Get_Base());
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
