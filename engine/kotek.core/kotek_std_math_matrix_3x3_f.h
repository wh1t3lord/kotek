#pragma once

#include "kotek_std_alias_math.h"

namespace Kotek
{
	namespace ktk
	{
		namespace math
		{
			class matrix3x3f
			{
			public:
#pragma region Constructors
				matrix3x3f(base_decimal_t m00, base_decimal_t m01,
					base_decimal_t m02, base_decimal_t m10, base_decimal_t m11,
					base_decimal_t m12, base_decimal_t m20, base_decimal_t m21,
					base_decimal_t m22) :
					m_base(m00, m01, m02, m10, m11, m12, m20, m21, m22)
				{
				}
				matrix3x3f(const base_mat3x3_t& data) : m_base(data) {}
				matrix3x3f(const matrix3x3f& data) : m_base(data.m_base) {}
				matrix3x3f(void) : m_base{} {}
#pragma endregion

				~matrix3x3f(void) = default;

#pragma region Assignment operators
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
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					row_original_0 =
						DirectX::XMVectorAdd(row_original_0, row_argument_0);
					row_original_1 =
						DirectX::XMVectorAdd(row_original_1, row_argument_1);
					row_original_2 =
						DirectX::XMVectorAdd(row_original_2, row_argument_2);

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
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					row_original_0 = DirectX::XMVectorSubtract(
						row_original_0, row_argument_0);
					row_original_1 = DirectX::XMVectorSubtract(
						row_original_1, row_argument_1);
					row_original_2 = DirectX::XMVectorSubtract(
						row_original_2, row_argument_2);

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

#endif
					return *this;
				}

				matrix3x3f& operator-=(const base_mat3x3_t& data) noexcept
				{
					return this->operator-=(data);
				}
#pragma endregion

#pragma region Unary operators

#pragma endregion

#pragma region Comparison operators
				bool operator==(const matrix3x3f& data) const noexcept
				{
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					bool is_equal_0 =
						DirectX::XMVector3Equal(row_original_0, row_argument_0);
					bool is_equal_1 =
						DirectX::XMVector3Equal(row_original_1, row_argument_1);
					bool is_equal_2 =
						DirectX::XMVector3Equal(row_original_2, row_argument_2);

					return (is_equal_0 && is_equal_1 && is_equal_2);
				}

				bool operator!=(const matrix3x3f& data) noexcept
				{
					DirectX::XMVECTOR row_original_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._11));
					DirectX::XMVECTOR row_original_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._21));
					DirectX::XMVECTOR row_original_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&this->m_base._31));

					DirectX::XMVECTOR row_argument_0 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._11));
					DirectX::XMVECTOR row_argument_1 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._21));
					DirectX::XMVECTOR row_argument_2 = DirectX::XMLoadFloat3(
						reinterpret_cast<const DirectX::XMFLOAT3*>(
							&data.m_base._31));

					bool is_equal_0 = DirectX::XMVector3NotEqual(
						row_original_0, row_argument_0);
					bool is_equal_1 = DirectX::XMVector3NotEqual(
						row_original_1, row_argument_1);
					bool is_equal_2 = DirectX::XMVector3NotEqual(
						row_original_2, row_argument_2);

					return (is_equal_0 || is_equal_1 || is_equal_2);
				}
#pragma endregion

#pragma region

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

			private:
				base_mat3x3_t m_base;
			};
		} // namespace math
	}     // namespace ktk
} // namespace Kotek