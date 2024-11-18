#pragma once

#include "kotek_std_alias_math.h"

KOTEK_BEGIN_NAMESPACE_KOTEK
KOTEK_BEGIN_NAMESPACE_KTK
KOTEK_BEGIN_NAMESPACE_MATH

class matrix4x4f
{
public:
	matrix4x4f(float m00, float m01, float m02, float m03, float m10, float m11,
		float m12, float m13, float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33) :
		m_base(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30,
			m31, m32, m33)
	{
	}
	matrix4x4f(const base_mat4x4_t& data) : m_base(data) {}
	matrix4x4f(const matrix4x4f& data) : m_base(data.m_base) {}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	matrix4x4f(const DirectX::XMMATRIX& data)
	{
		DirectX::XMStoreFloat4x4(&this->m_base, data);
	}
#endif

	matrix4x4f(void) : m_base{} {}

	~matrix4x4f(void) = default;

	matrix4x4f& operator=(const matrix4x4f& data)
	{
		this->m_base = data.m_base;
		return *this;
	}

	matrix4x4f& operator+=(const matrix4x4f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[0][0]));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[1][0]));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[2][0]));
		DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[3][0]));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[0][0]));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[1][0]));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[2][0]));
		DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[3][0]));

		row_original_0 = DirectX::XMVectorAdd(row_original_0, row_argument_0);
		row_original_1 = DirectX::XMVectorAdd(row_original_1, row_argument_1);
		row_original_2 = DirectX::XMVectorAdd(row_original_2, row_argument_2);
		row_original_3 = DirectX::XMVectorAdd(row_original_3, row_argument_3);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[0][0]),
			row_original_0);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[1][0]),
			row_original_1);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[2][0]),
			row_original_2);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[3][0]),
			row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base += data.m_base;
#endif
		return *this;
	}

	matrix4x4f& operator-=(const matrix4x4f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[0][0]));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[1][0]));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[2][0]));
		DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[3][0]));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[0][0]));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[1][0]));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[2][0]));
		DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[3][0]));

		row_original_0 =
			DirectX::XMVectorSubtract(row_original_0, row_argument_0);
		row_original_1 =
			DirectX::XMVectorSubtract(row_original_1, row_argument_1);
		row_original_2 =
			DirectX::XMVectorSubtract(row_original_2, row_argument_2);
		row_original_3 =
			DirectX::XMVectorSubtract(row_original_3, row_argument_3);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[0][0]),
			row_original_0);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[1][0]),
			row_original_1);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[2][0]),
			row_original_2);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[3][0]),
			row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base -= data.m_base;
#endif
		return *this;
	}

	matrix4x4f& operator*=(const matrix4x4f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMMATRIX m1 = *this;
		DirectX::XMMATRIX m2 = data;

		auto result = DirectX::XMMatrixMultiply(m1, m2);

		DirectX::XMStoreFloat4x4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= data.m_base;
#endif

		return *this;
	}

	matrix4x4f& operator*=(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[0][0]));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[1][0]));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[2][0]));
		DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[3][0]));

		row_original_0 = DirectX::XMVectorScale(row_original_0, value);
		row_original_1 = DirectX::XMVectorScale(row_original_1, value);
		row_original_2 = DirectX::XMVectorScale(row_original_2, value);
		row_original_3 = DirectX::XMVectorScale(row_original_3, value);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[0][0]),
			row_original_0);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[1][0]),
			row_original_1);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[2][0]),
			row_original_2);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[3][0]),
			row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base *= value;
#endif
		return *this;
	}

	matrix4x4f& operator/=(const matrix4x4f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[0][0]));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[1][0]));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[2][0]));
		DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[3][0]));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[0][0]));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[1][0]));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[2][0]));
		DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[3][0]));

		row_original_0 =
			DirectX::XMVectorDivide(row_original_0, row_argument_0);
		row_original_1 =
			DirectX::XMVectorDivide(row_original_1, row_argument_1);
		row_original_2 =
			DirectX::XMVectorDivide(row_original_2, row_argument_2);
		row_original_3 =
			DirectX::XMVectorDivide(row_original_3, row_argument_3);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[0][0]),
			row_original_0);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[1][0]),
			row_original_1);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[2][0]),
			row_original_2);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[3][0]),
			row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base /= data.m_base;
#endif
		return *this;
	}

	matrix4x4f& operator/=(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[0][0]));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[1][0]));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[2][0]));
		DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[3][0]));

		float factor = 1.f / value;

		row_original_0 = DirectX::XMVectorScale(row_original_0, factor);
		row_original_1 = DirectX::XMVectorScale(row_original_1, factor);
		row_original_2 = DirectX::XMVectorScale(row_original_2, factor);
		row_original_3 = DirectX::XMVectorScale(row_original_3, factor);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[0][0]),
			row_original_0);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[1][0]),
			row_original_1);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[2][0]),
			row_original_2);
		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base.m[3][0]),
			row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base /= value;
#endif

		return *this;
	}

	matrix4x4f operator+() const noexcept { return *this; }

	matrix4x4f operator-() const noexcept
	{
		matrix4x4f result;
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[0][0]));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[1][0]));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[2][0]));
		DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[3][0]));

		row_original_0 = DirectX::XMVectorNegate(row_original_0);
		row_original_1 = DirectX::XMVectorNegate(row_original_1);
		row_original_2 = DirectX::XMVectorNegate(row_original_2);
		row_original_3 = DirectX::XMVectorNegate(row_original_3);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&result.m_base.m[0][0]),
			row_original_0);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&result.m_base.m[1][0]),
			row_original_1);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&result.m_base.m[2][0]),
			row_original_2);

		DirectX::XMStoreFloat4(
			reinterpret_cast<DirectX::XMFLOAT4*>(&result.m_base.m[3][0]),
			row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		result = -this->m_base;
#endif
		return result;
	}

	bool operator==(const matrix4x4f& data) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[0][0]));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[1][0]));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[2][0]));
		DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[3][0]));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[0][0]));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[1][0]));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[2][0]));
		DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[3][0]));

		bool is_equal_0 =
			DirectX::XMVector4Equal(row_original_0, row_argument_0);
		bool is_equal_1 =
			DirectX::XMVector4Equal(row_original_1, row_argument_1);
		bool is_equal_2 =
			DirectX::XMVector4Equal(row_original_2, row_argument_2);
		bool is_equal_3 =
			DirectX::XMVector4Equal(row_original_3, row_argument_3);

		return (is_equal_0 && is_equal_1 && is_equal_2 && is_equal_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base == data.m_base;
#endif
	}

	bool operator!=(const matrix4x4f& data) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[0][0]));
		DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[1][0]));
		DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[2][0]));
		DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&this->m_base.m[3][0]));

		DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[0][0]));
		DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[1][0]));
		DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[2][0]));
		DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
			reinterpret_cast<const DirectX::XMFLOAT4*>(&data.m_base.m[3][0]));

		bool is_equal_0 =
			DirectX::XMVector4NotEqual(row_original_0, row_argument_0);
		bool is_equal_1 =
			DirectX::XMVector4NotEqual(row_original_1, row_argument_1);
		bool is_equal_2 =
			DirectX::XMVector4NotEqual(row_original_2, row_argument_2);
		bool is_equal_3 =
			DirectX::XMVector4NotEqual(row_original_3, row_argument_3);

		return (is_equal_0 || is_equal_1 || is_equal_2 || is_equal_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base != data.m_base;
#endif
	}

#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	operator DirectX::XMMATRIX(void) const noexcept
	{
		return DirectX::XMLoadFloat4x4(&this->m_base);
	}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

	float operator()(ktk::size_t row, ktk::size_t column) const
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.operator()(row, column);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[row][column];
#endif
	}

	float& operator()(ktk::size_t row, ktk::size_t column)
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.operator()(row, column);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[row][column];
#endif
	}

	float* operator[](kun_ktk size_t row)
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return &this->m_base.m[row][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return &this->m_base[row][0];
#else
		return nullptr;
#endif
	}

	const float* operator[](kun_ktk size_t row) const
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return &this->m_base.m[row][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return &this->m_base[row][0];
#else
		return nullptr;
#endif
	}

	matrix4x4f& Identity() noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		ktk::memory::memset(&this->m_base.m[0][0], 0, sizeof(this->m_base.m));
		this->m_base.m[0][0] = 1.0f;
		this->m_base.m[1][1] = 1.0f;
		this->m_base.m[2][2] = 1.0f;
		this->m_base.m[3][3] = 1.0f;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
		return *this;
	}

	float Get_00(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[0][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[0][0];
#endif
	}

	float Get_01(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base._12;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[0][1];
#endif
	}

	float Get_02(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base._13;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[0][2];
#endif
	}

	float Get_03(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base._14;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[0][3];
#endif
	}

	float Get_10(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[1][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[1][0];
#endif
	}

	float Get_11(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[1][1];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[1][1];
#endif
	}

	float Get_12(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base._23;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[1][2];
#endif
	}

	float Get_13(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base._24;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[1][3];
#endif
	}

	float Get_20(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[2][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[2][0];
#endif
	}

	float Get_21(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[2][1];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[2][1];
#endif
	}

	float Get_22(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[2][2];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[2][2];
#endif
	}

	float Get_23(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[2][3];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[2][3];
#endif
	}

	float Get_30(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[3][0];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[3][0];
#endif
	}

	float Get_31(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[3][1];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[3][1];
#endif
	}

	float Get_32(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[3][2];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[3][2];
#endif
	}

	float Get_33(void) const noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		return this->m_base.m[3][3];
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		return this->m_base[3][3];
#endif
	}

	matrix4x4f& Set_00(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[0][0] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[0][0] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_01(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[0][1] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[0][1] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_02(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[0][2] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[0][2] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_03(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[0][3] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[0][3] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_10(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[1][0] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[1][0] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_11(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[1][1] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[1][1] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_12(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[1][2] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[1][2] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_13(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[1][3] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[1][3] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_20(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[2][0] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[2][0] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_21(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[2][1] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[2][1] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_22(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[2][2] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[2][2] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_23(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[2][3] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[2][3] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_30(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[3][0] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[3][0] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_31(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[3][1] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[3][1] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_32(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[3][2] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[3][2] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_33(float value) noexcept
	{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
		this->m_base.m[3][3] = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
		this->m_base[3][3] = value;
#endif
		return *this;
	}

	matrix4x4f& Set_Base(const base_mat4x4_t& data) noexcept
	{
		this->m_base = data;
		return *this;
	}

	base_mat4x4_t& Get_Base(void) noexcept { return this->m_base; }
	const base_mat4x4_t& Get_Base(void) const noexcept { return this->m_base; }

private:
	base_mat4x4_t m_base;
};

inline matrix4x4f operator+(
	const matrix4x4f& left, const matrix4x4f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0 = {
		left.Get_00(), left.Get_01(), left.Get_02(), left.Get_03()};
	DirectX::XMFLOAT4 left_row_1 = {
		left.Get_10(), left.Get_11(), left.Get_12(), left.Get_13()};
	DirectX::XMFLOAT4 left_row_2 = {
		left.Get_20(), left.Get_21(), left.Get_22(), left.Get_23()};
	DirectX::XMFLOAT4 left_row_3 = {
		left.Get_30(), left.Get_31(), left.Get_32(), left.Get_33()};

	DirectX::XMFLOAT4 right_row_0 = {
		right.Get_00(), right.Get_01(), right.Get_02(), right.Get_03()};
	DirectX::XMFLOAT4 right_row_1 = {
		right.Get_10(), right.Get_11(), right.Get_12(), right.Get_13()};
	DirectX::XMFLOAT4 right_row_2 = {
		right.Get_20(), right.Get_21(), right.Get_22(), right.Get_23()};
	DirectX::XMFLOAT4 right_row_3 = {
		right.Get_30(), right.Get_31(), right.Get_32(), right.Get_33()};

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(&left_row_3);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(&right_row_0);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(&right_row_1);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(&right_row_2);
	DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(&right_row_3);

	row_original_0 = DirectX::XMVectorAdd(row_original_0, row_argument_0);
	row_original_1 = DirectX::XMVectorAdd(row_original_1, row_argument_1);
	row_original_2 = DirectX::XMVectorAdd(row_original_2, row_argument_2);
	row_original_3 = DirectX::XMVectorAdd(row_original_3, row_argument_3);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[0][0]),
		row_original_0);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[1][0]),
		row_original_1);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[2][0]),
		row_original_2);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[3][0]),
		row_original_3);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() + right.Get_Base());
#endif
}

inline matrix4x4f operator-(
	const matrix4x4f& left, const matrix4x4f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0 = {
		left.Get_00(), left.Get_01(), left.Get_02(), left.Get_03()};
	DirectX::XMFLOAT4 left_row_1 = {
		left.Get_10(), left.Get_11(), left.Get_12(), left.Get_13()};
	DirectX::XMFLOAT4 left_row_2 = {
		left.Get_20(), left.Get_21(), left.Get_22(), left.Get_23()};
	DirectX::XMFLOAT4 left_row_3 = {
		left.Get_30(), left.Get_31(), left.Get_32(), left.Get_33()};

	DirectX::XMFLOAT4 right_row_0 = {
		right.Get_00(), right.Get_01(), right.Get_02(), right.Get_03()};
	DirectX::XMFLOAT4 right_row_1 = {
		right.Get_10(), right.Get_11(), right.Get_12(), right.Get_13()};
	DirectX::XMFLOAT4 right_row_2 = {
		right.Get_20(), right.Get_21(), right.Get_22(), right.Get_23()};
	DirectX::XMFLOAT4 right_row_3 = {
		right.Get_30(), right.Get_31(), right.Get_32(), right.Get_33()};

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(&left_row_3);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(&right_row_0);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(&right_row_1);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(&right_row_2);
	DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(&right_row_3);

	row_original_0 = DirectX::XMVectorSubtract(row_original_0, row_argument_0);
	row_original_1 = DirectX::XMVectorSubtract(row_original_1, row_argument_1);
	row_original_2 = DirectX::XMVectorSubtract(row_original_2, row_argument_2);
	row_original_3 = DirectX::XMVectorSubtract(row_original_3, row_argument_3);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[0][0]),
		row_original_0);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[1][0]),
		row_original_1);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[2][0]),
		row_original_2);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[3][0]),
		row_original_3);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() - right.Get_Base());
#endif
}

inline matrix4x4f operator*(
	const matrix4x4f& left, const matrix4x4f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMMATRIX m1 = left;
	DirectX::XMMATRIX m2 = right;
	auto temp = DirectX::XMMatrixMultiply(m1, m2);

	matrix4x4f result;
	base_mat4x4_t data;
	DirectX::XMStoreFloat4x4(&data, temp);

	result.Set_Base(data);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * right.Get_Base());
#endif
}

inline matrix4x4f operator*(const matrix4x4f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0 = {
		left.Get_00(), left.Get_01(), left.Get_02(), left.Get_03()};
	DirectX::XMFLOAT4 left_row_1 = {
		left.Get_10(), left.Get_11(), left.Get_12(), left.Get_13()};
	DirectX::XMFLOAT4 left_row_2 = {
		left.Get_20(), left.Get_21(), left.Get_22(), left.Get_23()};
	DirectX::XMFLOAT4 left_row_3 = {
		left.Get_30(), left.Get_31(), left.Get_32(), left.Get_33()};

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(&left_row_3);

	row_original_0 = DirectX::XMVectorScale(row_original_0, value);
	row_original_1 = DirectX::XMVectorScale(row_original_1, value);
	row_original_2 = DirectX::XMVectorScale(row_original_2, value);
	row_original_3 = DirectX::XMVectorScale(row_original_3, value);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[0][0]),
		row_original_0);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[1][0]),
		row_original_1);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[2][0]),
		row_original_2);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[3][0]),
		row_original_3);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() * value);
#endif
}

inline matrix4x4f operator*(float value, const matrix4x4f& right) noexcept
{
	return operator*(right, value);
}

inline matrix4x4f operator/(const matrix4x4f& left, float value) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0 = {
		left.Get_00(), left.Get_01(), left.Get_02(), left.Get_03()};
	DirectX::XMFLOAT4 left_row_1 = {
		left.Get_10(), left.Get_11(), left.Get_12(), left.Get_13()};
	DirectX::XMFLOAT4 left_row_2 = {
		left.Get_20(), left.Get_21(), left.Get_22(), left.Get_23()};
	DirectX::XMFLOAT4 left_row_3 = {
		left.Get_30(), left.Get_31(), left.Get_32(), left.Get_33()};

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(&left_row_3);

	float factor = 1.f / value;

	row_original_0 = DirectX::XMVectorScale(row_original_0, factor);
	row_original_1 = DirectX::XMVectorScale(row_original_1, factor);
	row_original_2 = DirectX::XMVectorScale(row_original_2, factor);
	row_original_3 = DirectX::XMVectorScale(row_original_3, factor);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[0][0]),
		row_original_0);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[1][0]),
		row_original_1);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[2][0]),
		row_original_2);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[3][0]),
		row_original_3);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / value);
#endif
}

inline matrix4x4f operator/(
	const matrix4x4f& left, const matrix4x4f& right) noexcept
{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
	DirectX::XMFLOAT4 left_row_0 = {
		left.Get_00(), left.Get_01(), left.Get_02(), left.Get_03()};
	DirectX::XMFLOAT4 left_row_1 = {
		left.Get_10(), left.Get_11(), left.Get_12(), left.Get_13()};
	DirectX::XMFLOAT4 left_row_2 = {
		left.Get_20(), left.Get_21(), left.Get_22(), left.Get_23()};
	DirectX::XMFLOAT4 left_row_3 = {
		left.Get_30(), left.Get_31(), left.Get_32(), left.Get_33()};

	DirectX::XMFLOAT4 right_row_0 = {
		right.Get_00(), right.Get_01(), right.Get_02(), right.Get_03()};
	DirectX::XMFLOAT4 right_row_1 = {
		right.Get_10(), right.Get_11(), right.Get_12(), right.Get_13()};
	DirectX::XMFLOAT4 right_row_2 = {
		right.Get_20(), right.Get_21(), right.Get_22(), right.Get_23()};
	DirectX::XMFLOAT4 right_row_3 = {
		right.Get_30(), right.Get_31(), right.Get_32(), right.Get_33()};

	DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(&left_row_0);
	DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(&left_row_1);
	DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(&left_row_2);
	DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(&left_row_3);

	DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(&right_row_0);
	DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(&right_row_1);
	DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(&right_row_2);
	DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(&right_row_3);

	row_original_0 = DirectX::XMVectorDivide(row_original_0, row_argument_0);
	row_original_1 = DirectX::XMVectorDivide(row_original_1, row_argument_1);
	row_original_2 = DirectX::XMVectorDivide(row_original_2, row_argument_2);
	row_original_3 = DirectX::XMVectorDivide(row_original_3, row_argument_3);

	matrix4x4f result;

	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[0][0]),
		row_original_0);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[1][0]),
		row_original_1);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[2][0]),
		row_original_2);
	DirectX::XMStoreFloat4(
		reinterpret_cast<DirectX::XMFLOAT4*>(&result.Get_Base().m[3][0]),
		row_original_3);

	return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
	return (left.Get_Base() / right.Get_Base());
#endif
}

KOTEK_END_NAMESPACE_MATH
KOTEK_END_NAMESPACE_KTK
KOTEK_END_NAMESPACE_KOTEK
