#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class matrix4x4f
			{
			public:
#pragma region Constructors
				matrix4x4f(base_decimal_t m00, base_decimal_t m01,
					base_decimal_t m02, base_decimal_t m03, base_decimal_t m10,
					base_decimal_t m11, base_decimal_t m12, base_decimal_t m13,
					base_decimal_t m20, base_decimal_t m21, base_decimal_t m22,
					base_decimal_t m23, base_decimal_t m30, base_decimal_t m31,
					base_decimal_t m32, base_decimal_t m33) :
					m_base(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21,
						m22, m23, m30, m31, m32, m33)
				{
				}
				matrix4x4f(const base_mat4x4_t& data) : m_base(data) {}
				matrix4x4f(const matrix4x4f& data) : m_base(data.m_base) {}
				matrix4x4f(void) : m_base{} {}
#pragma endregion

				~matrix4x4f(void) = default;

#pragma region Assignment operators
				matrix4x4f& operator=(const matrix4x4f& data)
				{
					this->m_base = data.m_base;
					return *this;
				}

				matrix4x4f& operator=(const base_mat4x4_t& data)
				{
					this->m_base = data;
					return *this;
				}

				matrix4x4f& operator+=(const matrix4x4f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._31));
					DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._41));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._31));
					DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._41));

					row_original_0 =
						DirectX::XMVectorAdd(row_original_0, row_argument_0);
					row_original_1 =
						DirectX::XMVectorAdd(row_original_1, row_argument_1);
					row_original_2 =
						DirectX::XMVectorAdd(row_original_2, row_argument_2);
					row_original_3 =
						DirectX::XMVectorAdd(row_original_3, row_argument_3);

					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._31),
						row_original_2);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._41),
						row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& operator+=(const base_mat4x4_t& data) noexcept
				{
					return this->operator+=(data);
				}

				matrix4x4f& operator-=(const matrix4x4f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._31));
					DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._41));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._31));
					DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._41));

					row_original_0 = DirectX::XMVectorSubtract(
						row_original_0, row_argument_0);
					row_original_1 = DirectX::XMVectorSubtract(
						row_original_1, row_argument_1);
					row_original_2 = DirectX::XMVectorSubtract(
						row_original_2, row_argument_2);
					row_original_3 = DirectX::XMVectorSubtract(
						row_original_3, row_argument_3);

					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._31),
						row_original_2);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._41),
						row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& operator-=(const base_mat4x4_t& data) noexcept
				{
					return this->operator-=(data);
				}

				matrix4x4f& operator*=(const matrix4x4f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMMATRIX m1 = *this;
					DirectX::XMMATRIX m2 = data;

					auto result = DirectX::XMMatrixMultiply(m1, m2);

					DirectX::XMStoreFloat4x4(&this->m_base, result);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

					return *this;
				}

				matrix4x4f& operator*=(const base_mat4x4_t& data) noexcept
				{
					return this->operator*=(data);
				}

				matrix4x4f& operator*=(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._31));
					DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._41));

					row_original_0 =
						DirectX::XMVectorScale(row_original_0, value);
					row_original_1 =
						DirectX::XMVectorScale(row_original_1, value);
					row_original_2 =
						DirectX::XMVectorScale(row_original_2, value);
					row_original_3 =
						DirectX::XMVectorScale(row_original_2, value);

					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._31),
						row_original_2);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._41),
						row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

					return *this;
				}

				matrix4x4f& operator/=(const matrix4x4f& data) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._31));
					DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._41));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._31));
					DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._41));

					row_original_0 =
						DirectX::XMVectorDivide(row_original_0, row_argument_0);
					row_original_1 =
						DirectX::XMVectorDivide(row_original_1, row_argument_1);
					row_original_2 =
						DirectX::XMVectorDivide(row_original_2, row_argument_2);
					row_original_3 =
						DirectX::XMVectorDivide(row_original_3, row_argument_3);

					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._31),
						row_original_2);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._41),
						row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& operator/=(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._31));
					DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._41));

					base_decimal_t factor = 1.f / value;

					row_original_0 =
						DirectX::XMVectorScale(row_original_0, factor);
					row_original_1 =
						DirectX::XMVectorScale(row_original_1, factor);
					row_original_2 =
						DirectX::XMVectorScale(row_original_2, factor);
					row_original_3 =
						DirectX::XMVectorScale(row_original_3, factor);

					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._11),
						row_original_0);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._21),
						row_original_1);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._31),
						row_original_2);
					DirectX::XMStoreFloat4(
						reinterpret_cast<DirectX::XMFLOAT4*>(&this->m_base._41),
						row_original_3);
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif

					return *this;
				}
#pragma endregion

#pragma region Unary operators
				matrix4x4f operator+() const noexcept { return *this; }

				matrix4x4f operator-() const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._31));
					DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._41));

					row_original_0 = DirectX::XMVectorNegate(row_original_0);
					row_original_1 = DirectX::XMVectorNegate(row_original_1);
					row_original_2 = DirectX::XMVectorNegate(row_original_2);
					row_original_3 = DirectX::XMVectorNegate(row_original_3);

					matrix4x4f result;

					DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(
											   &result.m_base._11),
						row_original_0);

					DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(
											   &result.m_base._21),
						row_original_1);

					DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(
											   &result.m_base._31),
						row_original_2);

					DirectX::XMStoreFloat4(reinterpret_cast<DirectX::XMFLOAT4*>(
											   &result.m_base._41),
						row_original_3);

					return result;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}
#pragma endregion

#pragma region Comparison operators
				bool operator==(const matrix4x4f& data) const noexcept
				{
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._31));
					DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._41));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._31));
					DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._41));

					bool is_equal_0 =
						DirectX::XMVector3Equal(row_original_0, row_argument_0);
					bool is_equal_1 =
						DirectX::XMVector3Equal(row_original_1, row_argument_1);
					bool is_equal_2 =
						DirectX::XMVector3Equal(row_original_2, row_argument_2);
					bool is_equal_3 =
						DirectX::XMVector3Equal(row_original_3, row_argument_3);

					return (is_equal_0 && is_equal_1 && is_equal_2 && is_equal_3);
				}

				bool operator!=(const matrix4x4f& data) noexcept
				{
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._31));
					DirectX::XMVECTOR row_original_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&this->m_base._41));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._31));
					DirectX::XMVECTOR row_argument_3 = DirectX::XMLoadFloat4(
						reinterpret_cast<const DirectX::XMFLOAT4*>(
							&data.m_base._41));

					bool is_equal_0 = DirectX::XMVector3NotEqual(
						row_original_0, row_argument_0);
					bool is_equal_1 = DirectX::XMVector3NotEqual(
						row_original_1, row_argument_1);
					bool is_equal_2 = DirectX::XMVector3NotEqual(
						row_original_2, row_argument_2);
					bool is_equal_3 = DirectX::XMVector3NotEqual(
						row_original_3, row_argument_3);

					return (is_equal_0 || is_equal_1 || is_equal_2 || is_equal_3);
				}
#pragma endregion

#pragma region Cast operators
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
				operator DirectX::XMMATRIX(void) const noexcept
				{
					return DirectX::XMLoadFloat4x4(&this->m_base);
				}
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
#pragma endregion

				base_decimal_t Get_00(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._11;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_01(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._12;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_02(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._13;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_10(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._21;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_11(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._22;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_12(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._23;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_20(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._31;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_21(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._32;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				base_decimal_t Get_22(void) const noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					return this->m_base._33;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
				}

				matrix4x4f& Set_00(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._11 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				matrix4x4f& Set_01(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._12 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_02(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._13 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_03(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._14 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_10(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._21 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_11(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._22 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_12(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._23 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_13(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._24 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_20(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._31 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_21(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._32 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_22(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._33 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_23(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._34 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_30(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._41 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)
#endif
					return *this;
				}

				matrix4x4f& Set_31(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._42 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_32(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._43 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_33(base_decimal_t value) noexcept
				{
#ifdef KOTEK_USE_MATH_LIBRARY_DXM
					this->m_base._44 = value;
#elif defined(KOTEK_USE_MATH_LIBRARY_GLM)

#endif
					return *this;
				}

				matrix4x4f& Set_Base(const base_mat4x4_t& data) noexcept
				{
					this->m_base = data;
					return *this;
				}

				base_mat4x4_t& Get_Base(void) noexcept { return this->m_base; }
				const base_mat4x4_t& Get_Base(void) const noexcept
				{
					return this->m_base;
				}

			private:
				base_mat4x4_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek